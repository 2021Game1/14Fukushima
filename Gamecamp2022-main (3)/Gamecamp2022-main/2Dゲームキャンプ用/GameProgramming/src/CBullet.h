#ifndef CBULLET_H
#define CBULLET_H

#include "CRectangle.h"
/*
CBullet
弾クラス
CRectangleクラスを継承する
親：CRectangleクラス
子：CBulletクラス
*/
class CBullet : public CRectangle {
public:
	//デフォルトコンストラクタ
	CBullet();
	int mFx, mFy;	//移動量
	int mEnemyTipeBul;//エネミーの弾の種類

	
private:
	int mPlayerBullertCnt = 0;
	int mPlayerBullert;
	int mMotionCnt = 0;
	int mLoopCnt = 0;
	//更新処理
	void Update();
	//描画処理
	void Render();
	//衝突処理
	void Collision(CRectangle* i, CRectangle* y);
};

#endif
