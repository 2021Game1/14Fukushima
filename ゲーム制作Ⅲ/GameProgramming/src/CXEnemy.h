#ifndef CXENEMY_H
#define CXENEMY_H

#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCamera.h"




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
		EATTACK_1,								//攻撃1
		EATTACK_2,								//攻撃2
		EATTACK_3,								//攻撃3
		EKNOCKBACK,								//ノックバック
		//EREPELLED,								//はじかれた時のノックバック
		EDEATH,									//死亡
	};
	//他のクラスで参照用の関数
	static CXEnemy* GetInstance();				//staticで処理を作る
	bool GetIsAnimationFrame();
	bool GetHp();								//敵のHP取得関数
	bool GetIsHit();							//ヒット状態の判別
	void SetIsHit(bool hitflag);	//攻撃の当たり判定フラグを設定
	bool mIsDeath();							//死亡状態の時にtrueを返す
	CXEnemy::EEnemyState GetState();			//プレイヤーの状態を取得する
protected:
	//コライダの宣言
	CCollider mEnemy_ColSphereRightarm;	//右腕
	CCollider mEnemy_ColSphereLeftarm;	//左腕
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
	EEnemyState mEnemy_State;					//敵の状態判断用
	bool mEnemy_Flag;							//敵のフラグ
	bool mEnemy_IsHit;							//敵の攻撃時にtrueを返す　敵に攻撃が当たるor攻撃終了時にfalseを返す
	static CXEnemy* mpEnemy_Instance;			//別のクラスで敵の変数を呼び出す場合,staticでポインタを作る
	//敵の行動メソッド関数
	void Idle();								//待機処理
	void Move();								//移動処理
	void Dash();								//追跡処理
	void Attack_1();							//攻撃1処理
	void Attack_2();							//攻撃2処理
	void Attack_3();							//攻撃3処理
	void KnockBack();							//ノックバック処理
	//void Repelled();							//はじかれた時の処理
	void Death();								//死亡処理
	//移動の計算処理
	void MovingCalculation();


};
#endif

