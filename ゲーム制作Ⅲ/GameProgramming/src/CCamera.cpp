#include "CCamera.h"
#include "CInput.h"
#include"CXPlayer.h"
#include"CXEnemy.h"
#include "CTaskManager.h"
//�J�����̊O���ϐ�
CCamera Camera;
CCamera* CCamera::mpCameraInstance;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DELAY_RATE 0.005f				//�J�����A���O���ړ����̒x������
#define WIN_CENTRAL_X WINDOW_WIDTH/2 //��ʂ̒����iX���j
#define WIN_CENTRAL_Y WINDOW_HEIGHT/2 //��ʂ̒��� �iY���j
#define TARGETLOOK_Y 0.9f			//�^�[�Q�b�g���̃J��������
#define ROTATION_RATE 1.0f/15.0f	//��]���������p�x�ɑ΂����]���銄��

//�J�����̃C���X�^���X
CCamera* CCamera::Instance()
{
	return mpCameraInstance;
}

void CCamera::Init()
{
	int viewport[4];
	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[2]; //�����擾
	mScreenHeight = viewport[3]; //�������擾
	//�v���W�F�N�V�����s��̎擾
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 6.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);

	//�J�����N���X�̐ݒ�
	Set(e, c, u);
}
float CCamera::mLerp(float start, float point, float rate)
{
	return start + rate * (point - start);

}
void CCamera::SetTarget(const CVector& target)
{
	mTarget = target;
}
//�J�����̎��_��Ԃ�
const CVector& CCamera::Eye() const
{
	return mEye;
}

//�J�����̃A�b�v�f�[�g
void CCamera::Update() {
	CInput::GetMousePosWin(&mMouseX, &mMouseY);
	float moveX = (float)(mOldMouseX - mMouseX);
	float moveY = (float)(mOldMouseY - mMouseY);
	//�}�E�X�J�[�\���������������ɃJ�����̌��_�����킹��
	if (mSkip == false) {
		if (moveX != 0) mAngleX += (moveX * 0.005f);
		if (moveY != 0) mAngleY += (moveY * 0.005f);
		mAngleX = mLerp(mAngleX, mAngleDelayX, DELAY_RATE);
		mAngleY = mLerp(mAngleY, mAngleDelayY, DELAY_RATE);
	}
	mSkip = false;
	int X = WIN_CENTRAL_X;
	int Y = WIN_CENTRAL_Y;
	CInput::SetMousePosW(X, Y);
	mOldMouseX = X;
	mOldMouseY = Y;

	//Y������ 0�`3.14��180�x�͈�
	if (mAngleY < 0.05f) mAngleY = 0.05f;
	if (mAngleY > 1.51f) mAngleY = 1.51f;


	mPos.X(mTarget.X() + (sinf(mAngleX)) * (mDist * sinf(mAngleY)));
	mPos.Y(mTarget.Y() + cosf(mAngleY) * mDist);
	mPos.Z(mTarget.Z() + (cosf(mAngleX)) * (mDist * sinf(mAngleY)));

	mCenter = mTarget;
	mCenter.Y(mCenter.Y() + CAMERA_HEAD_ADJUST);
	mEye = mPos;

	//���R���C�_�Z�b�g
	mColliderLine.Set(this, nullptr, mEye, mCenter);
	CInput::InputReset();
}

CMatrix CCamera::GetMat() {
	return mMatrix;
}

//�J�����Z�b�g
void CCamera::Set(const CVector& eye, const CVector& center,
	const CVector& up) {
	mEye = eye;
	mCenter = center;
	mUp = up;

	mPos = eye;
	mTarget = center;
	mAngleX = 0.0f;
	mAngleY = 1.0f;
	mDist = DEF_CAMERA_DIST;
	mAngleDelayX = mAngleX;
	mAngleDelayY = mAngleY;
}

//�����Ȃ�
void CCamera::Render() {		
}

//�J�����K�p
void CCamera::Draw() {
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
	//���f���r���[�s��̎擾
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.M());
	//�t�s��쐬
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			inverse.M(i, j, mMatrix.M(j, i));
		}
	}
	//�r���{�[�h�̋t�s��ݒ�
	CBillBoard::ModelViewInverse(&inverse);
}

//�f�t�H���g�R���X�g���N�^
CCamera::CCamera()
	:mSkip(true)
	, mAngleX(0.0f)
	, mAngleY(0.0f)
	, mDist(0.0f)
	, mOldMouseX(0)
	, mOldMouseY(0)
	, mMouseX(0)
	, mMouseY(0)
	, mAngleDelayX(0.0f)
	, mAngleDelayY(0.0f)
	, mRotRad(0.0f)
	, mOldMousePosX(0)
	, mOldMousePosY(0)
{
//�D��x��ݒ�
mPriority = 100;
CTaskManager::Get()->Remove(this);//
CTaskManager::Get()->Add(this);//�ǉ�����
mpCameraInstance = this;
}

//�����蔻��
void CCamera::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ELINE: {//���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			if (CCollider::CollisionTriangleLine(o, m, &adjust)) {
				//�}�b�v���ɏՓ˂���ƁA���_���v���C���[�ɋ߂Â�
				mEye += (adjust.Normalize() + adjust.Normalize() * 0.5f);
				mColliderLine.Set(this, nullptr, mEye, mCenter);
			}
		}
	}
	}

}

//�^�X�N�R���W�����ɒǉ�
void CCamera::TaskCollision()
{
	CCollisionManager::Get()->Collision(&mColliderLine, COLLISIONRANGE);
}



//���[���h���W���X�N���[�����W�֕ϊ�����
//WorldToScreen(�X�N���[�����W, ���[���h���W)
bool CCamera::WorldToScreen(CVector* screen, const CVector& world)
{
	//���W�ϊ�
	CVector modelview_pos = world * mMatrix;
	CVector screen_pos = modelview_pos * mProjection;

	//��ʊO�Ȃ̂Ń��^�[��
	if (modelview_pos.Z() >= 0.0f) {
		return false;
	}
	//���W����
	screen_pos = screen_pos * (1.0f / -modelview_pos.Z());

	//�X�N���[���ϊ�
	screen->X((1.0f + screen_pos.X()) * mScreenWidth * 0.5f);
	screen->Y((1.0f + screen_pos.Y()) * mScreenHeight * 0.5f);
	screen->Z(screen_pos.Z());

	return true;
}









