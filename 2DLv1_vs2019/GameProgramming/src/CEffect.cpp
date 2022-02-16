#include "CEffect.h"

#define REMAIN 20

CTexture CEffect::mTexture;

void CEffect::LoadTexture(char* filename) {
	mTexture.Load(filename);
}

CEffect::CEffect(int ax, int ay, int aw, int ah)
	:mTime(REMAIN)
{
	x = ax;
	y = ay;
	w = aw;
	h = ah;
}

CEffect::CEffect()
{
	mTag = CRectangle::EEFFECT;
}
void CEffect::Update() {
	if (--mTime < 0)
	{
		mEnabled = false;
	}
}



void CEffect::Render()
{
	int i = 0;
	if (mTime > REMAIN * 3 / 4)
	{
		i = 1;
	}
	if (mTime > REMAIN * 2 / 4)
	{
		i = 2;
	}
	if (mTime > REMAIN * 1 / 4)
	{
		i = 3;
	}
	else
	{
		i = 4;
	}

	if (mEnabled) {
		CRectangle::Render(mTexture, 0.0f, 256 / 4, 256 * i / 4, 256 * (i - 1) / 4);
	}
}
