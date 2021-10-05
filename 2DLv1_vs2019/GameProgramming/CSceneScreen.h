#ifndef CSCENESCREEN_H
#define CSCENESCREEN_H

#include "CRectangle.h"

class CSceneScreen : public CRectangle {
public:
	CSceneScreen();
	static CSceneScreen* spInstance;
	
};
#endif

