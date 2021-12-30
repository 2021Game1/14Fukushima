#include"CSceneGame.h"
#include<stdio.h>
#include"CSceneScreen.h"
#include<stdlib.h>
#include<time.h>
#include"CBlock.h"
#include"CItem.h"
#include"CMapModel.h"

CMapModel mMapModel;

#define WIDTH 800.0 //��ʕ�

#define HEIGHT 600.0 //��ʍ���

//�X�N���[���̃X�N���[���X�s�[�h
#define SCROLL_SPEED -2.0

CBlock mBlockModel;

//���f���f�[�^�̎w��
#define MODEL_OBJ "MapDate.csv","Test.csv"

//�v���C���[�̎c�@
int CSceneGame::Remain = 3;

//�c�莞�ԁi30�b�j
int CSceneGame::Time = 31 * 60;

//�Q�[���N���A
int CSceneGame::CLEAR = 0;

//�Q�[���I�[�o�[
int CSceneGame::OVER = 0;

//�Q�[���X�R�A�̃J�E���^�ϐ�
int CSceneGame::ScoreCount = 0;

//�{�X���o�����Ă��邩�A���ʂ���t���O
int CSceneGame::Bossflug = 0;

//�{�X�̃J�E���^
int CSceneGame::BossCount = 0;

//�G�̃J�E���^
int CSceneGame::EnemyCount = 0;

//�X�����܂ŕ`��ł���ϐ�
char CSceneGame::buf[10];

int vel;


int val;

//�G���o������܂ł̎���
int CSceneGame::GameTime;




void CSceneGame::Init() 
{
		//�V�[���̐ݒ�
		mScene = EGAME;
		//���f���t�@�C���̓���
		mMapModel.Load(MODEL_OBJ);
		
		//�X�N���[���ꖇ��
	//�X�N���[���N���X�̃����o�ϐ��ւ̑��
		CSceneScreen* Screen = new CSceneScreen();
		//�X�N���[���ɒl��ݒ�
		Screen->x = 0;
		Screen->y = 240;
		//�X�N���[���X�s�[�h
		Screen->speed = SCROLL_SPEED;
		//�L���ɂ���
		Screen->mEnabled = true;

		//�X�N���[���Q����
		//�X�N���[���N���X�̃����o�ϐ��ւ̑��
		CSceneScreen* Screen2 = new CSceneScreen();
		//�X�N���[���ɒl��ݒ�
		Screen2->x = 0;
		Screen2->y = 1700;
		//�X�N���[���X�s�[�h
		Screen2->speed = SCROLL_SPEED;
		//�L���ɂ���
		Screen2->mEnabled = true;

		
		


		//�v���C���[�N���X�̃����o�ϐ��ւ̑��
		CPlayer* Player = new CPlayer();
		//�v���C���[�ɒl��ݒ�
		Player->x = 0;
		Player->y = -225;
		Player->w = 20;
		Player->h = 20;
		//�L���ɂ���
		Player->mEnabled = true;



	
	
	

			
}




