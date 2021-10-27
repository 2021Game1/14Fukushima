#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"
#include "CEnemyData.h"

extern 

class CEnemy : public CRectangle{
public:

	

	int mFx, mFy;
	//	bool mEnabled;	//—LŒøƒtƒ‰ƒO
	
	//CBullet EBullet[20];
	
	void Update();
	bool Collision(const CRectangle& r);
	void Render();
	//36
	void Collision(CRectangle* i, CRectangle* y);

	CEnemy();
	
	
	
	
	

};
#endif
