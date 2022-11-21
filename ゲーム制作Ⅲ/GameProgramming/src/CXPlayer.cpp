#include"CXPlayer.h"
#include"CSceneGame.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CCamera.h"

#define GRAVITY 0.001f//重力
#define RECEPTION 120 //入力の受付時間
#define INITIALIZATION 0 //初期化

CXPlayer* CXPlayer::mpPlayerInstance = nullptr;



//コライダ初期化
CXPlayer::CXPlayer()
	:mColSphereBody(this, nullptr, CVector(0.0f,80.0f,0.0f), CVector(0.0f, -80.0f, 0.0f), 0.7)
	, mColSphereShield(this, nullptr, CVector(0.0f, 0.0f, -5.0f), 0.5f)
	, mColSphereSword1(this, nullptr, CVector(-13.0f, 0.0f, 70.0f), 0.3f)
	, mColSphereSword2(this, nullptr, CVector(-10.0f, 0.0f, 50.0f), 0.3f)
	, mColSphereSword3(this, nullptr, CVector(-5.0f, 0.0f, 30.0f), 0.3f)
	, mColSphereSword4(this, nullptr, CVector(-0.0f, 0.0f, 10.0f), 0.3f)
	, mSpeed(SPEED_DEFAULT)
	, mHp(1)
	, mPlayerComboCount(0)
	, mAttackFlag_1(false)
	, mAttackFlag_2(false)
	, mAttackFlag_3(false)
	, mAttackFlag_Once(false)
	, mIsHit(false)
	, mTurnspeed(0.0f)
	, mPlayerFlag(false)

{
	mpPlayerInstance = this;
	mTag = EPLAYER;
	//初期状態を設定
	mState = EIDLE;	//待機状態
	//コライダのタグを設定
	mColSphereBody.Tag(CCollider::EBODY);		//体
	mColSphereShield.Tag(CCollider::ESHIERD);	//盾
	mColSphereSword1.Tag(CCollider::ESWORD);	//剣
	mColSphereSword2.Tag(CCollider::ESWORD);	//剣
	mColSphereSword3.Tag(CCollider::ESWORD);	//剣
	mColSphereSword4.Tag(CCollider::ESWORD);	//剣
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[14]);
	mColSphereShield.Matrix(&mpCombinedMatrix[41]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[71]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[71]);
	mColSphereSword3.Matrix(&mpCombinedMatrix[71]);
	mColSphereSword4.Matrix(&mpCombinedMatrix[71]);
	mPosition.Set(0.0f, 0.0f, 0.0);	//位置を設定
	mScale.Set(2.0f,2.0f,2.0f);//スケール設定
	mRotation.Set(0.0f, 180.0f, 0.0f);	//回転を設定
}

void CXPlayer::Update() {
	//状態を判別
	switch (mState) {
	case EIDLE:	//待機状態
		Idle();	//待機処理を呼ぶ
		break;

	case EATTACK_1:	//攻撃1状態の時
		Attack_1();	//攻撃1の処理を呼ぶ
		break;

	case EATTACK_2:	//攻撃2状態の時
		Attack_2();	//攻撃2の処理を呼ぶ
		break;

	case EATTACK_3:	//攻撃3状態の時
		Attack_3();	//攻撃3の処理を呼ぶ
		break;

	case EMOVE:	//移動状態
		Move();	//移動状態の処理を呼ぶ
		break;

	case EGUARD: //回避状態
		Guard(); //回避処理を呼ぶ
		break;

	case EDEATH: //死亡状態
		Death(); //死亡処理を呼ぶ
		break;

	case EKNOCKBACK: //ノックバック状態
		KnockBack(); //ノックバック処理を呼ぶ
		break;
	}
	//座標移動
	mPosition += mMove;
	//減速させる
	mMove = mMove * GRAVITY;

	////重力
	//mPosition.mY -= GRAVITY;

	//普通に3次元ベクトル計算で算出したほうが正確だが計算量を懸念する場合は擬似計算で軽量化
	//擬似ベクトル計算
	CVector ChackVec; //チェック用ベクトル
	ChackVec = mMoveDirKeep.Normalize(); //保存された移動時の方向ベクトルを代入
	ChackVec = mMoveDir.Normalize(); //移動時の方向ベクトルを代入
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / 180.0f));

	//回転速度　degreeに直す
	mTurnspeed = (180.0f / M_PI) * 0.3f;

	//急な振り返りを抑制
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//移動方向へキャラを向かせる
	if (tCheck.cross > 0.0f) {
		mRotation = mRotation + CVector(0.0f,tCheck.turn * mTurnspeed,0.0f);
	}
	if (tCheck.cross < 0.0f) {
		mRotation = mRotation - CVector(0.0f, tCheck.turn * mTurnspeed, 0.0f);
	}

	//リセット
	mMoveDir = CVector(0.0f, 0.0f, 0.0f);

	//体力が0になると死亡
	if (mHp <= 0) {
		mState = EDEATH;	//死亡状態へ移行
		mHp = 0;
	}

	Camera.SetTarget(mPosition);
	CXCharacter::Update();

}

