#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy : public CRectangle {
public:

	//	bool mEnabled;	//有効フラグ

	//CBullet EBullet[20];
	int mFx,mFy;
	int mType;//敵の種類
	int mSype;//敵の弾の種類
	int mPattern;//敵の行動パターン
	int mShotpattrn;//敵の弾の発射パターン
	int mEnemytime;// 敵の出現時間
	int mBullettime;//敵の弾発射時間
	int x;//X座標
	int y;//Y座標
	int mFirecount;//弾の発射間隔
	int mItem;//アイテム
	CEnemy();
	void Update();
	bool Collision(const CRectangle& r);
	void Render();
	int mFireCount;
	//36
	void Collision(CRectangle* i, CRectangle* y);

	
	

};
#endif
