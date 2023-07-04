#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include <time.h>
#include "CScene.h"
#include "CRes.h"
#include "CTutorial.h"
#include "CCamera.h"
#include "CXEnemyManager.h"
#include "CXPlayerManager.h"
#include "CMap.h"
#include "CSceneTutorial.h"

//影の設定
#define SHADOWCOLOR_0 0.4f
#define SHADOWCOLOR_1 0.4f
#define SHADOWCOLOR_2 0.4f
#define SHADOWCOLOR_3 0.2f

//光源の位置
#define LIGHTPOS_X 50.0f
#define LIGHTPOS_Y 160.0f
#define LIGHTPOS_Z 50.0f

//2D描画の描画範囲
#define START2D_FIRST_WID 0
#define START2D_END_WID 800
#define START2D_FIRST_HEI 0
#define START2D_END_HEI 600

//GAMECLEAR画像描画座標
#define GAMECLEAR_FIRST_WID 0
#define GAMECLEAR_END_WID 800
#define GAMECLEAR_FIRST_HEI 0
#define GAMECLEAR_END_HEI 600
#define GAMECLEAR_FIRST_X 0
#define GAMECLEAR_END_X 800
#define GAMECLEAR_FIRST_Y 0
#define GAMECLEAR_END_Y 600

//GAMEOVER画像描画座標
#define GAMEOVER_FIRST_WID 0
#define GAMEOVER_END_WID 800
#define GAMEOVER_FIRST_HEI 0
#define GAMEOVER_END_HEI 600
#define GAMEOVER_FIRST_X 0
#define GAMEOVER_END_X 800
#define GAMEOVER_FIRST_Y 0
#define GAMEOVER_END_Y 600

//敵生成数
#define ENEMY_GENERATE_A 1
#define ENEMY_GENERATE_B 1

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
private:
	//デストラクタ
	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//描画処理のオーバーライド
	void Render();
	//シーン変移関数
	EScene GetNextScene();

	//リソースクラスのインスタンス
	CRes mRes;
	//シャドウマップのインスタンス
	CShadowMap mShadowMap;
};
#endif