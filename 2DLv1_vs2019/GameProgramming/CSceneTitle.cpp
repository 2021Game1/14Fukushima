#include "CSceneTitle.h"
#include "CKey.h"



void CSceneTitle::Init() {
	//�V�[���̐ݒ�
	mScene = ETITLE;
	
}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {
	if (CSceneGame::OVER == 0)
	{
		//������̕`��
		CText::DrawString("TITLE", -200, 0, 50, 50);
		CText::DrawString("Push ENTER Key",
			-200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//���̃V�[���̓Q�[��
			mScene = EGAME;
		}
	}

	if (CSceneGame::CLEAR >= 1)
	{
		//������̕`��
		CText::DrawString("NEXT STAGE", -225, 0, 25, 25);
		CText::DrawString("Push ENTER Key",
			-200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//���̃V�[���̓Q�[��
			mScene = EGAME;
		}
	}
	
	
	
}
//���̃V�[���̎擾
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
