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
	//シャドウマップのインスタンス
	CShadowMap mShadowMap;
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//描画処理のオーバーライド
	void Render();
};
void WholeRender();
#endif