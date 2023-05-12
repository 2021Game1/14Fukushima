#ifndef CTUTORIAL_H
#define CTUTORIAL_H

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

//移動のチュートリアル画像描画座標
#define MOVE_FIRST_WID 0
#define MOVE_END_WID 800
#define MOVE_FIRST_HEI 0
#define MOVE_END_HEI 600
#define MOVE_FIRST_X 0
#define MOVE_END_X 800
#define MOVE_FIRST_Y 0
#define MOVE_END_Y 600

//カメラのチュートリアル画像描画座標
#define CAMERA_FIRST_WID 0
#define CAMERA_END_WID 800
#define CAMERA_FIRST_HEI 0
#define CAMERA_END_HEI 600
#define CAMERA_FIRST_X 0
#define CAMERA_END_X 800
#define CAMERA_FIRST_Y 0
#define CAMERA_END_Y 600

//攻撃アクションのチュートリアル画像描画座標
#define ACTION_FIRST_WID 0
#define ACTION_END_WID 800
#define ACTION_FIRST_HEI 0
#define ACTION_END_HEI 600
#define ACTION_FIRST_X 0
#define ACTION_END_X 800
#define ACTION_FIRST_Y 0
#define ACTION_END_Y 600

//回避アクションのチュートリアル画像描画座標
#define AVOIDDANCE_FIRST_WID 0
#define AVOIDDANCE_END_WID 800
#define AVOIDDANCE_FIRST_HEI 0
#define AVOIDDANCE_END_HEI 600
#define AVOIDDANCE_FIRST_X 0
#define AVOIDDANCE_END_X 800
#define AVOIDDANCE_FIRST_Y 0
#define AVOIDDANCE_END_Y 600
//カメラアングル



//アクションのチュートリアル画像表示する際のプレイヤと敵の距離を設定
#define ACTION_TUTORIAL_ENEMY_PLAYER_VECTOR 2.4f

class CTutorial{
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
	//カメラのチュートリアル画像のフラグ
	bool mCameraTutorialflag;
	//チュートリアル画像のフラグ
	bool mTutorial_Out_flag;
	//チュートリアルクラスのポインタ
	static CTutorial* mpTutorial_Instance;	//別のクラスでチュートリアルの変数を呼び出す場合,staticでポインタを作る
};





#endif 



