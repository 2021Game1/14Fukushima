#include "CSceneGame.h"
#include <stdio.h>
#include "CSceneScreen.h"
#include"CEnemyData.h"

#define WIDTH 800.0 //��ʕ�

#define HEIGHT 600.0 //��ʍ���

#define SCROLL_SPEED -2.0

//�c�莞�ԁi30�b�j
int Time = 30 * 60;
int Remain = 3;

int mEnemypoptime;

int EnemyTime = 2 * 60;

void CSceneGame::Init() {
	//�V�[���̐ݒ�
	mScene = EGAME;

	//�N���X�̃����o�ϐ��ւ̑��
//37
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



	int EnemyMap[6][8] =
	{

			{ 1,2,3,2,3,2,3,1},
			{ 1,0,0,0,0,0,0,1},
			{ 1,0,0,0,0,0,0,1},
			{ 1,0,0,0,0,0,0,1},
			{ 1,0,0,0,0,0,0,1},
			{ 1,1,1,1,1,1,1,1},
	};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (EnemyMap[j][i] == 2) {
				CEnemy* Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//���ֈړ�
				Enemy->mFx = 0;
				Enemy->mFy = -1;
				Enemy->mEnabled = true;
				Enemy->mTag = CRectangle::EENEMY;
				
			}
		}
	}



	//37






	CPlayer* Player = new CPlayer();
	Player->x = 0;
	Player->y = -255;
	Player->w = 25;
	Player->h = 25;
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
		}
	}

	

	for (int i = 0; i < VectorRect.size(); i++) {
		//�`�揈��
		VectorRect[i]->Render();
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
