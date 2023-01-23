#include"CXEnemy.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>
#include"CXPlayer.h"
#include "CRes.h"

#define DAMAGE_BODY 10		//�_���[�W(��)

#define ENEMY_ATTACK_DIS 3.2f		//�U���\�ɂȂ鋗��
#define ENEMY_SPEED_MOVE 0.1f		//�ʏ�ړ��̃X�s�[�h
#define ENEMY_SPEED_DASH 0.15f	//���s�̈ړ����x
#define ENEMY_SPEED_STOP 0.0f		//��~
#define ENEMY_WALK_DIS 30.0f		//���s���J�n���鋗��
#define ENEMY_SEARCH_DIS 60.0f		//���s���J�n���鋗��
#define ENEMY_WALK_DIS_MAX 50.0f	//���s�\�ȍő勗��
#define ENEMY_CHASE_DIS_MAX 80.0f   //���s�\�ȍő勗��
#define ENEMY_GRAVITY 0.1			//�d��

#define ENEMY_HP_MAX 200;	//HP�̍ő�l
//�G��HP�t���[��,HP�Q�[�W���W,��,����
#define ENEMY_GAUGE_WID_MAX 100.0f	//�Q�[�W�̕��̍ő�l
#define ENEMY_GAUGE_HEIGHT 20.0f //�Q�[�W�`�掞�̍���
#define ENEMY_GAUGE_HP_TOP -10.0f //HP�Q�[�W�`�掞�̏���W
#define ENEMY_GAUGE_HP_BOTTOM (ENEMY_GAUGE_HP_TOP - ENEMY_GAUGE_HEIGHT) //HP�Q�[�W�`�掞�̉����W


CXEnemy* CXEnemy::mpEnemy_Instance = nullptr;

//�R���C�_������
CXEnemy::CXEnemy()
	:mEnemy_Hp(200)
	,mEnemy_Speed(0.0f)
	,mEnemy_Turnspeed(0.0f)
	,mEnemy_PlayerDis(0.0f)
	, mEnemy_FollowGaugeWid(0.0f)
	,mEnemy_val(0)
	,mEnemy_IsHit(false)
	,mEnemy_Flag(false)
	, mEnemy_ColCapsuleBody(this, nullptr, CVector(0.0f, 90.0f, 0.0f), CVector(0.0f, -130.0f, 30.0f), 1.3)
	,mEnemy_ColSphereRightarm(this, nullptr, CVector(), 1.0)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(), 1.0)

{
	mpEnemy_Instance = this;
	//������Ԃ�ݒ�
	mEnemy_State = EIDLE;	//�ҋ@���
		//�R���C�_�̃^�O��ݒ�
	mEnemy_ColCapsuleBody.Tag(CCollider::EBODY);		//��
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
	mEnemy_ColCapsuleBody.Matrix(&mpCombinedMatrix[24]);
	mEnemy_ColSphereRightarm.Matrix(&mpCombinedMatrix[68]);
	mEnemy_ColSphereLeftarm.Matrix(&mpCombinedMatrix[41]);
	mPosition.Set(0.0f, -4.0f, -20.0);	//�ʒu��ݒ�
	mScale.Set(3.0f, 3.0f, 2.0f);//�X�P�[���ݒ�
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
	//case EREPELLED: //�͂����ꂽ���̏��
	//	Repelled(); //�͂����ꂽ�ꍇ�̏������Ă�
	//	break;
	}
	MovingCalculation();
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
		mEnemy_FollowGaugeWid = Camera.mLerp(mEnemy_FollowGaugeWid, HpGaugeWid, 0.05f);
	}
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕���菬�����Ƃ�
	else if (mEnemy_FollowGaugeWid < HpGaugeWid) {
		//��_���[�W����ǂ�����Q�[�W�̕��ɑ̗̓Q�[�W�̕���ݒ肷��
		mEnemy_FollowGaugeWid = HpGaugeWid;
	}
	//��ʊO�̎��ɕ\�����Ȃ�
	if (ret.X() > 0 && ret.X() < 800) {
		CRes::GetInstance()->GetInEnemyUiHpBackBar().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, ret.X() + ENEMY_GAUGE_WID_MAX, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 0, 30);
		//��_���[�W����ǂ�����Q�[�W��\��
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + mEnemy_FollowGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
		//�̗̓Q�[�W
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + HpGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
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
	CVector Point = mEnemy_Point - mPosition;
	//mMoveDir�Ƀv���C���[�����̃x�N�g��������
	mEnemy_MoveDir = Point.Normalize();
	//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % 30; //rand()�͐����̗�����Ԃ�
						 //%10��10�Ŋ������]������߂�
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
			random = rand() % 4;
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
			case 3:
				mEnemy_State = EIDLE;
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
	CVector Point = mEnemy_Point - mPosition;
	//mMoveDir�ɖڕW�n�_�����̃x�N�g��������
	mEnemy_MoveDir = Point.Normalize();
	//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % 25; //rand()�͐����̗�����Ԃ�
						  //%25��25�Ŋ������]������߂�
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
			random = rand() % 4;
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
			case 3:
				mEnemy_State = EIDLE;
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
	ChangeAnimation(1, false, 85);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false)
	{
		mEnemy_IsHit = true;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //�q�b�g����I��
		mEnemy_State = EIDLE;
		if (mEnemy_val >= 21 && mEnemy_val <= 100)
		{
			if (CXPlayer::GetInstance()->GetIsHit() == true) {
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
			}
		}
	}
}

