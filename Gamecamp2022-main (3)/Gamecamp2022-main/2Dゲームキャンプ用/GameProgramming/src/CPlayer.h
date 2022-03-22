#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"
#include <assert.h>

class CPlayer : public CRectangle {
public:
	int mFx, mFy;
	//37
	
	CPlayer();


	//36

	int GetPlayerHP();

	static CPlayer* spInstance;

private:
	void Update();
	void Render();
	void Collision(const CRectangle& r);
	int mHp;
	/*
	Œ»İ‚È‚ñ‚Ìƒ‚[ƒVƒ‡ƒ“‚ğ‚µ‚Ä‚¢‚é‚©
	0 —§‚¿ŠG,1 ‘–‚é,2 ƒWƒƒƒ“ƒv,3 UŒ‚,4 ”í’e
	*/
	int mPlayerMotion;
	int mMotionCnt;
	int mLoopCnt;
	int mJumpFlag;
	int mJumpCnt;
	int FireCount;
	int mGRAVITY = -15;
	int mV = 75;

};

#endif