void CXPlayer::Idle() 
{
	mPlayerComboCount = 0;
	ChangeAnimation(6, true, 30);
	//左クリックで攻撃
	if (CKey::Once(VK_LBUTTON)) {
		mState = EATTACK_1;
	}
	//WASDキーを押すと移動へ移行
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mState = EMOVE;
	}
	else if (CKey::Once(VK_SPACE)) {
		mState = EGUARD;
	}
}

//移動処理
void CXPlayer::Move()
{
	
	if (CKey::Once(VK_LBUTTON)) {
		mState = EATTACK_1;
	}
	//左クリックで攻撃1へ移行
	else if (CKey::Once(VK_SPACE)) {
		mState = EGUARD;
	}
	//WASDキーを押すと移動
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		MoveCamera(); //カメラを基準にした移動処理を呼ぶ
		ChangeAnimation(0, true, 30);
	}
	//待機状態へ移行
	else {
		mState = EIDLE;
	}
}


//攻撃1処理
void CXPlayer::Attack_1()
{
	
	if (mAttackFlag_1 == false) {
		mAttackFlag_1 = true;
		mAttackFlag_Once = true;
		ChangeAnimation(5, false, 1);//待機モーション
	}

	if (mAnimationIndex == 5)
	{
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mIsHit = false; //ヒット判定終了
			ChangeAnimation(1, false, 30);
		}
	}
	else if (mAnimationIndex == 3) {
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mIsHit = false; //ヒット判定終了
			ChangeAnimation(1, false, 30);
		}
	}

	else if (mAnimationIndex == 1)
	{
		if (mAnimationFrame < RECEPTION) {
			if (CKey::Once(VK_LBUTTON)) {
				mState = EATTACK_2;	//攻撃2のモーションへ移行
			}
			else if(CKey::Once(VK_SPACE)) {
				mState = EGUARD;
			}
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
	mState = EIDLE; //待機状態へ移行
	mAttackFlag_1 = false;
	}
}

//攻撃2処理
void CXPlayer::Attack_2()
{
	if (mAttackFlag_2 == false) {
		mAttackFlag_2 = true;
		mAttackFlag_Once = true;
	}
	if (mAnimationIndex == 1)
	{
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//アニメーション終了時
		else if (IsAnimationFinished())
		{
			mIsHit = false; //ヒット判定終了
			ChangeAnimation(2, false, 40);
		}
	}
	else if (mAnimationIndex == 2)
	{
		if (mAnimationFrame < RECEPTION) {
			if (CKey::Once(VK_LBUTTON)) {
				mState = EATTACK_3;	//攻撃3のモーションへ移行
			}
			else if (CKey::Once(VK_SPACE)) {
				mState = EGUARD;
			}
		}
	}
	if (IsAnimationFinished())
	{
	mState = EIDLE; //待機状態へ移行
	}
}

//攻撃3処理
void CXPlayer::Attack_3()
{
	if (mAttackFlag_3 == false) {
		mAttackFlag_3 = true;
		mAttackFlag_Once = true;
	}
	if (mAnimationIndex == 2)
	{
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mIsHit = false; //ヒット判定終了
			ChangeAnimation(3, false, 60);
		}
	}
	else if (mAnimationIndex == 3)
	{
		if (mAnimationFrame < RECEPTION) {
			if (CKey::Once(VK_LBUTTON)) {
				mState = EATTACK_1;	//攻撃1のモーションへ移行
			}
			else if(CKey::Once(VK_SPACE)) {
				mState = EGUARD;
			}
		}
	}

	if (IsAnimationFinished())
	{
	mState = EIDLE; //待機状態へ移行
	}
}

