#include"CXEnemy.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>
#include"CXPlayer.h"
#include "CRes.h"


//�R���C�_������
CXEnemy::CXEnemy()
	:mEnemy_Hp(Hp)
	, mEnemy_Speed(ENEMY_SPEED)
	, mEnemy_Turnspeed(ENEMY_TURNSPEED)
	, mEnemy_PlayerDis(ENEMY_FLOAT_INITIALIZATION)
	, mEnemy_FollowGaugeWid(ENEMY_FLOAT_INITIALIZATION)
	, mEnemy_val(ENEMY_INT_INITIALIZATION)
	, mEnemy_IsHit(false)
	, mEnemy_Flag(false)
	, mEnemy_ColCapsuleBody(this, nullptr, CVector(ENEMY_COLCAPSULE_BODY_X, ENEMY_COLCAPSULE_BODY_TOP_Y, ENEMY_COLCAPSULE_BODY_Z), CVector(ENEMY_COLCAPSULE_BODY_X, ENEMY_COLCAPSULE_BODY_BOTTOM_Y, ENEMY_COLCAPSULE_BODY_Z), ENEMY_COLCAPSULE_BODY_SIZE)
	, mEnemy_ColSphereBody(this, nullptr, CVector(ENEMY_COLSPHERE_BODY_X, ENEMY_COLSPHERE_BODY_Y, ENEMY_COLSPHERE_BODY_Z), ENEMY_COLSPHERE_BODY_SIZE)
	, mEnemy_ColSphereRightarm(this, nullptr, CVector(), ENEMY_COLSPHERE_RIGHTARM_SIZE)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(), ENEMY_COLSPHERE_LEFTARM_SIZE)
{
	//������Ԃ�ݒ�
	mEnemy_State = EIDLE;	//�ҋ@���
		//�R���C�_�̃^�O��ݒ�
	mEnemy_ColCapsuleBody.Tag(CCollider::EBODY);		//��
	mEnemy_ColSphereBody.Tag(CCollider::EBODY);		//��
	mEnemy_ColSphereRightarm.Tag(CCollider::ERIGHTARM);	//�E��
	mEnemy_ColSphereLeftarm.Tag(CCollider::ELEFTARM);	//����
	//�^�O�̐ݒ�
	mTag = EENEMY;
	//�D��x��1�ɕύX����
	mPriority = Enemy_Priority;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mEnemy_ColCapsuleBody.Matrix(&mpCombinedMatrix[2]);
	mEnemy_ColSphereBody.Matrix(&mpCombinedMatrix[2]);
	mEnemy_ColSphereRightarm.Matrix(&mpCombinedMatrix[68]);
	mEnemy_ColSphereLeftarm.Matrix(&mpCombinedMatrix[41]);
	mPosition.Set(Position_X, Position_Y, Position_Z);
	mScale.Set(Scale_X, Scale_Y, Scale_Z);
	mRotation.Set(Rotation_X, Rotation_Y, Rotation_Z);
}

