#include "CSceneTitle.h"

CSceneTitle::CSceneTitle()
	: mNextScene(ETITLE)
	, mSceneChange()
{
}

CSceneTitle::~CSceneTitle()
{
	CTaskManager::Get()->Delete();
}

void CSceneTitle::Init() {
	//�V�[���̐ݒ�
	mScene = ETITLE;
	//�^�C�g���摜�̒ǉ�
	gTitle_Image.Load2D(TITLE_IMAGE);
	Title_Bgm.Load(BGM_TITLE);

}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {
	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mNextScene = ETUTORIAL;
		mSceneChange = true;
		Title_Bgm.Stop();
	}
	if (mSceneChange) {
		mScene = mNextScene;
	}
}

void CSceneTitle::Render() {
	//2D�̕`��J�n
	CUtil::Start2D(0, 800, 0, 600);
	gTitle_Image.Draw(0, 800, 0, 600, 0, 800, 600, 0);
	//2D�̕`��I��
	CUtil::End2D();
}

CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}