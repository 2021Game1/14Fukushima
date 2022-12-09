#include"CXEnemy.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"CXPlayer.h"
#include "CRes.h"

#define ENEMY_ATTACK_DIS 3.2f		//�U���\�ɂȂ鋗��
#define ENEMY_SPEED_MOVE 0.1f		//�ʏ�ړ��̃X�s�[�h
#define ENEMY_SPEED_DASH 0.15f	//���s�̈ړ����x
#define ENEMY_SPEED_STOP 0.0f		//��~
#define ENEMY_RECEPTION 10	//���͂̓����蔻��̎�t����
#define ENEMY_OUTRECEPTION 60 //�����蔻��̎�t�I��
#define ENEMY_SEARCH_DIS 20.0f	//���s���J�n���鋗��
#define ENEMY_WALK_DIS 24.0f		//���s���J�n���鋗��
#define ENEMY_GRAVITY 0.9			//�d��
#define ENEMY_CHASE_DIS_MAX 25.0f	//���s�\�ȍő勗��
#define ENEMY_HP_MAX 100;	//HP�̍ő�l
//�G��HP�t���[��,HP�Q�[�W���W,��,����
#define ENEMY_GAUGE_FRAME_TEX_WID 480.0f	//�Q�[�W�g�̉摜�̕�
#define ENEMY_GAUGE_FRAME_TEX_HEI 30.0f	//�Q�[�W�g�̉摜�̍���
#define ENEMY_GAUGE_FRAME_TOP 10.0f //�Q�[�W�g����W
#define ENEMY_GAUGE_FRAME_BOTTOM (ENEMY_GAUGE_FRAME_TOP-ENEMY_GAUGE_FRAME_TEX_HEI) //�Q�[�W�g�����W
#define ENEMY_GAUGE_WID_MAX 50.0f	//�Q�[�W�̕��̍ő�l
#define ENEMY_GAUGE_HEIGHT 20.0f //�Q�[�W�`�掞�̍���
#define ENEMY_GAUGE_HP_TOP 10.0f //HP�Q�[�W�`�掞�̏���W
#define ENEMY_GAUGE_HP_BOTTOM (ENEMY_GAUGE_HP_TOP - ENEMY_GAUGE_HEIGHT) //HP�Q�[�W�`�掞�̉����W


CXEnemy* CXEnemy::mpEnemy_Instance = nullptr;

//�R���C�_������
CXEnemy::CXEnemy()
	:mEnemy_Hp(100)
	,mEnemy_Speed(0.0f)
	,mEnemy_Turnspeed(0.0f)
	,mEnemy_PlayerDis(0.0f)
	,mEnemy_IsHit(false)
	,mEnemy_ColSphereBody(this, nullptr, CVector(0.0f, 90.0f, 0.0f), CVector(0.0f, -130.0f, 30.0f), 1.3)
	,mEnemy_ColSphereRightarm(this, nullptr, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, -90.0f, 0.0f), 1.5)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(0.0f, 0.0f, 0.0f), CVector(-30.0f, -90.0f, 30.0f), 0.8)

{
	mpEnemy_Instance = this;
	//������Ԃ�ݒ�
	mEnemy_State = EIDLE;	//�ҋ@���
		//�R���C�_�̃^�O��ݒ�
	mEnemy_ColSphereBody.Tag(CCollider::EBODY);		//��
	mEnemy_ColSphereRightarm.Tag(CCollider::EARM);	//��
	mEnemy_ColSphereLeftarm.Tag(CCollider::EARM);	//��
}



void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mEnemy_ColSphereBody.Matrix(&mpCombinedMatrix[24]);
	mEnemy_ColSphereRightarm.Matrix(&mpCombinedMatrix[83]);
	mEnemy_ColSphereLeftarm.Matrix(&mpCombinedMatrix[41]);
	mPosition.Set(10.0f, 0.0f, 0.0);	//�ʒu��ݒ�
	mScale.Set(4.0f, 4.0f, 4.0f);//�X�P�[���ݒ�
	mRotation.Set(0.0f, 0.0f, 0.0f);	//��]��ݒ�
}

