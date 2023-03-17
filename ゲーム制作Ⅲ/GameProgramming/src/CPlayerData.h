#ifndef PLAYERDATA_H
#define PLAYERDATA_H

//初期化設定
#define PLAYER_INT_INITIALIZATION 0																//初期化
#define PLAYER_FLOAT_INITIALIZATION 0.0f														//浮動小数点の初期化

/*プレイヤのコライダ設定*/

//プレイヤーの身体
#define PLAYER_COLCAPSULE_BODY_X 0.0f					//カプセルコライダのX座標設定
#define PLAYER_COLCAPSULE_BODY_TOP_Y 95.0f				//カプセルコライダのY座標設定
#define PLAYER_COLCAPSULE_BODY_BOTTOM_Y -134.8f			//カプセルコライダのY座標設定
#define PLAYER_COLCAPSULE_BODY_Z 0.0f					//カプセルコライダのZ座標設定
#define PLAYER_COLCAPSULE_BODY_SIZE 0.7f				//カプセルコライダのサイズ設定

//プレイヤの当たり判定
#define PLAYER_COLSPHERE_BODY_SIZE 0.9					//球コライダのサイズ設定

//プレイヤの盾
#define PLAYER_COLSPHERE_SHIELD_X 0.0f					//球コライダのX座標
#define PLAYER_COLSPHERE_SHIELD_Y 0.0f					//球コライダのY座標
#define PLAYER_COLSPHERE_SHIELD_Z -5.0f					//球コライダのZ座標
#define PLAYER_COLSPHERE_SHIELD_SIZE 0.5				//球コライダのサイズ

//プレイヤの剣
#define PLAYER_COLSPHERE_SWORD_HEAD_X -13.0f			//球コライダのX座標設定
#define PLAYER_COLSPHERE_SWORD_HEAD_Y 0.0f				//球コライダのY座標設定
#define PLAYER_COLSPHERE_SWORD_HEAD_Z 70.0f				//球コライダのZ座標設定
#define PLAYER_COLSPHERE_SWORD_SIZE 0.3					//球コライダのサイズ設定

#endif // !PLAYERDATA_H

