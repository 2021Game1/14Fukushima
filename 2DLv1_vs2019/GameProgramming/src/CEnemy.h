#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"
#include <time.h>
#include"CBossEnemy.h" 

class CEnemy : public CRectangle {
public:


	int mFx, mFy;
	//	bool mEnabled;	//�L���t���O
	int mFireCount;
	void Update();
	bool Collision(CRectangle& r);
	void Render();
	//36
	void Collision(CRectangle* i, CRectangle* y);


	CEnemy();




};

#endif
