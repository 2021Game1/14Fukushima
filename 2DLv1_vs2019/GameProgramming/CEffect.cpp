#include "CEffect.h"

extern CTexture Effect;

CEffect::CEffect()
{
	mTag = CRectangle::EEFFECT;
}




void CEffect::Render()
{
	if (mEnabled) {
	CRectangle::Render(Effect,0,53,53,0);
	}
}
