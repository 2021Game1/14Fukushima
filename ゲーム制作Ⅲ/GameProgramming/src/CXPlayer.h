#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CColliderCapsule.h"
#include "CVector.h"
#include"CInput.h"
/*
CXPlayer
*/
#define SPEED_DEFAULT 0.5f		//スピード(通常時)

class CXPlayer : public CXCharacter{
public:
	//プレイヤの状態
	enum EPlayerState
	{
		EIDLE = 0,	//待機
		EMOVE,		//移動
		EGUARD,		//ガード
		EATTACK_1,	//攻撃1
		EATTACK_2,	//攻撃2
		EATTACK_3,	//攻撃3
		EDEATH,		//死亡
		EKNOCKBACK,	//ノックバック
	};
	void Update();
	void Init(CModelX* model);
	CXPlayer();


	void Collision(CCollider* m, CCollider* o);
	static CXPlayer* GetInstance();//staticで処理を作る
	bool GetIsHit();//ヒット状態の判別
	CXPlayer::EPlayerState GetState();	//プレイヤーの状態を取得する

private:
	//コライダの宣言
	CCollider mColSphereSword1;	//剣
	CCollider mColSphereSword2;	//剣
	CCollider mColSphereSword3;	//剣
	CCollider mColSphereSword4;	//剣
	CCollider mColSphereShield;	//盾
	CColliderCapsule mColSphereBody;	//身体
	EPlayerState mState;	//プレイヤーの状態判断用
	float mSpeed;			//スピード
	float mTurnspeed;		//ターンの速度

	CVector mMove;			//方向と速度をかけ合わせたベクトル、プレイヤーの移動量
	CVector mMoveDir;		//移動する方向、モデルの回転にも使用している、毎フレームリセットされる
	CVector mMoveDirKeep;	//移動時の方向を保存する
	CVector mKnockBackDir;	//ノックバックする方向を保持する
	CVector mAttackDir;		//攻撃時の方向を保持する

	//カメラのパラメータを作成する
	CVector e, c, u;		//視点,注視点,上方向
	CVector mSideVec;		//カメラの横ベクトル
	CVector mFrontVec;		//カメラの正面ベクトル
	int mHp;				//体力
	

	bool mAttackFlag_1;		//攻撃1状態の時trueを返す
	bool mAttackFlag_2;		//攻撃2状態の時trueを返す
	bool mAttackFlag_3;		//攻撃3状態の時trueを返す
	bool mIsHit;			//攻撃時にtrueを返す　敵に攻撃が当たるor攻撃終了時にfalseを返す
	bool mAttackFlag_Once;	//攻撃した瞬間だけtrueを返す、敵の回避判定に使用

	int mPlayerComboCount; //コンボルート判別用変数
	int mPlayerFlag;
	static CXPlayer* mpPlayerInstance;//別のクラスで変数を呼び出す場合,staticでポインタを作る


	void Idle();		//待機処理
	void MoveCamera();	//カメラを基準にした移動処理
	void Move();		//移動処理
	void Attack_1();	//攻撃1処理
	void Attack_2();	//攻撃2処理
	void Attack_3();	//攻撃3処理
	void Guard();		//回避処理
	void Death();		//死亡処理
	void KnockBack();	//ノックバック処理

};
#endif 

