#ifndef CXENEMY_H
#define CXENEMY_H


#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCamera.h"
#include"CUtil.h"
#include"CXPlayer.h"
#include "CTable.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>

/*
CXEnemyクラス
敵のクラス
*/

class CXEnemy : public CXCharacter {
public:
	//他のクラスで参照用の関数
	static CXEnemy* GetInstance();
	//敵の状態
	enum class EEnemyState
	{
		EIDLE = 0,								//待機
		EMOVE,									//移動
		EDASH,									//ダッシュ
		EBACKSTEP,								//後退
		EATTACK_1,								//攻撃1
		EATTACK_2,								//攻撃2
		EKNOCKBACK,								//ノックバック
		EDEATH,									//死亡
	};
	
	//敵の強さの種類
	enum class EEnemyType {
		ETYPE_TUTORIAL,							//チュートリアル時の敵の強さ
		ETYPE_GAME_1,							//ゲーム本番時の敵の強さ(強い)
		ETYPE_GAME_2,							//ゲーム本番時の敵の強さ(弱い)
	};
	//再生中のアニメーションフレーム数を取得する
	bool GetIsAnimationFrame();					
	//ヒット状態の判別
	bool GetIsHit();
	//死亡状態の時にtrueを返す
	bool GetIsDeath();	
	//現在のHPを取得する
	int GetHp();
	//現在の敵のタイプを取得
	CXEnemy::EEnemyType GetIsType();
	//タイプの設定
	void SetIsType(EEnemyType type);
	//攻撃の当たり判定フラグを設定
	void SetIsHit(bool hitflag);
	//プレイヤに与えるダメージ取得用
	int GetIsAttackPoint();	
	//プレイヤに与えるスタンダメージ取得用
	int GetIsStanPoint();
	//プレイヤの状態を取得する
	CXEnemy::EEnemyState GetState();					
	//敵モデル設定
	void Init(CModelX* model);					//敵のモデル設定
	//更新処理
	void Update();								//敵の更新
	//テーブル読み込み関数
	void EnemyTable();							//エネミーテーブル
	//当たり判定の格納
	void TaskCollision();						//タスクに当たり判定を格納する
	//デフォルトコンストラクタ
	CXEnemy();									//敵のデフォルトコンストラクタ
protected:

	//当たり判定設定
	void Collision(CCollider* m, CCollider* o);	//敵の当たり判定
	//2Dの描画処理
	void Render2D();							//2Dの描画処理
	//敵の行動メソッド関数
	void Idle();								//待機処理
	void Move();								//移動処理
	void Dash();								//ダッシュ処理
	void BackStep();							//後退処理
	void Attack_1();							//攻撃1処理
	void Attack_2();							//攻撃2処理
	void KnockBack();							//ノックバック処理
	void Death();								//死亡処理
	//移動の計算処理
	void MovingCalculation();


private:
	EEnemyState mEnemy_State;					//敵の状態判断用

