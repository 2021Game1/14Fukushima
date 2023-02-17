#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CColliderCapsule.h"
#include "CVector.h"
#include"CInput.h"
#include"CTexture.h"
#include"CEffect.h"

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

/*プレイヤのコライダ設定*/

//プレイヤーの身体
#define PLAYER_COLCAPSULE_BODY_X 0.0f					//カプセルコライダのX座標設定
#define PLAYER_COLCAPSULE_BODY_TOP_Y 175.0f				//カプセルコライダのY座標設定
#define PLAYER_COLCAPSULE_BODY_BOTTOM_Y -50.0f			//カプセルコライダのY座標設定
#define PLAYER_COLCAPSULE_BODY_Z 0.0f					//カプセルコライダのZ座標設定
#define PLAYER_COLCAPSULE_BODY_SIZE 0.6					//カプセルコライダのサイズ設定

//プレイヤの当たり判定
#define PLAYER_COLSPHERE_BODY_SIZE 0.7					//球コライダのサイズ設定

//プレイヤの盾
#define PLAYER_COLSPHERE_SHIELD_X 0.0f					//球コライダのX座標
#define PLAYER_COLSPHERE_SHIELD_Y 0.0f					//球コライダのY座標
#define PLAYER_COLSPHERE_SHIELD_Z -5.0f					//球コライダのZ座標
#define PLAYER_COLSPHERE_SHIELD_SIZE 0.5				//球コライダのサイズ

//プレイヤの剣
#define PLAYER_COLSPHERE_SWORD_HEAD_X -10.0f			//球コライダのX座標設定
#define PLAYER_COLSPHERE_SWORD_HEAD_Y 0.0f				//球コライダのY座標設定
#define PLAYER_COLSPHERE_SWORD_HEAD_Z 50.0f				//球コライダのZ座標設定
#define PLAYER_COLSPHERE_SWORD_SIZE 0.3					//球コライダのサイズ設定

/*
CXPlayer
*/

class CXPlayer : public CXCharacter{
public:
	//プレイヤの状態
	enum EPlayerState
	{
		EIDLE = 0,	//待機
		EMOVE,		//移動
		EAVOIDANCE,	//回避
		EATTACK_1,	//攻撃1
		EATTACK_2,	//攻撃2
		EATTACK_3,	//攻撃3
		EDEATH,		//死亡
		EKNOCKBACK,	//ノックバック
	};
	//更新処理
	void Update();
	//モデルの設定、初期設定
	void Init(CModelX* model);
	//2D描画
	void Render2D();
	//タスクコリジョン
	void TaskCollision();
	//デフォルトコンストラクタ
	CXPlayer();
	//プレイヤのHP取得関数
	bool GetHp();
	//プレイヤの衝突判定関数
	void Collision(CCollider* m, CCollider* o);	//衝突処理
	//プレイヤのインスタンス取得関数
	static CXPlayer* GetInstance();		//staticで処理を作る
	//プレイヤのアニメーションフレーム取得関数
	bool GetIsAnimationFrame();
	//プレイヤのヒット判定取得関数
	bool GetIsHit();					//ヒット状態の判別
	//プレイヤの状態取得関数
	CXPlayer::EPlayerState GetState();	//プレイヤの状態を取得する
	//プレイヤの剣コライダの座標取得
	CVector GetSwordColPos();			//剣のコライダの座標を取得する
private:
	//コライダの宣言
	CCollider mPlayer_ColSphereSword;						//剣
	CCollider mPlayer_ColSphereShield;				//盾
	CCollider mPlayer_ColSphereBody;				//球の身体
	CColliderCapsule mPlayer_ColCapsuleBody;		//カプセルの身体
	//プレイヤの状態推移
	EPlayerState mPlayer_State;			//プレイヤの状態判断用
	bool mPlayer_InvincibleFlag;				//無敵状態の時trueを返す


	//プレイヤのHPゲージ用の変数
	float mPlayer_FollowGaugeWid;		//被ダメージ分後追いするゲージの幅

	//プレイヤの移動用変数
	CVector mPlayer_Move;				//プレイヤの方向と速度をかけ合わせたベクトル、プレイヤの移動量
	CVector mPlayer_MoveDir;			//プレイヤの移動する方向、モデルの回転にも使用している、毎フレームリセットされる
	CVector mPlayer_MoveDirKeep;		//プレイヤの移動時の方向を保存する
	CVector mPlayer_KnockBackDir;		//プレイヤのノックバックする方向を保持する
	CVector mPlayer_AttackDir;			//プレイヤの攻撃時の方向を保持する
	float mPlayer_Speed;				//プレイヤのスピード
	float mPlayer_Turnspeed;			//プレイヤのターンの速度

	//カメラのパラメータを作成する
	CVector mPlayer_SideVec;			//プレイヤの横ベクトル
	CVector mPlayer_FrontVec;			//プレイヤのカメラの正面ベクトル
	int mPlayer_Hp;						//プレイヤの体力

	//プレイヤの攻撃フラグ変数
	bool mPlayer_AttackFlag_1;			//プレイヤの攻撃1状態の時trueを返す
	bool mPlayer_AttackFlag_2;			//プレイヤの攻撃2状態の時trueを返す
	bool mPlayer_AttackFlag_3;			//プレイヤの攻撃3状態の時trueを返す
	bool mPlayer_SeFlag;				//プレイヤのSEフラグ
	bool mPlayer_IsHit;					//プレイヤの攻撃時にtrueを返す　敵に攻撃が当たるor攻撃終了時にfalseを返す
	bool mPlayer_AttackFlag_Once;		//プレイヤの攻撃した瞬間だけtrueを返す、敵の回避判定に使用
	int mPlayer_ComboCount;				//プレイヤのコンボルート判別用変数
	int mPlayer_Flag;					//プレイヤのフラグ

	//プレイヤのポインタ
	static CXPlayer* mpPlayer_Instance;	//別のクラスでプレイヤの変数を呼び出す場合,staticでポインタを作る

	//プレイヤの行動処理
	void Idle();						//待機処理
	void MoveCamera();					//カメラを基準にした移動処理
	void Move();						//移動処理
	void Attack_1();					//攻撃1処理
	void Attack_2();					//攻撃2処理
	void Attack_3();					//攻撃3処理
	void Avoidance();					//回避処理
	void Death();						//死亡処理
	void KnockBack();					//ノックバック処理
	//移動の計算処理
	void MovingCalculation();
};
#endif 

