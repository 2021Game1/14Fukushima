#include "CSceneGame.h"
//OpenGL
#include "glut.h"



void CSceneGame::Init() {
	mRes.Init();
}

void CSceneGame::Update() {
	CTaskManager::Get()->Update();
	mRes.Update();
	CTaskManager::Get()->Render();
	CTaskManager::Get()->Render2D();
	//コライダの描画
	CCollisionManager::Get()->Render();
	//衝突処理
	CCollisionManager::Get()->Collision();
	//タスクリスト削除
	CTaskManager::Get()->Delete();
}

