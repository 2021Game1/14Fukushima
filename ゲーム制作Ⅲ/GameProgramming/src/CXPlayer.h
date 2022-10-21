#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CInput.h"
/*
CXPlayer
*/
#define SPEED_DEFAULT 0.15f		//スピード(通常時)

class CXPlayer : public CXCharacter {
public:
	//プレイヤの状態
	enum EPlayerState
	{
		EIDLE = 0,	//待機
		EMOVE,		//移動
		//EDASH,		//ダッシュ
		EGUARD,		//ガード
		EATTACK_1,	//攻撃1
		//EATTACK_2,	//攻撃2
		//EATTACK_3,	//攻撃3(攻撃1から派生)
		EDEATH,		//死亡
		EKNOCKBACK,	//ノックバック
	};
	void Update();
	void Init(CModelX* model);
	CXPlayer();
	static CXPlayer* mpPlayerInstance;//別のクラスで変数を呼び出す場合,staticでポインタを作る
	static CXPlayer* GetInstance();//staticで処理を作る

	void Collision(CCollider* m, CCollider* o);

	void Idle();		//待機処理
	void MoveCamera();	//カメラを基準にした移動処理
	void Move();		//移動処理
	//void Dash();		//ダッシュ処理
	void Attack_1();	//攻撃1処理
	//void Attack_2();	//攻撃2処理
	//void Attack_3();	//攻撃3処理
	void Guard();		//回避処理
	void Death();		//死亡処理
	void KnockBack();	//ノックバック処理

private:
	//コライダの宣言
	CCollider mColSphereHead;//頭
	CCollider mColSphereSword;//剣
	CCollider mColSphereBody; //身体
	EPlayerState mState;	//プレイヤーの状態判断用
	float mSpeed;	//スピード

	CVector mMove;			//方向と速度をかけ合わせたベクトル、プレイヤーの移動量
	CVector mMoveDir;		//移動する方向、モデルの回転にも使用している、毎フレームリセットされる
	CVector mMoveDirKeep;	//移動時の方向を保存する
	CVector mKnockBackDir;	//ノックバックする方向を保持する
	CVector mAttackDir;		//攻撃時の方向を保持する

	CVector mSideVec;		//カメラの横ベクトル
	CVector mFrontVec;		//カメラの正面ベクトル
	float mTurnspeed;		//ターンの速度


};
#endif 

