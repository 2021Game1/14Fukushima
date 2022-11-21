#include "CXEnemy.h"
#include"CUtil.h"
#include"CXPlayer.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define ATTACK_DIS 4.0f		//�U���\�ɂȂ鋗��
#define SPEED_MOVE 0.1f	//�ʏ�ړ��̃X�s�[�h
#define SPEED_DASH 0.15f	//�ǐՒ��̈ړ����x
#define SEARCH_DIS 20.0f	//�ǐՂ��J�n���鋗��
#define WALK_DIS 24.0f		//���s���J�n���鋗��
#define CHASE_DIS_MAX 25.0f	//�ǐՉ\�ȍő勗��

CXEnemy* CXEnemy::mpEnemyInstance = nullptr;

//�R���C�_������
CXEnemy::CXEnemy()
	:mHp(3)
	,mSpeed(0.0f)
	,mTurnspeed(0.0f)
	,mColSphereBody(this, nullptr, CVector(0.0f, 90.0f, 0.0f), CVector(0.0f, -130.0f, 30.0f), 1.3)
	,mColSphereRightarm1(this, nullptr, CVector(), 1.0)
	,mColSphereRightarm2(this, nullptr, CVector(), 1.0)
	,mColSphereLeftarm1(this, nullptr, CVector(), 1.0)
	,mColSphereLeftarm2(this, nullptr, CVector(), 1.0)
{
	mpEnemyInstance = this;
	//������Ԃ�ݒ�
	mState = EIDLE;	//�ҋ@���
		//�R���C�_�̃^�O��ݒ�
	mColSphereBody.Tag(CCollider::EBODY);		//��
	mColSphereRightarm1.Tag(CCollider::EARM);	//��
	mColSphereRightarm2.Tag(CCollider::EARM);	//��
	mColSphereLeftarm1.Tag(CCollider::EARM);	//��
	mColSphereLeftarm2.Tag(CCollider::EARM);	//��
}
//CXEnemy(�ʒu�A��]�A�g�k�j
CXEnemy::CXEnemy(const CVector& position, const CVector& rotation, const CVector& scale)
	:CXEnemy()
{
	//�ʒu�A��]�A�g�k��ݒ肷��
	mPosition = position;//�ʒu�̐ݒ�
	mRotation = rotation;//��]�̐ݒ�
	mScale = scale;//�g�k�̐ݒ�
	CTransform::Update();//�s��̍X�V
	//�D��x���P�ɕύX����
	mPriority = 1;
	mEnabled = true;
}


void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.Matrix(&mpCombinedMatrix[24]);
	mColSphereRightarm1.Matrix(&mpCombinedMatrix[68]);
	mColSphereRightarm2.Matrix(&mpCombinedMatrix[62]);
	mColSphereLeftarm1.Matrix(&mpCombinedMatrix[41]);
	mColSphereLeftarm2.Matrix(&mpCombinedMatrix[27]);
	mPosition.Set(10.0f, 0.0f, 0.0);	//�ʒu��ݒ�
	mScale.Set(3.0f, 3.0f, 3.0f);//�X�P�[���ݒ�
	mRotation.Set(0.0f, 0.0f, 0.0f);	//��]��ݒ�
}

void CXEnemy::Update() {
	//�v���C���[�����̃x�N�g�������߂�
	mPlayerPos = CXPlayer::GetInstance()->Position() - mPosition;
	//�v���C���[�܂ł̋��������߂�
	mPlayerDis = mPlayerPos.Length();
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

	case EATTACK_4: //�U��4��Ԃ̎�
		Attack_4(); //�U��4�̏������Ă�
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
	ChackVec = mMoveDirKeep.Normalize(); //�ۑ����ꂽ�ړ����̕����x�N�g������
	ChackVec = mMoveDir.Normalize(); //�ړ����̕����x�N�g������
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / 180.0f));

	//��]���x�@degree�ɒ���
	mTurnspeed = (180.0f / M_PI) * 0.3f;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//�ړ������փL��������������
	if (tCheck.cross > 0.0f) {
		mRotation.Y(mRotation.Y() + tCheck.turn * mTurnspeed);
	}
	if (tCheck.cross < 0.0f) {
		mRotation.Y(mRotation.Y() - tCheck.turn * mTurnspeed);
	}
	//�ړ�����
	mPosition += mMoveDir * mSpeed;

	//�ړ��������Z�b�g
	mMoveDir = CVector(0.0f, 0.0f, 0.0f);
	//�ړ��X�s�[�h���Z�b�g
	mSpeed = 0.0f;

	//�̗͂�0�ɂȂ�Ǝ��S
	if (mHp <= 0) {
		mState = EDEATH;	//���S��Ԃֈڍs
		mHp = 0;
	}
	CXCharacter::Update();

}

