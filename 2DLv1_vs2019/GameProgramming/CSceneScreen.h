#ifndef CSCENESCREEN_H
#define CSCENESCREEN_H

#include "CRectangle.h"




class CSceneScreen : public CRectangle {
public:
	CTexture Screen;
	int speed;
	static CSceneScreen* spInstance;
	void Update();
	void Render();
	CSceneScreen();
	
};
#endif

