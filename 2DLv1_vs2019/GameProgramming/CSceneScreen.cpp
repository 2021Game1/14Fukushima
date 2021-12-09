#include"CSceneScreen.h"

#include"CTexture.h"



CSceneScreen* CSceneScreen::spInstance = nullptr;

CSceneScreen::CSceneScreen()
{
	Screen.Load("screen.tga");
	spInstance = this;
	w = 510;
	h = 800;
	
}

void CSceneScreen::Update()
{
	y += speed;
		if (y == -1200)
			y = 1736;
}

void CSceneScreen::Render()
{
	if (mTag == ESCREEN)
	{
		CRectangle::Render(Screen, 0, 255, 255, 0);
	}
	

}
