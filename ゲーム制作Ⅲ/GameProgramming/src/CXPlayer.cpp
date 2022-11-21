#include"CXPlayer.h"
#include"CSceneGame.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CCamera.h"

#define GRAVITY 0.001f//�d��
#define RECEPTION 120 //���͂̎�t����
#define INITIALIZATION 0 //������

CXPlayer* CXPlayer::mpPlayerInstance = nullptr;



//�R���C�_������
CXPlayer::CXPlayer()
	:mColSphereBody(this, nullptr, CVector(0.0f,80.0f,0.0f), CVector(0.0f, -80.0f, 0.0f), 0.7)
	, mColSphereShield(this, nullptr, CVector(0.0f, 0.0f, -5.0f), 0.5f)
	, mColSphereSword1(this, nullptr, CVector(-13.0f, 0.0f, 70.0f), 0.3f)
	, mColSphereSword2(this, nullptr, CVector(-10.0f, 0.0f, 50.0f), 0.3f)
	, mColSphereSword3(this, nullptr, CVector(-5.0f, 0.0f, 30.0f), 0.3f)
	, mColSphereSword4(this, nullptr, CVector(-0.0f, 0.0f, 10.0f), 0.3f)
	, mSpeed(SPEED_DEFAULT)
	, mHp(1)
	, mPlayerComboCount(0)
	, mAttackFlag_1(false)
	, mAttackFlag_2(false)
	, mAttackFlag_3(false)
	, mAttackFlag_Once(false)
	, mIsHit(false)
	, mTurnspeed(0.0f)
	, mPlayerFlag(false)

{
	mpPlayerInstance = this;
	mTag = EPLAYER;
	//������Ԃ�ݒ�
	mState = EIDLE;	//�ҋ@���
	//�R���C�_�̃^�O��ݒ�
	mColSphereBody.Tag(CCollider::EBODY);		//��
	mColSphereShield.Tag(CCollider::ESHIERD);	//��
	mColSphereSword1.Tag(CCollider::ESWORD);	//��
	mColSphereSword2.Tag(CCollider::ESWORD);	//��
	mColSphereSword3.Tag(CCollider::ESWORD);	//��
	mColSphereSword4.Tag(CCollider::ESWORD);	//��
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.Matrix(&mpCombinedMatrix[14]);
	mColSphereShield.Matrix(&mpCombinedMatrix[41]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[71]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[71]);
	mColSphereSword3.Matrix(&mpCombinedMatrix[71]);
	mColSphereSword4.Matrix(&mpCombinedMatrix[71]);
	mPosition.Set(0.0f, 0.0f, 0.0);	//�ʒu��ݒ�
	mScale.Set(2.0f,2.0f,2.0f);//�X�P�[���ݒ�
	mRotation.Set(0.0f, 180.0f, 0.0f);	//��]��ݒ�
}

void CXPlayer::Update() {
	//��Ԃ𔻕�
	switch (mState) {
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

	case EMOVE:	//�ړ����
		Move();	//�ړ���Ԃ̏������Ă�
		break;

	case EGUARD: //������
		Guard(); //����������Ă�
		break;

	case EDEATH: //���S���
		Death(); //���S�������Ă�
		break;

	case EKNOCKBACK: //�m�b�N�o�b�N���
		KnockBack(); //�m�b�N�o�b�N�������Ă�
		break;
	}
	//���W�ړ�
	mPosition += mMove;
	//����������
	mMove = mMove * GRAVITY;

	////�d��
	//mPosition.mY -= GRAVITY;

	//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
	//�[���x�N�g���v�Z
	CVector ChackVec; //�`�F�b�N�p�x�N�g��
	ChackVec = mMoveDirKeep.Normalize(); //�ۑ����ꂽ�ړ����̕����x�N�g������
	ChackVec = mMoveDir.Normalize(); //�ړ����̕����x�N�g������
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / 180.0f));

	//��]���x�@degree�ɒ���
	mTurnspeed = (180.0f / M_PI) * 0.3f;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//�ړ������փL��������������
	if (tCheck.cross > 0.0f) {
		mRotation = mRotation + CVector(0.0f,tCheck.turn * mTurnspeed,0.0f);
	}
	if (tCheck.cross < 0.0f) {
		mRotation = mRotation - CVector(0.0f, tCheck.turn * mTurnspeed, 0.0f);
	}

	//���Z�b�g
	mMoveDir = CVector(0.0f, 0.0f, 0.0f);

	//�̗͂�0�ɂȂ�Ǝ��S
	if (mHp <= 0) {
		mState = EDEATH;	//���S��Ԃֈڍs
		mHp = 0;
	}

	Camera.SetTarget(mPosition);
	CXCharacter::Update();

}

