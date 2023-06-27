#ifndef CSCENESELECT_H
#define CSCENESELECT_H

#include "CScene.h"
#include "CSceneSelect_Data.h"
#include "CTaskManager.h"
#include "CTexture.h"
#include "CKey.h"
#include "CInput.h"
#include "CUtil.h"

/*
シーンのセレクト画面
CSceneSelectクラス
*/


class CSceneSelect : public CScene {
public:
	//デフォルトコンストラクタ
	CSceneSelect();
	//デストラクタ
	~CSceneSelect();

private:
	//選択している場所
	enum class ESelect {
		EBACKGROUND = 0,//背景
		EGAMESTART,		//ゲームスタート
		ETUTORIAL,		//チュートリアル
		EBACKTOTITLE,	//タイトルバック
		EQUITGAME,		//ゲーム終了
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
	bool CSceneSelect::mSceneChange;
	//次のシーンへ移行
	CScene::EScene CSceneSelect::mNextScene;
	//タイトルセレクト場面画像
	CTexture gTitle_Select_Image;
	//タイトルセレクト場面テキスト画像
	CTexture gTitle_Select_Text_Image;
	//ゲーム開始選択時テキスト
	CTexture gTitle_Select_GameStart_Text_Image;
	//チュートリアル開始選択時テキスト
	CTexture gTitle_Select_Tutorial_Text_Image;
	//タイトルバック選択時テキスト
	CTexture gTitle_Select_Back_to_Title_Text_Image;
	//ゲーム終了選択時テキスト
	CTexture gTitle_Select_Quit_Game_Text_Image;
	//ゲームスタート画像
	CTexture gTitle_Select_GameStart_Image;
	//チュートリアルスタート画像
	CTexture gTitle_Select_TutorialStart_Image;
	//タイトルバック画像
	CTexture gTitle_Select_Back_to_Title_Image;
	//ゲーム終了画像
	CTexture gTitle_Select_Quit_Game_Image;
	//ボタンを押したときに描画されるフェイドアウト、イン用背景
	CTexture gTitle_Select_Fade_Image;
	//ボタンを押すとtrue
	bool mIsButtonPush;
	//マウスの座標参照用
	int mMouseX, mMouseY;
};
#endif

