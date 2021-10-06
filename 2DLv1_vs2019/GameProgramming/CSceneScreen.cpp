#include"CSceneScreen.h"

#include"CTexture.h"



CSceneScreen* CSceneScreen::spInstance = nullptr;

CSceneScreen::CSceneScreen()
	:mSy(-1.0f)
{
	mTag = EScreen;
	Screen.Load("screen.tga");
	spInstance = this;
}

void CSceneScreen::Update()
{
	y += mSy;
}

void CSceneScreen::Render()
{
	CRectangle::Render(Screen,0,255,255,0);

}
