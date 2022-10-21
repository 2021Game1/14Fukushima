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