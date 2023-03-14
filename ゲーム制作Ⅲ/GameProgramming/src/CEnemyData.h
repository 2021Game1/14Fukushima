#ifndef ENEMYDATA_H
#define ENEMYDATA_H

//初期化設定
#define ENEMY_INT_INITIALIZATION 0																//初期化
#define ENEMY_FLOAT_INITIALIZATION 0.0f															//浮動小数点の初期化
#define ENEMY_NUM 5

//敵のHPフレーム,HPゲージ座標,幅,高さ
#define ENEMY_GAUGE_WID_MAX 100.0f	//ゲージの幅の最大値
#define ENEMY_GAUGE_HEIGHT 20.0f //ゲージ描画時の高さ
#define ENEMY_GAUGE_HP_TOP -10.0f //HPゲージ描画時の上座標
#define ENEMY_GAUGE_HP_BOTTOM (ENEMY_GAUGE_HP_TOP - ENEMY_GAUGE_HEIGHT) //HPゲージ描画時の下座標
#define ENEMY_GAUGE_HP_RATE 0.05f																//HPゲージの振動範囲のふり幅設定
//初期化
#define ENEMY_SPEED 0.0f //敵の速度初期化
#define ENEMY_TURNSPEED 0.0f //ターン速度初期化
#define ENEMY_TURN_SET 180.0f																	//回転の初期化
#define ENEMY_TURN_SPEEDS_SET 0.3f																//回転速度設定
#define ENEMY_TRUN_CHECK_SPEEDS_SET 1.5f														//急な回転速度を調整
#define ENEMY_TRUN_CHECK_SET 0.0f																//回転速度を検出し可動域を設定


#endif // !