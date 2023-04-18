#ifndef CXENEMY_H
#define CXENEMY_H

#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCamera.h"
#include"CEnemyData.h"
#include"CUtil.h"
#include"CXPlayer.h"
#include "CTable.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>



class CXEnemy : public CXCharacter{
public:
	//敵の基本的関数
	void Init(CModelX* model);					//敵の設定
	void Update();								//敵の更新
	CXEnemy();									//敵のデフォルトコンストラクタ
	void Collision(CCollider* m, CCollider* o);	//敵の当たり判定
	void Render2D();
	void TaskCollision();
	//敵の状態
	enum EEnemyState
	{
		EIDLE = 0,								//待機
		EAUTOMOVE,								//移動
		EDASH,									//ダッシュ
		EBACKSTEP,								//後退
		EATTACK_1,								//攻撃1
		EATTACK_2,								//攻撃2
		EATTACK_3,								//攻撃3
		EKNOCKBACK,								//ノックバック
		EDEATH,									//死亡
	};
	bool GetIsAnimationFrame();
	bool GetHp();								//敵のHP取得関数
	bool GetIsHit();							//ヒット状態の判別
	void SetIsHit(bool hitflag);				//攻撃の当たり判定フラグを設定
	CXEnemy::EEnemyState GetState();			//プレイヤーの状態を取得する
	//他のクラスで参照用の関数
	static CXEnemy* GetInstance();
protected:
	//コライダの宣言
	CCollider mEnemy_ColSphereRightarm;	//右腕
	CCollider mEnemy_ColSphereLeftarm;	//左腕
	CCollider mEnemy_ColSphereBody;				//球の身体
	CColliderCapsule mEnemy_ColCapsuleBody;		//カプセルの身体
	//敵のパラメータ
	float mEnemy_Speed;							//敵のスピード
	float mEnemy_Turnspeed;						//敵のターン速度
	float mEnemy_PlayerDis;						//敵がプレイヤの座標参照用
	float mEnemy_FollowGaugeWid;				//被ダメージ分後追いするゲージの幅
	int mEnemy_val;								//ランダム用の変数
	int mHp;
	//敵の攻撃時にtrueを返す　敵に攻撃が当たるor攻撃終了時にfalseを返す
	static CXEnemy* mpEnemy_Instance;

