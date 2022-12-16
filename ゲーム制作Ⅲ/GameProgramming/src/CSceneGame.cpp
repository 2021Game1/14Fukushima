#include "CSceneGame.h"
//OpenGL
#include "glut.h"



void CSceneGame::Init() {
	mRes.Init();
	//影の設定
	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.2f };	//影の色
	float lightPos[] = { 50.0f, 160.0f, 50.0f };		//光源の位置
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //シャドウマップ初期化
}

void CSceneGame::Update() {
	//更新処理
	CTaskManager::Get()->Update();
	//衝突処理
	CCollisionManager::Get()->Collision();
	//タスクリスト削除
	CTaskManager::Get()->Delete();
}
void CSceneGame::Render() {
	mShadowMap.Render();
	CTaskManager::Get()->Render2D();
	//コライダの描画
	CCollisionManager::Get()->Render();
}
void WholeRender() {
	//タスク描画
	CTaskManager::Get()->Render();
}

