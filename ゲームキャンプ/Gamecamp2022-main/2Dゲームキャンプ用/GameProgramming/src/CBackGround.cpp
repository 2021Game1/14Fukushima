#include"CBackground.h"

#include"CTexture.h"

#define BACKGROUND1_W 960
#define BACKGROUND1_H 590
#define BACKGROUND2_H 490

#define BACKGROUND_W 1920
#define BACKGROUND2_W 3840
#define BACKGROUND_H 1080
#define BACKGROUND_TOP 0
#define BACKGROUND_TOP1 10

extern CTexture mpBackground1;
extern CTexture mpBackground2;
extern CTexture mpBackground3;
extern CTexture mpBackground4;
extern CTexture mpBackground5;
extern CTexture mpBackground6;
extern CTexture mpBackground7;
extern CTexture mpBackground8;
extern CTexture mpBackground20;




CBackground::CBackground()
{
	w = BACKGROUND1_W;
	h = BACKGROUND1_H;
	mTag = EBUCKGROUND;
	mPriority = 11;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CBackground::Render()
{
	if (mEnabled)
	{
			CRectangle::Render(mpBackground1, BACKGROUND_TOP, BACKGROUND_W, BACKGROUND_H, BACKGROUND_TOP);
	}
}
//”wŒi‚Ìƒ|ƒCƒ“ƒ^
CBackground2* CBackground2::spInstance = nullptr;

CBackground2::CBackground2()
{

	spInstance = this;
	w = BACKGROUND_W;
	h = BACKGROUND1_H;
	mTag = EBUCKGROUND;
	mPriority = 10;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CBackground2::Update()
{
	
	x += speed;
	
		if (x == -BACKGROUND2_W) {
			mEnabled = false;
		}
}

void CBackground2::Render()
{
	if (mEnabled)
	{
		CRectangle::Render(mpBackground5, BACKGROUND_TOP, BACKGROUND2_W, BACKGROUND_H, BACKGROUND_TOP1);
	}

}

//”wŒi‚Ìƒ|ƒCƒ“ƒ^
CBackground3* CBackground3::spInstance = nullptr;

CBackground3::CBackground3()
{

	spInstance = this;
	w = BACKGROUND_W;
	h = BACKGROUND2_H;
	mTag = EBUCKGROUND;
	mPriority = 9;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CBackground3::Update()
{

	x += speed;
		if (x == -BACKGROUND2_W) {
			mEnabled = false;
		}

}

void CBackground3::Render()
{
	if (mEnabled)
	{
		CRectangle::Render(mpBackground7, BACKGROUND_TOP, BACKGROUND2_W, BACKGROUND_H, BACKGROUND_TOP1);
	}
}	

//”wŒi‚Ìƒ|ƒCƒ“ƒ^
CBackground4* CBackground4::spInstance = nullptr;

CBackground4::CBackground4()
{

	spInstance = this;
	w = BACKGROUND1_W;
	h = BACKGROUND1_H;
	mTag = EBUCKGROUND;
	mPriority = 1;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CBackground4::Update()
{

	x += speed;
	if (x == -BACKGROUND2_W) {
		mEnabled = false;
	}

}

void CBackground4::Render()
{
	if (mEnabled)
	{
		CRectangle::Render(mpBackground20, BACKGROUND_TOP1, BACKGROUND_W, BACKGROUND_H, BACKGROUND_TOP);
	}
}




