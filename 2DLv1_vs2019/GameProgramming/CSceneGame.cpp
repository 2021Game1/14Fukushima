#include"CSceneGame.h"
#include<stdio.h>
#include"CSceneScreen.h"
#include<stdlib.h>
#include<time.h>

#define WIDTH 800.0 //��ʕ�

#define HEIGHT 600.0 //��ʍ���

#define SCROLL_SPEED -2.0


int CSceneGame::Remain = 3;
//�c�莞�ԁi30�b�j
int CSceneGame::Time = 30 * 60;

int CSceneGame::CLEAR = 0;

int CSceneGame::OVER = 0;

int CSceneGame::ScoreCount;

char CSceneGame::buf[10];

//���Ԃ�\���ϐ�

int val;



int CSceneGame::GameTime;

int CSceneGame::EnemyPattern;

int EnemyPattern = 0;

void CSceneGame::Init() {
	//�V�[���̐ݒ�
	mScene = EGAME;

	CSceneScreen* Screen = new CSceneScreen();
	Screen->x = 0;
	Screen->y = 250;
	Screen->speed = SCROLL_SPEED;
	Screen->mEnabled = true;

	CSceneScreen* Screen2 = new CSceneScreen();
	Screen2->x = 0;
	Screen2->y = 1700;
	Screen2->speed = SCROLL_SPEED;
	Screen2->mEnabled = true;
	
	//�N���X�̃����o�ϐ��ւ̑��
//37
	//�z��̐錾�Ə����l�̐ݒ�
	int map[6][8] =
	{
		{ 0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0},
		{ 1,1,1,1,1,1,1,1},
	};
	//MapSize = 0; //0��������
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 8; i++) {
			//map�̗v�f���P�̎��A�l�p�`�z�u
			if (map[j][i] == 1) {
				CMap* Map = new CMap;
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 5;
			}
		}
	}
	

	
	
	
	
	
	



	//37






	

	

	CPlayer* Player = new CPlayer();
	Player->x = 0;
	Player->y = -225;
	Player->w = 20;
	Player->h = 20;
	Player->mEnabled = true;

	/*37
	for (int k = 0; k < 10; k++) {
		if (!Enemy[k].mEnabled) {
			//�G�ɒl��ݒ�
			Enemy[k].x = i * 100 - 350;
			Enemy[k].y = j * -100 + 250;
			//�E�ֈړ�
			Enemy[k].mFx = 0;
			Enemy[k].mFy = 1;
			//�L���ɂ���
			Enemy[k].mEnabled = true;
			break;
		}
	}
	*/
}




void CSceneGame::Update() {

	for (int k = 0; k < 3; k = k + 1) {
		if (GameTime % 240 == 0)
		{
			/*srand(time(NULL));*/
			//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
			val = rand() % 501 - 250;
			CEnemy* Enemy = new CEnemy();
			Enemy->x = val;
			Enemy->y = 250;
			Enemy->mFy = -1;
			//�G�ɒl��ݒ�
			//�L���ɂ���
			Enemy->mEnabled = true;


		}
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
	if (Time > 0) {
		Time--;
	}
	

	for (int i = 0; i < VectorRect.size(); i++) {
		//�`�揈��
		VectorRect[i]->Render();
	}
	if (CSceneGame::Remain < 0) {
		CSceneGame::Remain = 0;
	}
	CText::DrawString("Score", -350, 250, 12, 12);
	sprintf(buf, "%d", ScoreCount);
	CText::DrawString(buf, -350 + 32 * 4.0, 250, 12, 12);
	
	//������̕`��
	CText::DrawString("Player", 200, -250, 12, 12);
	sprintf(buf, "%d", Remain);
	CText::DrawString(buf, 360, -250, 12, 12);

	//������̕`��
	CText::DrawString("Time", 200, 250, 12, 12);
	sprintf(buf, "%d", Time / 60);
	CText::DrawString(buf, 300, 250, 12, 12);

	if (Remain == 0) {
		CText::DrawString("GAME OVER!", -270, 0, 32, 32);
		CText::DrawString("Push ENETER Key", -225, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			Remain = 3;
			ScoreCount = 0;
			Time = 30 * 60;
			mScene = ETITLE;
		}
	}
	if (Time == 0 && Remain != 0) {
		CText::DrawString("GAME SCORE", -225, 0, 16, 16);
		sprintf(buf, "%d", ScoreCount);
		CText::DrawString(buf, 140, 0, 16, 16);
		CText::DrawString("GAME CLEAR!", -165, 100, 16, 16);
		CText::DrawString("Push ENETER Key", -225, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			Remain = 3;
			Time = 30 * 60;
			mScene = ETITLE;
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
