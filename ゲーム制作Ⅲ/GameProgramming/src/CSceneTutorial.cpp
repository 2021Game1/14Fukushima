#include "CSceneTutorial.h"
//OpenGL
#include "glut.h"


CSceneTutorial::~CSceneTutorial()
{
	CXEnemyManager::GetInstance()->Release();	//敵管理解放
	CXPlayerManager::GetInstance()->Release();	//プレイヤ管理開放
	CMap::GetInstance()->Release();
	CSkyMap::GetInstance()->Release();
	CTaskManager::Get()->Delete();
}

void CSceneTutorial::Init() {
	//シーンの設定
	mScene = ETUTORIAL;
	//カメラ初期化
	Camera.Init();
	//マップ設定
	CMap::GetInstance()->Generate();
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
	//影の設定
	float shadowColor[] = { SHADOWCOLOR_0, SHADOWCOLOR_1, SHADOWCOLOR_2, SHADOWCOLOR_3 };	//影の色
	float lightPos[] = { LIGHTPOS_X, LIGHTPOS_Y, LIGHTPOS_Z };		//光源の位置
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //シャドウマップ初期化
}

void CSceneTutorial::Update() {

	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{

			mScene = ETITLE;
		}
	}
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{
			mScene = EGAME;
		}
	}

	mTutorial.Update();

	//更新処理
	CTaskManager::Get()->Update();
	//衝突処理
	CCollisionManager::Get()->Collision();
	CXEnemyManager::GetInstance()->Update();


	//タスクリスト削除
	CTaskManager::Get()->Delete();
}
void CSceneTutorial::Render() {
	CTaskManager::Get()->Draw();
	mShadowMap.Render();
	if (mTutorial.GetIsTutorialFlag() == true) {
		CTaskManager::Get()->Render2D();
	}

	//デバッグバージョンのみ有効
#ifdef _DEBUG
	//コライダの描画
	CCollisionManager::Get()->Render();
#endif
	mTutorial.Render();

}
CScene::EScene CSceneTutorial::GetNextScene()
{
	return mScene;
}
void WholeRender() {
	//タスク描画
	CTaskManager::Get()->Render();
}