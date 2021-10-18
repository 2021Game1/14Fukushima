#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy : public CRectangle {
public:
	int mType;//敵の種類
	int mSype;//敵の弾の種類
	int mPattern;//敵の行動パターン
	int mShotpattrn;//敵の弾の発射パターン
	int mEnemytime;// 敵の出現時間
	int mFirecount;//敵の弾発射時間
	int x;//X座標
	int y;//Y座標
	int mBullettime;//弾のスピード
	int mItem;//アイテム
//	bool mEnabled;	//有効フラグ

//37	CBullet EBullet[20];
	
	CEnemy();
	void Update();
	bool Collision(const CRectangle &r);
	void Render();

	//36
	void Collision(CRectangle *i, CRectangle *y);
};

#endif
