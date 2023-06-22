#include "CRes.h"

CRes* CRes::mpRes_Instance = nullptr;												//リソースのインスタンス変数の初期化

void CRes::Init() {
	//インスタンスの有効化
	mpRes_Instance = this;
	//BGMの読み込み
	Game_Bgm.Load(BGM_GAME);
	//ゲームクリア画像の追加
	gGameClear_Image.Load2D(GAMECLEAR_IMAGE);
	//ゲームオーバー画像の追加
	gGameOver_Image.Load2D(GAMEOVER_IMAGE);
	//チュートリアルの終了画像の追加
	gTutorial_End_Image.Load2D(TUTORIAL_END_IMAGE);
	//アクションチュートリアル画像の追加
	gAction_Tutorial_Image.Load2D(ACTION_TUTORIAL_IMAGE);
	//移動チュートリアル画像の追加
	gMove_Tutorial_Image.Load2D(MOVE_TUTORIAL_IMAGE);
	//回避アクションチュートリアル画像の追加
	gAvoidDance_Tutorial_Image.Load2D(AVOIDANCE_TUTORIAL_IMAGE);
	//カメラアングルのチュートリアル画像の追加
	gCamera_Angle_Image.Load2D(CAMERA_ANGLE_TUTORIAL_IMAGE);
	//プレイヤの視点操作チュートリアル
	gCamera_Action_Image.Load2D(CAMERA_ACTION_TUTORIAL_IMAGE);
	//キャラクタのUI追加
	gCharacter_Ui_Hp_GreenGauge.Load2D(CHARACTER_UI_HP_GREENGAUGE);
	gCharacter_Ui_Hp_RedGauge.Load2D(CHARACTER_UI_HP_REDGAUGE);
	mFont.LoadTexture("Font\\FontG.png", 1, 4096 / 64);
	//カメラ初期化
	Camera.Init();
}
void CRes::Update() {

}
//リソースのポインタを返すことで、座標などが参照できるようになる
CRes* CRes::GetInstance()
{
	return mpRes_Instance;
}
//フォントの取得
CText& CRes::GetInUiFont()
{
	return mFont;
}
//クリア画面の取得
CTexture& CRes::GetinGameClearImage()
{
	return gGameClear_Image;
}
//ゲームオーバー画面の取得
CTexture& CRes::GetinGameOverImage()
{
	return gGameOver_Image;
}

//チュートリアルの終了画像の取得
CTexture& CRes::GetinTutorialEndImage()
{
	return gTutorial_End_Image;
}
//アクションチュートリアル画像を取得する
CTexture& CRes::GetinActionTutorialImage()
{
	return gAction_Tutorial_Image;
}
//移動チュートリアル画像を取得する
CTexture& CRes::GetinMoveTutorialImage()
{
	return gMove_Tutorial_Image;
}
//回避チュートリアル画像を取得
CTexture& CRes::GetinAvoidDanceTutorialImage()
{
	return gAvoidDance_Tutorial_Image;
}
//カメラアングルチュートリアル画像を取得
CTexture& CRes::GetinCameraAngleImage()
{
	return gCamera_Angle_Image;
}
//カメラアングルチュートリアル画像を取得
CTexture& CRes::GetinCameraActionImage()
{
	return gCamera_Action_Image;
}
//緑HPバーの取得
CTexture& CRes::GetInUiHpGreenGauge()
{
	return gCharacter_Ui_Hp_GreenGauge;
}
//赤HPバーの取得
CTexture& CRes::GetInUiHpRedGauge()
{
	return gCharacter_Ui_Hp_RedGauge;
}
//ゲームBGMの取得
CSound& CRes::GetinSoundBgmGame() 
{
	return Game_Bgm;
}
