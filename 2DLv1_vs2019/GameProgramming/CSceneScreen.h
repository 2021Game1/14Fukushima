#ifndef CSCENESCREEN_H
#define CSCENESCREEN_H

#include "CRectangle.h"



class CSceneScreen : public CRectangle {
public:
	CTexture Screen;
	int mSy; //Y²•ûŒü‚Ö‚Ì”wŒi‚ÌˆÚ“® -1 ‰º•ûŒü‚Ö‚ÌˆÚ“® 0 ˆÚ“®‚µ‚È‚¢ 1 ã•ûŒü‚Ö‚ÌˆÚ“®
	static CSceneScreen* spInstance;
	void Update();
	void Render();
	CSceneScreen();
};
#endif

