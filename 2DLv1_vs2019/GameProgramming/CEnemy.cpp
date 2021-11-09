#include "CEnemy.h"
#include "CTexture.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
#include "CSceneGame.h"
#include "CPlayer.h"
extern CTexture Texture;

CEnemy* CEnemy::spInstance = nullptr;
//CBullet CEnemy::EBullet[20];


//�G�̃f�[�^//
CEnemy::CEnemy() 
	: mFx(0), mFy(0)
{
	{
		spInstance = this;
		w = 25;
		h = 25;
		//37
	//	mEnabled = true;
		mTag = CRectangle::EENEMY;
		
	}
}



void CEnemy::Update() {


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
	//60�t���[����1�񔭎�
	if (mFireCount > 0) {
		mFireCount--;
	}
	//37e
	/**/

	else {
		for (int j = 0; j < 2; j++) {
			CBullet* EBullet = new CBullet();
			//���W�ݒ�
			EBullet->x = x;
			EBullet->y = y;
			//�ړ��ʐݒ�
			if (CEnemy::x < CPlayer::spInstance->x) {
				EBullet->mFx = +1;
				EBullet->mFy = -3 * ((j / 2) + 1);
			}
			if (CEnemy::x > CPlayer::spInstance->x) {
				EBullet->mFx = -1;
				EBullet->mFy = -3 * ((j / 2) + 1);
			}
			//�L���ɂ���
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;
		}
		mFireCount = 40;


	}
}
	
	
	





	
	
	

		/*
		//�G�e�����J��Ԃ�
		for (int i = 0; i < 20; i++) {
			//�����Ȓe�Ȃ甭�˂���
			if (!EBullet[i].mEnabled) {
				//���W�ݒ�
				EBullet[i].x = x;
				EBullet[i].y = y;
				//�ړ��ʐݒ�
				EBullet[i].mFx = -2;
				EBullet[i].mFy = 0;
				//�L���ɂ���
				EBullet[i].mEnabled = true;
				EBullet[i].mTag = EENEMYBULLET;
				//���ˊԊu��60�t���[���ɂ���
				break;
			}
			mFireCount = 60;
		}
		//�G�e�����J��Ԃ�
		for (int i = 0; i < 20; i++) {
			//�����Ȓe�Ȃ甭�˂���
			if (!EBullet[i].mEnabled) {
				//���W�ݒ�
				EBullet[i].x = x;
				EBullet[i].y = y;
				//�ړ��ʐݒ�
				EBullet[i].mFx = 0;
				EBullet[i].mFy = 2;
				//�L���ɂ���
				EBullet[i].mEnabled = true;
				EBullet[i].mTag = EENEMYBULLET;
				//���ˊԊu��60�t���[���ɂ���
				break;
			}
			mFireCount = 60;
		}
		//�G�e�����J��Ԃ�
		for (int i = 0; i < 20; i++) {
			//�����Ȓe�Ȃ甭�˂���
			if (!EBullet[i].mEnabled) {
				//���W�ݒ�
				EBullet[i].x = x;
				EBullet[i].y = y;
				//�ړ��ʐݒ�
				EBullet[i].mFx = 0;
				EBullet[i].mFy = -2;
				//�L���ɂ���
				EBullet[i].mEnabled = true;
				EBullet[i].mTag = EENEMYBULLET;
				//���ˊԊu��60�t���[���ɂ���
				break;
			}
			mFireCount = 60;
		}
		*/
	
	

/*
�e��Collision���I�[�o�[���C�h����
�Փ˂���ƈړ������𔽑΂ɂ���
*/
bool CEnemy::Collision(const CRectangle &r) {
	//mEnabled��false�Ȃ�߂�
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			//�Փ˂��Ă���Δ��]
			mEnabled = false;
			break;
		case EPLAYERBULLET:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			break;
		case EPLAYER:
			mEnabled = false;
			break;
		CSceneGame::GameTime = CSceneGame::GameTime + 1;
		}
		return true;
	}
	return false;
}

void CEnemy::Render() {
		if (mEnabled) {
			CRectangle::Render(Texture, 140, 190, 75, 25);
		}
	
}

//36
void CEnemy::Collision(CRectangle *i, CRectangle *y) {
	Collision(*y);
}
