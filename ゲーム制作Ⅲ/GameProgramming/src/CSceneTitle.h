#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "TitleData.h"
#include "CInput.h"

/*
シーンタイトルクラス
*/

class CSceneTitle : public CScene {
private:
	//選択している場所
	enum ESelect {
		EBACKGROUND = 0,//背景
		EGAMESTART,		//ゲームスタート
		ETUTORIAL,		//チュートリアル
	};
	ESelect mSelect; //選択している場所の判断用

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
	//タイトルセレクト画像
	CTexture gTitle_Select_Image;
	//ゲームスタート画像
	CTexture gTitle_Select_GameStart_Image;
	//チュートリアルスタート画像
	CTexture gTitle_Select_TutorialStart_Image;
	//ボタンを押すとtrue
	bool mIsButtonPush;
	//チュートリアル開始の画像のフラグ
	bool mTutorialflag;
	//チュートリアル終了の画像フラグ
	bool mTitleflag;
	//タイトルBGM
	CSound Title_Bgm;
	//マウスの座標参照用
	int mMouseX, mMouseY;

public:
	//デフォルトコンストラクタ
	CSceneTitle();
	//デストラクタ
	~CSceneTitle();

};
#endif