void CXEnemy::Update() {
	//�v���C���[�����̃x�N�g�������߂�
	mEnemy_PlayerPos = CXPlayer::GetInstance()->Position() - mPosition;
	//�v���C���[�܂ł̋��������߂�
	mEnemy_PlayerDis = mEnemy_PlayerPos.Length();
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
	tpos = mpCombinedMatrix[24].GetPos();
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
		//��_���[�W����ǂ�����Q�[�W��\��
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() + ENEMY_GAUGE_WID_MAX) + mEnemy_FollowGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
		//�̗̓Q�[�W
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() + ENEMY_GAUGE_WID_MAX) + HpGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
		//�Q�[�W�w�i
		CRes::GetInstance()->GetInEnemyUiHpFrame().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, ret.X() + ENEMY_GAUGE_WID_MAX * 2.0f, ret.Y() + ENEMY_GAUGE_FRAME_BOTTOM, ret.Y() + ENEMY_GAUGE_FRAME_TOP, 0.0f, ENEMY_GAUGE_FRAME_TEX_WID, 0.0f, ENEMY_GAUGE_FRAME_TEX_HEI);
	}
	//2D�̕`��I��
	CUtil::End2D();
}

void CXEnemy::Idle()
{
	//�v���C���[�����S��Ԃł͖����Ƃ�
	if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH) 
	{
		//�v���C���[����苗���܂ŋ߂Â��ƒǐՏ�Ԃֈڍs
		if (mEnemy_PlayerDis <= ENEMY_SEARCH_DIS)
		{
			mEnemy_State = EDASH;
		}
		else if (mEnemy_PlayerDis <= ENEMY_WALK_DIS)
		{
			mEnemy_State = EAUTOMOVE;
		}
		else 
		{
			ChangeAnimation(5, true, 60);
		}
	}
	else 
	{
		ChangeAnimation(5, true, 60);
	}
}
void CXEnemy::Move(){
	ChangeAnimation(3, true, 50);
	//�ړ��X�s�[�h��ύX
	//�v���C���[���U���\�ȋ����ɂ��Ȃ��Ƃ�
	if (mEnemy_PlayerDis > ENEMY_ATTACK_DIS)
	{
		mEnemy_Speed = ENEMY_SPEED_MOVE;
	}
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= ENEMY_ATTACK_DIS)
	{
		//�ړ��X�s�[�h���~����
		mEnemy_Speed = ENEMY_SPEED_STOP;
	}
	mPosition = mPosition + CVector(0.0f, 0.0f, mEnemy_Speed) * mMatrixRotate;
	//�v���C���[�Ɍ������ĉ�]���鏈��
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mEnemy_Point - mPosition;
	//���x�N�g���Ƃ̓��ς����߂�
	float dx = vp.Dot(vx);
	//��x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy);
	//�O�x�N�g���Ƃ̓��ς����߂�
	float dz = vp.Dot(vz);
	float margin = 0.1f;
	//���E�����։�]
	if (dx > margin) 
	{
		mRotation.Y(mRotation.Y() + 3.0f);//���։�]
	}
	else if (dx < -margin) 
	{
		mRotation.Y(mRotation.Y() - 3.0f);//�E�։�]
	}
	CTransform::Update();//�s��X�V

		//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % 30; //rand()�͐����̗�����Ԃ�
						 //%10��10�Ŋ������]������߂�

	if (r == 0)	
	{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
	}
	int random = 0;
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= ENEMY_ATTACK_DIS)
	{
		//�����_���ōU�����s�����ǂ����𔻒肷��
		random = rand() % 1;
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

}

