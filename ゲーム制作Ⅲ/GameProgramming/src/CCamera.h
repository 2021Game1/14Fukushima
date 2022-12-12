#ifndef CCAMERA_H
#define CCAMERA_H
#include "CInput.h"
#include "CVector.h"
#include "CCharacter.h"
#include "CColliderLine.h"


/*
カメラクラス
*/
#define DEF_CAMERA_DIST 8.0f
#define CAMERA_HEAD_ADJUST 2.0f	//注視点の高さ調整
class CCamera : public CCharacter{
public:
	//視点座標の取得
	const CVector& Eye() const;
	CCamera();
	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);
	void SetTarget(const CVector& target);
	void Init();
	//カメラ更新
	void Update();
	//カメラ適用
	void Render();
	//ベクトル取得
	CMatrix GetMat();
	//当たり判定
	void Collision(CCollider* m, CCollider* o);
	//線形補間
	float mLerp(float start, float point, float rate);
	//ターゲットへカメラを向かせる処理
	void TargetLook();
	//インスタンスの取得
	static CCamera* Instance();
	//ワールド座標をスクリーン座標へ変換する
	//WorldToScreen(スクリーン座標, ワールド座標)
	bool WorldToScreen(CVector* screen, const CVector& world);
private:
	CVector mRotation;//回転
	CVector mEye;//視点
	CVector mCenter;//注視点
	CVector mUp;//上方向
	int mScreenWidth; //幅
	int mScreenHeight; //高さ
	CMatrix mProjection; //プロジェクション行列
	CMatrix mModelView; //モデルビュー行列


	//コライダ
	CColliderLine mColliderLine;
	//重複するがカメラ制御用
	CVector mPos;		//位置
	CVector mTarget;	//ターゲット
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
