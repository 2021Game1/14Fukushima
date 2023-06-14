#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CColliderCapsule.h"
#include "CVector.h"
#include"CInput.h"
#include"CTexture.h"
#include"CEffect.h"
#include"CUtil.h"
#include"CSound.h"
#include"CTable.h"
#include"CPlayerData.h"
#include"CXEnemy.h"
#include "CModelX.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>

//プレイヤUI
#define PLAYER_UI_HP_FRAME "res\\Ui\\Player_HP_Frame.png"

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
		EDEATH,		//死亡
		EKNOCKBACK,	//ノックバック
	};
	//更新処理
	void Update();
	//モデルの設定、初期設定
	void Init(CModelX* model);
	//座標、回転値、スケールの取得
	void GetPos();								//座標の取得
	void GetScale();							//スケールの取得
	void GetRotation();							//モデルの回転値取得
	//2D描画
	void Render2D();
	//タスクコリジョン
	void TaskCollision();
	//デフォルトコンストラクタ
	CXPlayer();
	//プレイヤのHP取得関数
	int GetHp();	
	//プレイヤのインスタンス取得関数
	static CXPlayer* GetInstance();		//staticで処理を作る
	//プレイヤのモデル取得
	//プレイヤのアニメーションフレーム取得関数
	bool GetIsAnimationFrame();
	//プレイヤのヒット判定取得関数
	bool GetIsHit();					//ヒット状態の判別
	//プレイヤの与えるダメージ取得用
	int GetIsAttackPoint();
	//プレイヤの与えるスタンダメージ取得用
	int GetIsStanPoint();
	//プレイヤの状態取得関数
	CXPlayer::EPlayerState GetState();	//プレイヤの状態を取得する
	//プレイヤの剣コライダの座標取得
	CVector GetSwordColPos();			//剣のコライダの座標を取得する
	//プレイヤの移動量取得
	CVector GetInMoveDir();
	//テーブル取得関数
	void PlayerTable();