void CXEnemy::Dash()
{
	ChangeAnimation(4, true, 40);
	//�v���C���[���U���\�ȋ����ɂ��Ȃ��Ƃ�
	if (mEnemy_PlayerDis > ENEMY_ATTACK_DIS)
	{
		//�ړ��X�s�[�h��ύX
		mEnemy_Speed = ENEMY_SPEED_DASH;
	}
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= ENEMY_ATTACK_DIS)
	{
		//�ړ��X�s�[�h���~����
		mEnemy_Speed = ENEMY_SPEED_STOP;
	}
	mPosition = mPosition + CVector(0.0f, 0.0f, mEnemy_Speed) * mMatrixRotate;
	//�v���C���[�Ɍ������ĉ�]���鏈��
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mEnemy_Point - mPosition;
	//���x�N�g���Ƃ̓��ς����߂�
	float dx = vp.Dot(vx);
	//��x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy);
	//�O�x�N�g���Ƃ̓��ς����߂�
	float dz = vp.Dot(vz);
	float margin = 0.1f;

	//���E�����։�]
	if (dx > margin) 
	{
		mRotation.Y(mRotation.Y() + 3.0f);//���։�]
	}
	else if (dx < -margin) 
	{
		mRotation.Y(mRotation.Y() - 3.0f);//�E�։�]
	}
	CTransform::Update();//�s��X�V
		
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
		//�����_���ōU�����s�����ǂ����𔻒肷��
		random = rand() % 50;
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
	ChangeAnimation(1, false, 60);
	mEnemy_IsHit = false; //�q�b�g����I��
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mEnemy_PlayerDis >= ENEMY_CHASE_DIS_MAX)
	{
		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
	}

	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		if (mAnimationFrame >= ENEMY_RECEPTION) 
		{
			mEnemy_IsHit = true;
		}
		else if (mAnimationFrame == ENEMY_OUTRECEPTION)
		{
			mEnemy_IsHit = false;
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE;
	}

}

void CXEnemy::Attack_2()
{
	ChangeAnimation(2, false, 60);
	mEnemy_IsHit = false; //�q�b�g����I��
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mEnemy_PlayerDis >= ENEMY_CHASE_DIS_MAX)
	{
		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
	}
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		if (mAnimationFrame >= ENEMY_RECEPTION) 
		{
			mEnemy_IsHit = true;
		}
		else if (mAnimationFrame == ENEMY_OUTRECEPTION)
		{
			mEnemy_IsHit = false;
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE;
	}
}

void CXEnemy::Attack_3()
{
	ChangeAnimation(0, false, 60);
	mEnemy_IsHit = false; //�q�b�g����I��
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) 
	{
		if (mAnimationFrame >= ENEMY_RECEPTION) 
		{
			mEnemy_IsHit = true;
		}
		else if (mAnimationFrame == ENEMY_OUTRECEPTION)
		{
			mEnemy_IsHit = false;
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE;
	}
}


void CXEnemy::KnockBack()
{
	ChangeAnimation(6, false, 50);
	//�A�j���[�V�����I����
	if (IsAnimationFinished()) 
	{
		mEnemy_State = EIDLE; //�ҋ@��Ԃֈڍs
		mEnemy_Hp -= 20;
	}
}

void CXEnemy::Death()
{
	ChangeAnimation(7, false, 30);
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
						if (CXPlayer::GetInstance()->GetIsHit() == true) {
							new CEffect(((CXPlayer*)(o->Parent()))->GetSwordColPos(), 10.0f, 10.0f, "", 3, 3, 4); //�G�t�F�N�g�𐶐�����
							mEnemy_State = EKNOCKBACK;
						}
					}
					else if (o->Tag() == CCollider::ESHIERD)
					{
							if (CXPlayer::GetInstance()->GetIsHit() == true)
							{
								mEnemy_State = EKNOCKBACK;
							}
					}
					else 
					{
						//�ʒu�̍X�V(mPosition + adjust)
						mPosition = mPosition + adjust;
						//�s��̍X�V
						CTransform::Update();
					}
				}

			}
		}
	}
}
//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CXEnemy* CXEnemy::GetInstance()
{
	return mpEnemy_Instance;
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

//�v���C���[�̏�Ԃ��擾����
CXEnemy::EEnemyState CXEnemy::GetState()
{
	return mEnemy_State;
}
	

