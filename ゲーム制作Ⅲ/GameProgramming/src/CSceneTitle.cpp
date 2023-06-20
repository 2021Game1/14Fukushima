#include "CSceneTitle.h"

//デフォルトコンストラクタ
CSceneTitle::CSceneTitle()
	: mNextScene(CScene::EScene::ETITLE)
	, mSceneChange()
{
}

//デストラクタ
CSceneTitle::~CSceneTitle()
{
	CTaskManager::Get()->Delete();
}

//Init処理
//一度しか動かさない処理
void CSceneTitle::Init() {
	//シーンの設定
	mScene = CScene::EScene::ETITLE;
	//タイトル画像の追加
	gTitle_Image.Load2D(TITLE_IMAGE);
	Title_Bgm.Load(BGM_TITLE);
	Title_Bgm.Play(BGM_TITLE_VOLUME);
}

//更新処理のオーバーライド
void CSceneTitle::Update() {
	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mNextScene = CScene::EScene::ETUTORIAL;
		mSceneChange = true;
		Title_Bgm.Stop();
	}
	if (mSceneChange) {
		mScene = mNextScene;
	}
}

//描画処理
void CSceneTitle::Render() {
	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	gTitle_Image.Draw(TITLE_FIRST_WID, TITLE_END_WID, TITLE_FIRST_HEI, TITLE_END_HEI, TITLE_FIRST_X, TITLE_END_X, TITLE_END_Y, TITLE_FIRST_Y);
	//2Dの描画終了
	CUtil::End2D();
}

//次のシーンに移行
CScene::EScene CSceneTitle::GetNextScene() {
	//現在のシーンを返す
	return mScene;
}