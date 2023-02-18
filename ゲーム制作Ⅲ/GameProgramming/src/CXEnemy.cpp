#include"CXEnemy.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>
#include"CXPlayer.h"
#include "CRes.h"





CXEnemy* CXEnemy::mpEnemy_Instance = nullptr;

//�R���C�_������
CXEnemy::CXEnemy()
	:mEnemy_Hp(ENEMY_HP)
	,mEnemy_Speed(ENEMY_SPEED)
	,mEnemy_Turnspeed(ENEMY_TURNSPEED)
	,mEnemy_PlayerDis(0.0f)
	, mEnemy_FollowGaugeWid(0.0f)
	,mEnemy_val(0)
	,mEnemy_IsHit(false)
	,mEnemy_Flag(false)
	, mEnemy_ColCapsuleBody(this, nullptr, CVector(0.0f, 190.0f, 0.0f), CVector(0.0f, -30.0f, 0.0f), 1.2)
	, mEnemy_ColSphereBody(this, nullptr, CVector(0.0, 94.0f, 5.0f), 1.3f)
	,mEnemy_ColSphereRightarm(this, nullptr, CVector(), 0.7)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(), 0.7)

{
	mpEnemy_Instance = this;
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
	mPriority = 80;
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
	mPosition.Set(0.0f, 1.5f, -20.0);	//�ʒu��ݒ�
	mScale.Set(3.0f, 2.63f, 2.0f);		//�X�P�[���ݒ�
	mRotation.Set(0.0f, 0.0f, 0.0f);	//��]��ݒ�
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
	if (mEnemy_PlayerDis >= ENEMY_ATTACK_DIS) {
		mEnemy_AttackDir = mEnemy_Player_Point; //�U�����̌��������߂�
	}
	//�̗͂�0�ɂȂ�Ǝ��S
	if (mEnemy_Hp <= 0)
	{
		mEnemy_State = EDEATH;	//���S��Ԃֈڍs
		mEnemy_Hp = 0;
	}
	CXCharacter::Update();
}
void CXEnemy::Render2D()
{
	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);
	CVector tpos;
	CVector ret;
	tpos = mPosition + CVector(ret.X(), ret.Y()+ 7.0f, 0.0f);
	Camera.WorldToScreen(&ret, tpos);
	float HpRate = (float)mEnemy_Hp / (float)ENEMY_HP_MAX; //�̗͍ő�l�ɑ΂���A���݂̗̑͂̊���
	float HpGaugeWid = ENEMY_GAUGE_WID_MAX * HpRate; //�̗̓Q�[�W�̕�
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕����傫����
	if (mEnemy_FollowGaugeWid > HpGaugeWid) {
		//���`��ԂŔ�_���[�W����ǂ�����Q�[�W�̕���ݒ肷��
		mEnemy_FollowGaugeWid = Camera.mHpLerp(mEnemy_FollowGaugeWid, HpGaugeWid, 0.05f);
	}
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕���菬�����Ƃ�
	else if (mEnemy_FollowGaugeWid < HpGaugeWid) {
		//��_���[�W����ǂ�����Q�[�W�̕��ɑ̗̓Q�[�W�̕���ݒ肷��
		mEnemy_FollowGaugeWid = HpGaugeWid;
	}
	//��ʊO�̎��ɕ\�����Ȃ�
	if (ret.X() > 0 && ret.X() < 800) {
		if (!mEnemy_Hp <= 0)
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
	int random = 0;
	//�v���C���[�����S��Ԃł͖����Ƃ�
	if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH) 
	{
		mEnemy_Flag = false;
		//�v���C���[����苗���܂ŋ߂Â��ƒǐՏ�Ԃֈڍs
		if (mEnemy_PlayerDis <= ENEMY_WALK_DIS)
		{
			mEnemy_State = EAUTOMOVE;
		}
		else if (mEnemy_PlayerDis <= ENEMY_SEARCH_DIS)
		{
			mEnemy_State = EDASH;
		}
		else
		{
			//�A�j���[�V�����̐ݒ�
			ChangeAnimation(5, true, 60);
		}
	}
	else 
	{
		//�A�j���[�V�����̐ݒ�
		ChangeAnimation(5, true, 60);
	}
}
void CXEnemy::Move(){
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(3, true, 60);
	mEnemy_Speed = ENEMY_SPEED_MOVE;
	//�ړI�n�_�܂ł̃x�N�g�������߂�
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDir�Ƀv���C���[�����̃x�N�g��������
	mEnemy_MoveDir.Y(0.0f);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % 30; //rand()�͐����̗�����Ԃ�
						 //%10��10�Ŋ������]������߂�
	//�U���o���鋗���ɂ��Ȃ���ΖڕW�n�_�Ɉړ�
	if (mEnemy_PlayerDis > ENEMY_ATTACK_DIS)
	{
		if (r == 0)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = 0;
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= ENEMY_ATTACK_DIS)
	{
		if (random == 0) 
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
	if (mEnemy_PlayerDis >= ENEMY_WALK_DIS_MAX)
	{
		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
	}

}

void CXEnemy::Dash()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(4, true, 50);
	//�ړ��X�s�[�h��ύX
	mEnemy_Speed = ENEMY_SPEED_DASH;
	//�ړI�n�_�܂ł̃x�N�g�������߂�
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDir�ɖڕW�n�_�����̃x�N�g��������
	mEnemy_MoveDir.Y(0.0f);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % 25; //rand()�͐����̗�����Ԃ�
						  //%25��25�Ŋ������]������߂�
	//�U���o���鋗���ɂ��Ȃ���ΖڕW�n�_�Ɉړ�
	if (mEnemy_PlayerDis > ENEMY_ATTACK_DIS)
	{
		if (r == 0)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = 0;
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= ENEMY_ATTACK_DIS)
	{
		if (random == 0) 
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
	if (mEnemy_PlayerDis >= ENEMY_CHASE_DIS_MAX)
	{
		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
	}

	CTransform::Update();

}

void CXEnemy::Attack_1()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(1, false, 110);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false)
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame <= ENEMY_RECEPTION)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else {
			mEnemy_IsHit = true;
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > ENEMY_OUTRECEPTION)
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
						mEnemy_Hp = mEnemy_Hp - 10;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - 10;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - 15;
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
	ChangeAnimation(2, false, 120);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame <= ENEMY_RECEPTION)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else {
			mEnemy_IsHit = true;
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > ENEMY_OUTRECEPTION)
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
						mEnemy_Hp = mEnemy_Hp - 10;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - 10;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - 15;
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
	ChangeAnimation(0, false, 130);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame <= ENEMY_RECEPTION)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else {
			mEnemy_IsHit = true;
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > ENEMY_OUTRECEPTION)
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
						mEnemy_Hp = mEnemy_Hp - 10;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - 10;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //�G�t�F�N�g�𐶐�����
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - 15;
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
	ChangeAnimation(6, false, 60);
	//�_���[�W����
	//1�x�����������Ȃ����߂̃J�E���^
	if (mEnemy_Flag == false)
	{
		if (mEnemy_val >= 0 && mEnemy_val <= 60) {
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
			mEnemy_Hp -= ENEMY_DAMAGE_BODY * 2;
		}
		else
		{
			mEnemy_Hp -= ENEMY_DAMAGE_BODY;	//�_���[�W���󂯂�(��)

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
	ChangeAnimation(7, false, 60);
	mEnemy_IsHit = false;
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//����̐e�������̎��̓��^�[��
	if (o->Parent() == this)return;

	if (!mEnemy_Hp <= 0)
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



	if (!mEnemy_Hp <= 0)
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
								mEnemy_val = (rand() % 100) + 1;
								if (mEnemy_val >= 0 && mEnemy_val <= 60) {
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
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / 180.0f));

	//��]���x�@degree�ɒ���
	mEnemy_Turnspeed = (180.0f / M_PI) * 0.3f;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//�ړ������փL��������������
	if (tCheck.cross > 0.0f)
	{
		mRotation.Y(mRotation.Y() + tCheck.turn * mEnemy_Turnspeed);
	}
	if (tCheck.cross < 0.0f)
	{
		mRotation.Y(mRotation.Y() - tCheck.turn * mEnemy_Turnspeed);
	}
	//�ړ�����
	mPosition += mEnemy_MoveDir * mEnemy_Speed;
	mPosition.Y(mPosition.Y() * ENEMY_GRAVITY);

	//�ړ��������Z�b�g
	mEnemy_MoveDir = CVector(0.0f, 0.0f, 0.0f);
	//�ړ��X�s�[�h���Z�b�g
	mEnemy_Speed = 0.0f;
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
//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CXEnemy* CXEnemy::GetInstance()
{
	return mpEnemy_Instance;
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
	

