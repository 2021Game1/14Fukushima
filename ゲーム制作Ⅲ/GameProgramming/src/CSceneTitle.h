#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "TitleData.h"

/*
シーンタイトルクラス
*/

class CSceneTitle : public CScene {
private:
	//Init処理
	//一度しか動かさない処理
	void Init();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//次のシーンの取得
	EScene GetNextScene();
	//シーン変移
	bool CSceneTitle::mSceneChange;
	//次のシーンへ移行
	CScene::EScene CSceneTitle::mNextScene;
	//タイトル画像
	CTexture gTitle_Image;
	//タイトルBGM
	CSound Title_Bgm;
public:
	//デフォルトコンストラクタ
	CSceneTitle();
	//デストラクタ
	~CSceneTitle();

};
#endif
