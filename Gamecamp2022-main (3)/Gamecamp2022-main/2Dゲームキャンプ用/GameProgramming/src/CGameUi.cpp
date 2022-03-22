#include "CGameUi.h"

extern CTexture Texture;
extern CTexture GameUI1;
extern CTexture GameUI2;

CScoreUi::CScoreUi()
{
	y = 0;
	x = -0;
	mScoreCnt = 0;
	mScoreUi = 0;
	//CTaskManager::Get()->Remove(this);
	//CTaskManager::Get()->Add(this);
}

void CScoreUi::Update()
{

}

void CScoreUi::Render()
{
	CRectangle::Render(GameUI1, mScoreCnt * 30, (mScoreCnt + 1) * 30, 30, 0);
}



CHpUi::CHpUi()
{
	
	mHpCnt = 5;
	mHpUi = 0;
	y = 500;
	h = 50;
	
	mEnabled = true;
	mTag = EUI;
	//mPriority = 7;
	//CTaskManager::Get()->Remove(this);
	//CTaskManager::Get()->Add(this);
}

void CHpUi::Update()
{
	mHpCnt = GetPlayerHP();
	
	w = mHpCnt * 50;
	x = -900 + (mHpCnt * 50);
	
}

void CHpUi::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI2, 0, 344*mHpCnt, 344, 0);
	}
}