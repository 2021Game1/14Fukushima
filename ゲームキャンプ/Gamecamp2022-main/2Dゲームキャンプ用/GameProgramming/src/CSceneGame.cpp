#include "CSceneGame.h"
#include"CText.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
//タスクマネージャクラスのインクルード
#include "CTaskManager.h"
int CSceneGame::EnemyScore = 0;

//９文字まで描画できる変数
char buf[10];

void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;
	mDf.Init();
	mDs.Init();
	mDk.Init();

	//クラスのメンバ変数への代入
//37
	CPlayer* Player = new CPlayer();
	Player->mEnabled = true;

	

	


	
}

void CSceneGame::Update() {
	//タスクマネージャの更新
	CTaskManager::Get()->Update();
	//コリジョンマネージャの更新
	CTaskManager::Get()->Collision();

	mDs.Update();
	mDf.Update();


	








	//タスクリストの削除
	CTaskManager::Get()->Delete();
	//タスクマネージャの描画	
	CTaskManager::Get()->Render();



}

	


//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	
	return mScene;
}
//デストラクタ
CSceneGame::~CSceneGame() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
