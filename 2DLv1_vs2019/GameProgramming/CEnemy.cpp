#include "CEnemy.h"
#include "CTexture.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
#include "CSceneGame.h"
#include "CPlayer.h"
#include"CItem.h"
#include"CSceneTitle.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture ItemTexture;
extern CTexture Texture;

//CBullet CEnemy::EBullet[20];

//�G�̃f�[�^//
CEnemy::CEnemy() 
	: mFx(0), mFy(0)
{
	{

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

	if (y > 280)
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
	if (y == -50) {
		CEnemy::mFy = 2;
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
		case EPLAYERBULLET:	
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;
			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
			{
				CItemA* ItemA = new CItemA;
				CItemB* ItemB = new CItemB;
				CItemC* ItemC = new CItemC;
				CItemD* ItemD = new CItemD;
				CItemE* ItemE = new CItemE;

				for (int j = 0; j < 1; j++) {
					ItemA->x = x;
					ItemA->y = y;
					if (CEnemy::x < CPlayer::spInstance->x) {
						ItemA->mFx = -1;
						ItemA->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x == CPlayer::spInstance->x) {
						ItemA->mFx = 0;
						ItemA->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x > CPlayer::spInstance->x) {
						ItemA->mFx = +1;
						ItemA->mFy = -3 * ((j / 2) + 1);
					}
					ItemA->mFy = -3;
				}

				for (int j = 0; j < 1; j++) {
					ItemB->x = x;
					ItemB->y = y;
					if (CEnemy::x < CPlayer::spInstance->x) {
						ItemB->mFx = -1;
						ItemB->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x == CPlayer::spInstance->x) {
						ItemB->mFx = 0;
						ItemB->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x > CPlayer::spInstance->x) {
						ItemB->mFx = +1;
						ItemB->mFy = -3 * ((j / 2) + 1);
					}
					ItemB->mFy = -3;
				}

				for (int j = 0; j < 1; j++) {
					ItemC->x = x;
					ItemC->y = y;
					if (CEnemy::x < CPlayer::spInstance->x) {
						ItemC->mFx = -1;
						ItemC->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x == CPlayer::spInstance->x) {
						ItemC->mFx = 0;
						ItemC->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x > CPlayer::spInstance->x) {
						ItemC->mFx = +1;
						ItemC->mFy = -3 * ((j / 2) + 1);
					}
					
				}
				
				for (int j = 0; j < 1; j++) {
					ItemD->x = x;
					ItemD->y = y;
					if (CEnemy::x < CPlayer::spInstance->x) {
						ItemD->mFx = -1;
						ItemD->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x == CPlayer::spInstance->x) {
						ItemD->mFx = 0;
						ItemD->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x > CPlayer::spInstance->x) {
						ItemD->mFx = +1;
						ItemD->mFy = -3 * ((j / 2) + 1);
					}
					
				}
				for (int j = 0; j < 1; j++) {
					ItemE->x = x;
					ItemE->y = y;
					if (CEnemy::x < CPlayer::spInstance->x) {
						ItemE->mFx = -1;
						ItemE->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x == CPlayer::spInstance->x) {
						ItemE->mFx = 0;
						ItemE->mFy = -3 * ((j / 2) + 1);
					}
					if (CEnemy::x > CPlayer::spInstance->x) {
						ItemE->mFx = +1;
						ItemE->mFy = -3 * ((j / 2) + 1);
					}
					
				}

				srand((unsigned)time(NULL));
				vel = (rand() % 100) + 1;


				if (vel >= 0 && vel <= 50) {
					ItemA->mEnabled = false;
					ItemA->mTag = EENEMYITEM;
					if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
					{

					}
				}
				if (vel > 50 && vel <= 70) {
					ItemB->mEnabled = true;
					ItemB->mTag = EENEMYITEM;
					if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
					{
						CSceneGame::ScoreCount += 50;
					}
					mEnabled = false;
				}
				if (vel > 70 && vel <= 80) {
					ItemD->mEnabled = true;
					ItemD->mTag = EENEMYITEM;
					if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
					{
						CSceneGame::Remain += 1;
					}
					mEnabled = false;
				}

				if (vel > 80 && vel <= 85) {
					ItemE->mEnabled = true;
					ItemE->mTag = EENEMYITEM;
					if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
					{
						CSceneGame::Time += 21 * 60;
					}
					mEnabled = false;
				}

				if (vel > 85 && vel <= 100) {

					ItemC->mEnabled = true;
					ItemC->mTag = EENEMYITEM;
					if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
					{
						CSceneGame::Time += 10 * 60;
					}
					mEnabled = false;
				}
			}
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0 && CBossEnemy::mBossEnemyLife != 0)
				{
					CSceneGame::ScoreCount += 1000;
					CSceneGame::EnemyCount += 1;
				}

			break;
			
		case EPLAYER:


			//�v���C���[�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0 && CBossEnemy::mBossEnemyLife != 0)
			{
				CSceneGame::ScoreCount += 25;
				CSceneGame::Remain -= 1;
			}
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
