#include "CEnemy.h"
#include "CTexture.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
#include "CSceneGame.h"
#include "CPlayer.h"
#include"CItem.h"
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture ItemTexture;
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
		for (int j = 0; j < 1; j++) {
			CBullet* EBullet = new CBullet();
			//���W�ݒ�
			EBullet->x = x;
			EBullet->y = y;
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
				ItemA->x = x;
				ItemA->y = y;
				ItemA->mFy = -3;
				CItemB* ItemB = new CItemB;
				ItemB->x = x;
				ItemB->y = y;
				ItemB->mFy = -3;
				CItemC* ItemC = new CItemC;
				ItemC->x = x;
				ItemC->y = y;
				ItemC->mFy = -3;
				CItemD* ItemD = new CItemD;
				ItemD->x = x;
				ItemD->y = y;
				ItemD->mFy = -3;
				CItemE* ItemE = new CItemE;
				ItemE->x = x;
				ItemE->y = y;
				ItemE->mFy = -3;

				srand((unsigned)time(NULL));
				vel = (rand() % 100) + 1;
				
				if (vel >= 0 && vel <= 50) {
					ItemA->mEnabled = false;
					ItemA->mTag = EENEMYITEM;
					
					mEnabled = false;
				}
				if (vel > 50 && vel <= 70) {
					ItemB->mEnabled = true;
					ItemB->mTag = EENEMYITEM;
					
					mEnabled = false;
				}
				if (vel > 70 && vel <= 80) {
					ItemD->mEnabled = true;
					ItemD->mTag = EENEMYITEM;
					
					mEnabled = false;
				}
				if (vel > 80  && vel <= 85) {
					
					ItemE->mEnabled = true;
					ItemE->mTag = EENEMYITEM;
					
					
					mEnabled = false;
				}
				if (vel > 85 && vel <= 100) {
					
					ItemC->mEnabled = true;
					ItemC->mTag = EENEMYITEM;
					mEnabled = false;
				}

			}
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
				{
					CSceneGame::ScoreCount += 50;
				}

			break;
			
		case EPLAYER:

			//�v���C���[�ɓ�����ƁA�����ɂ���
			mEnabled = false;

			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
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
