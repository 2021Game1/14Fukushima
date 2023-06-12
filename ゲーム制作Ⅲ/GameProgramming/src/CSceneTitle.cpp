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
	//シーンの設定
	mScene = ETITLE;
	//タイトル画像の追加
	gTitle_Image.Load2D(TITLE_IMAGE);
	Title_Bgm.Load(BGM_TITLE);
	Title_Bgm.Play(BGM_TITLE_VOLUME);
}

//更新処理のオーバーライド
void CSceneTitle::Update() {
	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mNextScene = ETUTORIAL;
		mSceneChange = true;
		Title_Bgm.Stop();
	}
	if (mSceneChange) {
		mScene = mNextScene;
	}
}

void CSceneTitle::Render() {
	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	gTitle_Image.Draw(TITLE_FIRST_WID, TITLE_END_WID, TITLE_FIRST_HEI, TITLE_END_HEI, TITLE_FIRST_X, TITLE_END_X, TITLE_END_Y, TITLE_FIRST_Y);
	//2Dの描画終了
	CUtil::End2D();
}

CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}