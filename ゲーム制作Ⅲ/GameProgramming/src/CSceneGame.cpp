#include "CSceneGame.h"
//OpenGL
#include "glut.h"


CSceneGame* CSceneGame::mpSceneGameInstance;
//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
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