void CSceneGame::Update() {

	
		//�G�̏o���������
		if (GameTime % 280 == 140 && ScoreCount < 1000 && GameTime != 0)
		{
			/*srand(time(NULL));*/
			//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
			val = rand() % 501 - 250;
			CEnemy* Enemy = new CEnemy();
			//�G�ɒl��ݒ�
			Enemy->x = val;
			Enemy->y = 250;
			Enemy->mFy = -1;
			//�L���ɂ���
			Enemy->mEnabled = true;
			
		}

		if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
		{
				if (GameTime % 100 == 50)
				{
					/*srand(time(NULL));*/
					//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
					val = rand() % 501 - 250;
					/*srand(time(NULL));*/
					//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
					srand((unsigned)time(NULL));
					vel = (rand() % 100) + 1;
					for (int i = 0; i < 1; i++)
					{
						//�A�C�e��1�̏o���m��(�O��A�C�e��)
						if (vel >= 0 && vel <= 70) {
							CItemA* ItemA = new CItemA;
							ItemA->x = val;
							ItemA->y = 250;
							ItemA->mFy = -3;
							ItemA->mEnabled = false;
							ItemA->mTag = CRectangle::EENEMYITEM1;
						}
					}
					for (int i = 0; i < 1; i++)
					{
						//�A�C�e��2�̏o���m��
						if (vel > 70 && vel <= 80) {
							CItemB* ItemB = new CItemB;
							ItemB->x = val;
							ItemB->y = 250;
							ItemB->mFy = -3;
							ItemB->mEnabled = true;
							ItemB->mTag = CRectangle::EENEMYITEM2;
						}
					}
					for (int i = 0; i < 1; i++)
					{
						//�A�C�e��4�̏o���m��
						if (vel > 80 && vel <= 90) {
							CItemD* ItemD = new CItemD;
							ItemD->x = val;
							ItemD->y = 250;
							ItemD->mFy = -3;
							ItemD->mEnabled = true;
							ItemD->mTag = CRectangle::EENEMYITEM3;
						}
					}
					for (int i = 0; i < 1; i++)
					{
						//�A�C�e��5�̏o���m��
						if (vel > 90 && vel <= 95) {
							CItemE* ItemE = new CItemE;
							ItemE->x = val;
							ItemE->y = 250;
							ItemE->mFy = -3;
							ItemE->mEnabled = true;
							ItemE->mTag = CRectangle::EENEMYITEM4;
						}
					}
					for (int i = 0; i < 1; i++)
					{
						//�A�C�e��3�̏o���m��
						if (vel > 95 && vel <= 100) {
							CItemC* ItemC = new CItemC;
							ItemC->x = val;
							ItemC->y = 250;
							ItemC->mFy = -3;
							ItemC->mEnabled = true;
							ItemC->mTag = CRectangle::EENEMYITEM5;
						}
					}

				}
		}

	//�{�X�̃t���O��2�ȊO�̎��ɏo������
	if (Bossflug != 2)
	{
		//�X�R�A��1000�ȏォ�A��������
		if (ScoreCount >= 1000)
		{
			//�{�X�G�l�~�[�N���X�̃����o�ϐ��ւ̑��
			CBossEnemy* EBossEnemy = new CBossEnemy();
			Bossflug += 1;
			//�{�X�G�l�~�[�ɒl��ݒ�
			EBossEnemy->x = 0;
			EBossEnemy->y = 250;
			EBossEnemy->mFx = 2;
			EBossEnemy->mFy = 0;
			//�L���ɂ���
			EBossEnemy->mEnabled = true;
			//������������t���O��2�ɂ���
			Bossflug = 2;
		}

	}
		//�G�̏o���������
		if (GameTime % 140 == 70 && GameTime != 0)
		{
			/*srand(time(NULL));*/
			//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
			val = rand() % 501 - 250;
			//�G�l�~�[�N���X�̃����o�ϐ��ւ̑��
			CEnemy* Enemy2 = new CEnemy();
			//�G�ɒl��ݒ�
			Enemy2->x = val;
			Enemy2->y = 250;
			Enemy2->mFy = -1;
			//�L���ɂ���
			Enemy2->mEnabled = true;
			
		}
	

		//���Ԃ����Z����
		GameTime = GameTime + 1;


		


	
		
	
	
	

	
	
	
		
	
	
	
	

	
	
	/*
	�z��̗v�f���J��Ԃ�
	�z��.size()
	�z��̗v�f�����擾����
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		�z��̎Q��
		�z��[�Y����]
		�ʏ�̔z�񓯗l�ɓY�����ŗv�f�ɃA�N�Z�X�ł���
		*/
		//�X�V����
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//�Փˏ���
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//���X�g����폜����
	//�C�e���[�^�̐���
	std::vector<CRectangle*>::iterator itr;
	//�C�e���[�^��擪
	itr = VectorRect.begin();
	//�Ō�܂ŌJ��Ԃ�
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//����
			itr++;
		}
		else {
			//false�̃C���X�^���X���폜
			delete *itr;
			//���X�g������폜
			itr = VectorRect.erase(itr);
						//����
			
		}
	}

	//�������Ԃ�0�ł͂Ȃ��A�v���C���[�̎c�@��0�ł͖������ɗL���ɂ���
	if (Time > 0 && Remain > 0) {
		//�������Ԃ����Z���Ă���
		Time--;
	}

	

	for (int i = 0; i < VectorRect.size(); i++) {
		//�`�揈��
		VectorRect[i]->Render();
	}

	if (CSceneGame::Remain < 0) {
		CSceneGame::Remain = 0;
	}

	//�v���C���[�̎c�@��0�ł͂Ȃ��A�������Ԃ�0�ł͂Ȃ����ɗL���ɂ���
	if (Remain != 0 && Time != 0)
	{
		CText::DrawString("Score", -350, 250, 12, 12);
		sprintf(buf, "%d", ScoreCount);
		CText::DrawString(buf, -350 + 32 * 4.0, 250, 12, 12);
	}
	
	//������̕`��
	CText::DrawString("Player", 200, -250, 12, 12);
	sprintf(buf, "%d", Remain);
	CText::DrawString(buf, 360, -250, 12, 12);
	
		//������̕`��
		CText::DrawString("Time", 200, 250, 12, 12);
		sprintf(buf, "%d", Time / 60);
		CText::DrawString(buf, 300, 250, 12, 12);
	
	
	//�v���C���[�̎c�@��0�̎��܂��́A�������Ԃ�0�̎��ɗL���ɂ���
	if (Remain == 0 || Time == 0 ) {
		CText::DrawString("GAME SCORE", -180, 0, 16, 16);
		sprintf(buf, "%d", ScoreCount);
		CText::DrawString(buf, 160, 0, 16, 16);
		CText::DrawString("GAME OVER!", -140, 100, 16, 16);
		CText::DrawString("Push ENETER Key", -210, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			Remain = 3;
			OVER = 0;
			ScoreCount = 0;
			Time = 31 * 60;
			Bossflug = 0;
			EnemyCount = 0;
			BossCount = 0;
			CBossEnemy::mBossEnemyLife = 20;
			mScene = ETITLE;
		}
	}

	if (Remain != 0) {
		if (BossCount == 1){
			CText::DrawString("GAME SCORE", -225, 0, 16, 16);
			sprintf(buf, "%d", ScoreCount);
			CText::DrawString(buf, 140, 0, 16, 16);
			CText::DrawString("GAME CLEAR!", -165, 100, 16, 16);
			CText::DrawString("Push ENETER Key", -225, -100, 16, 16);
			if (CKey::Once(VK_RETURN)) {
			Remain = 3;
			ScoreCount = 0;
			Time = 31 * 60;
			Bossflug = 0;
			EnemyCount = 0;
			BossCount = 0;
			CBossEnemy::mBossEnemyLife = 20;
			mScene = ETITLE;
			}
		}
	}
