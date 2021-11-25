#ifndef CBOSSENEMY_H
#define CBOSSENEMY_H

#include "CRectangle.h"
#include "CBullet.h"
#include <time.h>
#include "CSceneGame.h"
#include "CPlayer.h"

class CBossEnemy : public CRectangle {
public:

	int mFx, mFy;
	//	bool mEnabled;	//有効フラグ
	int mBossFireCount;
	static int CBossEnemyLife;
	static CBossEnemy* spInstance;
	void Update();
	bool Collision(CRectangle& r);
	void Render();
	//36
	void Collision(CRectangle* i, CRectangle* y);
	CBossEnemy();


};
#endif //

