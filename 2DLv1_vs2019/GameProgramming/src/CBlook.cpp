#include"CBlock.h"
#include"CSceneGame.h"
#include"CBullet.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture MoonBlock;



CBlock::CBlock()
	: mFx(0), mFy(0)
{
	mTag = CRectangle::EBLOCK;

}

void CBlock::Update()
{
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled)return;

	if (y < -450)
	{

		mEnabled = false;
	}
	//�L���Ȏ�
	if (mEnabled) {
		//�ړ�
		x += mFx * 0;
		y += mFy * 1;
	}
	if (CComet::speed == -1)
	{
		mFy = -1;
	}
	if (CComet::speed == 0)
	{
		mFy = 0;
	}

}
bool CBlock::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {

		}
		return true;
	}
	return false;
}

void CBlock::Render()
{
	if (mEnabled) {
		CRectangle::Render(MoonBlock, 0, 320, 320, 0);
	}

}

void CBlock::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}

int CComet::speed = -1;

CComet::CComet()
	: mFx(0), mFy(0)
{
	mTag = CRectangle::ECOMET;


}

void CComet::Update()
{
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled)return;

	if (y > 345) {
		CComet::speed = -1;
	}

	if (y < 345) {
		CComet::speed = 0;
	}

	//�L���Ȏ�

	if (mEnabled) {
		//�ړ�
		x += mFx * 0;
		y += mFy * 1;
	}
	if (CComet::speed == -1)
	{
		mFy = -1;
	}
	if (CComet::speed == 0)
	{
		mFy = 0;
	}

}



void CComet::Render()
{
	if (mEnabled) {
		CRectangle::Render(MoonBlock, 0, 445, 1285, 825);
	}

}