#ifndef CXENEMY_H
#define CXENEMY_H

#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCamera.h"
#include"CEnemyData.h"



class CXEnemy : public CXCharacter{
public:
	//敵の基本的関数
	void Init(CModelX* model);					//敵の設定
	void Update();								//敵の更新
	CXEnemy();									//敵のデフォルトコンストラクタ
	void Collision(CCollider* m, CCollider* o);	//敵の当たり判定
	void Render2D();
	void Load(int argc, char* argv[]);
	void TaskCollision();
	//敵の状態
	enum EEnemyState
	{
		EIDLE = 0,								//待機
		EAUTOMOVE,								//移動
		EDASH,									//ダッシュ
		EATTACK_1,								//攻撃1
		EATTACK_2,								//攻撃2
		EATTACK_3,								//攻撃3
		EKNOCKBACK,								//ノックバック
		//EREPELLED,								//はじかれた時のノックバック
		EDEATH,									//死亡
	};
	bool GetIsAnimationFrame();
	bool GetHp();								//敵のHP取得関数
	bool GetIsHit();							//ヒット状態の判別
	void SetIsHit(bool hitflag);				//攻撃の当たり判定フラグを設定
	CXEnemy::EEnemyState GetState();			//プレイヤーの状態を取得する
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
	int mEnemy_Hp;								//敵の体力
	int mEnemy_val;								//ランダム用の変数

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
	void Dash();								//追跡処理
	void Attack_1();							//攻撃1処理
	void Attack_2();							//攻撃2処理
	void Attack_3();							//攻撃3処理
	void KnockBack();							//ノックバック処理
	void Death();								//死亡処理
	//移動の計算処理
	void MovingCalculation();

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
#endif

