//�V�[���Q�[���N���X�̃C���N���[�h
#include "CSceneGame.h"
//OpenGL
#include"glut.h"
 



void CSceneGame::Init() {
	mGameTest.Init();
}

void CSceneGame::Update() {
	//�^�X�N�}�l�[�W���̍X�V
	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	CTaskManager::Get()->TaskCollision();
	
	mGameTest.Update();

	//�R���W�����}�l�[�W���̃R���C�_�`��
	CCollisionManager::Get()->Render();
	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();
	//�^�X�N�}�l�[�W���̕`��	
	CTaskManager::Get()->Render();


}



