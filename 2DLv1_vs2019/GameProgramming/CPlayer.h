#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"

class CPlayer : public CRectangle {
public:
	int mFx, mFy;
	//37
	int FireCount;
	//�v���C���[���x��
	int mLevel;
	CPlayer();
	void Update();
	void Render();
	//36
	void Collision(CRectangle *i, CRectangle *y);

	
};

#endif
