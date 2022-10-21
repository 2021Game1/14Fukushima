#include"CXPlayer.h"
#include"CSceneGame.h"
#include "CCamera.h"
#define GRAVITY 0.1f//�d��


CXPlayer* CXPlayer::mpPlayerInstance;
//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayerInstance;
}

//�R���C�_������
CXPlayer::CXPlayer()
	:mColSphereBody(this,nullptr,CVector(),0.5)
	,mColSphereHead(this,nullptr,CVector(0.0f,5.0f,-3.0f),0.5f)
	,mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
	,mSpeed(SPEED_DEFAULT)
{
	mTag = EPLAYER;
	//������Ԃ�ݒ�
	mState = EIDLE;	//�ҋ@���
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.Matrix(&mpCombinedMatrix[9]);
	mColSphereHead.Matrix(&mpCombinedMatrix[12]);
	mColSphereSword.Matrix(&mpCombinedMatrix[22]);

}
void CXPlayer::Update() {
	CSceneGame* tSceneGame = CSceneGame::GetInstance();

	//��Ԃ𔻕�
	switch (mState) {
	case EIDLE:	//�ҋ@���
		Idle();	//�ҋ@�������Ă�
		break;

	case EATTACK_1:	//�U��1��Ԃ̎�
		Attack_1();	//�U��1�̏������Ă�
		break;

	//case EATTACK_2:	//�U��2��Ԃ̎�
	//	Attack_2();	//�U��2�̏������Ă�
	//	break;

	//case EATTACK_3:	//�U��3��Ԃ̎�
	//	Attack_3();	//�U��3�̏������Ă�
		break;

	case EMOVE:	//�ړ����
		Move();	//�ړ���Ԃ̏������Ă�
		break;

	//case EDASH:	//�_�b�V�����
	//	Dash();	//�_�b�V����Ԃ̏������Ă�
	//	break;

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

	CXCharacter::Update();
}

void CXPlayer::Idle() 
{
	ChangeAnimation(1, true, 60);//�ҋ@���[�V����

	//���N���b�N�ōU��
	if (CKey::Once(VK_LBUTTON)) {
		mState = EATTACK_1;
	}
	//WASD�L�[�������ƈړ��ֈڍs
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mState = EMOVE;
	}
}

//�ړ�����
void CXPlayer::Move()
{
	//WASD�L�[�������ƈړ�
	if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		MoveCamera(); //�J��������ɂ����ړ��������Ă�
	}
}

//�U��1����
void CXPlayer::Attack_1()
{
}

//���S����
void CXPlayer::Death()
{
	ChangeAnimation(11, false, 50);	//�|���A�j���[�V����
}

//�K�[�h
void CXPlayer::Guard()
{

}

//�J��������ɂ����ړ�����
void CXPlayer::MoveCamera()
{
	//�J�������_�ړ��@�ʏ̖��o�ړ�
	//�J�����̍��E�ƑO��̃x�N�g�����擾
	mSideVec = Camera.GetMat().GetXVec();
	mFrontVec = Camera.GetMat().GetZVec();
	//�����ړ��̓J�b�g����
	mSideVec.mY = 0.0f;
	mFrontVec.mY = 0.0f;
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

	//�ړ��ʐ��K���@��������Ȃ��Ǝ΂߈ړ��������Ȃ��Ă��܂��̂Œ���
	//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
	mMoveDir = mMoveDir.Normalize();
	mMoveDirKeep = mMoveDir;	//MoveDir�ۑ�
	mMove = mMoveDir * mSpeed;	//�ړ��ʂ�ݒ�
}

//�m�b�N�o�b�N����
void CXPlayer::KnockBack() 
{
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
	}
	}
}