void CXEnemy::Update() {
	//��Ԃ𔻕�
	switch (mEnemy_State) 
	{
	case EIDLE:	//�ҋ@���
		Idle();	//�ҋ@�������Ă�
		break;

	case EATTACK_1:	//�U��1��Ԃ̎�
		Attack_1();	//�U��1�̏������Ă�
		break;

	case EATTACK_2:	//�U��2��Ԃ̎�
		Attack_2();	//�U��2�̏������Ă�
		break;

	case EATTACK_3:	//�U��3��Ԃ̎�
		Attack_3();	//�U��3�̏������Ă�
		break;

	case EAUTOMOVE:	//�ړ����
		Move();	//�ړ���Ԃ̏������Ă�
		break;

	case EDASH: //������
		Dash(); //����������Ă�
		break;

	case EDEATH: //���S���
		Death(); //���S�������Ă�
		break;

	case EKNOCKBACK: //�m�b�N�o�b�N���
		KnockBack(); //�m�b�N�o�b�N�������Ă�
		break;
	}
	MovingCalculation();
	if (mEnemy_PlayerDis >= Enemy_Attack_Dis) {
		mEnemy_AttackDir = mEnemy_Player_Point; //�U�����̌��������߂�
	}
	//�̗͂�0�ɂȂ�Ǝ��S
	if (mEnemy_Hp <= Death_Hp)
	{
		mEnemy_State = EDEATH;	//���S��Ԃֈڍs
		mEnemy_Hp = Death_Hp;
	}
	CXCharacter::Update();
}
void CXEnemy::Render2D()
{
	//2D�`��J�n
	CUtil::Start2D(WINDOW_FIRST_WIDTH, WINDOW_WIDTH, WINDOW_FIRST_HEIGHT, WINDOW_HEIGHT);
	CVector tpos;
	CVector ret;
	tpos = mPosition + CVector(ret.X(), ret.Y()+ 7.0f, 0.0f);
	Camera.WorldToScreen(&ret, tpos);
	float HpRate = (float)mEnemy_Hp / (float)Hp_Max; //�̗͍ő�l�ɑ΂���A���݂̗̑͂̊���
	float HpGaugeWid = ENEMY_GAUGE_WID_MAX * HpRate; //�̗̓Q�[�W�̕�
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕����傫����
	if (mEnemy_FollowGaugeWid > HpGaugeWid) {
		//���`��ԂŔ�_���[�W����ǂ�����Q�[�W�̕���ݒ肷��
		mEnemy_FollowGaugeWid = Camera.mHpLerp(mEnemy_FollowGaugeWid, HpGaugeWid, ENEMY_GAUGE_HP_RATE);
	}
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕���菬�����Ƃ�
	else if (mEnemy_FollowGaugeWid < HpGaugeWid) {
		//��_���[�W����ǂ�����Q�[�W�̕��ɑ̗̓Q�[�W�̕���ݒ肷��
		mEnemy_FollowGaugeWid = HpGaugeWid;
	}
	//��ʊO�̎��ɕ\�����Ȃ�
	if (ret.X() > WINDOW_FIRST_WIDTH && ret.X() < WINDOW_WIDTH) {
		if (!mEnemy_Hp <= Death_Hp)
		{
			CRes::GetInstance()->GetInEnemyUiHpBackBar().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, ret.X() + ENEMY_GAUGE_WID_MAX, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 0, 30);
			//��_���[�W����ǂ�����Q�[�W��\��
			CRes::GetInstance()->GetInUiHpRedGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + mEnemy_FollowGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
			//�̗̓Q�[�W
			CRes::GetInstance()->GetInUiHpGreenGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + HpGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
		}
	}
	//2D�̕`��I��
	CUtil::End2D();
}

void CXEnemy::Idle()
{
	int random = ENEMY_INT_INITIALIZATION;
	//�v���C���[�����S��Ԃł͖����Ƃ�
	if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH) 
	{
		mEnemy_Flag = false;
		//�v���C���[����苗���܂ŋ߂Â��ƒǐՏ�Ԃֈڍs
		if (mEnemy_PlayerDis <= Enemy_Walk_Dis)
		{
			mEnemy_State = EAUTOMOVE;
		}
		else if (mEnemy_PlayerDis <= Enemy_Dash_Dis)
		{
			mEnemy_State = EDASH;
		}
		else
		{
			//�A�j���[�V�����̐ݒ�
			ChangeAnimation(ENEMY_ANIMATION_No_IDLE, true, ENEMY_IDLE_ANIMATION_FRAME);
		}
	}
	else 
	{
		//�A�j���[�V�����̐ݒ�
		ChangeAnimation(ENEMY_ANIMATION_No_IDLE, true, ENEMY_IDLE_ANIMATION_FRAME);
	}
}
void CXEnemy::Move(){
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(ENEMY_ANIMATION_No_WALK, true, ENEMY_MOVE_ANIMATION_FRAME);
	mEnemy_Speed = Enemy_Speed_WalkPattern;
	//�ړI�n�_�܂ł̃x�N�g�������߂�
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDir�Ƀv���C���[�����̃x�N�g��������
	mEnemy_MoveDir.Y(ENEMY_FLOAT_INITIALIZATION);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % Enemy_Attack_Walk_Rand; //rand()�͐����̗�����Ԃ�
						 //%10��10�Ŋ������]������߂�
	//�U���o���鋗���ɂ��Ȃ���ΖڕW�n�_�Ɉړ�
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = ENEMY_INT_INITIALIZATION;
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
	{
		if (random == ENEMY_INT_INITIALIZATION)
		{
			//�����_���ōU���̎�ނ����߂�
			random = rand() % 3;
			switch (random) 
			{
			case 0:
				mEnemy_State = EATTACK_1; //�U��1��Ԃֈڍs
			break;
			case 1:
				mEnemy_State = EATTACK_2; //�U��2��Ԃֈڍs
			break;
			case 2:
				mEnemy_State = EATTACK_3; //�U��3��Ԃֈڍs
			break;
			}
		}
	}
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mEnemy_PlayerDis >= Enemy_Walk_Dis_Max)
	{
		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
	}

}

