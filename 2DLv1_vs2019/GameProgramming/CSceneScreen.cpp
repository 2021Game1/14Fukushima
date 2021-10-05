#include"CSceneScreen.h"

CSceneScreen* CSceneScreen::spInstance = nullptr;

CSceneScreen::CSceneScreen()
{
	mTag = EScreen;
	spInstance = this;
}

void CSceneScreen::Update()
{
	y += mSy;
}

void CSceneScreen::Render()
{

}
