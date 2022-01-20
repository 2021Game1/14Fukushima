#include "CEnemy.h"
#include "CTexture.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
#include "CSceneGame.h"
#include "CPlayer.h"
#include"CItem.h"
#include"CSceneTitle.h"
#include"CEffect.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;

//CSound�N���X�̃C���N���[�h
#include "CSound.h"
//�O���ϐ��̎Q�Ƃ̍쐬
extern CSound Se;
//CBullet CEnemy::EBullet[20];

//�G�̃f�[�^//
CEnemy::CEnemy() 
	: mFx(0), mFy(0),mFireCount(0)
{
	{
		//37
	//	mEnabled = true;
		mTag = CRectangle::EENEMY;
		
	}
}
void CEnemy::Update() {


	//mEnabled��false�Ȃ�߂�
	if (!mEnabled)return;

	if (y < -425)
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
		for (int j = 0; j < 1; j++) {
			CBullet* EBullet = new CBullet();
			//���W�ݒ�
			EBullet->x = x;
			EBullet->y = y;
			EBullet->w = 8;
			EBullet->h = 8;
			//�ړ��ʐݒ�
			if (CEnemy::x < CPlayer::spInstance->x) {
				EBullet->mFx = +1;
				EBullet->mFy = -3 * ((j / 2) + 1);
			}
			if (CEnemy::x == CPlayer::spInstance->x) {
				EBullet->mFx = 0;
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
		mFireCount = 55;


	}



}


	

/*
�e��Collision���I�[�o�[���C�h����
�Փ˂���ƈړ������𔽑΂ɂ���
*/
bool CEnemy::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYERBULLET: {
			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0 && CBossEnemy::mBossEnemyLife != 0)
			{
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;
			//�T�E���h�Đ�
			Se.Play();
			CEffect* Effect = new CEffect();
			//�L���ɂ���
			Effect->x = x;
			Effect->y = y;
			Effect->w = 25;
			Effect->h = 25;
			Effect->mEnabled = true;
			Effect->mTag = EEFFECT;

			
				CSceneGame::ScoreCount += 100;
				CSceneGame::EnemyCount += 1;
			}
			break;
		}
		
			
			
		case EPLAYER: {
			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0 && CBossEnemy::mBossEnemyLife != 0)
			{
			//�v���C���[�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			//�T�E���h�Đ�
			Se.Play();
			CEffect* Effect2 = new CEffect();
			//�L���ɂ���
			Effect2->x = x;
			Effect2->y = y;
			Effect2->w = 25;
			Effect2->h = 25;
			Effect2->mEnabled = true;
			Effect2->mTag = EEFFECT;
			
				CSceneGame::ScoreCount += 25;
				CSceneGame::Remain -= 1;
			}
			break;
		}


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
