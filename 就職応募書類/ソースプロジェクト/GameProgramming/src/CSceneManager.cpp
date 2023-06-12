#include "CSceneManager.h"
#include "CSceneGame.h"
#include "CSceneTitle.h"
#include "CSceneTutorial.h"

//コンストラクタ
CSceneManager::CSceneManager()
	: mpScene(nullptr)
	, mScene(CScene::ETITLE)
{}
//デストラクタ（削除されるときに実行されます）
CSceneManager::~CSceneManager() {
	//シーンがあれば削除
	if (mpScene)
		//シーンの削除
		delete mpScene;
	mpScene = nullptr;
}
//初期化処理
void CSceneManager::Init() {
	//シーンの識別を設定する
	mScene = CScene::ETITLE;
	//シーンを生成し、ポインタを設定する
	mpScene = new CSceneTitle();
	//生成したクラスのメソッドが呼ばれる
	mpScene->Init();
}
//更新処理
void CSceneManager::Update() {
	//ポインタのUpdateを呼ぶ
	mpScene->Update();
	//次のシーンを取得し異なるか判定
	if (mScene != mpScene->GetNextScene()) {
		mScene = mpScene->GetNextScene();

		delete mpScene;//今のシーン削除
		//該当するシーンを生成
		switch (mScene) {
		case CScene::EGAME:
			mpScene = new CSceneGame();
			mpScene->Init();
			break;

		case CScene::ETUTORIAL:
			mpScene = new CSceneTutorial();
			mpScene->Init();
			break;

		case CScene::ETITLE:
			mpScene = new CSceneTitle();
			mpScene->Init();
			break;
		}
	}
}

//描画処理
void CSceneManager::Render()
{
	//ポインタの描画処理を呼ぶ
	if (mpScene) {
		mpScene->Render();
	}
}
