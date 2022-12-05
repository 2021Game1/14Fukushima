#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include <time.h>
#include "CScene.h"
#include "CRes.h"



/*
ゲームのシーン
*/
class CSceneGame : public CScene {
	CRes mRes;
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//staticで処理を作る
	static CSceneGame* GetInstance();

};

#endif