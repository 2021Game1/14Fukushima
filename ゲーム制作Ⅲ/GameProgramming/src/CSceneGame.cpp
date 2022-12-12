#include "CSceneGame.h"
//OpenGL
#include "glut.h"



void CSceneGame::Init() {
	mRes.Init();
}

void CSceneGame::Update() {
	CTaskManager::Get()->Update();
	mRes.Update();
	CTaskManager::Get()->Render();
	CTaskManager::Get()->Render2D();
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
	//�Փˏ���
	CCollisionManager::Get()->Collision();
	//�^�X�N���X�g�폜
	CTaskManager::Get()->Delete();
}