	EEnemyType mEnemy_Type;						//敵の種類判断用
	//始め
	//テーブル取得用変数
	int Enemy_Priority;							//描画優先度
	int Enemy_Hp;								//HP
	int Enemy_Hp_Max;							//HP最大値
	int Enemy_Attack_Point;						//攻撃力
	int Enemy_Defense_Point;					//守備力
	int Enemy_Stan_Point;						//スタン値
	float Enemy_Damage_Magnification;			//ダメージ倍率
	int Enemy_Death_Hp;							//死亡条件
	float Enemy_Gravity;						//敵の重力
	int Enemy_StanAccumulation;				    //敵のスタン蓄積
	int Enemy_StanAccumulation_Max;				//敵のスタン蓄積最大値
	float Enemy_Speed_WalkPattern;				//移動スピードパターン
	float Enemy_Speed_DashPattern;				//ダッシュスピードパターン
	float Enemy_Speed_BackPattern;				//後退スピードパターン
	float Enemy_Walk_Dis;						//歩行開始の距離
	float Enemy_Dash_Dis;						//走行開始の距離
	float Enemy_Walk_Dis_Max;					//歩行終了の距離
	float Enemy_Dash_Dis_Max;					//走行終了の距離
	float Enemy_Attack_Dis;						//攻撃可能な距離
	float Enemy_Attack_Reception;				//当たり判定の開始
	float Enemy_Attack_Outreception;			//当たり判定の終了
	int Enemy_Action_Rand;						//アクションの推移設定
	int Enemy_Attack_Walk_Rand;					//歩行時、ランダムに攻撃する
	int Enemy_Attack_Dash_Rand;					//走行時、ランダムに攻撃する
	int Enemy_AttackSp1_Set;					//攻撃1の時、攻撃可能時追従する精度設定
	int Enemy_AttackSp2_Set;					//攻撃2の時、攻撃可能時追従する精度設定
	float Enemy_Idle_Animation_Frame;			//敵の待機アニメーションフレーム
	float Enemy_Move_Animation_Frame;			//敵の移動アニメーションフレーム
	float Enemy_Dash_Animation_Frame;			//敵の走行アニメーションフレーム
	float Enemy_BackStep_Animation_Frame;		//敵のバックステップアニメーションフレーム
	float Enemy_Attack1_Animation_Frame;		//敵の攻撃1アニメーションフレーム
	float Enemy_Attack2_Animation_Frame;		//敵の攻撃2アニメーションフレーム
	float Enemy_Knockback_Animation_Frame;		//敵のノックバックアニメーションフレーム
	float Enemy_Death_Animation_Frame;			//敵の死亡アニメーションフレーム
	int Enemy_Animation_No_Attack_1;			//敵の攻撃1アニメーション番号
	int Enemy_Animation_No_Attack_2;			//敵の攻撃2アニメーション番号
	int Enemy_Animation_No_Walk;				//敵の移動アニメーション番号
	int Enemy_Animation_No_Dash;				//敵の走行アニメーション番号
	int Enemy_Animation_No_BackStep;			//敵のバックステップアニメーション番号
	int Enemy_Animation_No_Idle;				//敵の待機アニメーション番号
	int Enemy_Animation_No_Knockback;			//敵のノックバックアニメーション番号
	int Enemy_Animation_No_Death;				//敵の死亡アニメーション番号
	float Enemy_Position_X;						//敵のポジション設定X座標
	float Enemy_Position_Y;						//敵のポジション設定Y座標
	float Enemy_Position_Z;						//敵のポジション設定Z座標
	float Enemy_Scale_X;						//モデルスケールのX座標
	float Enemy_Scale_Y;						//モデルスケールのY座標
	float Enemy_Scale_Z;						//モデルスケールのZ座標
	float Enemy_Rotation_X;						//モデルの回転X座標
	float Enemy_Rotation_Y;						//モデルの回転Y座標
	float Enemy_Rotation_Z;						//モデルの回転Z座標
	//終わり

	//コライダの宣言
	CCollider mEnemy_ColSphereRightarm;			//右腕
	CCollider mEnemy_ColSphereLeftarm;			//左腕
	CCollider mEnemy_ColSphereBody;				//球の身体
	CColliderCapsule mEnemy_ColCapsuleBody;		//カプセルの身体

	//敵のUIインスタンス
	CTexture gEnemy_Ui_Hp_BackBar;				//HPの背景バー
	//敵モデル
	CModelX gEnemy_Model_Mutant;

	//敵のパラメータ
	float mEnemy_Speed;							//敵のスピード
	float mEnemy_Turnspeed;						//敵のターン速度
	float mEnemy_PlayerDis;						//敵がプレイヤの座標参照用
	float mEnemy_FollowGaugeWid;				//被ダメージ分後追いするゲージの幅
	int mEnemy_val;								//ランダム用の変数


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
	bool mEnemy_Flag;							//敵のフラグ
	bool mEnemy_IsHit;							//敵の攻撃時にtrueを返す　敵に攻撃が当たるor攻撃終了時にfalseを返す
	bool mEnemy_Death_Flag;						//敵の死亡時消去フラグ

	//ステータス
	int mHp;									//HP設定
	int mAttack_Point;							//攻撃力
	int mDefense_Point;							//守備力
	int mStan_Point;							//スタン値
	int mStanAccumulation;						//スタン蓄積

	//プレイヤからの攻撃判断用
	int mDamage;								//プレイヤからのダメージ
	int mStan_Damage;							//プレイヤからのスタンダメージ

};
#endif