void CXEnemy::Idle()
{
	ChangeAnimation(6, true, 30);
	//�v���C���[�����S��Ԃł͖����Ƃ�
	if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH) {
		//�v���C���[����苗���܂ŋ߂Â��ƒǐՏ�Ԃֈڍs
		if (mPlayerDis <= SEARCH_DIS) {
			mState = EDASH;
		}
		else if (mPlayerDis <= WALK_DIS)
		{
			mState = EAUTOMOVE;
		}
	}

}
void CXEnemy::Move(){
	ChangeAnimation(4, true, 30);
	//�ړ��X�s�[�h��ύX
	mSpeed = SPEED_MOVE;
	mPosition = mPosition + CVector(0.0f, 0.0f, mSpeed) * mMatrixRotate;
	//�v���C���[�Ɍ������ĉ�]���鏈��
//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	//���x�N�g���Ƃ̓��ς����߂�
	float dx = vp.Dot(vx);
	//��x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy);
	//�O�x�N�g���Ƃ̓��ς����߂�
	float dz = vp.Dot(vz);
	float margin = 0.1f;
	//���E�����։�]
	if (dx > margin) {
		mRotation.Y(mRotation.Y() + 3.0f);//���։�]
	}
	else if (dx < -margin) {
		mRotation.Y(mRotation.Y() - 3.0f);//�E�։�]
	}
	CTransform::Update();//�s��X�V

		//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % 10; //rand()�͐����̗�����Ԃ�
						  //%10��10�Ŋ������]������߂�
	if (r == 0)
	{
		mPoint = CXPlayer::GetInstance()->Position();
	}
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mPlayerDis <= ATTACK_DIS) {
		mState = EATTACK_2; //�U��1��Ԃֈڍs
	}
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //�ҋ@��Ԃֈڍs
	}

}

void CXEnemy::Dash()
{
	ChangeAnimation(5, true, 20);
	//�ړ��X�s�[�h��ύX
	mSpeed = SPEED_DASH;
	mPosition = mPosition + CVector(0.0f, 0.0f, mSpeed) * mMatrixRotate;
	//�v���C���[�Ɍ������ĉ�]���鏈��
	//�������iX���j�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//������iY���j�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O�����iZ���j�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	//���x�N�g���Ƃ̓��ς����߂�
	float dx = vp.Dot(vx);
	//��x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy);
	//�O�x�N�g���Ƃ̓��ς����߂�
	float dz = vp.Dot(vz);
	float margin = 0.1f;

	//���E�����։�]
	if (dx > margin) {
		mRotation.Y(mRotation.Y() + 3.0f);//���։�]
	}
	else if (dx < -margin) {
		mRotation.Y(mRotation.Y() - 3.0f);//�E�։�]
	}
	CTransform::Update();//�s��X�V
		
	//���悻1�b���ɖڕW�n�_���X�V
	int r = rand() % 10; //rand()�͐����̗�����Ԃ�
						  //%10��10�Ŋ������]������߂�
	if (r == 0)
	{
		mPoint = CXPlayer::GetInstance()->Position();
	}

	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mPlayerDis <= ATTACK_DIS) {
		mState = EATTACK_1; //�U��1��Ԃֈڍs
	}
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //�ҋ@��Ԃֈڍs
	}

	CTransform::Update();

}

void CXEnemy::Attack_1()
{
	ChangeAnimation(1, false, 30);

	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //�ҋ@��Ԃֈڍs
	}
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) {
		mIsHit = true;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mIsHit = false; //�q�b�g����I��
	}
	//���悻40�b���ɖڕW�n�_���X�V
	int r = rand() % 50; //rand()�͐����̗�����Ԃ�
						  //%180��180�Ŋ������]������߂�
	if (r == 0)
	{
		mState = EATTACK_2;
	}

}

void CXEnemy::Attack_2()
{
	ChangeAnimation(2, false, 40);

	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //�ҋ@��Ԃֈڍs
	}
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) {
		mIsHit = true;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mIsHit = false; //�q�b�g����I��
	}
	//���悻40�b���ɖڕW�n�_���X�V
	int r = rand() % 90; //rand()�͐����̗�����Ԃ�
						  //%180��180�Ŋ������]������߂�
	if (r == 0)
	{
		mState = EATTACK_3;
	}

}

void CXEnemy::Attack_3()
{
	ChangeAnimation(0, false, 30);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) {
		mIsHit = true;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mIsHit = false; //�q�b�g����I��
	}
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //�ҋ@��Ԃֈڍs
	}

	//���悻40�b���ɖڕW�n�_���X�V
	int r = rand() % 160; //rand()�͐����̗�����Ԃ�
						  //%180��180�Ŋ������]������߂�
	if (r == 0)
	{
		mState = EATTACK_4;
	}
}

void CXEnemy::Attack_4()
{
	ChangeAnimation(3, false, 30);
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false) {
		mIsHit = true;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mIsHit = false; //�q�b�g����I��
	}
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //�ҋ@��Ԃֈڍs
	}
	//���悻40�b���ɖڕW�n�_���X�V
	int r = rand() % 200; //rand()�͐����̗�����Ԃ�
						  //%180��180�Ŋ������]������߂�
	if (r == 0)
	{
		mState = EATTACK_1;
	}
}

void CXEnemy::KnockBack()
{
	ChangeAnimation(7, false, 30);

	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //�ҋ@��Ԃֈڍs
	}
}

void CXEnemy::Death()
{
	ChangeAnimation(8, false, 30);
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//����̐e�������̎��̓��^�[��
	if (o->Parent() == this)return;

	if (o->Type() == CCollider::ECAPSUL && m->Type() == CCollider::ECAPSUL)
	{
		CVector adjust;//�����p�x�N�g��
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::CollisionCapsule(m,o, &adjust)) {
			//����̐e�̃^�O���v���C���[
			if (o->Parent()->Tag() == EPLAYER)
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();
			}
		}

	}

}

//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CXEnemy* CXEnemy::GetInstance()
{
	return mpEnemyInstance;
}
//�U���̓����蔻����擾����
bool CXEnemy::GetIsHit()
{
	return mIsHit; //�U���̓����蔻���Ԃ�
}

//�v���C���[�̏�Ԃ��擾����
CXEnemy::EEnemyState CXEnemy::GetState()
{
	return mState;
}
	

