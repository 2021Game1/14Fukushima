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

void CCamera::Init()
{
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����N���X�̐ݒ�
	Set(e, c, u);
}

const CVector& CCamera::Eye() const
{
	return mEye;
}

void CCamera::Update() {
	static int oldMouseX(0), oldMouseY(0);
	int mouseX(0), mouseY(0);
	CInput::GetMousePosWin(&mouseX, &mouseY);

	float moveX = (float)(oldMouseX - mouseX);
	float moveY = (float)(oldMouseY - mouseY);

	//�}�E�X����ʒ����ɌŒ�
	int X = WIN_CENTRAL_X;
	int Y = WIN_CENTRAL_Y;
	CInput::SetMousePosW(X, Y);
	oldMouseX = X;
	oldMouseY = Y;


	/*
	oldMouseX = mouseX;
	oldMouseY = mouseY;
	*/
	if (CKey::Push(VK_RIGHT)) {
		mAngleX += 0.1f;
	}
	if (CKey::Push(VK_LEFT)) {
		mAngleX -= 0.1f;
	}
	if (CKey::Push(VK_UP)) {
		mAngleY += 0.01f;
	}
	if (CKey::Push(VK_DOWN)) {
		mAngleY -= 0.01f;
	}

	//Y������ 0�`3.14��180�x�͈�
	if (mAngleY < 0.05f) mAngleY = 0.05f;
	if (mAngleY > 1.51f) mAngleY = 1.51f;
	if (mAngleDelayY < 0.05f) mAngleDelayY = 0.05f;
	if (mAngleDelayY > 1.51f) mAngleDelayY = 1.51f;

	mPos.mX = mTarget.mX + (sinf(mAngleX)) * (mDist * sinf(mAngleY));
	mPos.mY = mTarget.mY + cosf(mAngleY) * mDist;
	mPos.mZ = mTarget.mZ + (cosf(mAngleX)) * (mDist * sinf(mAngleY));

	mCenter = mTarget;
	mCenter.mY += CAMERA_HEAD_ADJUST;//����␳
	mEye = mPos;

	//���R���C�_�Z�b�g
	mColliderLine.Set(this, nullptr, mEye, mCenter);
	CInput::InputReset();
	
}

CMatrix CCamera::GetMat() {
	return mMatrix;
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