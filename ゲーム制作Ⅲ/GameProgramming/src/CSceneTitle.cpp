#include "CSceneTitle.h"
#include "CKey.h"
#include "CUtil.h"




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
	mRes.Init();
	CRes::GetInstance()->GetinSoundBgmTitle().Repeat(0.2);

}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {
	if (CKey::Once(VK_RETURN)) {
		//���̃V�[���̓Q�[��
		mNextScene = EGAME;
		mSceneChange = true;
		CRes::GetInstance()->GetinSoundBgmTitle().Stop();
	}
	if (mSceneChange) {
		mScene = mNextScene;
	}
}

void CSceneTitle::Render() {
	//2D�̕`��J�n
	CUtil::Start2D(0, 800, 0, 600);
	CRes::GetInstance()->GetInTitleImage().Draw(0, 800, 0, 600, 0, 800, 600, 0);
	//2D�̕`��I��
	CUtil::End2D();
}

CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}