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
#define DEF_CAMERA_HEAD_ADJUST 3.0f
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
	//カメラ適用
	void Render();
	//当たり判定
	void Collision(CCollider* m, CCollider* o);
	//staticでポインタを作る
	static CCamera* mpCameraInstance;
	//視点
	CVector mEye;
private:

	//上方向
	CVector mUp;
	//コライダ
	CColliderLine mColliderLine;
	//重複するがカメラ制御用
	CVector mCenter;	//注視点
};

//カメラの外部参照
extern CCamera Camera;
#endif
