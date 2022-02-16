#include"CItem.h"
#include"CSceneGame.h"
#include"CPlayer.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture ItemTexture;



CItemA::CItemA()
	: mFy(0), mFx(0)
{
	x, y = 0;
	mEnabled = false;
	w = 15;
	h = 15;
	mTag = CRectangle::EENEMYITEM1;
}

void CItemA::Update() {
	if (CItemA::x >= 400 || CItemA::x <= -400 ||
		CItemA::y >= 280 || CItemA::y <= -280) {
		mEnabled = false;
	}
	//�L���Ȏ�
	if (mEnabled) {
		x += mFx;
		y += mFy;


	}
}

void CItemA::Render() {
	if (mEnabled) {
		CRectangle::Render(ItemTexture, 190, 206, 126, 112);
	}
}

bool CItemA::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:

			//�v���C���[�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;


			break;
		}
		return true;
	}
	return false;
}

CItemB::CItemB()
	: mFy(0), mFx(0)
{
	x, y = 0;
	mEnabled = false;
	w = 15;
	h = 15;
	mTag = CRectangle::EENEMYITEM2;
}

void CItemB::Update() {
	if (CItemB::x >= 400 || CItemB::x <= -400 ||
		CItemB::y >= 280 || CItemB::y <= -280) {
		mEnabled = false;
	}
	//�L���Ȏ�
	if (mEnabled) {
		x += mFx;
		y += mFy;


	}


}

void CItemB::Render() {
	if (mEnabled) {
		CRectangle::Render(ItemTexture, 241, 253, 0, 16);
	}
}

bool CItemB::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:
			//�v���C���[�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;


			break;
		}
		return true;
	}
	return false;
}


CItemC::CItemC()
	: mFy(0), mFx(0)
{
	x, y = 0;
	mEnabled = false;
	w = 15;
	h = 15;
	mTag = CRectangle::EENEMYITEM3;
}

void CItemC::Update() {
	if (CItemC::x >= 400 || CItemC::x <= -400 ||
		CItemC::y >= 280 || CItemC::y <= -280) {
		mEnabled = false;
	}
	//�L���Ȏ�
	if (mEnabled) {
		x += mFx;
		y += mFy;


	}

}

void CItemC::Render() {
	if (mEnabled) {
		CRectangle::Render(ItemTexture, 224, 239, 1, 16);
	}
}

bool CItemC::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;

			break;
		}
		return true;
	}
	return false;
}

CItemD::CItemD()
	: mFy(0), mFx(0)
{
	x, y = 0;
	mEnabled = false;
	w = 15;
	h = 15;
	mTag = CRectangle::EENEMYITEM4;
}

void CItemD::Update() {
	if (CItemD::x >= 400 || CItemD::x <= -400 ||
		CItemD::y >= 280 || CItemD::y <= -280) {
		mEnabled = false;
	}
	//�L���Ȏ�
	if (mEnabled) {
		x += mFx;
		y += mFy;


	}

}

void CItemD::Render()
{
	if (mEnabled) {
		CRectangle::Render(ItemTexture, 192, 207, 112, 97);
	}
}

bool CItemD::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;

			break;
		}
		return true;
	}
	return false;
}

CItemE::CItemE()
	: mFy(0), mFx(0)
{
	mEnabled = false;
	w = 15;
	h = 15;
	mTag = CRectangle::EENEMYITEM5;
}

void CItemE::Update() {
	if (CItemE::x >= 400 || CItemE::x <= -400 ||
		CItemE::y >= 280 || CItemE::y <= -280) {
		mEnabled = false;
	}
	//�L���Ȏ�
	if (mEnabled) {
		x += mFx;
		y += mFy;


	}

}

void CItemE::Render() {
	if (mEnabled) {
		CRectangle::Render(ItemTexture, 225, 240, 16, 32);
	}
}

bool CItemE::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYER:

			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;

			break;
		}
		return true;
	}
	return false;
}