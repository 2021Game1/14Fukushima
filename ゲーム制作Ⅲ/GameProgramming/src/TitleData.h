#ifndef TITLEDATA_H
#define TITLEDATA_H

#include"CTexture.h"
#include "CSound.h"
#include "CTaskManager.h"
#include "CKey.h"
#include "CUtil.h"

//タイトル画像
#define TITLE_IMAGE "res\\Image\\Title_Image.png"
//選択画面
#define TITLE_SELECT_IMAGE "res\\Image\\Title_Select.png"
//ゲームスタートボタン
#define TITLE_SELECT_GAMESTART_IMAGE "res\\Image\\Game_Start.png"
//チュートリアルスタートボタン
#define TITLE_SELECT_TUTORIALSTART_IMAGE "res\\Image\\Tutorial_Start.png"
//タイトルセレクトテキスト
#define TITLE_SELECT_TEXT "res\\Image\\Title_Text.png"
//ゲーム開始選択時テキスト
#define TITLE_SELECT_GAMESTART_TEXT "res\\Image\\Title_Select_Game_Text.png"
//チュートリアル開始選択時テキスト
#define TITLE_SELECT_TUTORIAL_TEXT "res\\Image\\Title_Select_Tutorial_Text.png"
//ボタンを押したときに描画されるフェイドアウト、イン用背景
#define TITLE_SELECT_FADE_IMAGE "res\\Image\\Fade.png"


//2D描画の描画範囲
#define START2D_FIRST_WID 0
#define START2D_END_WID 800
#define START2D_FIRST_HEI 0
#define START2D_END_HEI 600

//タイトル画像描画座標
#define TITLE_FIRST_WID 0
#define TITLE_END_WID 800
#define TITLE_FIRST_HEI 0
#define TITLE_END_HEI 600
#define TITLE_FIRST_X 0
#define TITLE_END_X 800
#define TITLE_FIRST_Y 0
#define TITLE_END_Y 600

//タイトル選択画像描画座標
#define TITLE_SELECT_FIRST_WID 0
#define TITLE_SELECT_END_WID 800
#define TITLE_SELECT_FIRST_HEI 0
#define TITLE_SELECT_END_HEI 600
#define TITLE_SELECT_FIRST_X 0
#define TITLE_SELECT_END_X 800
#define TITLE_SELECT_FIRST_Y 0
#define TITLE_SELECT_END_Y 600

//タイトル選択テキスト画像描画座標
#define TITLE_SELECT_TEXT_FIRST_WID 0
#define TITLE_SELECT_TEXT_END_WID 800
#define TITLE_SELECT_TEXT_FIRST_HEI 0
#define TITLE_SELECT_TEXT_END_HEI 600
#define TITLE_SELECT_TEXT_FIRST_X 0
#define TITLE_SELECT_TEXT_END_X 800
#define TITLE_SELECT_TEXT_FIRST_Y 0
#define TITLE_SELECT_TEXT_END_Y 600

//ゲームスタート選択時テキスト画像描画座標
#define TITLE_SELECT_GAMESTART_TEXT_FIRST_WID 0
#define TITLE_SELECT_GAMESTART_TEXT_END_WID 800
#define TITLE_SELECT_GAMESTART_TEXT_FIRST_HEI 0
#define TITLE_SELECT_GAMESTART_TEXT_END_HEI 600
#define TITLE_SELECT_GAMESTART_TEXT_FIRST_X 0
#define TITLE_SELECT_GAMESTART_TEXT_END_X 800
#define TITLE_SELECT_GAMESTART_TEXT_FIRST_Y 0
#define TITLE_SELECT_GAMESTART_TEXT_END_Y 600

//チュートリアル選択時テキスト画像描画座標
#define TITLE_SELECT_TUTORIAL_TEXT_FIRST_WID 0
#define TITLE_SELECT_TUTORIAL_TEXT_END_WID 800
#define TITLE_SELECT_TUTORIAL_TEXT_FIRST_HEI 0
#define TITLE_SELECT_TUTORIAL_TEXT_END_HEI 600
#define TITLE_SELECT_TUTORIAL_TEXT_FIRST_X 0
#define TITLE_SELECT_TUTORIAL_TEXT_END_X 800
#define TITLE_SELECT_TUTORIAL_TEXT_FIRST_Y 0
#define TITLE_SELECT_TUTORIAL_TEXT_END_Y 600

//スタートボタン座標
#define STARTBUTTON_LEFT 270	//スタートボタン左座標
#define STARTBUTTON_RIGHT 530	//スタートボタン右座標
#define STARTBUTTON_DOWN 240	//スタートボタン下座標
#define STARTBUTTON_UP 300		//スタートボタン上座標
#define STARTBUTTON_FIRST_X 0	//スタートボタン最初のX座標
#define STARTBUTTON_END_X 245	//スタートボタン終わりのX座標
#define STARTBUTTON_FIRST_Y 0	//スタートボタン最初のY座標
#define STARTBUTTON_END_Y 81	//スタートボタン終わりのY座標

//チュートリアルボタン座標
#define TUTORIALBUTTON_LEFT 270		//チュートリアルボタン左座標
#define TUTORIALBUTTON_RIGHT 530	//チュートリアルボタン右座標
#define TUTORIALBUTTON_DOWN 140		//チュートリアルボタン下座標
#define TUTORIALBUTTON_UP 200		//チュートリアルボタン上座標
#define TUTORIALBUTTON_FIRST_X 0	//チュートリアルボタン最初のX座標
#define TUTORIALBUTTON_END_X 245	//チュートリアルボタン終わりのX座標
#define TUTORIALBUTTON_FIRST_Y 0	//チュートリアルボタン最初のY座標
#define TUTORIALBUTTON_END_Y 81	//チュートリアルボタン終わりのY座標

//タイトルBGM
#define BGM_TITLE "res\\Bgm\\Bgm_Title.wav"
//タイトルBGM音量
#define BGM_TITLE_VOLUME 0.2



#endif 