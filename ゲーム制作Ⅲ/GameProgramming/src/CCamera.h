#ifndef CCAMERA_H
#define CCAMERA_H
#include "CInput.h"
#include "CVector.h"
#include "CCharacter.h"
#include "CColliderLine.h"
#include "CCollisionManager.h"

//カメラの描画範囲
#define WINDOW_WIDTH 800				//ゲーム画面の描画範囲幅設定
#define WINDOW_FIRST_WIDTH 0			//ゲーム画面の描画し始める範囲幅設定
#define WINDOW_HEIGHT 600				//ゲーム画面の描画範囲高さ設定
#define WINDOW_FIRST_HEIGHT 0				//ゲーム画面の描画し始める範囲高さ設定

//カメラの視点描画設定
#define CAMERA_VIEWPORT 4				//現在のカメラ全体のビューポート初期設定
#define CAMERA_VIEWPORT_WIDTH 2			//現在のカメラのビューポートの幅設定
#define CAMERA_VIEWPORT_HEIGHT 3		//現在のカメラのビューポートの高さ設定

//カメラの距離設定
#define CAMERA_DEF_DIST 4.0f	//カメラの距離設定
//カメラの距離設定変更
#define CAMERA_DEF_DIST_CHANGE 8.0 //カメラの距離設定変更

//カメラ操作時のマウス設定
#define WIN_CENTRAL_X WINDOW_WIDTH/2 //画面の中央（X軸）
#define WIN_CENTRAL_Y WINDOW_HEIGHT/2 //画面の中央 （Y軸）
#define ROTATION_RATE 1.0f/15.0f	//回転させたい角度に対する回転する割合

#define CAMERA_PRIORITY 100
#define CAMERA_SENSITIVITY 0.0002f
#define CAMERA_COLLIDE_DIST 0.05f
#define CAMERA_DELAY_RATE 0.003f
#define CAMERA_POINT_VIEW_X 1.0f
#define CAMERA_POINT_VIEW_Y 6.0f
#define CAMERA_POINT_VIEW_Z 10.0f
#define CAMERA_POINT_HERD_ADJUST 2.0f
#define CAMERA_POINT_INSTALLATION_X 0.0f
#define CAMERA_POINT_INSTALLATION_Y 1.0f
#define CAMERA_POINT_INSTALLATION_Z 0.0f
#define CAMERA_SCREEN_POS_X 1.0f
#define CAMERA_SCREEN_POS_Y 1.0f
#define CAMERA_SCREEN_WIDTH 0.5f
#define CAMERA_SCREEN_HEIGHT 0.5f

/*
カメラクラス
*/
class CCamera : public CCharacter{
public:
	CCamera();
	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);	
	//カメラのアングル変更設定
	void CameraAngleChange();
	//カメラのアングルデフォルト設定
	void CameraAngleDefault();
	//カメラのターゲット設定
	void SetTarget(const CVector& target);
	//一度しか更新しない
	void Init();
	//カメラ更新
	void Update();

	//処理をしないRender
	void Render();
	//カメラ描画
	void Draw();
	//当たり判定
	void Collision(CCollider* m, CCollider* o);
	//線形補間
	float mLerp(float start, float point, float rate);
	//HPの線形補間
	float mHpLerp(float start, float point, float rate);
	//コリジョンマネージャ追加処理
	void TaskCollision();
	//インスタンスの取得
	static CCamera* Instance();
	//ベクトル取得
	CMatrix GetMat();
	//視点座標の取得
	const CVector& Eye() const;
	//ワールド座標をスクリーン座標へ変換する
	//WorldToScreen(スクリーン座標, ワールド座標)
	bool WorldToScreen(CVector* screen, const CVector& world);

private:
	//描画優先度
	int mCamera_Priority;
	//カメラの感度設定
	float mCamera_Sensitivity;
	//当たり判定の距離
	float mCamera_Collide_Dist;
	//カメラの遅延設定
	float mCamera_Delay_Rate;
	//カメラの描画位置X座標
	float mCamera_Point_View_X;
	//カメラの描画位置Y座標
	float mCamera_Point_View_Y;
	//カメラの描画位置Z座標
	float mCamera_Point_View_Z;
	//カメラの高さ調整
	float mCamera_Point_Herd_Adjust;
	//カメラの上方向X座標設定
	float mCamera_Point_Installation_X;
	//カメラの上方向Y座標設定
	float mCamera_Point_Installation_Y;
	//カメラの上方向Z座標設定
	float mCamera_Point_Installation_Z;
	//カメラのスクリーンX座標設定
	float mCamera_Screen_Pos_X;
	//カメラのスクリーンY座標設定
	float mCamera_Screen_Pos_Y;
	//カメラのスクリーン幅設定
	float mCamera_Screen_Width;
	//カメラのスクリーン高さ設定
	float mCamera_Screen_Height;


	CVector mRotation;//回転
	CVector mEye;//視点
	CVector mCenter;//注視点
	CVector mUp;//上方向
	int mScreenWidth; //幅
	int mScreenHeight; //高さ
	CMatrix mProjection; //プロジェクション行列
	CMatrix inverse; //モデルビュー行列の逆行列


	//コライダ
	CColliderLine mColliderLine;
	//重複するがカメラ制御用
	CVector mPos;		//位置
	CVector mTarget;	//ターゲット
	CVector mZoom;		//ズーム用
	float	mDist;	//距離
	float mRotRad;		//回転させたい角度
	float mOldMousePosX, mOldMousePosY;

	bool mSkip;
	CTransform mTransform; //回転縮小用行列
	

	float	mAngleX;	//アングル
	float	mAngleY;	//アングル
	//アングル遅延用、通常モード時に使用
	float mAngleDelayX;
	float mAngleDelayY;
	//マウスの座標保持用
	int mOldMouseX, mOldMouseY; //以前の座標
	int mMouseX, mMouseY;		//現在の座標
		//staticでポインタを作る
	static CCamera* mpCameraInstance;


};

//カメラの外部参照
extern CCamera Camera;
#endif
