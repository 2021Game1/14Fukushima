#include "CSceneManager.h"
#include "CSceneGame.h"
#include "CSceneTitle.h"
#include "CSceneTutorial.h"

//�f�t�H���g�R���X�g���N�^
CSceneManager::CSceneManager()
	: mpScene(nullptr)
	, mScene(CScene::EScene::ETITLE)
{}
//�f�X�g���N�^�i�폜�����Ƃ��Ɏ��s����܂��j
CSceneManager::~CSceneManager() {
	//�V�[��������΍폜
	if (mpScene)
		//�V�[���̍폜
		delete mpScene;
	mpScene = nullptr;
}
//����������
void CSceneManager::Init() {
	//�V�[���̎��ʂ�ݒ肷��
	mScene = CScene::EScene::ETITLE;
	//�V�[���𐶐����A�|�C���^��ݒ肷��
	mpScene = new CSceneTitle();
	//���������N���X�̃��\�b�h���Ă΂��
	mpScene->Init();
}
//�X�V����
void CSceneManager::Update() {
	//�|�C���^��Update���Ă�
	mpScene->Update();
	//���̃V�[�����擾���قȂ邩����
	if (mScene != mpScene->GetNextScene()) {
		mScene = mpScene->GetNextScene();

		delete mpScene;//���̃V�[���폜
		//�Y������V�[���𐶐�
		switch (mScene) {
		case CScene::CScene::EScene::EGAME:
			mpScene = new CSceneGame();
			mpScene->Init();
			break;

		case CScene::CScene::EScene::ETUTORIAL:
			mpScene = new CSceneTutorial();
			mpScene->Init();
			break;

		case CScene::CScene::EScene::ETITLE:
			mpScene = new CSceneTitle();
			mpScene->Init();
			break;
		}
	}
}

//�`�揈��
void CSceneManager::Render()
{
	//�|�C���^�̕`�揈�����Ă�
	if (mpScene) {
		mpScene->Render();
	}
}