	//敵の移動
	CVector mEnemy_Point;						//敵移動時の目標地点
	CVector mEnemy_PlayerPos;					//敵追跡時の目標地点
	CVector mEnemy_Move;						//敵の方向と速度をかけ合わせたベクトル、プレイヤーの移動量
	CVector mEnemy_MoveDir;						//敵の移動する方向、モデルの回転にも使用している、毎フレームリセットされる
	CVector mEnemy_MoveDirKeep;					//敵の移動時の方向を保存する
	CVector mEnemy_Player_Point;				//プレイヤの方向ベクトル保存用
	CVector mEnemy_AttackDir;					//敵の攻撃時の方向を保持する
	EEnemyState mEnemy_State;					//敵の状態判断用
	bool mEnemy_Flag;							//敵のフラグ
	bool mEnemy_IsHit;							//敵の攻撃時にtrueを返す　敵に攻撃が当たるor攻撃終了時にfalseを返す
	//敵の行動メソッド関数
	void Idle();								//待機処理
	void Move();								//移動処理
	void Dash();								//ダッシュ処理
	void BackStep();							//後退処理
	void Attack_1();							//攻撃1処理
	void Attack_2();							//攻撃2処理
	void Attack_3();							//攻撃3処理
	void KnockBack();							//ノックバック処理
	void Death();								//死亡処理
	//移動の計算処理
	void MovingCalculation();

private:
	void EnemyTable();
	int mEnemy_Priority;						//描画優先度
	float mEnemy_Speed_WalkPattern;				//移動スピードパターン
	float mEnemy_Speed_DashPattern;				//ダッシュスピードパターン
	float mEnemy_Walk_Dis;						//歩行開始の距離
	float mEnemy_Dash_Dis;						//走行開始の距離
	float mEnemy_Walk_Dis_Max;					//歩行終了の距離
	float mEnemy_Dash_Dis_Max;					//走行終了の距離
	float mEnemy_Attack_Dis;					//攻撃可能な距離
	float mEnemy_Attack_Reception;				//当たり判定の開始
	float mEnemy_Attack_Outreception;			//当たり判定の終了
	int mEnemy_Attack_Walk_Rand;				//歩行時、ランダムに攻撃する
	int mEnemy_Attack_Dash_Rand;				//走行時、ランダムに攻撃する
	int mEnemy_Damage_PlayerSp1;				//プレイヤの攻撃1のダメージ
	int mEnemy_Damage_PlayerSp2;				//プレイヤの攻撃2のダメージ
	float mEnemy_Idle_Animation_Frame;			//敵の待機アニメーションフレーム
	float mEnemy_Move_Animation_Frame;			//敵の移動アニメーションフレーム
	float mEnemy_Dash_Animation_Frame;			//敵の走行アニメーションフレーム
	float mEnemy_BackStep_Animation_Frame;		//敵のバックステップアニメーションフレーム
	float mEnemy_Attack1_Animation_Frame;		//敵の攻撃1アニメーションフレーム
	float mEnemy_Attack2_Animation_Frame;		//敵の攻撃2アニメーションフレーム
	float mEnemy_Attack3_Animation_Frame;		//敵の攻撃3アニメーションフレーム
	float mEnemy_Knockback_Animation_Frame;		//敵のノックバックアニメーションフレーム
	float mEnemy_Death_Animation_Frame;			//敵の死亡アニメーションフレーム
	int mEnemy_Animation_No_Attack_1;			//敵の攻撃1アニメーション番号
	int mEnemy_Animation_No_Attack_2;			//敵の攻撃2アニメーション番号
	int mEnemy_Animation_No_Attack_3;			//敵の攻撃3アニメーション番号
	int mEnemy_Animation_No_Walk;				//敵の移動アニメーション番号
	int mEnemy_Animation_No_Dash;				//敵の走行アニメーション番号
	int mEnemy_Animation_No_BackStep;			//敵のバックステップアニメーション番号
	int mEnemy_Animation_No_Idle;				//敵の待機アニメーション番号
	int mEnemy_Animation_No_Knockback;			//敵のノックバックアニメーション番号
	int mEnemy_Animation_No_Death;				//敵の死亡アニメーション番号
	float mEnemy_Position_X;					//初期位置のX座標
	float mEnemy_Position_Y;					//初期位置のY座標
	float mEnemy_Position_Z;					//初期位置のZ座標
	float mEnemy_Scale_X;						//モデルスケールのX座標
	float mEnemy_Scale_Y;						//モデルスケールのY座標
	float mEnemy_Scale_Z;						//モデルスケールのZ座標
	float mEnemy_Rotation_X;					//モデルの回転X座標
	float mEnemy_Rotation_Y;					//モデルの回転Y座標
	float mEnemy_Rotation_Z;					//モデルの回転Z座標
	int mEnemy_Probability_Low_Set1;			//敵の行動1設定ランダム変数最低値設定
	int mEnemy_Probability_Max_Set1;			//敵の行動1設定ランダム変数最高値設定
	int mEnemy_Probability_Low_Set2;			//敵の行動2設定ランダム変数最低値設定
	int mEnemy_Probability_Max_Set2;			//敵の行動2設定ランダム変数最高値設定
	float mEnemy_Gravity;						//敵の重力
	int mEnemy_Hp;								//HP
	int mEnemy_Hp_Max;							//HP最大値
	int mEnemy_Hp_State;						//HP状態推移設定
	int mEnemy_Death_Hp;						//死亡条件
};
#endif

