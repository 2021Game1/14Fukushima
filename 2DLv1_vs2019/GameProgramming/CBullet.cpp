#include "CBullet.h"
#include "CTexture.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture BulletTexture;

//�f�t�H���g�R���X�g���N�^
CBullet::CBullet()
: mFx(0), mFy(0)
{
	mEnabled = false;
	w = 10;	//���ݒ�
	h = 10;	//�����ݒ�
}

//�X�V����
void CBullet::Update() {
	if (CBullet::x >= 400 || CBullet::x <= -400 ||
		CBullet::y >= 280 || CBullet::y <= -280) {
		mEnabled = false;
	}
	//�L���Ȏ�
	if (mEnabled) {
		//�ړ�
		x += mFx;
		y += mFy;


	}
}

//�`�揈��
void CBullet::Render() {
	//�L���Ȏ�
	if (mEnabled) {
		//�e�̕`�惁�\�b�h���Ă�
		CRectangle::Render(BulletTexture, 17, 26, 99, 88);
	}
}

//36
void CBullet::Collision(CRectangle *i, CRectangle *y) {
	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == EBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		if (i->mTag == EENEMYBULLET && y->mTag == EPLAYER) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
	}
}
