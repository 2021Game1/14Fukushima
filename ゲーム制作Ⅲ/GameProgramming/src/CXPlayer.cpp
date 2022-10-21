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
{
	mTag = EPLAYER;
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
	if (CKey::Once(' ')) {
		ChangeAnimation(3, false, 30);
	}
	else if (IsAnimationFinished() && mAnimationIndex == 3) {
		ChangeAnimation(4, false, 30);
	}
	if (IsAnimationFinished())
	{
		ChangeAnimation(0, true, 60);
	}


	if (mAnimationIndex == 1 || mAnimationIndex == 0)
	{
		//W�L�[���͂őO�i
		if (CKey::Push('W')) {
			mPosition = mPosition + (mMatrixRotate.VectorZ() * 0.1f);
			ChangeAnimation(0, true, 60);

		}
		else if (mAnimationIndex == 1)
		{
			ChangeAnimation(1, true, 60);
		}
		//A�L�[�������ƂQ�x��]
		if (CKey::Push('A')) {
			mRotation = mRotation + (mMatrixRotate.VectorY() * 2.0f);
		}
		//D�L�[�������ƂQ�x��]
		if (CKey::Push('D')) {
			mRotation = mRotation - (mMatrixRotate.VectorY() * 2.0f);
		}
	}


	CXCharacter::Update();
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