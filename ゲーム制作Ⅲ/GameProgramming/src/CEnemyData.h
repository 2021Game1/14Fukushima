#ifndef ENEMYDATA_H
#define ENEMYDATA_H

//敵UI
#define ENEMY_UI_HP_BACKBAR "res\\Ui\\Enemy_HP_BackBar.png"

/*敵のコライダ設定*/
//敵の身体
#define ENEMY_COLCAPSULE_BODY_X 0.0f					//カプセルコライダのX座標設定
#define ENEMY_COLCAPSULE_BODY_TOP_Y 190.0f				//カプセルコライダ頂点Y座標設定
#define ENEMY_COLCAPSULE_BODY_BOTTOM_Y -12.0f			//カプセルコライダ底のY座標設定
#define ENEMY_COLCAPSULE_BODY_Z 0.0f					//カプセルコライダのZ座標設定
#define ENEMY_COLCAPSULE_BODY_SIZE 1.2f					//カプセルコライダのサイズ設定

//敵の当たり判定用コライダサイズ設定
#define ENEMY_COLSPHERE_BODY_X 0.0f					//球コライダのX座標設定
#define ENEMY_COLSPHERE_BODY_Y 94.0f				//球コライダのY座標設定
#define ENEMY_COLSPHERE_BODY_Z 5.0f					//球コライダのZ座標設定
#define ENEMY_COLSPHERE_BODY_SIZE 1.6f				//球コライダのサイズ設定

//敵の右手
#define ENEMY_COLSPHERE_RIGHTARM_SIZE 0.8f				//球コライダのサイズ設定

//敵の左手
#define ENEMY_COLSPHERE_LEFTARM_SIZE 0.8f					//球コライダのサイズ設定

//敵のHPフレーム,HPゲージ座標,幅,高さ
#define ENEMY_GAUGE_WID_MAX 100.0f										//ゲージの幅の最大値
#define ENEMY_GAUGE_HEIGHT 20.0f										//ゲージ描画時の高さ
#define ENEMY_GAUGE_HP_TOP -10.0f										//HPゲージ描画時の上座標
#define ENEMY_GAUGE_HP_BOTTOM (ENEMY_GAUGE_HP_TOP - ENEMY_GAUGE_HEIGHT) //HPゲージ描画時の下座標
#define ENEMY_GAUGE_HP_RATE 0.05f										//HPゲージの振動範囲のふり幅設定
#define ENEMY_GAUGE_HP_Y 5.5f											//HPゲージ表示のY座標
#define ENEMY_GAUGE_HP_Z 0.0f											//HPゲージ表示のZ座標
//初期化
#define ENEMY_SPEED 0.0f												//敵の速度初期化
#define ENEMY_TURNSPEED 0.0f											//ターン速度初期化
#define ENEMY_TURN_SET 180.0f											//回転の初期化
#define ENEMY_TURN_SPEEDS_SET 0.3f										//回転速度設定
#define ENEMY_TRUN_CHECK_SPEEDS_SET 1.5f								//急な回転速度を調整
#define ENEMY_TRUN_CHECK_SET 0.0f										//回転速度を検出し可動域を設定
#define ENEMY_ATTACK_MAGNIFICATION 0.2									//ダメージの倍率設定

/*敵データテーブル*/

//敵データテーブル(チュートリアル版)
#define ENEMY_DATATABLE_TUTORIAL "res\\Enemy\\DataTable\\Tutorial\\EnemyData_Tutorial.txt"

//敵データテーブル(本番のゲーム版で使用する敵1設定)
#define ENEMY_DATATABLE_MAINGAME1 "res\\Enemy\\DataTable\\MainGame\\EnemyData_MainGame1.txt"

//敵データテーブル(本番のゲーム版で使用する敵2設定)
#define ENEMY_DATATABLE_MAINGAME2 "res\\Enemy\\DataTable\\MainGame\\EnemyData_MainGame2.txt"

/*エネミーのアニメーションモデル*/

#define ENEMY_MODEL_FILE "res\\Enemy\\Mutant\\mutant.x"
#define ENEMY_ANIMATION_ATTACKSP1 "res\\Enemy\\Mutant\\Attack1.x"
#define ENEMY_ANIMATION_WALK "res\\Enemy\\Mutant\\Walk.x"
#define ENEMY_ANIMATION_DASH "res\\Enemy\\Mutant\\Dash.x"
#define ENEMY_ANIMATION_BACKSTEP "res\\Enemy\\Mutant\\BackStep.x"
#define ENEMY_ANIMATION_IDLE "res\\Enemy\\Mutant\\Idle.x"
#define ENEMY_ANIMATION_KNOCKBACK "res\\Enemy\\Mutant\\KnockBack.x"
#define ENEMY_ANIMATION_DEATH "res\\Enemy\\Mutant\\Death.x"

/*SE*/

//死亡SE
#define SE_EMEMY_DEATH "res\\Se\\SE_Enemy_Death.wav"

/*エフェクト*/

//敵ダメージエフェクト
#define ENEMY_EF_DAMAGESP1 "Effect\\Enemy_DamageSp1.png"
#define ENEMY_EF_DAMAGESP2 "Effect\\Enemy_DamageSp2.png"
//敵攻撃予備動作エフェクト
#define ENEMY_ATTACK_ACTION "Effect\\Enemy_Attack_Action.png"

/*UI*/

//敵UI
#define ENEMY_UI_HP_BACKBAR "res\\Ui\\Enemy_HP_BackBar.png"
#endif // !