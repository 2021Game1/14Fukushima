#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"
#include "CEnemyData.h"

 

class CEnemy : public CRectangle{
public:
	int mFx, mFy;
	//	bool mEnabled;	//有効フラグ
	

	void Update();
	bool Collision(const CRectangle& r);
	void Render();
	//36
	void Collision(CRectangle* i, CRectangle* y);

	CEnemy();

	
	

};
#endif
