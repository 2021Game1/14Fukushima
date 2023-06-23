#include "CSceneTutorial.h"
//OpenGL
#include "glut.h"


//デストラクタ
CSceneTutorial::~CSceneTutorial()
{
	//敵の管理削除
	CXEnemyManager::GetInstance()->~CXEnemyManager();
	//プレイヤを削除
	CXPlayerManager::GetInstance()->Release();
	//ステージマップを削除
	CMap::GetInstance()->Release();
	//空の背景マップを削除
	CSkyMap::GetInstance()->Release();
	//タスクマネージャの削除
	CTaskManager::Get()->Delete();
}
//Init処理
//一度しか動かさない処理
void CSceneTutorial::Init() {
	//シーンの設定
	//チュートリアルにシーンを設定
	mScene = CScene::EScene::ETUTORIAL;
	//地上マップの生成
	CMap::GetInstance()->Generate();
	//背景マップの生成
	CSkyMap::GetInstance()->Generate();
	//リソースの読み込み設定
	mRes.Init();
	//BGMセット(リピート）
	CRes::GetInstance()->GetinSoundBgmGame().Repeat(0.2);
	//プレイヤ管理生成
	CXPlayerManager::GetInstance()->Generate();
	//敵管理生成
	CXEnemyManager::GetInstance()->Generate();
	//プレイヤ生成
	CXPlayerManager::GetInstance()->PlayerGenerate();
	//敵生成
	CXEnemyManager::GetInstance()->EnemyGenerate(TUTORIAL_GENERATE_A, CXEnemy::EEnemyType::ETYPE_TUTORIAL);
	//カメラ初期化
	Camera.Init();
	//カメラターゲット
	Camera.SetTarget(CXPlayer::GetInstance()->Position());
	//影の設定
	float shadowColor[] = { SHADOWCOLOR_0, SHADOWCOLOR_1, SHADOWCOLOR_2, SHADOWCOLOR_3 };	//影の色
	float lightPos[] = { LIGHTPOS_X, LIGHTPOS_Y, LIGHTPOS_Z };		//光源の位置
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //シャドウマップ初期化
}
//更新処理
void CSceneTutorial::Update() {
	//プレイヤHPが0になったら実行
	if (CXPlayer::GetInstance()->GetHp() == NULL) {
		//ゲームBGMを止める
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		//Enterキーを押したら、タイトルシーンに切り替える
		if (CKey::Once(VK_RETURN))
		{
			//シーンをタイトルシーンに設定
			mScene = CScene::EScene::ETITLE;
		}
	}
	//エネミーマネージャに格納されている敵が全て死亡してるなら実行
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		//ゲームBGMを止める
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		//Enterキーを押したら、本番のゲームシーンに切り替える
		if (CKey::Once(VK_RETURN))
		{
			//シーンをゲームシーンに設定
			mScene = CScene::EScene::EGAME;
		}
	}
	//チュートリアルクラスのUpdateを呼び出す
	mTutorial.Update();

	//タスクマネージャに格納されている全ての更新処理を呼び出す
	CTaskManager::Get()->Update();
	//コリジョンマネージャに格納されている全ての衝突処理を呼び出す
	CCollisionManager::Get()->Collision();
	//エネミーマネージャの更新処理を呼び出す
	CXEnemyManager::GetInstance()->Update();


	//タスクリスト削除
	CTaskManager::Get()->Delete();
}
//描画処理
void CSceneTutorial::Render() {
	//タスクマネージャの描画を呼び出す
	CTaskManager::Get()->Draw();
	//影の描画を取得
	mShadowMap.Render();
	//チュートリアルのフラグがtrueの時、タスクマネージャの2D描画される
	if (mTutorial.GetIsTutorialFlag() == true) {
		CTaskManager::Get()->Render2D();
	}

	//デバッグバージョンのみ有効
#ifdef _DEBUG
	//コライダの描画
	CCollisionManager::Get()->Render();
#endif
	//チュートリアルの描画
	mTutorial.Render();

}
//次のシーン取得
CScene::EScene CSceneTutorial::GetNextScene()
{
	//現在のシーンを返す
	return mScene;
}
//影の描画のために外部からタスク描画
//影の描画時、1度全て描画するものを消し影を描画してから全て描画するものを描画しなおす
void WholeRender() {
	//タスク描画
	CTaskManager::Get()->Render();
}