private:
	//プレイヤSE
	CSound Se_Player_AttackSp1;						//プレイヤが攻撃1の時流す
	CSound Se_Player_AttackSp2;						//プレイヤが攻撃2の時流す
	CSound Se_Player_Walk;							//プレイヤが移動時流す
	CSound Se_Player_Death;							//プレイヤ死亡時流す
	//敵SE
	CSound Se_Enemy_AttackSp;						//敵から攻撃を受けた時に流す
	//プレイヤのUIインスタンス
	CTexture gPlayer_Ui_Hp_Frame;

	//コライダの宣言
	CCollider mPlayer_ColSphereSword;				//剣
	CCollider mPlayer_ColSphereBody;				//球の身体
	CCollider mPlayer_ColSphereLowerBody;				//球の身体
	CCollider mPlayer_ColSphereHead;				//球の頭
	CColliderCapsule mPlayer_ColCapsuleBody;		//カプセルの身体

	//プレイヤの状態推移
	EPlayerState mPlayer_State;			//プレイヤの状態判断用
	bool mPlayer_InvincibleFlag;		//無敵状態の時trueを返す
	bool mPlayer_Avoid;					//回避状態の時trueを返す

	//プレイヤのHPゲージ用の変数
	float mPlayer_FollowGaugeWid;		//被ダメージ分後追いするゲージの幅
	float mPlayer_Gauge_Hp_Rate;		//プレイヤのHPゲージの揺れ幅設定

	//プレイヤの移動用変数
	CVector mPlayer_Point;				//プレイヤ移動時の目標地点
	CVector mPlayer_Move;				//プレイヤの方向と速度をかけ合わせたベクトル、プレイヤの移動量
	CVector mPlayer_MoveDir;			//プレイヤの移動する方向、モデルの回転にも使用している、毎フレームリセットされる
	CVector mPlayer_MoveDirKeep;		//プレイヤの移動時の方向を保存する
	CVector mPlayer_KnockBackDir;		//プレイヤのノックバックする方向を保持する
	CVector mPlayer_AttackDir;			//プレイヤの攻撃時の方向を保持する
	float mPlayer_Speed;				//プレイヤのスピード(デフォルト)
	float mPlayer_Speed_Avoid;			//プレイヤのスピード(回避)
	float mPlayer_Avoid_Time;			//プレイヤの回避時間
	float mPlayer_Turnspeed;			//プレイヤのターンの速度
	float mPlayer_EnemyDis;				//プレイヤが敵の座標参照用
	float mPlayer_Attack_Dis;			//プレイヤの攻撃対象判別後の距離設定
	CVector mPlayer_Gravity;				//重力の保存用

	//カメラのパラメータを作成する
	CVector mPlayer_SideVec;			//プレイヤの横ベクトル
	CVector mPlayer_FrontVec;			//プレイヤのカメラの正面ベクトル


	int	mPlayer_Gauge_Hp_Shake_X;		//HPゲージの揺れ幅最小値のX
	int	mPlayer_Gauge_Hp_Shake_Y;		//HPゲージの揺れ幅最小値のY
	int	mPlayer_Gauge_Hp_Shake_Range_X; //HPゲージの揺れ幅最小値のX
	int	mPlayer_Gauge_Hp_Shake_Range_Y; //HPゲージの揺れ幅最小値のY

	//プレイヤの攻撃フラグ変数
	bool mPlayer_AttackFlag_1;			//プレイヤの攻撃1状態の時trueを返す
	bool mPlayer_SeFlag;				//プレイヤのSEフラグ
	bool mPlayer_IsHit;					//プレイヤの攻撃時にtrueを返す　敵に攻撃が当たるor攻撃終了時にfalseを返す
	bool mPlayer_AttackFlag_Once;		//プレイヤの攻撃した瞬間だけtrueを返す、敵の回避判定に使用
	int mPlayer_ComboCount;				//プレイヤのコンボルート判別用変数
	int mPlayer_Flag;					//プレイヤのフラグ

	//敵に与える攻撃
	int mDamage;					//敵からのダメージ
	int mStan_Damage;				//敵からのスタンダメージ
	int mStanAccumulation;			//スタン蓄積
	//ステータス
	int mPlayer_Hp;					//体力
	int mPlayer_Hp_Max;				//体力の上限
	int mAttack_Point;				//攻撃力
	int mDefense_Point;				//守備力
	int mStan_Point;				//スタン値

	//プレイヤのポインタ
	static CXPlayer* mpPlayer_Instance;	//別のクラスでプレイヤの変数を呼び出す場合,staticでポインタを作る

	//テーブル取得用変数
	int Player_Priority;							//描画優先度
	int Player_Hp;									//プレイヤのHP
	int	Player_Hp_Max;								//プレイヤのHP上限
	int Player_Attack_Point;						//プレイヤの攻撃力
	int Player_Defense_Point;						//プレイヤの守備力
	int	Player_Stan_Point;							//敵に与えるスタン値
	int Player_StanAccumulation;					//プレイヤのスタン蓄積
	int Player_StanAccumulation_Max;				//プレイヤのスタン蓄積最大値
	float Player_Damage_Magnification;				//プレイヤのダメージ倍率
	int Player_GameOver_Hp;							//プレイヤのゲームオーバー条件(HP)
	float Player_Speed_Default;						//プレイヤのスピード(デフォルト)
	float Player_Speed_Avoid;						//プレイヤのスピード(回避)
	float Player_Avoid_Time;						//プレイヤの回避時間
	float Player_Gravity;							//プレイヤに掛かる重力
	float Player_Thrust;							//プレイヤに掛かる推力
	float Player_Se;								//SEの音量設定
	float Player_Damage_Se;							//ダメージSEの音量設定
	float Player_Push_Reception;					//マウス左クリックの反応タイミング
	float Player_Attack_InReception;				//攻撃判定始め
	float Player_Attack_OutReception;				//攻撃判定終わり
	float Player_Attack_Dis;						//プレイヤの攻撃対象判別後の距離設定
	float Player_Position_X;						//プレイヤの位置X座標
	float Player_Position_Y;						//プレイヤの位置Y座標
	float Player_Position_Z;						//プレイヤの位置Z座標
	float Player_Scale_X;							//プレイヤのスケールX座標
	float Player_Scale_Y;							//プレイヤのスケールY座標
	float Player_Scale_Z;							//プレイヤのスケールZ座標
	float Player_Rotation_X;						//プレイヤのモデルの回転値
	float Player_Rotation_Y;						//プレイヤのモデルの回転値
	float Player_Rotation_Z;						//プレイヤのモデルの回転値
	float Player_Idle_Animation_Frame;				//プレイヤの待機アニメーションフレーム
	float Player_Move_Animation_Frame;				//プレイヤの移動アニメーションフレーム
	float Player_Avoidance_Animation_Frame;			//プレイヤの回避アニメーションフレーム
	float Player_Attack1_Animation_Frame;			//プレイヤの攻撃1アニメーションフレーム
	float Player_Attack1_Idle_Animation_Frame;		//プレイヤの攻撃1の後、再生する待機アニメーションフレーム
	float Player_Attack2_Animation_Frame;			//プレイヤの攻撃2アニメーションフレーム
	float Player_Attack2_Idle_Animation_Frame;		//プレイヤの攻撃2の後、再生する待機アニメーションフレーム
	float Player_KnockBack_Animation_Frame;			//プレイヤのノックバックアニメーションフレーム
	float Player_Death_Animation_Frame;				//プレイヤの死亡アニメーションフレーム
	int Player_Animation_No_Move;					//プレイヤの移動アニメーション番号
	int Player_Animation_No_Attack1;				//プレイヤの攻撃1アニメーション番号
	int Player_Animation_No_Attack1_Idle;			//攻撃1再生後の待機アニメーション番号
	int Player_Animation_No_Attack2;				//プレイヤの攻撃2アニメーション番号
	int Player_Animation_No_Attack2_Idle;			//攻撃2再生後の待機アニメーション番号
	int Player_Animation_No_AvoidDance;				//プレイヤの回避アニメーション番号
	int Player_Animation_No_Idle;					//プレイヤの待機アニメーション番号
	int Player_Animation_No_Knockback;				//プレイヤのノックバックアニメーション番号
	int Player_Animation_No_Death;					//プレイヤの死亡アニメーション番号
	float Player_Gauge_Frame_Tex_Wid;				//プレイヤのHPゲージフレームテクスチャ終点の横幅
	float Player_Gauge_Frame_Tex_First_Wid;			//プレイヤのHPゲージフレームテクスチャ始点の横幅
	float Player_Gauge_Frame_Tex_Hei;				//プレイヤのHPゲージフレームテクスチャ終点の縦幅
	float Player_Gauge_Frame_Tex_First_Hei;			//プレイヤのHPゲージフレームテクスチャ始点の縦幅
	float Player_Gauge_Frame_Left;					//プレイヤのHPゲージフレーム左座標指定
	float Player_Gauge_Frame_Right;					//プレイヤのHPゲージフレーム右座標指定
	float Player_Gauge_Frame_Top;					//プレイヤのHPゲージフレーム頂点座標指定
	float Player_Gauge_Frame_Bottom;				//プレイヤのHPゲージフレーム底辺座標指定
	float Player_Gauge_Wid;							//プレイヤのHPゲージ終点の横幅
	float Player_Gauge_Wid_First;					//プレイヤのHPゲージ始点の横幅
	float Player_Gauge_Height;						//プレイヤのHPゲージ終点の縦幅
	float Player_Gauge_Height_first;				//プレイヤのHPゲージ始点の縦幅
	float Player_Gauge_Hp_Top;						//プレイヤのHPゲージ頂点座標指定
	float Player_Gauge_Hp_Bottom;					//プレイヤのHPゲージ底辺座標指定
	int Player_Gauge_Hp_Shake_X;					//プレイヤのHPゲージを揺らすX座標の初期値値設定
	int Player_Gauge_Hp_Shake_Y;					//プレイヤのHPゲージを揺らすY座標の初期値設定
	int Player_Gauge_Hp_Shake_Range_X;				//プレイヤのHPゲージを揺らすX座標の最大値
	int Player_Gauge_Hp_Shake_Range_Y;				//プレイヤのHPゲージを揺らすY座標の最大値
	float Player_Gauge_Hp_Rate;						//プレイヤのHPゲージの揺れ判定
	float Player_Trun_Set;							//プレイヤの回転設定
	float Player_Trun_Speeds_Set;					//プレイヤの回転速度設定
	float Player_Trun_Check_Speeds_Set;				//プレイヤの回転速度チェック設定
	float Player_Trun_Check_Set;					//プレイヤの回転チェック設定

	//プレイヤの行動処理
	void Idle();						//待機処理
	void MoveCamera();					//カメラを基準にした移動処理
	void Move();						//移動処理
	void Attack_1();					//攻撃1処理
	void Attack_2();					//攻撃2処理
	void Avoidance();					//回避処理
	void Death();						//死亡処理
	void KnockBack();					//ノックバック処理
	//移動の計算処理
	void MovingCalculation();
	//プレイヤの衝突判定関数
	void Collision(CCollider* m, CCollider* o);		//衝突処理

};
#endif 

