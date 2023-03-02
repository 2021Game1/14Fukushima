#ifndef ENEMYDATA_H
#define ENEMYDATA_H



//初期化設定
#define ENEMY_INT_INITIALIZATION 0																//初期化
#define ENEMY_FLOAT_INITIALIZATION 0.0f															//浮動小数点の初期化

//描画優先度設定
#define ENEMY_SPEED_STOP 0.0f		//停止
#define ENEMY_GRAVITY 0.9f			//重力


//敵のアニメーションのフレーム設定
#define ENEMY_IDLE_ANIMATION_FRAME 60															//待機のアニメーションフレーム設定
#define ENEMY_MOVE_ANIMATION_FRAME 60															//歩行のアニメーションフレーム設定
#define ENEMY_DASH_ANIMATION_FRAME 50															//走行のアニメーションフレーム設定
#define ENEMY_ATTACK1_ANIMATION_FRAME 130														//攻撃1のアニメーションフレーム設定
#define ENEMY_ATTACK2_ANIMATION_FRAME 110														//攻撃2のアニメーションフレーム設定
#define ENEMY_ATTACK3_ANIMATION_FRAME 120														//攻撃3のアニメーションフレーム設定
#define ENEMY_KNOCKBACK_ANIMATION_FRAME 60														//ノックバックのアニメーションフレーム設定
#define ENEMY_DEATH_ANIMATION_FRAME 60															//死亡のアニメーションフレーム設定

//敵のアニメーション番号の設定
#define ENEMY_ANIMATION_No_ATTACK_1 0		//攻撃アニメーション1番号
#define ENEMY_ANIMATION_No_ATTACK_2 1		//攻撃アニメーション2番号
#define ENEMY_ANIMATION_No_ATTACK_3 2		//攻撃アニメーション3番号
#define ENEMY_ANIMATION_No_WALK 3			//歩行アニメーション番号
#define ENEMY_ANIMATION_No_DASH 4			//走行アニメーション番号
#define ENEMY_ANIMATION_No_IDLE 5			//待機アニメーション番号
#define ENEMY_ANIMATION_No_KNOCKBACK 6		//ノックバックアニメーション番号
#define ENEMY_ANIMATION_No_DEATH 7			//死亡アニメーション番号


/*敵のコライダ設定*/

//敵の身体
#define ENEMY_COLCAPSULE_BODY_X 0.0f					//カプセルコライダのX座標設定
#define ENEMY_COLCAPSULE_BODY_TOP_Y 190.0f				//カプセルコライダ頂点Y座標設定
#define ENEMY_COLCAPSULE_BODY_BOTTOM_Y -31.0f			//カプセルコライダ底のY座標設定
#define ENEMY_COLCAPSULE_BODY_Z 0.0f					//カプセルコライダのZ座標設定
#define ENEMY_COLCAPSULE_BODY_SIZE 1.2f					//カプセルコライダのサイズ設定

//敵の当たり判定用コライダサイズ設定
#define ENEMY_COLSPHERE_BODY_X 0.0f					//球コライダのX座標設定
#define ENEMY_COLSPHERE_BODY_Y 94.0f				//球コライダのY座標設定
#define ENEMY_COLSPHERE_BODY_Z 5.0f					//球コライダのZ座標設定
#define ENEMY_COLSPHERE_BODY_SIZE 1.3f				//球コライダのサイズ設定

//敵の右手
#define ENEMY_COLSPHERE_RIGHTARM_SIZE 0.7f				//球コライダのサイズ設定

//敵の左手
#define ENEMY_COLSPHERE_LEFTARM_SIZE 0.7f					//球コライダのサイズ設定

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
#define ENEMY_PROBABILITY_LOW_SET1 0
#define ENEMY_PROBABILITY_MAX_SET1 60
#define ENEMY_PROBABILITY_LOW_SET2 61
#define ENEMY_PROBABILITY_MAX_SET2 100

struct ENEMYDATA {
        int Enemy_Type;//敵種類
        int Enemy_Priority;//描画優先度
        float Enemy_Speed_WalkPattern;//移動スピードパターン
        float Enemy_Speed_DashPattern;//走行スピードパターン
        float Enemy_Walk_Dis; //歩行開始の距離
        float Enemy_Dash_Dis; //走行開始の距離
        float Enemy_Walk_Dis_Max; //歩行終了の距離
        float Enemy_Dash_Dis_Max; //走行終了の距離
        float Enemy_Attack_Dis;//攻撃可能な距離
        float Enemy_Attack_Reception;//当たり判定の開始
        float Enemy_Attack_Outreception;//当たり判定の終了
        int Enemy_Attack_Walk_Rand;
        int Enemy_Attack_Dash_Rand;
        int Enemy_Damage_PlayerSp1;
        int Enemy_Damage_PlayerSp2;
        int Enemy_Damage_PlayerSp3;
        float Position_X;//位置のX座標
        float Position_Y;//位置のY座標
        float Position_Z;//位置のZ座標
        float Scale_X;   //スケールのX座標
        float Scale_Y;   //スケールのY座標
        float Scale_Z;   //スケールのZ座標
        float Rotation_X;//モデルの回転X座標
        float Rotation_Y;//モデルの回転Y座標
        float Rotation_Z;//モデルの回転Z座標
        int Hp;          //HP
        int Hp_Max;      //HP最大値
        int Death_Hp;    //死亡条件
};
#define ENEMY_NUM 1

#endif // !