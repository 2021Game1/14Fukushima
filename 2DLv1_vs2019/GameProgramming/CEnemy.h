#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"
#include "CEnemyData.h"

class CEnemy : public CRectangle {
public:

	//	bool mEnabled;	//有効フラグ

	//CBullet EBullet[20];
	int mFx,mFy;
	CEnemy();
	void Update();
	bool Collision(const CRectangle& r);
	void Render();
	int mFireCount;
	//36
	void Collision(CRectangle* i, CRectangle* y);
	

	
	

};
#endif