void CXEnemy::Dash()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(ENEMY_ANIMATION_No_DASH, true, ENEMY_DASH_ANIMATION_FRAME);
	//�ړ��X�s�[�h��ύX
	mEnemy_Speed = Enemy_Speed_DashPattern;
	//�ړI�n�_�܂ł̃x�N�g�������߂�
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDir�ɖڕW�n�_�����̃x�N�g��������
	mEnemy_MoveDir.Y(ENEMY_FLOAT_INITIALIZATION);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % Enemy_Attack_Dash_Rand; //rand()�͐����̗�����Ԃ�
						  //%25��25�Ŋ������]������߂�
	//�U���o���鋗���ɂ��Ȃ���ΖڕW�n�_�Ɉړ�
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = ENEMY_INT_INITIALIZATION;
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
	{
		if (random == ENEMY_INT_INITIALIZATION)
		{
			//�����_���ōU���̎�ނ����߂�
			random = rand() % 3;
			switch (random) 
			{
			case 0:
				mEnemy_State = EATTACK_1; //�U��1��Ԃֈڍs
			break;
			case 1:
				mEnemy_State = EATTACK_2; //�U��2��Ԃֈڍs
			break;
			case 2:
				mEnemy_State = EATTACK_3; //�U��3��Ԃֈڍs
			break;
			}
		}
	}
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mEnemy_PlayerDis >= Enemy_Dash_Dis_Max)
	{
		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
	}

	CTransform::Update();

}

void CXEnemy::Attack_1()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(ENEMY_ANIMATION_No_ATTACK_1, false, ENEMY_ATTACK1_ANIMATION_FRAME);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false)
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else {
			mEnemy_IsHit = true;
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //�q�b�g����I��
		mEnemy_State = EIDLE; //�ҋ@��ԂɈڍs

		//1�x�����������Ȃ����߂̃J�E���^
		if (mEnemy_Flag == false)
		{
			mEnemy_Flag = true;
			//�X�[�p�[�A�[�}���������̃_���[�W�Q��
			if (mEnemy_val >= 61 && mEnemy_val <= 100)
			{
				if (CXPlayer::GetInstance()->GetIsHit() == true) {
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp1;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp2;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp3;
						new CEffectEnemyDamageSp3(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP3, 4, 5, 2); //�G�t�F�N�g�𐶐�����
					}
				}
			}
		}
	}
}

