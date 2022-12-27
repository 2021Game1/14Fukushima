#include "CCamera.h"
#include "CInput.h"
#include"CXPlayer.h"
#include"CXEnemy.h"
#include "CTaskManager.h"
//カメラの外部変数
CCamera Camera;
CCamera* CCamera::mpCameraInstance;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DELAY_RATE 0.005f				//カメラアングル移動時の遅延割合
#define WIN_CENTRAL_X WINDOW_WIDTH/2 //画面の中央（X軸）
#define WIN_CENTRAL_Y WINDOW_HEIGHT/2 //画面の中央 （Y軸）
#define TARGETLOOK_Y 0.9f			//ターゲット時のカメラ高さ
#define ROTATION_RATE 1.0f/15.0f	//回転させたい角度に対する回転する割合

//カメラのインスタンス
CCamera* CCamera::Instance()
{
	return mpCameraInstance;
}

void CCamera::Init()
{
	int viewport[4];
	/* 現在のビューポートを保存しておく */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[2]; //幅を取得
	mScreenHeight = viewport[3]; //高さを取得
	//プロジェクション行列の取得
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 6.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);

	//カメラクラスの設定
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
//カメラの視点を返す
const CVector& CCamera::Eye() const
{
	return mEye;
}

//カメラのアップデート
void CCamera::Update() {
	CInput::GetMousePosWin(&mMouseX, &mMouseY);
	float moveX = (float)(mOldMouseX - mMouseX);
	float moveY = (float)(mOldMouseY - mMouseY);
	//マウスカーソルが動いた方向にカメラの原点をあわせる
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

	//Y軸制限 0～3.14が180度範囲
	if (mAngleY < 0.05f) mAngleY = 0.05f;
	if (mAngleY > 1.51f) mAngleY = 1.51f;


	mPos.X(mTarget.X() + (sinf(mAngleX)) * (mDist * sinf(mAngleY)));
	mPos.Y(mTarget.Y() + cosf(mAngleY) * mDist);
	mPos.Z(mTarget.Z() + (cosf(mAngleX)) * (mDist * sinf(mAngleY)));

	mCenter = mTarget;
	mCenter.Y(mCenter.Y() + CAMERA_HEAD_ADJUST);
	mEye = mPos;

	//線コライダセット
	mColliderLine.Set(this, nullptr, mEye, mCenter);
	CInput::InputReset();
}
CMatrix CCamera::GetMat() {
	return mMatrix;
}

//カメラセット
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

//処理なし
void CCamera::Render() {		
}

//カメラ適用
void CCamera::Draw() {
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(),
		mCenter.X(), mCenter.Y(), mCenter.Z(),
		mUp.X(), mUp.Y(), mUp.Z());
	//モデルビュー行列の取得
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix.M());
}

//デフォルトコンストラクタ
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
//優先度を設定
mPriority = 100;
CTaskManager::Get()->Remove(this);//
CTaskManager::Get()->Add(this);//追加する
mpCameraInstance = this;
}

//当たり判定
void CCamera::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ELINE: {//線コライダ
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

//タスクコリジョンに追加
void CCamera::TaskCollision()
{
	CCollisionManager::Get()->Collision(&mColliderLine, COLLISIONRANGE);
}

//ターゲットになっている敵の方向へカメラを向かせる処理
void CCamera::TargetLook()
{
		//プレイヤーに敵からプレイヤーに伸びるベクトルを求める
		CVector pos = CXPlayer::GetInstance()->Position() - CXEnemy::GetInstance()->Position();
		//posのYは0.0にしておく
		pos.Y(0.0f);
		//ベクトルを正規化
		pos = pos.Normalize();
		//プレイヤーからの距離を設定
		pos = pos * DEF_CAMERA_DIST;
		//カメラを移動させたい位置を設定
		mPos = CXPlayer::GetInstance()->Position() + pos;

		//プレイヤーから現在のカメラの始点までのベクトル
		CVector vec1 = CXPlayer::GetInstance()->Position() - mEye;
		//プレイヤーからカメラを移動させたい位置までのベクトル
		CVector vec2 = CXPlayer::GetInstance()->Position() - mPos;
		//高さは0にする
		vec1.Y(0.0f);
		vec2.Y(0.0f);
		//ベクトルの長さをもとめる
		float len1 = vec1.Length();
		float len2 = vec2.Length();
		float dot = (vec1.X() * vec2.X()) + (vec1.Y() * vec2.Y()) + (vec1.Z() * vec2.Z());	//内積
		float cross = (vec1.Y() * vec2.Z() - vec1.Z() * vec2.Y(),vec1.Z() * vec2.X() - vec1.X()* vec2.Z(),vec1.X() * vec2.Y() - vec1.Y() *vec2.X());//外積
		float cos_sita = dot / (len1 * len2);	//コサインシータを求める
		mRotRad = acosf(cos_sita);	//回転させたい角度を設定
		//NaN判定
		if (isnan(mRotRad)) {
			mRotRad = 0.0f;
		}
		//外積で回転させる方向を判断
		if (cross > 0.0f) {
			//アングルXを減算、左方向へ回転
			mAngleX -= mLerp(0.0f, mRotRad, ROTATION_RATE);
		}
		else if (cross < 0.0f) {
			//アングルXを加算、右方向へ回転
			mAngleX += mLerp(0.0f, mRotRad, ROTATION_RATE);
		}
		//アングルYを変更
		mAngleY = mLerp(mAngleY, TARGETLOOK_Y, 0.1f);

	//アングル遅延の値を合わせておく
	mAngleDelayX = mAngleX;
	mAngleDelayY = mAngleY;
}

//ワールド座標をスクリーン座標へ変換する
//WorldToScreen(スクリーン座標, ワールド座標)
bool CCamera::WorldToScreen(CVector* screen, const CVector& world)
{
	//座標変換
	CVector modelview_pos = world * mMatrix;
	CVector screen_pos = modelview_pos * mProjection;

	//画面外なのでリターン
	if (modelview_pos.Z() >= 0.0f) {
		return false;
	}
	//座標調整
	screen_pos = screen_pos * (1.0f / -modelview_pos.Z());

	//スクリーン変換
	screen->X((1.0f + screen_pos.X()) * mScreenWidth * 0.5f);
	screen->Y((1.0f + screen_pos.Y()) * mScreenHeight * 0.5f);
	screen->Z(screen_pos.Z());

	return true;
}









