#include "CSceneTitle.h"
#include "CKey.h"

int CSceneTitle::mStage = 0;

void CSceneTitle::Init() {
	//シーンの設定
	mScene = ETITLE;
	
}

//更新処理のオーバーライド
void CSceneTitle::Update() {
	if (mStage == 0) {
	//文字列の描画
	CText::DrawString("TITLE", -200, 0, 50, 50);
	CText::DrawString("Push ENTER Key",
		-200, -100, 16, 16);
	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = EGAME;
	}
	}
	if (CKey::Once('V'))
	{
		if (mStage > 0)
		{
			mStage -= 1;
		}
	}
	if (CKey::Once('B'))
	{
		if (mStage < 5)
		{
			mStage += 1;
		}
	}
	if (mStage == 1)
	{
		//文字列の描画
		CText::DrawString("STAGE_A", -220, 0, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//次のシーンはゲーム
			mScene = EGAME_A;
		}
	}
	if (mStage == 2)
	{
		//文字列の描画
		CText::DrawString("STAGE_B", -220, 0, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//次のシーンはゲーム
			mScene = EGAME_B;
		}
	}
	if (mStage == 3)
	{
		//文字列の描画
		CText::DrawString("STAGE_C", -220, 0, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//次のシーンはゲーム
			mScene = EGAME_C;
		}
	}
	if (mStage == 4)
	{
		//文字列の描画
		CText::DrawString("STAGE_D", -220, 0, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//次のシーンはゲーム
			mScene = EGAME_D;
		}
	}
	if (mStage == 5)
	{
		//文字列の描画
		CText::DrawString("STAGE_E", -220, 0, 40, 40);
		CText::DrawString("Push ENTER Key", -200, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			//次のシーンはゲーム
			mScene = EGAME_E;
		}
	}

}
//次のシーンの取得
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
