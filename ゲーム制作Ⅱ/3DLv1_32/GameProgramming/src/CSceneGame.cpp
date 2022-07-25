//シーンゲームクラスのインクルード
#include "CSceneGame.h"
//OpenGL
#include"glut.h"
 



void CSceneGame::Init() {
	mGameTest.Init();
}

void CSceneGame::Update() {
	//タスクマネージャの更新
	CTaskManager::Get()->Update();
	//コリジョンマネージャの衝突処理
	CTaskManager::Get()->TaskCollision();
	
	mGameTest.Update();

	//コリジョンマネージャのコライダ描画
	CCollisionManager::Get()->Render();
	//タスクリストの削除
	CTaskManager::Get()->Delete();
	//タスクマネージャの描画	
	CTaskManager::Get()->Render();


}



