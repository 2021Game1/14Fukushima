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




CBackground::CBackground()
:m_BackgroundDrawCount(0)
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
		if (m_BackgroundDrawCount <= 8) {
			CRectangle::Render(mpBackground1, BACKGROUND_TOP, BACKGROUND_W, BACKGROUND_H, BACKGROUND_TOP);
		}
		if (m_BackgroundDrawCount >= 8 && m_BackgroundDrawCount <= 16) {
			CRectangle::Render(mpBackground2, BACKGROUND_TOP, BACKGROUND_W, BACKGROUND_H, BACKGROUND_TOP);
		}
		if (m_BackgroundDrawCount >= 16 && m_BackgroundDrawCount <= 24) {
			CRectangle::Render(mpBackground3, BACKGROUND_TOP, BACKGROUND_W, BACKGROUND_H, BACKGROUND_TOP);
		}
		if (m_BackgroundDrawCount >= 24 && m_BackgroundDrawCount < 25) {
			CRectangle::Render(mpBackground4, BACKGROUND_TOP, BACKGROUND_W, BACKGROUND_H, BACKGROUND_TOP);
		}
	}
}
//”wŒi‚Ìƒ|ƒCƒ“ƒ^
CBackground2* CBackground2::spInstance = nullptr;

CBackground2::CBackground2()
:m_BackgroundDrawCount(0)
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
	if (m_BackgroundDrawCount <= 24) {
		if (x == -BACKGROUND2_W) {
			x = BACKGROUND2_W;
			m_BackgroundDrawCount += 1;
		}
	}
}

void CBackground2::Render()
{
	if (mEnabled)
	{
		if (m_BackgroundDrawCount <= 16) {
			CRectangle::Render(mpBackground5, BACKGROUND_TOP, BACKGROUND2_W, BACKGROUND_H, BACKGROUND_TOP1);
		}
		if (m_BackgroundDrawCount >= 16 && m_BackgroundDrawCount <= 24) {
			CRectangle::Render(mpBackground6, BACKGROUND_TOP, BACKGROUND_W, BACKGROUND_H, BACKGROUND_TOP);
			
		}
	}
}

//”wŒi‚Ìƒ|ƒCƒ“ƒ^
CBackground3* CBackground3::spInstance = nullptr;

CBackground3::CBackground3()
:m_BackgroundDrawCount(0)
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
	if (m_BackgroundDrawCount <= 24) {
		if (x == -BACKGROUND2_W) {
			x = BACKGROUND2_W;
		}
	}

}

void CBackground3::Render()
{
	if (mEnabled)
	{
		if (m_BackgroundDrawCount <= 16) {
			CRectangle::Render(mpBackground7, BACKGROUND_TOP, BACKGROUND2_W, BACKGROUND_H, BACKGROUND_TOP1);
		}
		if (m_BackgroundDrawCount >= 16 && m_BackgroundDrawCount <= 24) {
			CRectangle::Render(mpBackground8, BACKGROUND_TOP, BACKGROUND_W, BACKGROUND_H, BACKGROUND_TOP);
		}

	}
}






