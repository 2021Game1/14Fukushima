#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"

#include "CGameTest.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

	CGameTest mGameTest;
	int Repoptime;

};

#endif
