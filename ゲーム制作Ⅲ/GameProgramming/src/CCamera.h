#ifndef CCAMERA_H
#define CCAMERA_H
#include "CInput.h"
#include "CVector.h"
#include "CCollider.h"
#include "CColliderLine.h"
#include "CCharacter.h"

/*
カメラクラス
*/
#define DEF_CAMERA_DIST 8.0f
#define CAMERA_HEAD_ADJUST 3.0f	//注視点の高さ調整
class CCamera : CCharacter{
public:
	//回転
	CVector mRotation;
	//視点座標の取得
	const CVector& Eye() const;
	CCamera();
	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);
	//カメラ更新
	void Update();
	//カメラ初期化
	void Init();
	//カメラ適用
	void Render();
	//ベクトル取得
	CMatrix GetMat();
	//当たり判定
	void Collision(CCollider* m, CCollider* o);
	//staticでポインタを作る
	static CCamera* mpCameraInstance;
	//視点
	CVector mEye;
	//上方向
	CVector mUp;
	//コライダ
	CColliderLine mColliderLine;
	//重複するがカメラ制御用
	CVector mCenter;	//注視点
	//重複するがカメラ制御用
	CVector mPos;		//位置
	CVector mTarget;	//ターゲット
	float	mAngleX;	//アングル
	float	mAngleY;	//アングル
	float	mDist;	//距離

private:
	//アングル遅延用、通常モード時に使用
	float mAngleDelayX;
	float mAngleDelayY;
};

//カメラの外部参照
extern CCamera Camera;
#endif