//ノックバック処理
void CXPlayer::KnockBack()
{
	ChangeAnimation(7, false, 50);	//のけ反りアニメーション
		//アニメーション終了時
	if (IsAnimationFinished())
	{
		mState = EIDLE; //待機状態へ移行
	}
}

//ガード
void CXPlayer::Guard()
{
	if (mPlayerFlag == false) {
		ChangeAnimation(6, false, 1);//待機モーション
		mPlayerFlag = true;
	}
	
	if (mAnimationIndex == 6){
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			ChangeAnimation(4, false, 10);	//ガード待機アニメーション
		}
	}
	else if (mAnimationIndex == 4) {
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
			mIsHit = true;
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mIsHit = false; //ヒット判定終了
			ChangeAnimation(5, false, 30);	//ガード待機アニメーション
		}

	}
	//アニメーション終了時
	else if (IsAnimationFinished())
	{
		mState = EIDLE;
		mPlayerFlag = false;
	}

}

//死亡処理
void CXPlayer::Death()
{
	ChangeAnimation(8, false, 50);	//死亡アニメーション
}

//カメラを基準にした移動処理
void CXPlayer::MoveCamera()
{
	//カメラ視点移動　通称無双移動
	//カメラの左右と前後のベクトルを取得
	mSideVec = Camera.GetMat().GetXVec();
	mFrontVec = Camera.GetMat().GetZVec();
	//高さ移動はカットする
	mSideVec.Y(0.0f);
	mFrontVec.Y(0.0f);
	//正規化する
	mSideVec.Normalize();
	mFrontVec.Normalize();

	if (CKey::Push('A'))
	{
		mMoveDir -= mSideVec;
	}
	else if (CKey::Push('D'))
	{
		mMoveDir += mSideVec;
	}
	if (CKey::Push('W')) {
		mMoveDir += mFrontVec;
	}
	else if (CKey::Push('S'))
	{
		mMoveDir -= mFrontVec;
	}

	//ジャンプ時などはY軸を正規化しないよう注意
	mMoveDir = mMoveDir.Normalize();
	mMoveDirKeep = mMoveDir;	//MoveDir保存
	mMove = mMoveDir * mSpeed;	//移動量を設定
}



void CXPlayer::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ESPHERE: {//球コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と球の衝突判定
			CCollider::CollisionTriangleSphere(o, m, &adjust);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition + adjust;
			//行列の更新
			CTransform::Update();
		}

		break;
	}
						   
	case CCollider::ECAPSUL:{//カプセルコライダ
		//相手のコライダがカプセルコライダの時
		if (o->Type() == CCollider::ECAPSUL) {
			CVector adjust;//調整用ベクトル
			if (CCollider::CollisionCapsule(o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();

			}

			break;
		}
		else if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();
			}
			break;
		}
		//if (o->Type() == CCollider::ESPHERE) {
		//	CVector adjust;//調整用ベクトル
		//	//コライダのmとoが衝突しているかの判定
		//		CCollider::Collision(m, o);
		//		//相手の親のタグがプレイヤー
		//		if (o->Parent()->Tag() == EENEMY)
		//		{
		//			//相手のコライダのタグが剣
		//			if (o->Tag() == CCollider::EARM) {
		//				if (CXEnemy::GetInstance()->GetIsHit() == true) {
		//					mState = EKNOCKBACK;
		//					mHp = mHp - 1;
		//				}
		//			}
		//		}
		//	
		//	
		//}
	}
	}		
}

//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayerInstance;
}
//攻撃の当たり判定を取得する
bool CXPlayer::GetIsHit()
{
	return mIsHit; //攻撃の当たり判定を返す
}

//プレイヤーの状態を取得する
CXPlayer::EPlayerState CXPlayer::GetState()
{
	return mState;
}