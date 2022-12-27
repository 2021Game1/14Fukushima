#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CColliderCapsule.h"
#include "CVector.h"
#include"CInput.h"
#include"CTexture.h"
#include"CEffect.h"

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
		EGUARD,		//ガード
		EATTACK_1,	//攻撃1
		EATTACK_2,	//攻撃2
		EATTACK_3,	//攻撃3
		EDEATH,		//死亡
		EKNOCKBACK,	//ノックバック
	};
	//プレイヤのエフェクト
	enum EPlayerEffect
	{
		EEFFECT_NULL = 0,				//エフェクトなし
		EEFFECT_PLAYER_ATTACKSP1,		//プレイヤの攻撃1エフェクト
		EEFFECT_PLAYER_ATTACKSP2,		//プレイヤの攻撃2エフェクト
		EEFFECT_PLAYER_ATTACKSP3,		//プレイヤの攻撃3エフェクト
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
	CColliderCapsule mPlayer_ColCapsuleSword;	//剣
	CColliderCapsule mPlayer_ColCapsuleShield;	//盾
	CColliderCapsule mPlayer_ColCapsuleBody;	//身体
	//プレイヤの状態推移
	EPlayerState mPlayer_State;			//プレイヤの状態判断用
	//プレイヤのエフェクト推移
	EPlayerEffect mPlayer_Effect;		//プレイヤのエフェクト判断用

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
	void Guard();						//回避処理
	void Death();						//死亡処理
	void KnockBack();					//ノックバック処理
	//移動の計算処理
	void MovingCalculation();
};

class CPlayerGuard : public CCharacter
{
public:
	CPlayerGuard(CModel* model);
	//更新
	void Update();
	//描画
	void Render();
private:

};
#endif 

