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
	Title_Bgm.Play(BGM_TITLE_VOLUME);
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
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	gTitle_Image.Draw(TITLE_FIRST_WID, TITLE_END_WID, TITLE_FIRST_HEI, TITLE_END_HEI, TITLE_FIRST_X, TITLE_END_X, TITLE_END_Y, TITLE_FIRST_Y);
	//2D�̕`��I��
	CUtil::End2D();
}

CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}