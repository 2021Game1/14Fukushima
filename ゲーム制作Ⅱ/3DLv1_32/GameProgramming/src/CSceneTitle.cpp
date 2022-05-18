//#include "CSceneTitle.h"
//#include "CKey.h"
//#include "CSceneManager.h"
//
////シーンマネージャのインスタンス
//CSceneManager mSceneManager;
//
//void CSceneTitle::Init() {
//	//シーンの設定
//	mScene = ETITLE;
//	//テクスチャファイルの読み込み(1行64列)
//	text.LoadTexture("FontGreen.tga", 1, 64);
//}
//
////更新処理のオーバーライド
//void CSceneTitle::Update() {
//
//	//2Dの描画開始
//	CUtil::Start2D(-400, 400, -300, 300);
//	//描画色の設定(緑色の半透明)
//	glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
//	//文字列編集エリアの作成
//	char buf[64];
//	//文字列の描画
//	text.DrawString("TITLE", -130, 85, 30, 30);
//	//文字列の描画
//	text.DrawString("PUSH ENTER KEY", -216, -20, 16, 16);
//	if (CKey::Once(VK_RETURN)) {
//		//次のシーンはゲーム
//		mScene = EGAME;
//		//シーンマネージャの初期化
//		mSceneManager.Init();
//	}
//	//2Dの描画終了
//	CUtil::End2D();
//
//
//
//
//
//
//}
////次のシーンの取得
//CScene::EScene CSceneTitle::GetNextScene() {
//	return mScene;
//}