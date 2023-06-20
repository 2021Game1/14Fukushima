#include "CCamera.h"
#include "CInput.h"
#include"CXPlayer.h"
#include"CXEnemy.h"
#include "CTaskManager.h"
#include "CTable.h"
#include <math.h>
//カメラの外部変数
CCamera Camera;
CCamera* CCamera::mpCameraInstance;

//外部クラスから参照できるようの関数
//カメラのインスタンス
CCamera* CCamera::Instance()
{
	return mpCameraInstance;
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
	CTaskManager::Get()->Add(this);//追加する
	mpCameraInstance = this;
}

//Init処理
//一度しか動かさない処理
void CCamera::Init()
{
	int viewport[CAMERA_VIEWPORT];
	/* 現在のビューポートを保存しておく */
	glGetIntegerv(GL_VIEWPORT, viewport);
	mScreenWidth = viewport[CAMERA_VIEWPORT_WIDTH]; //幅を取得
	mScreenHeight = viewport[CAMERA_VIEWPORT_HEIGHT]; //高さを取得
	//プロジェクション行列の取得
	glGetFloatv(GL_PROJECTION_MATRIX, mProjection.M());

	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(mCamera_Point_View_X, mCamera_Point_View_Y, mCamera_Point_View_Z);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(mCamera_Point_Installation_X, mCamera_Point_Installation_Y, mCamera_Point_Installation_Z);

	//カメラクラスの設定
	Set(e, c, u);
}
//線形補完処理
float CCamera::mLerp(float start, float point, float rate)
{
	return start + point * (point * rate);
}
//HPゲージ用の線形補完処理
float CCamera::mHpLerp(float start, float point, float rate)
{
	return start + rate * (point - start);
}
//ターゲットを設定
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
	mCameraMoveX = (float)(mOldMouseX - mMouseX);
	mCameraMoveY = (float)(mOldMouseY - mMouseY);
	//マウスカーソルが動いた方向にカメラの原点をあわせる
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


	//カメラの位置座標設定
	mPos.X(mTarget.X() + (sinf(mAngleX)) * (mDist * sinf(mAngleY)));
	mPos.Y(mTarget.Y() + cosf(mAngleY) * mDist * sinf(mAngleY));
	mPos.Z(mTarget.Z() + (cosf(mAngleX)) * (mDist * sinf(mAngleY)));
	//カメラのターゲット設定
	mCenter = mTarget;
	//カメラのY座標の高さ調整
	mCenter.Y(mCenter.Y() + mCamera_Point_Herd_Adjust);
	//カメラの位置をカメラ視点に格納
	mEye = mPos;

	//線コライダセット
	mColliderLine.Set(this, nullptr, mEye, mCenter);
	//リセット
	CInput::InputReset();
}

//マトリックスの取得
CMatrix CCamera::GetMat() {
	return mMatrix;
}

//アングルXを絶対値に変換してから返す
float CCamera::GetInAngleX()
{
	return fabsf(mAngleX);
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
	mDist = CAMERA_DEF_DIST;
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
	//逆行列作成
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			inverse.M(i, j, mMatrix.M(j, i));
		}
	}
	//ビルボードの逆行列設定
	CBillBoard::ModelViewInverse(&inverse);
}

void CCamera::CameraAngleChange() {
	mDist = CAMERA_DEF_DIST_CHANGE;
}

void CCamera::CameraAngleDefault() {
	mDist = CAMERA_DEF_DIST;
}

//当たり判定
void CCamera::Collision(CCollider* m, CCollider* o) {
	//相手のコライダが三角コライダの時
	if (o->CCollider::Type() == CCollider::EType::ETRIANGLE) {
		CVector adjust;//調整用ベクトル
		if (CCollider::CollisionTriangleLine(o, m, &adjust)) {
			//マップ等に衝突すると、視点をプレイヤーに近づく
			mEye = mEye + adjust;
			mColliderLine.Set(this, nullptr, mEye, mCenter);
		}
	}
}

//タスクコリジョンに追加
void CCamera::TaskCollision()
{
	CCollisionManager::Get()->Collision(&mColliderLine, COLLISIONRANGE);
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
	screen->X((mCamera_Screen_Pos_X + screen_pos.X()) * mScreenWidth * mCamera_Screen_Width);
	screen->Y((mCamera_Screen_Pos_Y + screen_pos.Y()) * mScreenHeight * mCamera_Screen_Height);
	screen->Z(screen_pos.Z());

	return true;
}









