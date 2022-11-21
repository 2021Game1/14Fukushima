#ifndef CXENEMY_H
#define CEENEMY_H

#include"CXCharacter.h"
#include"CColliderCapsule.h"

class CXEnemy : public CXCharacter{
public:
	void Collision(CCollider* m, CCollider* o);
	void Init(CModelX* model);
	void Update();
	CXEnemy(const CVector& position, const CVector& rotation, const CVector& scale);
	CXEnemy();


	enum EEnemyState
	{
		EIDLE = 0,		//待機
		EAUTOMOVE,		//移動
		EDASH,			//ダッシュ
		EATTACK_1,		//攻撃1
		EATTACK_2,		//攻撃2
		EATTACK_3,		//攻撃3
		EATTACK_4,		//攻撃4
		EKNOCKBACK,		//ノックバック
		EDEATH,			//死亡
	};

	static CXEnemy* GetInstance();//staticで処理を作る
	bool GetIsHit();//ヒット状態の判別
	CXEnemy::EEnemyState GetState();	//プレイヤーの状態を取得する
protected:
	//コライダの宣言
	CCollider mColSphereRightarm1;	//右腕1
	CCollider mColSphereLeftarm1;	//左腕
	CCollider mColSphereRightarm2;	//右腕2
	CCollider mColSphereLeftarm2;	//左腕2
	CColliderCapsule mColSphereBody;	//身体

	float mSpeed;			//スピード
	float mTurnspeed;		//ターンの速度
	float mPlayerDis;
	int mHp;				//体力
	CVector mPoint;			//移動時の目標地点
	CVector mPlayerPos;	//追跡時の目標地点

	CVector mMove;			//方向と速度をかけ合わせたベクトル、プレイヤーの移動量
	CVector mMoveDir;		//移動する方向、モデルの回転にも使用している、毎フレームリセットされる
	CVector mMoveDirKeep;	//移動時の方向を保存する
	EEnemyState mState;		//敵の状態判断用

	bool mIsHit;			//攻撃時にtrueを返す　敵に攻撃が当たるor攻撃終了時にfalseを返す
	static CXEnemy* mpEnemyInstance;//別のクラスで変数を呼び出す場合,staticでポインタを作る

	void Idle();		//待機処理
	void Move();	//移動処理
	void Dash();		//追跡処理
	void Attack_1();	//攻撃1処理
	void Attack_2();	//攻撃2処理
	void Attack_3();	//攻撃3処理
	void Attack_4();	//攻撃4処理
	void KnockBack();	//ノックバック処理
	void Death();		//死亡処理
};

#endif