void CXPlayer::Idle() 
{
	mPlayerComboCount = 0;
	ChangeAnimation(6, true, 30);
	//���N���b�N�ōU��
	if (CKey::Once(VK_LBUTTON)) {
		mState = EATTACK_1;
	}
	//WASD�L�[�������ƈړ��ֈڍs
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mState = EMOVE;
	}
	else if (CKey::Once(VK_SPACE)) {
		mState = EGUARD;
	}
}

//�ړ�����
void CXPlayer::Move()
{
	
	if (CKey::Once(VK_LBUTTON)) {
		mState = EATTACK_1;
	}
	//���N���b�N�ōU��1�ֈڍs
	else if (CKey::Once(VK_SPACE)) {
		mState = EGUARD;
	}
	//WASD�L�[�������ƈړ�
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		MoveCamera(); //�J��������ɂ����ړ��������Ă�
		ChangeAnimation(0, true, 30);
	}
	//�ҋ@��Ԃֈڍs
	else {
		mState = EIDLE;
	}
}


//�U��1����
void CXPlayer::Attack_1()
{
	
	if (mAttackFlag_1 == false) {
		mAttackFlag_1 = true;
		mAttackFlag_Once = true;
		ChangeAnimation(5, false, 1);//�ҋ@���[�V����
	}

	if (mAnimationIndex == 5)
	{
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mIsHit = false; //�q�b�g����I��
			ChangeAnimation(1, false, 30);
		}
	}
	else if (mAnimationIndex == 3) {
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mIsHit = false; //�q�b�g����I��
			ChangeAnimation(1, false, 30);
		}
	}

	else if (mAnimationIndex == 1)
	{
		if (mAnimationFrame < RECEPTION) {
			if (CKey::Once(VK_LBUTTON)) {
				mState = EATTACK_2;	//�U��2�̃��[�V�����ֈڍs
			}
			else if(CKey::Once(VK_SPACE)) {
				mState = EGUARD;
			}
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
	mState = EIDLE; //�ҋ@��Ԃֈڍs
	mAttackFlag_1 = false;
	}
}

//�U��2����
void CXPlayer::Attack_2()
{
	if (mAttackFlag_2 == false) {
		mAttackFlag_2 = true;
		mAttackFlag_Once = true;
	}
	if (mAnimationIndex == 1)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//�A�j���[�V�����I����
		else if (IsAnimationFinished())
		{
			mIsHit = false; //�q�b�g����I��
			ChangeAnimation(2, false, 40);
		}
	}
	else if (mAnimationIndex == 2)
	{
		if (mAnimationFrame < RECEPTION) {
			if (CKey::Once(VK_LBUTTON)) {
				mState = EATTACK_3;	//�U��3�̃��[�V�����ֈڍs
			}
			else if (CKey::Once(VK_SPACE)) {
				mState = EGUARD;
			}
		}
	}
	if (IsAnimationFinished())
	{
	mState = EIDLE; //�ҋ@��Ԃֈڍs
	}
}

//�U��3����
void CXPlayer::Attack_3()
{
	if (mAttackFlag_3 == false) {
		mAttackFlag_3 = true;
		mAttackFlag_Once = true;
	}
	if (mAnimationIndex == 2)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mIsHit = false; //�q�b�g����I��
			ChangeAnimation(3, false, 60);
		}
	}
	else if (mAnimationIndex == 3)
	{
		if (mAnimationFrame < RECEPTION) {
			if (CKey::Once(VK_LBUTTON)) {
				mState = EATTACK_1;	//�U��1�̃��[�V�����ֈڍs
			}
			else if(CKey::Once(VK_SPACE)) {
				mState = EGUARD;
			}
		}
	}

	if (IsAnimationFinished())
	{
	mState = EIDLE; //�ҋ@��Ԃֈڍs
	}
}