void CXEnemy::Attack_2()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(2, false, 95);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		mEnemy_IsHit = true;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //�q�b�g����I��
		mEnemy_State = EIDLE;
		if (mEnemy_val >= 36 && mEnemy_val <= 100)
		{
			if (CXPlayer::GetInstance()->GetIsHit() == true) {
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
				{
					mEnemy_Hp = mEnemy_Hp - 10;
				}
			}
		}
	}
}

void CXEnemy::Attack_3()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(0, false, 95);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		mEnemy_IsHit = true;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //�q�b�g����I��
		mEnemy_State = EIDLE;
		if (mEnemy_val >= 36 && mEnemy_val <= 100)
		{
			if (CXPlayer::GetInstance()->GetIsHit() == true) {
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
				{
					mEnemy_Hp = mEnemy_Hp - 10;
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
		mEnemy_Flag = true;
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
		{
			mEnemy_Hp -= DAMAGE_BODY * 2;
		}
		else
		{
			mEnemy_Hp -= DAMAGE_BODY;	//�_���[�W���󂯂�(��)

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


//void CXEnemy::Repelled()
//{
//	ChangeAnimation(6, false, 50);
//	//�A�j���[�V�����I����
//	if (IsAnimationFinished())
//	{
//		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
//	}
//}

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
				//����̐e�̃^�O���v���C���[
				if (o->Parent()->Tag() == EPLAYER)
				{
					//����̃R���C�_�̃^�O����
					if (o->Tag() == CCollider::ESWORD)
					{
						if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH)
						{
							//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
							srand((unsigned)time(NULL));
							mEnemy_val = (rand() % 100) + 1;
							if (mEnemy_val >= 0 && mEnemy_val <= 35) {
								if (CXPlayer::GetInstance()->GetIsHit() == true) {
									mEnemy_State = EKNOCKBACK;
								}
							}
						}
					}
					//else if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EGUARD)
					//{
					//	if (CXPlayer::GetInstance()->GetIsHit() == true)
					//	{
					//		mEnemy_State = EREPELLED;
					//	}
					//}
					else if (m->Tag() == CCollider::EBODY && o->Tag() == CCollider::EBODY)
					{
						//�ʒu�̍X�V(mPosition + adjust)
						mPosition = mPosition + adjust;
						//�s��̍X�V
						CTransform::Update();
					}
				}
			}
		}
		else if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();
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
	mEnemy_ColSphereRightarm.ChangePriority();
	mEnemy_ColSphereLeftarm.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mEnemy_ColCapsuleBody, COLLISIONRANGE);
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
	

