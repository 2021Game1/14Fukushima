#include "CCamera.h"
#include "CInput.h"
#include"CXPlayer.h"
#include"CXEnemy.h"
#include "CTaskManager.h"
#include "CTable.h"
#include <math.h>
//�J�����̊O���ϐ�
CCamera Camera;
CCamera* CCamera::mpCameraInstance;

//�O���N���X����Q�Ƃł���悤�̊֐�
//�J�����̃C���X�^���X
CCamera* CCamera::Instance()
{
	return mpCameraInstance;
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
	, mScreenHeight(0.0f)
	, mScreenWidth(0.0f)
	, mCamera_Sensitivity(CAMERA_SENSITIVITY)
	, mCamera_Collide_Dist(CAMERA_COLLIDE_DIST)
	, mCamera_Delay_Rate(CAMERA_DELAY_RATE)
	, mCamera_Point_View_X(CAMERA_POINT_VIEW_X)
	, mCamera_Point_View_Y(CAMERA_POINT_VIEW_Y)
	, mCamera_Point_View_Z(CAMERA_POINT_VIEW_Z)
	, mCamera_Point_Herd_Adjust(CAMERA_POINT_HERD_ADJUST)
	, mCamera_Point_Installation_X(CAMERA_POINT_INSTALLATION_X)
	, mCamera_Point_Installation_Y(CAMERA_POINT_INSTALLATION_Y)
	, mCamera_Point_Installation_Z(CAMERA_POINT_INSTALLATION_Z)
	, mCamera_Screen_Pos_X(CAMERA_SCREEN_POS_X)
	, mCamera_Screen_Pos_Y(CAMERA_SCREEN_POS_Y)
	, mCamera_Screen_Width(CAMERA_SCREEN_WIDTH)
	, mCamera_Screen_Height(CAMERA_SCREEN_HEIGHT)
	, mCameraMoveX(NULL)
	, mCameraMoveY(NULL)
	, mCamera_Priority(CAMERA_PRIORITY)
{
	mPriority = mCamera_Priority;
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//�ǉ�����
	mpCameraInstance = this;
}

//Init����
//��x�����������Ȃ�����
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
	e = CVector(mCamera_Point_View_X, mCamera_Point_View_Y, mCamera_Point_View_Z);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(mCamera_Point_Installation_X, mCamera_Point_Installation_Y, mCamera_Point_Installation_Z);

	//�J�����N���X�̐ݒ�
	Set(e, c, u);
}
//���`�⊮����
float CCamera::mLerp(float start, float point, float rate)
{
	return start + point * (point * rate);
}
//HP�Q�[�W�p�̐��`�⊮����
float CCamera::mHpLerp(float start, float point, float rate)
{
	return start + rate * (point - start);
}
//�^�[�Q�b�g��ݒ�
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
	mCameraMoveX = (float)(mOldMouseX - mMouseX);
	mCameraMoveY = (float)(mOldMouseY - mMouseY);
	//�}�E�X�J�[�\���������������ɃJ�����̌��_�����킹��
	if (mSkip == false) {
		if (mCameraMoveX != mCamera_Sensitivity)mAngleX += (mCameraMoveX * mCamera_Sensitivity);
		mAngleX = mLerp(mAngleX, mAngleDelayX, mCamera_Delay_Rate);
	}
	mSkip = false;
	int X = WIN_CENTRAL_X;
	int Y = WIN_CENTRAL_Y;
	CInput::SetMousePosW(X, Y);
	mOldMouseX = X;
	mOldMousePosY = Y;


	//�J�����̈ʒu���W�ݒ�
	mPos.X(mTarget.X() + (sinf(mAngleX)) * (mDist * sinf(mAngleY)));
	mPos.Y(mTarget.Y() + cosf(mAngleY) * mDist * sinf(mAngleY));
	mPos.Z(mTarget.Z() + (cosf(mAngleX)) * (mDist * sinf(mAngleY)));
	//�J�����̃^�[�Q�b�g�ݒ�
	mCenter = mTarget;
	//�J������Y���W�̍�������
	mCenter.Y(mCenter.Y() + mCamera_Point_Herd_Adjust);
	//�J�����̈ʒu���J�������_�Ɋi�[
	mEye = mPos;

	//���R���C�_�Z�b�g
	mColliderLine.Set(this, nullptr, mEye, mCenter);
	//���Z�b�g
	CInput::InputReset();
}

//�}�g���b�N�X�̎擾
CMatrix CCamera::GetMat() {
	return mMatrix;
}

//�A���O��X���Βl�ɕϊ����Ă���Ԃ�
float CCamera::GetInAngleX()
{
	return fabsf(mAngleX);
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

void CCamera::CameraAngleChange() {
	mDist = CAMERA_DEF_DIST_CHANGE;
}

void CCamera::CameraAngleDefault() {
	mDist = CAMERA_DEF_DIST;
}

//�����蔻��
void CCamera::Collision(CCollider* m, CCollider* o) {
	//����̃R���C�_���O�p�R���C�_�̎�
	if (o->CCollider::Type() == CCollider::EType::ETRIANGLE) {
		CVector adjust;//�����p�x�N�g��
		if (CCollider::CollisionTriangleLine(o, m, &adjust)) {
			//�}�b�v���ɏՓ˂���ƁA���_���v���C���[�ɋ߂Â�
			mEye = mEye + adjust;
			mColliderLine.Set(this, nullptr, mEye, mCenter);
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
	screen->X((mCamera_Screen_Pos_X + screen_pos.X()) * mScreenWidth * mCamera_Screen_Width);
	screen->Y((mCamera_Screen_Pos_Y + screen_pos.Y()) * mScreenHeight * mCamera_Screen_Height);
	screen->Z(screen_pos.Z());

	return true;
}









