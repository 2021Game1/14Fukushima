#include"CSceneScreen.h"

#include"CTexture.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

CSceneScreen* CSceneScreen::spInstance = nullptr;

CSceneScreen::CSceneScreen()
	:mSy(-0.5)
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
	CRectangle::Render(Texture,10,37,27,54);
}
