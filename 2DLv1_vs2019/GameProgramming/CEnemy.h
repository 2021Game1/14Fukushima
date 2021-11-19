#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"
#include"CItem.h"
#include <time.h>
 

class CEnemy : public CRectangle{
public:

	int item[5];
	int mFx, mFy;
	//	bool mEnabled;	//有効フラグ
	int mFireCount;
	int vel;
	static CEnemy* spInstance;
	void Update();
	bool Collision(CRectangle& r);
	void Render();
	//36
	void Collision(CRectangle* i, CRectangle* y);

	CEnemy();

	
	

};
#endif
