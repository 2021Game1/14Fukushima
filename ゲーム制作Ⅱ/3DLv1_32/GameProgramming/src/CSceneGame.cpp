//シーンゲームクラスのインクルード
#include "CSceneGame.h"
//OpenGL
#include"glut.h"
 
int CSceneGame::Score;

CSound Se2;//取得音
CSound Se3;//衝突音1

void CSceneGame::Init() {
	Se2.Load("res\\音楽\\money.wav");
	Se3.Load("res\\音楽\\crash.wav");
	mGameTest.Init();
}

void CSceneGame::Update() {
	//タスクマネージャの更新
	CTaskManager::Get()->Update();
	//コリジョンマネージャの衝突処理
	CTaskManager::Get()->TaskCollision();
	
	mGameTest.Update();

	////コリジョンマネージャのコライダ描画
	//CCollisionManager::Get()->Render();
	//タスクリストの削除
	CTaskManager::Get()->Delete();
	//タスクマネージャの描画	
	CTaskManager::Get()->Render();


}