void CXEnemy::Attack_2()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(ENEMY_ANIMATION_No_ATTACK_2, false, ENEMY_ATTACK2_ANIMATION_FRAME);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else {
			mEnemy_IsHit = true;
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //�q�b�g����I��
		mEnemy_State = EIDLE; //�ҋ@��ԂɈڍs

		//1�x�����������Ȃ����߂̃J�E���^
		if (mEnemy_Flag == false)
		{
			mEnemy_Flag = true;
			//�X�[�p�[�A�[�}���������̃_���[�W�Q��
			if (mEnemy_val >= 61 && mEnemy_val <= 100)
			{
				if (CXPlayer::GetInstance()->GetIsHit() == true) {
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp1;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp2;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp3;
						new CEffectEnemyDamageSp3(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP3, 4, 5, 2); //�G�t�F�N�g�𐶐�����
					}
				}
			}
		}
	}
}

void CXEnemy::Attack_3()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(ENEMY_ANIMATION_No_ATTACK_3, false, ENEMY_ATTACK3_ANIMATION_FRAME);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else {
			mEnemy_IsHit = true;
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //�q�b�g����I��
		mEnemy_State = EIDLE; //�ҋ@��ԂɈڍs
		//1�x�����������Ȃ����߂̃J�E���^
		if (mEnemy_Flag == false)
		{
			mEnemy_Flag = true;
			//�X�[�p�[�A�[�}���������̃_���[�W�Q��
			if (mEnemy_val >= ENEMY_PROBABILITY_LOW_SET2 && mEnemy_val <= ENEMY_PROBABILITY_MAX_SET2)
			{
				if (CXPlayer::GetInstance()->GetIsHit() == true) {
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp1;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp2;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp3;
						new CEffectEnemyDamageSp3(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP3, 4, 5, 2); //�G�t�F�N�g�𐶐�����
					}
				}
			}
		}
	}
}


void CXEnemy::KnockBack()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(ENEMY_ANIMATION_No_KNOCKBACK, false, ENEMY_KNOCKBACK_ANIMATION_FRAME);
	//�_���[�W����
	//1�x�����������Ȃ����߂̃J�E���^
	if (mEnemy_Flag == false)
	{
		if (mEnemy_val >= ENEMY_PROBABILITY_LOW_SET1 && mEnemy_val <= ENEMY_PROBABILITY_MAX_SET1) {
			if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
			{
				new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //�G�t�F�N�g�𐶐�����
			}
			if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
			{
				new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //�G�t�F�N�g�𐶐�����
			}
			if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
			{
				new CEffectEnemyDamageSp3(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP3, 4, 5, 2); //�G�t�F�N�g�𐶐�����
			}
		}
		mEnemy_Flag = true;
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
		{
			mEnemy_Hp -= Enemy_Damage_PlayerSp3 * 2;
		}
		else
		{
			mEnemy_Hp -= Enemy_Damage_PlayerSp3;	//�_���[�W���󂯂�(��)

		}
	}
	//�A�j���[�V�������Đ�����
	if (IsAnimationFinished() == false)
	{
		mEnemy_IsHit = false;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
	}
}

void CXEnemy::Death()
{
	ChangeAnimation(ENEMY_ANIMATION_No_DEATH, false, ENEMY_KNOCKBACK_ANIMATION_FRAME);
	mEnemy_IsHit = false;
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//����̐e�������̎��̓��^�[��
	if (o->Parent() == this)return;

	if (!mEnemy_Hp <= Death_Hp)
	{
		if (m->Type() == CCollider::ECAPSUL && o->Type() == CCollider::ECAPSUL)
		{
			CVector adjust;//�����p�x�N�g��
			//�R���C�_��m��o���Փ˂��Ă��邩�̔���
			if (CCollider::CollisionCapsule(m, o, &adjust))
			{
			if (m->Tag() == CCollider::EBODY && o->Tag() == CCollider::EBODY)
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();
			}
			}
		}
	}

	if (m->Type() == CCollider::ECAPSUL && o->Type() == CCollider::ETRIANGLE) {
		CVector adjust;//�����p�x�N�g��
		if (CCollider::CollisionTriangleLine(o, m, &adjust))
		{
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition + adjust;
			//�s��̍X�V
			CTransform::Update();
		}

	}



	if (!mEnemy_Hp <= Death_Hp)
	{
		//���g�̃R���C�_�^�C�v�̔���
		if (m->Type() == CCollider::ESPHERE) {
			//����̃R���C�_�����R���C�_�̎�
			if (o->Type() == CCollider::ESPHERE) {
				//���̏Փ˔���
				if (CCollider::Collision(m, o)) {
					//����̐e�̃^�O���v���C���[
					if (o->Parent()->Tag() == EPLAYER)
					{
						//����̃R���C�_�̃^�O���E��
						if (o->Tag() == CCollider::ESWORD)
						{
							if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH)
							{
								//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
								srand((unsigned)time(NULL));
								mEnemy_val = (rand() % ENEMY_PROBABILITY_MAX_SET2) + 1;
								if (mEnemy_val >= ENEMY_PROBABILITY_LOW_SET1 && mEnemy_val <= ENEMY_PROBABILITY_MAX_SET1) {
									if (CXPlayer::GetInstance()->GetIsHit() == true) {
											mEnemy_State = EKNOCKBACK;
									}
								}
							}
						}
					}
				}
			}
		}	
	}
}

