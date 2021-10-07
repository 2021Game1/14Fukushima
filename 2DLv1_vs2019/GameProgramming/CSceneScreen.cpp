#include"CSceneScreen.h"

#include"CTexture.h"



CSceneScreen* CSceneScreen::spInstance = nullptr;

CSceneScreen::CSceneScreen()
{
	mTag = EScreen;
	Screen.Load("screen.tga");
	spInstance = this;
	w = 510;
	h = 800;
}

void CSceneScreen::Update()
{
	y += speed;
}

void CSceneScreen::Render()
{
	CRectangle::Render(Screen,0,255,255,0);

}
