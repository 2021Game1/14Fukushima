#ifndef CSCENESCREEN_H
#define CSCENESCREEN_H

#include "CRectangle.h"



class CSceneScreen : public CRectangle {
public:
	CTexture Screen;
	int mSy; //Y�������ւ̔w�i�̈ړ� -1 �������ւ̈ړ� 0 �ړ����Ȃ� 1 ������ւ̈ړ�
	static CSceneScreen* spInstance;
	void Update();
	void Render();
	CSceneScreen();
};
#endif

