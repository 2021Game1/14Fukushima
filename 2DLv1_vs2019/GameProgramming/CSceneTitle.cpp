#include "CSceneTitle.h"
#include "CKey.h"



void CSceneTitle::Init() {
	//�V�[���̐ݒ�
	mScene = ETITLE;
	
}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {
		//������̕`��
		CText::DrawString("TITLE", -150, 100, 40, 40);
		CText::DrawString("Push ENTER Key",
			-200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//���̃V�[���̓Q�[��
			mScene = EGAME;
		}

	


	
	
	
}
//���̃V�[���̎擾
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
