#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"


 

class CEnemy : public CRectangle{
public:

	int mFx, mFy;
	//	bool mEnabled;	//—LŒøƒtƒ‰ƒO
	int mFireCount;
	int val;
	static CEnemy* spInstance;
	void Update();
	bool Collision(CRectangle& r);
	void Render();
	//36
	void Collision(CRectangle* i, CRectangle* y);

	CEnemy();

	
	

};
#endif
