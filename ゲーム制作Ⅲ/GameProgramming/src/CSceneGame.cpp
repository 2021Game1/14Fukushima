#include "CSceneGame.h"
//OpenGL
#include "glut.h"



void CSceneGame::Init() {
	mRes.Init();
	//�e�̐ݒ�
	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.2f };	//�e�̐F
	float lightPos[] = { 50.0f, 160.0f, 50.0f };		//�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //�V���h�E�}�b�v������
}

void CSceneGame::Update() {
	//�X�V����
	CTaskManager::Get()->Update();
	//�Փˏ���
	CCollisionManager::Get()->Collision();
	//�^�X�N���X�g�폜
	CTaskManager::Get()->Delete();
}
void CSceneGame::Render() {
	mShadowMap.Render();
	CTaskManager::Get()->Render2D();
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
}
void WholeRender() {
	//�^�X�N�`��
	CTaskManager::Get()->Render();
}

