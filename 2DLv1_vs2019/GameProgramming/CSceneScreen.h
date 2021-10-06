#ifndef CSCENESCREEN_H
#define CSCENESCREEN_H

#include "CRectangle.h"



class CSceneScreen : public CRectangle {
public:
	int mSy; //Y軸方向への背景の移動 -1 下方向への移動 0 移動しない 1 上方向への移動
	static CSceneScreen* spInstance;
	void Update();
	void Render();
	CSceneScreen();
};
#endif

