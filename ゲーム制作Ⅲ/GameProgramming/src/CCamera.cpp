#include "CCamera.h"
#include "CInput.h"
#include"CXPlayer.h"
#include "CTaskManager.h"
//�J�����̊O���ϐ�
CCamera Camera;
CCamera* CCamera::mpCameraInstance;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WIN_CENTRAL_X WINDOW_WIDTH/2 //��ʂ̒����iX���j
#define WIN_CENTRAL_Y WINDOW_HEIGHT/2 //��ʂ̒��� �iY���j


const CVector& CCamera::Eye() const
{
	return mEye;
}

void CCamera::Update() {



	/*
	oldMouseX = mouseX;
	oldMouseY = mouseY;
	*/
	CInput::InputReset();
	
}



void CCamera::Set(const CVector& eye, const CVector& center,
	const CVector& up) {
	mEye = eye;
	mCenter = center;
	mUp = up;
}

void CCamera::Render() {
	//gluLookAt(mEye.mX, mEye.mY, mEye.mZ,
	//	mCenter.mX, mCenter.mY, mCenter.mZ,
	//	mUp.mX, mUp.mY, mUp.mZ);
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());

	//�J�����s��i�[
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.M());
}

CCamera::CCamera()

{
//�D��x��ݒ�
mPriority = 100;
CTaskManager::Get()->Remove(this);//
CTaskManager::Get()->Add(this);//�ǉ�����
mpCameraInstance = this;
}

void CCamera::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ELINE: {//���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			if (CCollider::CollisionTriangleLine(o, m, &adjust)) {
				//�}�b�v���ɏՓ˂���ƁA���_���v���C���[�ɋ߂Â�
				mEye += (adjust + adjust.Normalize() * 0.5f);
				mColliderLine.Set(this, nullptr, mEye, mCenter);
			}
		}

	}
	}

}