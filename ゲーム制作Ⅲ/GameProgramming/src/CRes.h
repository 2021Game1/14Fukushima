#ifndef CRES_H
#define CRES_H

#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"
#include "CText.h"
#include "CEffect.h"
#include "CShadowMap.h"
#include "CSound.h"

//シャドウマッピング用マクロ
#define TEXWIDTH  8192	//テクスチャ幅
#define TEXHEIGHT  6144	//テクスチャ高さ

/*画像, UI*/
//ゲームクリア画像
#define GAMECLEAR_IMAGE "res\\Image\\GameClear.png"
//ゲームオーバー画像
#define GAMEOVER_IMAGE "res\\Image\\GameOver_Image.png"
//チュートリアル画像
//チュートリアル終了画像
#define TUTORIAL_END_IMAGE "res\\Image\\Tutorial_End.png"
//アクションチュートリアル画像
#define ACTION_TUTORIAL_IMAGE "res\\Image\\Action_Tutorial.png"
//移動チュートリアル画像
#define MOVE_TUTORIAL_IMAGE "res\\Image\\Move_Tutorial.png"
//回避アクションチュートリアル画像
#define AVOIDANCE_TUTORIAL_IMAGE "res\\Image\\AvoidDance_Tutorial.png"
//カメラアングル変更チュートリアル画像
#define CAMERA_ANGLE_TUTORIAL_IMAGE "res\\Image\\Camera_Angle_Tutorial.png"
//プレイヤ視点の操作チュートリアル画像
#define CAMERA_ACTION_TUTORIAL_IMAGE "res\\Image\\Camera_Action_Tutorial.png"
//HPゲージ
#define CHARACTER_UI_HP_GREENGAUGE "res\\Ui\\HP_Gauge.png"
#define CHARACTER_UI_HP_REDGAUGE "res\\Ui\\HP_RedGauge.png"

/*BGM・SE*/

//BGM
#define BGM_GAME "res\\Bgm\\Bgm_Game.wav"


class CRes {
public:
	//更新処理
	void Update();
	void Init();
	/*画像の取得用関数*/
	//ゲームクリア画像を取得する
	CTexture& GetinGameClearImage();
	//ゲームオーバー画像を取得する
	CTexture& GetinGameOverImage();
	//チュートリアル終了の画像
	CTexture& GetinTutorialEndImage();
	//アクションのチュートリアル画像を取得する
	CTexture& GetinActionTutorialImage();
	//移動のチュートリアル画像を取得する
	CTexture& GetinMoveTutorialImage();
	//回避アクションのチュートリアル画像を取得する
	CTexture& GetinAvoidDanceTutorialImage();
	//カメラアングルのチュートリアル画像を取得する
	CTexture& GetinCameraAngleImage();
	//プレイヤ視点操作のチュートリアル画像を取得する
	CTexture& GetinCameraActionImage();
	//UIフォントの取得
	CText& GetInUiFont();
	//HPゲージを取得する
	CTexture& GetInUiHpGreenGauge();
	CTexture& GetInUiHpRedGauge();
	//ゲームBGMの取得
	CSound& GetinSoundBgmGame();
	//インスタンスの取得
	static CRes* GetInstance();//staticで処理を作る

private:
	//フォント
	CText mFont;
	//CSoundクラスのインスタンス作成
	//BGM
	CSound Game_Bgm;

	//キー入力で回転
	CMatrix gMatrix;

	/*画像変数*/
	//ゲームクリア画像
	CTexture gGameClear_Image;
	//ゲームオーバー画像
	CTexture gGameOver_Image;
	//チュートリアルの終了画像
	CTexture gTutorial_End_Image;
	//アクションチュートリアル画像
	CTexture gAction_Tutorial_Image;
	//移動チュートリアル画像
	CTexture gMove_Tutorial_Image;
	//回避アクションチュートリアル画像
	CTexture gAvoidDance_Tutorial_Image;
	//カメラアングルのチュートリアル画像
	CTexture gCamera_Angle_Image;
	//プレイヤ視点の操作チュートリアル画像
	CTexture gCamera_Action_Image;
	//キャラクタのUIインスタンス
	CTexture gCharacter_Ui_Hp_GreenGauge;
	CTexture gCharacter_Ui_Hp_RedGauge;
	static CRes* mpRes_Instance;//別のクラスでリソースの変数を呼び出す場合,staticでポインタを作る
};
#endif

