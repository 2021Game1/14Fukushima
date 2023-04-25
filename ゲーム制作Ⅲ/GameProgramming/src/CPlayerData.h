#ifndef PLAYERDATA_H
#define PLAYERDATA_H

//初期化設定
#define PLAYER_INT_INITIALIZATION 0																//初期化
#define PLAYER_FLOAT_INITIALIZATION 0.0f														//浮動小数点の初期化

#define PLAYER_DATATABLE "res\\Player\\DataTable\\PlayerData.txt"

/*SE設定*/

//SE・プレイヤ
#define SE_PLAYER_ATTACK1 "res\\Se\\SE_Player_AttackSp1.wav"	//攻撃1のSE
#define SE_PLAYER_ATTACK2 "res\\Se\\SE_Player_AttackSp2.wav"	//攻撃2のSE
#define SE_PLAYER_WALK "res\\Se\\SE_Player_Walk.wav"			//歩行時のSE
#define SE_PLAYER_DEATH "res\\Se\\SE_Player_Death.wav"			//死亡時のSE
//SE・敵
#define SE_ENEMY_ATTACK "res\\Se\\SE_Enemy_AttackSp.wav"		//被弾時のSE

/*プレイヤのコライダ設定*/

//プレイヤの頭
#define PLAYER_COLSPHER_HEAD_X 0.0f					//球コライダのX座標設定
#define PLAYER_COLSPHER_HEAD_Y 16.0f				//球コライダのY座標設定
#define PLAYER_COLSPHER_HEAD_Z 0.0f					//球コライダのZ座標設定
#define PLAYER_COLSPHER_HEAD_SIZE 0.7f				//球コライダサイズ

//プレイヤーの身体
#define PLAYER_COLCAPSULE_BODY_X 0.0f				//カプセルコライダのX座標設定
#define PLAYER_COLCAPSULE_BODY_TOP_Y 95.0f			//カプセルコライダのY座標設定
#define PLAYER_COLCAPSULE_BODY_BOTTOM_Y -134.8f		//カプセルコライダのY座標設定
#define PLAYER_COLCAPSULE_BODY_Z 0.0f				//カプセルコライダのZ座標設定
#define PLAYER_COLCAPSULE_BODY_SIZE 0.7f			//カプセルコライダのサイズ設定

//プレイヤの当たり判定
#define PLAYER_COLSPHERE_BODY_SIZE 0.9				//球コライダのサイズ設定

//プレイヤの剣
#define PLAYER_COLSPHERE_SWORD_X -13.0f				//球コライダのX座標設定
#define PLAYER_COLSPHERE_SWORD_Y 0.0f				//球コライダのY座標設定
#define PLAYER_COLSPHERE_SWORD_Z 70.0f				//球コライダのZ座標設定
#define PLAYER_COLSPHERE_SWORD_SIZE 0.35			//球コライダのサイズ設定

/*プレイヤのUI設定*/

//プレイヤのHPフレーム,HPゲージ座標,幅,高さ
#define PLAYER_GAUGE_FRAME_TEX_WID 480															//ゲージ枠の画像の幅
#define PLAYER_GAUGE_FRAME_TEX_HEI 80															//ゲージ枠の画像の高さ
#define PLAYER_GAUGE_FRAME_TEX_FIRST_WID 0														//ゲージ枠の画像描画の幅
#define PLAYER_GAUGE_FRAME_TEX_FIRST_HEI 10														//ゲージ枠の画像描画の高さ
#define PLAYER_GAUGE_FRAME_LEFT 0																//ゲージ枠左座標
#define PLAYER_GAUGE_FRAME_RIGHT 380															//ゲージ枠右座標
#define PLAYER_GAUGE_FRAME_TOP PLAYER_GAUGE_FRAME_TEX_HEI										//ゲージ枠上座標
#define PLAYER_GAUGE_FRAME_BOTTOM (PLAYER_GAUGE_FRAME_TOP-PLAYER_GAUGE_FRAME_TEX_HEI)			//ゲージ枠下座標
#define PLAYER_GAUGE_LEFT 0																		//ゲージ描画時の左座標
#define PLAYER_GAUGE_WID_MAX 380																//ゲージの幅の最大値
#define GAUGE_HEIGHT 20																			//ゲージ描画時の高さ
#define PLAYER_GAUGE_HP_TOP 30																	//HPゲージ描画時の上座標
#define PLAYER_GAUGE_HP_BOTTOM (PLAYER_GAUGE_HP_TOP-GAUGE_HEIGHT)								//HPゲージ描画時の底辺座標

#endif // !PLAYERDATA_H

