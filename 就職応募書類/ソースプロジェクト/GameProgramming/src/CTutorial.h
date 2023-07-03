#ifndef CTUTORIAL_H
#define CTUTORIAL_H

#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CXEnemyManager.h"
#include "CRes.h"
/*
チュートリアル描画クラス
*/

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

/*
チュートリアル描画クラス
*/

//2D描画の描画範囲
#define START2D_FIRST_WID 0
#define START2D_END_WID 800
#define START2D_FIRST_HEI 0
#define START2D_END_HEI 600

//Tutorial画像描画座標
#define TUTORIAL_FIRST_WID 0
#define TUTORIAL_END_WID 800
#define TUTORIAL_FIRST_HEI 0
#define TUTORIAL_END_HEI 600
#define TUTORIAL_FIRST_X 0
#define TUTORIAL_END_X 800
#define TUTORIAL_FIRST_Y 0
#define TUTORIAL_END_Y 600

//移動のチュートリアル画像描画座標
#define MOVE_FIRST_WID 0
#define MOVE_END_WID 800
#define MOVE_FIRST_HEI -150
#define MOVE_END_HEI 500
#define MOVE_FIRST_X -100
#define MOVE_END_X 900
#define MOVE_FIRST_Y -125
#define MOVE_END_Y 675

//カメラのチュートリアル画像描画座標
#define CAMERA_FIRST_WID 0
#define CAMERA_END_WID 800
#define CAMERA_FIRST_HEI -150
#define CAMERA_END_HEI 500
#define CAMERA_FIRST_X -25
#define CAMERA_END_X 825
#define CAMERA_FIRST_Y -125
#define CAMERA_END_Y 675

//攻撃アクションのチュートリアル画像描画座標
#define ACTION_FIRST_WID 0
#define ACTION_END_WID 800
#define ACTION_FIRST_HEI -150
#define ACTION_END_HEI 500
#define ACTION_FIRST_X -150
#define ACTION_END_X 950
#define ACTION_FIRST_Y -200
#define ACTION_END_Y 600

//回避アクションのチュートリアル画像描画座標
#define AVOIDDANCE_FIRST_WID 0
#define AVOIDDANCE_END_WID 800
#define AVOIDDANCE_FIRST_HEI -150
#define AVOIDDANCE_END_HEI 500
#define AVOIDDANCE_FIRST_X -25
#define AVOIDDANCE_END_X 825
#define AVOIDDANCE_FIRST_Y -125
#define AVOIDDANCE_END_Y 600

//カメラアングルの操作累積値設定
#define CAMERA_ANGLE_ACCEUMULATION 1
//カメラアングルの操作累積値設定
#define CAMERA_ANGLE_ACCEUMULATION_MAX 4

//回避操作累積値設定
#define AVOIDDANCE_ACCEUMULATION 1
//回避操作累積値設定
#define AVOIDDANCE_ACCEUMULATION_MAX 6

//アクションのチュートリアル画像表示する際のプレイヤと敵の距離を設定
#define ACTION_TUTORIAL_ENEMY_PLAYER_VECTOR 2.4f

//移動操作量上限の設定
#define MOVE_ACCEUMULATION_MAX 15

//カメラ操作量上限設定
#define CAMERA_ACCEUMULATION_MAX 180

class CTutorial : public CCharacter{
public:
	//デフォルトコンストラクタ
	CTutorial();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//チュートリアルのフラグ取得
	bool GetIsTutorialFlag();
private:
	//アクションのチュートリアル画像のフラグ
	bool mActionTutorialflag;
	//移動のチュートリアル画像のフラグ
	bool mMoveTutorialflag;
	//回避のチュートリアル画像のフラグ
	bool mAvoidDanceTutorialflag;
	//カメラのアングルチュートリアル画像のフラグ
	bool mCameraAngleTutorialflag;
	//プレイヤの視点操作チュートリアル画像のフラグ
	bool mCameraActionTutorialflag;
	//チュートリアル終了の画像フラグ
	bool mTutorialEndflag;
	//チュートリアルの終了フラグ
	bool mTutorial_Out_flag;
	//チュートリアルクラスのポインタ
	static CTutorial* mpTutorial_Instance;	//別のクラスでチュートリアルの変数を呼び出す場合,staticでポインタを作る
	//歩行チュートリアルのプレイヤの累積移動変数
	CVector mMoveTutorial_Accumulation;
	//歩行チュートリアルのプレイヤの累積変数
	float mMoveTutorial_Accumulation_Pos;
	//歩行累積移動値の最大値
	float mMoveTutorial_Accumulation_Max;
	//カメラ操作チュートリアルの累積変数
	float mCameraActionTutorial_Accumulation;
	//カメラ操作累積値の最大値
	float mCameraActionTutorial_Accumulation_Max;
	//カメラアングル操作累積設定
	int mCameraAngle_Acceumulation;
	//回避操作蓄積設定
	int mAvoidDance_Acceumulation;
};
#endif 



