#ifndef CSCENETUTORIAL_H
#define CSCENETUTORIAL_H
#include <time.h>
#include "CScene.h"
#include "CRes.h"
#include "CTutorial.h"

//影の設定
#define SHADOWCOLOR_0 0.4f
#define SHADOWCOLOR_1 0.4f
#define SHADOWCOLOR_2 0.4f
#define SHADOWCOLOR_3 0.2f

//光源の位置
#define LIGHTPOS_X 50.0f
#define LIGHTPOS_Y 160.0f
#define LIGHTPOS_Z 50.0f

//チュートリアルステージに出現する敵の数
#define TUTORIAL_GENERATE_A 1

/*
ゲームのシーン
*/
class CSceneTutorial : public CScene {
private:
	~CSceneTutorial();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//描画処理のオーバーライド
	void Render();
	//シーン変移関数
	EScene GetNextScene();

	//チュートリアルのインスタンス
	CTutorial mTutorial;
	//リソースクラスのインスタンス
	CRes mRes;
	//シャドウマップのインスタンス
	CShadowMap mShadowMap;
};
void WholeRender();
#endif
