#include "CSceneTutorial.h"
//OpenGL
#include "glut.h"


CSceneTutorial::~CSceneTutorial()
{
	CTaskManager::Get()->Delete();
}

void CSceneTutorial::Init() {
	//シーンの設定
	mScene = ETUTORIAL;
	mRes.Init();
	CRes::GetInstance()->GetinSoundBgmGame().Repeat(0.2);
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
	if (CXEnemy::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{

			mScene = EGAME;
		}
	}

	mTutorial.Update();

	if (mTutorial.GetIsTutorialFlag() == true) {
		//更新処理
		CTaskManager::Get()->Update();
		//衝突処理
		CCollisionManager::Get()->Collision();
	}



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

void WholeRender() {
	//タスク描画
	CTaskManager::Get()->Render();
}
CScene::EScene CSceneTutorial::GetNextScene()
{
	return mScene;
}