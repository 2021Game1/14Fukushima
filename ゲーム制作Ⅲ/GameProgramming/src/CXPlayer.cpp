#include"CXPlayer.h"
#include"CSceneGame.h"
#include "CCamera.h"
#define GRAVITY 0.1f//重力


CXPlayer* CXPlayer::mpPlayerInstance;
//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayerInstance;
}

//コライダ初期化
CXPlayer::CXPlayer()
	:mColSphereBody(this,nullptr,CVector(),0.5)
	,mColSphereHead(this,nullptr,CVector(0.0f,5.0f,-3.0f),0.5f)
	,mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
	,mSpeed(SPEED_DEFAULT)
{
	mTag = EPLAYER;
	//初期状態を設定
	mState = EIDLE;	//待機状態
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[9]);
	mColSphereHead.Matrix(&mpCombinedMatrix[12]);
	mColSphereSword.Matrix(&mpCombinedMatrix[22]);

}
void CXPlayer::Update() {
	CSceneGame* tSceneGame = CSceneGame::GetInstance();

	//状態を判別
	switch (mState) {
	case EIDLE:	//待機状態
		Idle();	//待機処理を呼ぶ
		break;

	case EATTACK_1:	//攻撃1状態の時
		Attack_1();	//攻撃1の処理を呼ぶ
		break;

	//case EATTACK_2:	//攻撃2状態の時
	//	Attack_2();	//攻撃2の処理を呼ぶ
	//	break;

	//case EATTACK_3:	//攻撃3状態の時
	//	Attack_3();	//攻撃3の処理を呼ぶ
		break;

	case EMOVE:	//移動状態
		Move();	//移動状態の処理を呼ぶ
		break;

	//case EDASH:	//ダッシュ状態
	//	Dash();	//ダッシュ状態の処理を呼ぶ
	//	break;

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

	CXCharacter::Update();
}

void CXPlayer::Idle() 
{
	ChangeAnimation(1, true, 60);//待機モーション

	//左クリックで攻撃
	if (CKey::Once(VK_LBUTTON)) {
		mState = EATTACK_1;
	}
	//WASDキーを押すと移動へ移行
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mState = EMOVE;
	}
}

//移動処理
void CXPlayer::Move()
{
	//WASDキーを押すと移動
	if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		MoveCamera(); //カメラを基準にした移動処理を呼ぶ
	}
}

//攻撃1処理
void CXPlayer::Attack_1()
{
}

//死亡処理
void CXPlayer::Death()
{
	ChangeAnimation(11, false, 50);	//倒れるアニメーション
}

//ガード
void CXPlayer::Guard()
{

}

//カメラを基準にした移動処理
void CXPlayer::MoveCamera()
{
	//カメラ視点移動　通称無双移動
	//カメラの左右と前後のベクトルを取得
	mSideVec = Camera.GetMat().GetXVec();
	mFrontVec = Camera.GetMat().GetZVec();
	//高さ移動はカットする
	mSideVec.mY = 0.0f;
	mFrontVec.mY = 0.0f;
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

	//移動量正規化　これをしないと斜め移動が早くなってしまうので注意
	//ジャンプ時などはY軸を正規化しないよう注意
	mMoveDir = mMoveDir.Normalize();
	mMoveDirKeep = mMoveDir;	//MoveDir保存
	mMove = mMoveDir * mSpeed;	//移動量を設定
}

//ノックバック処理
void CXPlayer::KnockBack() 
{
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
	}
	}
}