/*
	CText::DrawChar('S', -350, 250, 16, 16);
	CText::DrawChar('c', -350 + 32, 250, 16, 16);
	CText::DrawChar('o', -350 + 32 * 2, 250, 16, 16);
	CText::DrawChar('r', -350 + 32 * 3, 250, 16, 16);
	CText::DrawChar('e', -350 + 32 * 4, 250, 16, 16);

	CText::DrawChar('P', 150, -250, 16, 16);
	CText::DrawChar('l', 150 + 32, -250, 16, 16);
	CText::DrawChar('a', 150 + 32 * 2, -250, 16, 16);
	CText::DrawChar('y', 150 + 32 * 3, -250, 16, 16);
	CText::DrawChar('e', 150 + 32 * 4, -250, 16, 16);
	CText::DrawChar('r', 150 + 32 * 5, -250, 16, 16);

	//������̕`��
	CText::DrawString("Time", 150, 250, 16, 16);
	if (Time > 0) {
		Time--;
	}
	//�����𕶎���ɕϊ�����
	char buf[10];//9�����܂�OK
	sprintf(buf, "%d", Time / 60);
	CText::DrawString(buf, 300, 250, 16, 16);

	sprintf(buf, "%d", Remain);
	CText::DrawString(buf, 150 + 32 * 7, -250, 16, 16);
*/

}




//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//�f�X�g���N�^
CSceneGame::~CSceneGame() {
	//�S�ẴC���X�^���X���폜���܂�
	for (int i = 0; i < VectorRect.size(); i++) {
		//�C���X�^���X�̍폜
		delete VectorRect[i];
	}
	//�ϒ��z��̃N���A
	VectorRect.clear();
}
