#include "CSceneGame.h"
//OpenGL
#include "glut.h"

//デストラクタ
CSceneGame::~CSceneGame()
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
	//カメラの削除
	CCamera::Instance()->~CCamera();
}
//Init処理
//一度しか動かさない処理
void CSceneGame::Init() {
	//シーンの設定
	//シーンにゲームシーンを設定する
	mScene = CScene::EScene::EGAME;
	//マップを生成
	CMap::GetInstance()->Generate();
	//マップ背景を生成
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
	CXEnemyManager::GetInstance()->EnemyGenerate(ENEMY_GENERATE_A, CXEnemy::EEnemyType::ETYPE_GAME_1);
	//影の設定
	float shadowColor[] = { SHADOWCOLOR_0, SHADOWCOLOR_1, SHADOWCOLOR_2, SHADOWCOLOR_3 };	//影の色
	float lightPos[] = { LIGHTPOS_X, LIGHTPOS_Y, LIGHTPOS_Z };		//光源の位置
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //シャドウマップ初期化
}
//更新処理
void CSceneGame::Update() {
	//プレイヤHPが0になったら実行
	if (CXPlayer::GetInstance()->GetHp() == NULL) {
		//ゲームBGMを止める
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		//Enterキーを押したら、タイトルシーンに切り替える
		if (CKey::Once(VK_RETURN))
		{

			mScene = CScene::EScene::ETITLE;
		}
	}
	//エネミーマネージャに格納されている敵が全て死亡してるなら実行
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		//ゲームBGMを止める
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		//Enterキーを押したら、タイトルシーンに切り替える
		if (CKey::Once(VK_RETURN))
		{
			mScene = CScene::EScene::ETITLE;
		}
	}

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
void CSceneGame::Render() {
	//タスクマネージャの描画を呼び出す
	CTaskManager::Get()->Draw();
	//影の描画を取得
	mShadowMap.Render();
	//タスクマネージャの2D描画を呼び出す
	CTaskManager::Get()->Render2D();

	//デバッグバージョンのみ有効
#ifdef _DEBUG
	//コライダの描画
	CCollisionManager::Get()->Render();
#endif
	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	//プレイヤのHPが0だったら実行
	if (CXPlayer::GetInstance()->GetHp() == NULL) {
		//ゲームオーバー画像を描画
		CRes::GetInstance()->GetinGameOverImage().DrawImage(GAMEOVER_FIRST_WID, GAMEOVER_END_WID, GAMEOVER_FIRST_HEI, GAMEOVER_END_HEI, GAMEOVER_FIRST_X, GAMEOVER_END_X, GAMEOVER_END_Y, GAMEOVER_FIRST_Y);
	}
	//敵のマネージャクラスに格納されている敵が全て死亡状態であれば実行
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		//ゲームクリア画像を描画
		CRes::GetInstance()->GetinGameClearImage().DrawImage(GAMECLEAR_FIRST_WID, GAMECLEAR_END_WID, GAMECLEAR_FIRST_HEI, GAMECLEAR_END_HEI, GAMECLEAR_FIRST_X, GAMECLEAR_END_X, GAMECLEAR_END_Y, GAMECLEAR_FIRST_Y);
	}
	//2Dの描画終了
	CUtil::End2D(); {
	}
}
//次のシーンを取得
CScene::EScene CSceneGame::GetNextScene()
{
	//現在のシーンを返す
	return mScene;
}





