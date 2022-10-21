#include "CCamera.h"
#include "CInput.h"
#include"CXPlayer.h"
#include "CTaskManager.h"
//カメラの外部変数
CCamera Camera;
CCamera* CCamera::mpCameraInstance;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WIN_CENTRAL_X WINDOW_WIDTH/2 //画面の中央（X軸）
#define WIN_CENTRAL_Y WINDOW_HEIGHT/2 //画面の中央 （Y軸）

void CCamera::Init()
{
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 2.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);

	//カメラクラスの設定
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

	//マウスを画面中央に固定
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

	//Y軸制限 0～3.14が180度範囲
	if (mAngleY < 0.05f) mAngleY = 0.05f;
	if (mAngleY > 1.51f) mAngleY = 1.51f;
	if (mAngleDelayY < 0.05f) mAngleDelayY = 0.05f;
	if (mAngleDelayY > 1.51f) mAngleDelayY = 1.51f;

	mPos.mX = mTarget.mX + (sinf(mAngleX)) * (mDist * sinf(mAngleY));
	mPos.mY = mTarget.mY + cosf(mAngleY) * mDist;
	mPos.mZ = mTarget.mZ + (cosf(mAngleX)) * (mDist * sinf(mAngleY));

	mCenter = mTarget;
	mCenter.mY += CAMERA_HEAD_ADJUST;//頭上補正
	mEye = mPos;

	//線コライダセット
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

	//カメラ行列格納
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.M());
}

CCamera::CCamera()

{
//優先度を設定
mPriority = 100;
CTaskManager::Get()->Remove(this);//
CTaskManager::Get()->Add(this);//追加する
mpCameraInstance = this;
}

void CCamera::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ELINE: {//球コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			if (CCollider::CollisionTriangleLine(o, m, &adjust)) {
				//マップ等に衝突すると、視点をプレイヤーに近づく
				mEye += (adjust + adjust.Normalize() * 0.5f);
				mColliderLine.Set(this, nullptr, mEye, mCenter);
			}
		}

	}
	}

}