#include"CSceneScreen.h"

CSceneScreen* CSceneScreen::spInstance = nullptr;

CSceneScreen::CSceneScreen()

{
	mTag = EScreen;
	spInstance = this;
}

