#include "CGameUi.h"


extern CTexture GameUI1;
extern CTexture GameUI2;

CScoreUi0::CScoreUi0() {
	mEnabled = true;
}

void CScoreUi0::Render()
{
	if (mEnabled) {
			CRectangle::Render(GameUI1, 0, 28, 28, 0);
	}
}

CScoreUi1::CScoreUi1() {
	mEnabled = true;
}

void CScoreUi1::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 28, 56, 28, 0);
	}
}
CScoreUi2::CScoreUi2() {
	mEnabled = true;
}

void CScoreUi2::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 56, 84, 28, 0);
	}
}
CScoreUi3::CScoreUi3() {
	mEnabled = true;
}

void CScoreUi3::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 84, 112, 28, 0);
	}
}
CScoreUi4::CScoreUi4() {
	mEnabled = true;
}

void CScoreUi4::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 112, 140, 28, 0);
	}
}
CScoreUi5::CScoreUi5() {
	mEnabled = true;
}

void CScoreUi5::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 140, 168, 28, 0);
	}
}
CScoreUi6::CScoreUi6() {
	mEnabled = true;
}

void CScoreUi6::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 168, 196, 28, 0);
	}
}
CScoreUi7::CScoreUi7() {
	mEnabled = true;
}

void CScoreUi7::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 196, 224, 28, 0);
	}
}
CScoreUi8::CScoreUi8() {
	mEnabled = true;
}

void CScoreUi8::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 224, 252, 28, 0);
	}
}
CScoreUi9::CScoreUi9() {
	mEnabled = true;
}

void CScoreUi9::Render()
{
	if (mEnabled) {
		CRectangle::Render(GameUI1, 252, 280, 28, 0);
	}
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