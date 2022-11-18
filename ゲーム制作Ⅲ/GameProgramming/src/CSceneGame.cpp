#include "CSceneGame.h"
//OpenGL
#include "glut.h"


CSceneGame* CSceneGame::mpSceneGameInstance;
//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CSceneGame* CSceneGame::GetInstance()
{
	return mpSceneGameInstance;
}
void CSceneGame::Init() {
	mRes.Init();
}

void CSceneGame::Update() {
	mRes.Update();
}

