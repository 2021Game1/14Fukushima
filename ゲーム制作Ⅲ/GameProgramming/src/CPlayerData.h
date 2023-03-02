#ifndef PLAYERDATA_H
#define PLAYERDATA_H

//初期化設定
#define PLAYER_INT_INITIALIZATION 0																//初期化
#define PLAYER_FLOAT_INITIALIZATION 0.0f														//浮動小数点の初期化
//描画優先度設定
#define PLAYER_PRIORITY 95																		//描画優先度の設定

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
#define PLAYER_GAUGE_HP_BOTTOM (PLAYER_GAUGE_HP_TOP-GAUGE_HEIGHT)								//HPゲージ描画時の下座標
#define PLAYER_GAUGE_HP_SHAKE_X -5																//HPゲージの振動の初期X座標設定
#define PLAYER_GAUGE_HP_SHAKE_RANGE_X 12														//HPゲージの振動範囲のX座標設定											
#define PLAYER_GAUGE_HP_SHAKE_Y -2																//HPゲージの振動の初期Y座標設定
#define PLAYER_GAUGE_HP_SHAKE_RANGE_Y 2															//HPゲージの振動範囲のY座標設定
#define PLAYER_GAUGE_HP_RATE 0.05f																//HPゲージの振動範囲のふり幅設定
#define PLAYER_TURN_SET 180.0f																	//回転の初期化
#define PLAYER_TURN_SPEEDS_SET 0.3f																//回転速度設定
#define PLAYER_TRUN_CHECK_SPEEDS_SET 1.5f														//急な回転速度を調整
#define PLAYER_TRUN_CHECK_SET 0.0f																//回転速度を検出しカメラの可動域を設定



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


//プレイヤのゲームオーバ体力設定
#define PLAYER_GAMEOVER_HP 0																	//ゲームオーバ設定
//プレイヤのパラメータマクロ
#define PLAYER_HP_MAX 100																		//HPの最大値
#define PLAYER_HP 100																			//HPの設定
#define PLAYER_SPEED_DEFAULT 0.2f																//スピード(通常時)
#define PLAYER_GRAVITY 0.9f																		//重力
#define PLAYER_THRUST 0.9																		//推力
#define PLAYER_SE 0.1																			//プレイヤSE設定
#define PLAYER_DAMAGE_SE 0.3																	//プレイヤダメージSE設定
#define PLAYER_RECEPTION 15																		//キー入力の受付時間
#define PLAYER_INRECEPTION 	21.0f																//当たり判定の受付時間															
#define PLAYER_OUTRECEPTION 60.0f																//当たり判定の終了時間
#define PLAYER_ATTACK_DIS 2.2f																	//敵に攻撃が追従可能になる距離

//プレイヤのアニメーションのフレーム設定
#define PLAYER_IDLE_ANIMATION_FRAME 20
#define PLAYER_MOVE_ANIMATION_FRAME 45															//移動のアニメーションフレーム設定
#define PLAYER_AVOIDANCE_ANIMATION_FRAME 50														//回避のアニメーションフレーム設定
#define PLAYER_ATTACK1_ANIMATION_FRAME 70														//攻撃1のアニメーションフレーム設定
#define PLAYER_ATTACK2_ANIMATION_FRAME 90														//攻撃2のアニメーションフレーム設定
#define PLAYER_ATTACK3_ANIMATION_FRAME 110														//攻撃3のアニメーションフレーム設定
#define PLAYER_KNOCKBACK_ANIMATION_FRAME 60														//ノックバックのアニメーションフレーム設定
#define PLAYER_DEATH_ANIMATION_FRAME 60															//死亡のアニメーションフレーム設定

//プレイヤのダメージ設定
#define PLAYER_DAMAGE_ENEMYSP1 15						//敵の攻撃1のダメージ	
#define PLAYER_DAMAGE_ENEMYSP2 10						//敵の攻撃2のダメージ
#define PLAYER_DAMAGE_ENEMYSP3 20						//敵の攻撃3のダメージ

//プレイヤのアニメーション番号の設定
#define PLAYER_ANIMATION_No_MOVE 0			//移動アニメーション番号
#define PLAYER_ANIMATION_No_ATTACK_1 1		//攻撃アニメーション1番号
#define PLAYER_ANIMATION_No_ATTACK_2 2		//攻撃アニメーション2番号
#define PLAYER_ANIMATION_No_ATTACK_3 3		//攻撃アニメーション3番号
#define PLAYER_ANIMATION_No_AVOIDANCE 4		//回避アニメーション番号
#define PLAYER_ANIMATION_No_IDLE 5			//待機アニメーション番号
#define PLAYER_ANIMATION_No_KNOCKBACK 6		//ノックバックアニメーション番号
#define PLAYER_ANIMATION_No_DEATH 7			//死亡アニメーション番号

#endif // !PLAYERDATA_H

