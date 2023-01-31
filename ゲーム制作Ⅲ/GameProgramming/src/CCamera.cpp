#include "CCamera.h"
#include "CInput.h"
#include"CXPlayer.h"
#include"CXEnemy.h"
#include "CTaskManager.h"
//�J�����̊O���ϐ�
CCamera Camera;
CCamera* CCamera::mpCameraInstance;

//�J�����̃C���X�^���X
CCamera* CCamera::Instance()
{
	return mpCameraInstance;
}

void CCamera::Init()
{
	int viewport[CAMERA_VIEWPORT];
	/* ���݂̃r���[�|�[�g��ۑ����Ă��� */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[CAMERA_VIEWPORT_WIDTH]; //�����擾
	mScreenHeight = viewport[CAMERA_VIEWPORT_HEIGHT]; //�������擾
	//�v���W�F�N�V�����s��̎擾
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(CAMERA_POINT_VIEW_X, CAMERA_POINT_VIEW_Y, CAMERA_POINT_VIEW_Z);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(CAMERA_POINT_INSTALLATION_X, CAMERA_POINT_INSTALLATION_Y, CAMERA_POINT_INSTALLATION_Z);

	//�J�����N���X�̐ݒ�
	Set(e, c, u);
}
float CCamera::mLerp(float start, float point, float rate)
{
	return start + point * (point * rate);
}
float CCamera::mHpLerp(float start, float point, float rate)
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
		if (moveX != CAMERA_SENSITIVITY)mAngleX += (moveX * CAMERA_SENSITIVITY);
		mAngleX = mLerp(mAngleX, mAngleDelayX, CAMERA_DELAY_RATE);
	}
	mSkip = false;
	int X = WIN_CENTRAL_X;
	int Y = WIN_CENTRAL_Y;
	CInput::SetMousePosW(X, Y);
	mOldMouseX = X;



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
	mDist = CAMERA_DEF_DIST;
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
				mEye += (adjust.Normalize() + adjust.Normalize() * CAMERA_COLLIDE_DIST);
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
	screen->X((CAMERA_SCREEN_POS_X + screen_pos.X()) * mScreenWidth * CAMERA_SCREEN_WIDTH);
	screen->Y((CAMERA_SCREEN_POS_Y + screen_pos.Y()) * mScreenHeight * CAMERA_SCREEN_HEIGHT);
	screen->Z(screen_pos.Z());

	return true;
}









