#include"CSceneScreen.h"

#include"CTexture.h"



//スクリーンのポインタ
CSceneScreen* CSceneScreen::spInstance = nullptr;

CSceneScreen::CSceneScreen()
{
	Screen.Load("screen.tga");
	spInstance = this;
	w = 510;
	h = 800;
	mTag = ESCREEN;
}

void CSceneScreen::Update()
{
	
	y += speed;
		if (y == -1200)
			y = 1736;
}

void CSceneScreen::Render()
{
	if (mEnabled)
	{
		CRectangle::Render(Screen, 0, 255, 255, 0);
	}
		
	
	

}

