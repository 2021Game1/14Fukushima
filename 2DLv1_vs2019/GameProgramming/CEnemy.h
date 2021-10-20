#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy : public CRectangle {
public:

	//	bool mEnabled;	//—LŒøƒtƒ‰ƒO

	//37	CBullet EBullet[20];

	CEnemy();
	void Update();
	bool Collision(const CRectangle& r);
	void Render();

	//36
	void Collision(CRectangle* i, CRectangle* y);

	

};
#endif
