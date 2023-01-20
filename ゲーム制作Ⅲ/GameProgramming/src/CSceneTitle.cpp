#include "CSceneTitle.h"
#include "CKey.h"
#include "CUtil.h"




CSceneTitle::CSceneTitle()
	: mNextScene(ETITLE)
	, mSceneChange()
{
}

void CSceneTitle::Init() {
	//シーンの設定
	mScene = ETITLE;
	mRes.Init();
	CRes::GetInstance()->GetinSoundBgmTitle().Repeat(0.2);

}

//更新処理のオーバーライド
void CSceneTitle::Update() {
	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム説明
		mNextScene = EGAME;
		mSceneChange = true;
		CRes::GetInstance()->GetinSoundBgmTitle().Stop();
	}
	if (mSceneChange) {
		mScene = mNextScene;
	}
	Render();
}

void CSceneTitle::Render() {
	//2Dの描画開始
	CUtil::Start2D(0, 800, 0, 600);
	CRes::GetInstance()->GetInTitleImage().Draw(0, 800, 0, 600, 0, 800, 600, 0);
	//2Dの描画終了
	CUtil::End2D();
}

CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}