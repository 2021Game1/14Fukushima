#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"
#include "CSceneGame.h"

class CPlayer : public CRectangle {
public:
	static CPlayer* spInstance;
	int mFx, mFy;
	int FireCount;
	static int CPlayerLevel;
	CPlayer();
	void Update();
	void Render();
	//36
	void Collision(CRectangle *i, CRectangle *y);

	
};

#endif
