#include "CSceneTitle.h"
#include "CKey.h"
#include "CRectangle.h"

extern CTexture Title;


void CSceneTitle::Init() {
	//シーンの設定
	mScene = ETITLE;


}



//void CSceneTitle::Render() {
//	
//	Draw(Title,0,1920, 1080,0,0,0,0);
//
//}







//更新処理のオーバーライド
void CSceneTitle::Update() {
	Title.Draw(-1000, 1000, -520, 520, 0, 1920, 1080, 0);
	//文字列の描画
	/*CText::DrawString("TITLE", -200, 0, 50, 50);
	CText::DrawString("Push ENTER Key",
		-200, -100, 16, 16);*/
	
	
	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = EGAME;
	}
}




//次のシーンの取得
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