//�m�b�N�o�b�N����
void CXPlayer::KnockBack()
{
	ChangeAnimation(7, false, 50);	//�̂�����A�j���[�V����
		//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mState = EIDLE; //�ҋ@��Ԃֈڍs
	}
}

//�K�[�h
void CXPlayer::Guard()
{
	if (mPlayerFlag == false) {
		ChangeAnimation(6, false, 1);//�ҋ@���[�V����
		mPlayerFlag = true;
	}
	
	if (mAnimationIndex == 6){
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			ChangeAnimation(4, false, 10);	//�K�[�h�ҋ@�A�j���[�V����
		}
	}
	else if (mAnimationIndex == 4) {
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mIsHit = false; //�q�b�g����I��
			ChangeAnimation(5, false, 30);	//�K�[�h�ҋ@�A�j���[�V����
		}

	}
	//�A�j���[�V�����I����
	else if (IsAnimationFinished())
	{
		mState = EIDLE;
		mPlayerFlag = false;
	}

}

//���S����
void CXPlayer::Death()
{
	ChangeAnimation(8, false, 50);	//���S�A�j���[�V����
}

//�J��������ɂ����ړ�����
void CXPlayer::MoveCamera()
{
	//�J�������_�ړ��@�ʏ̖��o�ړ�
	//�J�����̍��E�ƑO��̃x�N�g�����擾
	mSideVec = Camera.GetMat().GetXVec();
	mFrontVec = Camera.GetMat().GetZVec();
	//�����ړ��̓J�b�g����
	mSideVec.Y(0.0f);
	mFrontVec.Y(0.0f);
	//���K������
	mSideVec.Normalize();
	mFrontVec.Normalize();

	if (CKey::Push('A'))
	{
		mMoveDir -= mSideVec;
	}
	else if (CKey::Push('D'))
	{
		mMoveDir += mSideVec;
	}
	if (CKey::Push('W')) {
		mMoveDir += mFrontVec;
	}
	else if (CKey::Push('S'))
	{
		mMoveDir -= mFrontVec;
	}

	//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
	mMoveDir = mMoveDir.Normalize();
	mMoveDirKeep = mMoveDir;	//MoveDir�ۑ�
	mMove = mMoveDir * mSpeed;	//�ړ��ʂ�ݒ�
}



void CXPlayer::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ESPHERE: {//���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			CCollider::CollisionTriangleSphere(o, m, &adjust);
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition + adjust;
			//�s��̍X�V
			CTransform::Update();
		}

		break;
	}
						   
	case CCollider::ECAPSUL:{//�J�v�Z���R���C�_
		//����̃R���C�_���J�v�Z���R���C�_�̎�
		if (o->Type() == CCollider::ECAPSUL) {
			CVector adjust;//�����p�x�N�g��
			if (CCollider::CollisionCapsule(o, m, &adjust))
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();

			}

			break;
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
			break;
		}
		//if (o->Type() == CCollider::ESPHERE) {
		//	CVector adjust;//�����p�x�N�g��
		//	//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		//		CCollider::Collision(m, o);
		//		//����̐e�̃^�O���v���C���[
		//		if (o->Parent()->Tag() == EENEMY)
		//		{
		//			//����̃R���C�_�̃^�O����
		//			if (o->Tag() == CCollider::EARM) {
		//				if (CXEnemy::GetInstance()->GetIsHit() == true) {
		//					mState = EKNOCKBACK;
		//					mHp = mHp - 1;
		//				}
		//			}
		//		}
		//	
		//	
		//}
	}
	}		
}

//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayerInstance;
}
//�U���̓����蔻����擾����
bool CXPlayer::GetIsHit()
{
	return mIsHit; //�U���̓����蔻���Ԃ�
}

//�v���C���[�̏�Ԃ��擾����
CXPlayer::EPlayerState CXPlayer::GetState()
{
	return mState;
}