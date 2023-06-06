#include "CSceneGame.h"
//OpenGL
#include "glut.h"


CSceneGame::~CSceneGame()
{
	CXEnemyManager::GetInstance()->Release();
	CXPlayerManager::GetInstance()->Release();
	CMap::GetInstance()->Release();
	CSkyMap::GetInstance()->Release();
	CTaskManager::Get()->Delete();
}

void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;
	//マップ設定
	CMap::GetInstance()->Generate();
	CSkyMap::GetInstance()->Generate();
	//リソースの読み込み設定
	mRes.Init();
	//BGMセット(リピート）
	CRes::GetInstance()->GetinSoundBgmGame().Repeat(0.2);
	//プレイヤ管理生成
	CXPlayerManager::GetInstance()->Generate();

	//プレイヤ生成
	CXPlayerManager::GetInstance()->PlayerGenerate();
	//敵管理生成1
	CXEnemyManager::GetInstance()->Generate();
	//敵生成
	CXEnemyManager::GetInstance()->EnemyGenerate(ENEMY_GENERATE_A, CXEnemy::EEnemyType::ETYPE_GAME_1);
	//敵管理生成2
	CXEnemyManager::GetInstance()->Generate();
	//敵生成
	CXEnemyManager::GetInstance()->EnemyGenerate(ENEMY_GENERATE_B, CXEnemy::EEnemyType::ETYPE_GAME_2);
	//影の設定
	float shadowColor[] = { SHADOWCOLOR_0, SHADOWCOLOR_1, SHADOWCOLOR_2, SHADOWCOLOR_3 };	//影の色
	float lightPos[] = { LIGHTPOS_X, LIGHTPOS_Y, LIGHTPOS_Z };		//光源の位置
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //シャドウマップ初期化
}

void CSceneGame::Update() {
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{

			mScene = ETITLE;
		}
	}
	if (CXEnemy::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{

			mScene = ETITLE;
		}
	}

	//更新処理
	CTaskManager::Get()->Update();
	//衝突処理
	CCollisionManager::Get()->Collision();



	//タスクリスト削除
	CTaskManager::Get()->Delete();
}
void CSceneGame::Render() {
	CTaskManager::Get()->Draw();
	mShadowMap.Render();
	CTaskManager::Get()->Render2D();

	//デバッグバージョンのみ有効
#ifdef _DEBUG
	//コライダの描画
	CCollisionManager::Get()->Render();
#endif
	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameOverImage().DrawImage(GAMEOVER_FIRST_WID, GAMEOVER_END_WID, GAMEOVER_FIRST_HEI, GAMEOVER_END_HEI, GAMEOVER_FIRST_X, GAMEOVER_END_X, GAMEOVER_END_Y, GAMEOVER_FIRST_Y);
	}
	if (CXEnemy::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameClearImage().DrawImage(GAMECLEAR_FIRST_WID, GAMECLEAR_END_WID, GAMECLEAR_FIRST_HEI, GAMECLEAR_END_HEI, GAMECLEAR_FIRST_X, GAMECLEAR_END_X, GAMECLEAR_END_Y, GAMECLEAR_FIRST_Y);
	}
	//2Dの描画終了
	CUtil::End2D(); {
	}
}
CScene::EScene CSceneGame::GetNextScene()
{
	return mScene;
}





