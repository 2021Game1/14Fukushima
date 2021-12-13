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
	//	bool mEnabled;	//—LŒøƒtƒ‰ƒO
	int mBossFireCount;
	static int mBossEnemyLife;
	int Count;
	int Hit;
	void Update();
	bool Collision(CRectangle& r);
	void Render();
	//36
	void Collision(CRectangle* i, CRectangle* y);
	CBossEnemy();


};
#endif //

