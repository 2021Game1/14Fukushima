//#include "CSceneTitle.h"
//#include "CKey.h"
//#include "CSceneManager.h"
//
////�V�[���}�l�[�W���̃C���X�^���X
//CSceneManager mSceneManager;
//
//void CSceneTitle::Init() {
//	//�V�[���̐ݒ�
//	mScene = ETITLE;
//	//�e�N�X�`���t�@�C���̓ǂݍ���(1�s64��)
//	text.LoadTexture("FontGreen.tga", 1, 64);
//}
//
////�X�V�����̃I�[�o�[���C�h
//void CSceneTitle::Update() {
//
//	//2D�̕`��J�n
//	CUtil::Start2D(-400, 400, -300, 300);
//	//�`��F�̐ݒ�(�ΐF�̔�����)
//	glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
//	//������ҏW�G���A�̍쐬
//	char buf[64];
//	//������̕`��
//	text.DrawString("TITLE", -130, 85, 30, 30);
//	//������̕`��
//	text.DrawString("PUSH ENTER KEY", -216, -20, 16, 16);
//	if (CKey::Once(VK_RETURN)) {
//		//���̃V�[���̓Q�[��
//		mScene = EGAME;
//		//�V�[���}�l�[�W���̏�����
//		mSceneManager.Init();
//	}
//	//2D�̕`��I��
//	CUtil::End2D();
//
//
//
//
//
//
//}
////���̃V�[���̎擾
//CScene::EScene CSceneTitle::GetNextScene() {
//	return mScene;
//}