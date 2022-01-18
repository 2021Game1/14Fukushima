#include "CEffect.h"

extern CTexture Effect;

CEffect::CEffect()
{
	mTag = CRectangle::EEFFECT;
}
void CEffect::Update(){
	if (mEnabled == true) {
		if (time > 0) {
			//�������Ԃ����Z���Ă���
			time--;
		}
		if (time <=  0) {
			mEnabled = false;
			time = 0.3 * 60;
		}
	}

}



void CEffect::Render()
{
	if (mEnabled) {
	CRectangle::Render(Effect,0,53,53,0);
	}
}
