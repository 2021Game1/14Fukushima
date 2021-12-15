#include"CBlock.h"

//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture BulletTexture;

CBlock::CBlock() 
	: mFx(0), mFy(0)
{
	w = 25;
	h = 25;
	mTag = CRectangle::EBLOCK;
}

void CBlock::Update() 
{
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled)return;

	if (y < -280)
	{
		//�G�̃t���O��false��
		mEnabled = false;
	}

	//�L���Ȏ�
	if (mEnabled) {
		//�ړ�
		x += mFx * 0;
		y += mFy * 1;
	}


}
bool CBlock::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYERBULLET:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;
		case EPLAYER:
			//�v���C���[�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			break;
		}
		return true;
	}
	return false;
}

void CBlock::Render()
{
	if (mEnabled) {
		CRectangle::Render(BulletTexture, 106, 116, 106, 112);
	}

}

void CBlock::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}