void CXEnemy::MovingCalculation() {
	//�v���C���[�����̃x�N�g�������߂�
	mEnemy_PlayerPos = CXPlayer::GetInstance()->Position() - mPosition;
	//�v���C���[�܂ł̋��������߂�
	mEnemy_PlayerDis = mEnemy_PlayerPos.Length();
	//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
	//�[���x�N�g���v�Z
	CVector ChackVec; //�`�F�b�N�p�x�N�g��
	ChackVec = mEnemy_MoveDirKeep.Normalize(); //�ۑ����ꂽ�ړ����̕����x�N�g������
	ChackVec = mEnemy_MoveDir.Normalize(); //�ړ����̕����x�N�g������
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / ENEMY_TURN_SET));

	//��]���x�@degree�ɒ���
	mEnemy_Turnspeed = (ENEMY_TURN_SET / M_PI) * ENEMY_TURN_SPEEDS_SET;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > ENEMY_TRUN_CHECK_SPEEDS_SET) tCheck.turn = ENEMY_TRUN_CHECK_SPEEDS_SET;

	//�ړ������փL��������������
	if (tCheck.cross > ENEMY_TRUN_CHECK_SET)
	{
		mRotation.Y(mRotation.Y() + tCheck.turn * mEnemy_Turnspeed);
	}
	if (tCheck.cross < ENEMY_TRUN_CHECK_SET)
	{
		mRotation.Y(mRotation.Y() - tCheck.turn * mEnemy_Turnspeed);
	}
	//�ړ�����
	mPosition += mEnemy_MoveDir * mEnemy_Speed;
	mPosition.Y(mPosition.Y() * ENEMY_GRAVITY);

	//�ړ��������Z�b�g
	mEnemy_MoveDir = CVector(0.0f, 0.0f, 0.0f);
	//�ړ��X�s�[�h���Z�b�g
	mEnemy_Speed = ENEMY_SPEED;
}
void CXEnemy::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mEnemy_ColCapsuleBody.ChangePriority();
	mEnemy_ColSphereBody.ChangePriority();
	mEnemy_ColSphereRightarm.ChangePriority();
	mEnemy_ColSphereLeftarm.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mEnemy_ColCapsuleBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereRightarm, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereLeftarm, COLLISIONRANGE);
}
bool CXEnemy::GetHp()
{
	return mEnemy_Hp;
}
//�A�j���[�V�����t���[���̎擾
bool CXEnemy::GetIsAnimationFrame() {
	return mAnimationFrame;
}
//�U���̓����蔻����擾����
bool CXEnemy::GetIsHit()
{
	return mEnemy_IsHit; //�U���̓����蔻���Ԃ�
}
//�U���̓����蔻��t���O��ݒ�
void CXEnemy::SetIsHit(bool hitflag)
{
	mEnemy_IsHit = hitflag;
}

//�v���C���[�̏�Ԃ��擾����
CXEnemy::EEnemyState CXEnemy::GetState()
{
	return mEnemy_State;
}
	

