#include "CXEnemy.h"
#include"CUtil.h"
#include"CXPlayer.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define ATTACK_DIS 4.0f		//攻撃可能になる距離
#define SPEED_MOVE 0.1f	//通常移動のスピード
#define SPEED_DASH 0.15f	//追跡中の移動速度
#define SEARCH_DIS 20.0f	//追跡を開始する距離
#define WALK_DIS 24.0f		//歩行を開始する距離
#define CHASE_DIS_MAX 25.0f	//追跡可能な最大距離

CXEnemy* CXEnemy::mpEnemyInstance = nullptr;

//コライダ初期化
CXEnemy::CXEnemy()
	:mHp(3)
	,mSpeed(0.0f)
	,mTurnspeed(0.0f)
	,mColSphereBody(this, nullptr, CVector(0.0f, 90.0f, 0.0f), CVector(0.0f, -130.0f, 30.0f), 1.3)
	,mColSphereRightarm1(this, nullptr, CVector(), 1.0)
	,mColSphereRightarm2(this, nullptr, CVector(), 1.0)
	,mColSphereLeftarm1(this, nullptr, CVector(), 1.0)
	,mColSphereLeftarm2(this, nullptr, CVector(), 1.0)
{
	mpEnemyInstance = this;
	//初期状態を設定
	mState = EIDLE;	//待機状態
		//コライダのタグを設定
	mColSphereBody.Tag(CCollider::EBODY);		//体
	mColSphereRightarm1.Tag(CCollider::EARM);	//手
	mColSphereRightarm2.Tag(CCollider::EARM);	//手
	mColSphereLeftarm1.Tag(CCollider::EARM);	//手
	mColSphereLeftarm2.Tag(CCollider::EARM);	//手
}
//CXEnemy(位置、回転、拡縮）
CXEnemy::CXEnemy(const CVector& position, const CVector& rotation, const CVector& scale)
	:CXEnemy()
{
	//位置、回転、拡縮を設定する
	mPosition = position;//位置の設定
	mRotation = rotation;//回転の設定
	mScale = scale;//拡縮の設定
	CTransform::Update();//行列の更新
	//優先度を１に変更する
	mPriority = 1;
	mEnabled = true;
}


void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[24]);
	mColSphereRightarm1.Matrix(&mpCombinedMatrix[68]);
	mColSphereRightarm2.Matrix(&mpCombinedMatrix[62]);
	mColSphereLeftarm1.Matrix(&mpCombinedMatrix[41]);
	mColSphereLeftarm2.Matrix(&mpCombinedMatrix[27]);
	mPosition.Set(10.0f, 0.0f, 0.0);	//位置を設定
	mScale.Set(3.0f, 3.0f, 3.0f);//スケール設定
	mRotation.Set(0.0f, 0.0f, 0.0f);	//回転を設定
}

void CXEnemy::Update() {
	//プレイヤー方向のベクトルを求める
	mPlayerPos = CXPlayer::GetInstance()->Position() - mPosition;
	//プレイヤーまでの距離を求める
	mPlayerDis = mPlayerPos.Length();
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

	case EATTACK_4: //攻撃4状態の時
		Attack_4(); //攻撃4の処理を呼ぶ
		break;

	case EAUTOMOVE:	//移動状態
		Move();	//移動状態の処理を呼ぶ
		break;

	case EDASH: //回避状態
		Dash(); //回避処理を呼ぶ
		break;

	case EDEATH: //死亡状態
		Death(); //死亡処理を呼ぶ
		break;

	case EKNOCKBACK: //ノックバック状態
		KnockBack(); //ノックバック処理を呼ぶ
		break;
	}
	
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
		mRotation.Y(mRotation.Y() + tCheck.turn * mTurnspeed);
	}
	if (tCheck.cross < 0.0f) {
		mRotation.Y(mRotation.Y() - tCheck.turn * mTurnspeed);
	}
	//移動する
	mPosition += mMoveDir * mSpeed;

	//移動方向リセット
	mMoveDir = CVector(0.0f, 0.0f, 0.0f);
	//移動スピードリセット
	mSpeed = 0.0f;

	//体力が0になると死亡
	if (mHp <= 0) {
		mState = EDEATH;	//死亡状態へ移行
		mHp = 0;
	}
	CXCharacter::Update();

}

void CXEnemy::Idle()
{
	ChangeAnimation(6, true, 30);
	//プレイヤーが死亡状態では無いとき
	if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH) {
		//プレイヤーが一定距離まで近づくと追跡状態へ移行
		if (mPlayerDis <= SEARCH_DIS) {
			mState = EDASH;
		}
		else if (mPlayerDis <= WALK_DIS)
		{
			mState = EAUTOMOVE;
		}
	}

}
void CXEnemy::Move(){
	ChangeAnimation(4, true, 30);
	//移動スピードを変更
	mSpeed = SPEED_MOVE;
	mPosition = mPosition + CVector(0.0f, 0.0f, mSpeed) * mMatrixRotate;
	//プレイヤーに向かって回転する処理
//左向き（X軸）のベクトルを求める
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//上向き（Y軸）のベクトルを求める
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//前方向（Z軸）のベクトルを求める
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;
	//目標地点までのベクトルを求める
	CVector vp = mPoint - mPosition;
	//左ベクトルとの内積を求める
	float dx = vp.Dot(vx);
	//上ベクトルとの内積を求める
	float dy = vp.Dot(vy);
	//前ベクトルとの内積を求める
	float dz = vp.Dot(vz);
	float margin = 0.1f;
	//左右方向へ回転
	if (dx > margin) {
		mRotation.Y(mRotation.Y() + 3.0f);//左へ回転
	}
	else if (dx < -margin) {
		mRotation.Y(mRotation.Y() - 3.0f);//右へ回転
	}
	CTransform::Update();//行列更新

		//およそ1秒毎に目標地点を更新
	int r = rand() % 10; //rand()は整数の乱数を返す
						  //%10は10で割った余りを求める
	if (r == 0)
	{
		mPoint = CXPlayer::GetInstance()->Position();
	}
	//プレイヤーが攻撃可能な距離にいるとき
	if (mPlayerDis <= ATTACK_DIS) {
		mState = EATTACK_2; //攻撃1状態へ移行
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //待機状態へ移行
	}

}

void CXEnemy::Dash()
{
	ChangeAnimation(5, true, 20);
	//移動スピードを変更
	mSpeed = SPEED_DASH;
	mPosition = mPosition + CVector(0.0f, 0.0f, mSpeed) * mMatrixRotate;
	//プレイヤーに向かって回転する処理
	//左向き（X軸）のベクトルを求める
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//上向き（Y軸）のベクトルを求める
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//前方向（Z軸）のベクトルを求める
	CVector vz = CVector(0.0f, 0.0f, 5.0f) * mMatrixRotate;
	//目標地点までのベクトルを求める
	CVector vp = mPoint - mPosition;
	//左ベクトルとの内積を求める
	float dx = vp.Dot(vx);
	//上ベクトルとの内積を求める
	float dy = vp.Dot(vy);
	//前ベクトルとの内積を求める
	float dz = vp.Dot(vz);
	float margin = 0.1f;

	//左右方向へ回転
	if (dx > margin) {
		mRotation.Y(mRotation.Y() + 3.0f);//左へ回転
	}
	else if (dx < -margin) {
		mRotation.Y(mRotation.Y() - 3.0f);//右へ回転
	}
	CTransform::Update();//行列更新
		
	//およそ1秒毎に目標地点を更新
	int r = rand() % 10; //rand()は整数の乱数を返す
						  //%10は10で割った余りを求める
	if (r == 0)
	{
		mPoint = CXPlayer::GetInstance()->Position();
	}

	//プレイヤーが攻撃可能な距離にいるとき
	if (mPlayerDis <= ATTACK_DIS) {
		mState = EATTACK_1; //攻撃1状態へ移行
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //待機状態へ移行
	}

	CTransform::Update();

}

void CXEnemy::Attack_1()
{
	ChangeAnimation(1, false, 30);

	//プレイヤーが追跡可能な距離にいないとき
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //待機状態へ移行
	}
	//ヒット判定発生
	if (IsAnimationFinished() == false) {
		mIsHit = true;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mIsHit = false; //ヒット判定終了
	}
	//およそ40秒毎に目標地点を更新
	int r = rand() % 50; //rand()は整数の乱数を返す
						  //%180は180で割った余りを求める
	if (r == 0)
	{
		mState = EATTACK_2;
	}

}

void CXEnemy::Attack_2()
{
	ChangeAnimation(2, false, 40);

	//プレイヤーが追跡可能な距離にいないとき
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //待機状態へ移行
	}
	//ヒット判定発生
	if (IsAnimationFinished() == false) {
		mIsHit = true;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mIsHit = false; //ヒット判定終了
	}
	//およそ40秒毎に目標地点を更新
	int r = rand() % 90; //rand()は整数の乱数を返す
						  //%180は180で割った余りを求める
	if (r == 0)
	{
		mState = EATTACK_3;
	}

}

void CXEnemy::Attack_3()
{
	ChangeAnimation(0, false, 30);
	//ヒット判定発生
	if (IsAnimationFinished() == false) {
		mIsHit = true;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mIsHit = false; //ヒット判定終了
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //待機状態へ移行
	}

	//およそ40秒毎に目標地点を更新
	int r = rand() % 160; //rand()は整数の乱数を返す
						  //%180は180で割った余りを求める
	if (r == 0)
	{
		mState = EATTACK_4;
	}
}

void CXEnemy::Attack_4()
{
	ChangeAnimation(3, false, 30);
	//ヒット判定発生
	if (IsAnimationFinished() == false) {
		mIsHit = true;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mIsHit = false; //ヒット判定終了
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //待機状態へ移行
	}
	//およそ40秒毎に目標地点を更新
	int r = rand() % 200; //rand()は整数の乱数を返す
						  //%180は180で割った余りを求める
	if (r == 0)
	{
		mState = EATTACK_1;
	}
}

void CXEnemy::KnockBack()
{
	ChangeAnimation(7, false, 30);

	//プレイヤーが追跡可能な距離にいないとき
	if (mPlayerDis >= CHASE_DIS_MAX) {
		mState = EIDLE; //待機状態へ移行
	}
}

void CXEnemy::Death()
{
	ChangeAnimation(8, false, 30);
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//相手の親が自分の時はリターン
	if (o->Parent() == this)return;

	if (o->Type() == CCollider::ECAPSUL && m->Type() == CCollider::ECAPSUL)
	{
		CVector adjust;//調整用ベクトル
		//コライダのmとoが衝突しているかの判定
		if (CCollider::CollisionCapsule(m,o, &adjust)) {
			//相手の親のタグがプレイヤー
			if (o->Parent()->Tag() == EPLAYER)
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();
			}
		}

	}

}

//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXEnemy* CXEnemy::GetInstance()
{
	return mpEnemyInstance;
}
//攻撃の当たり判定を取得する
bool CXEnemy::GetIsHit()
{
	return mIsHit; //攻撃の当たり判定を返す
}

//プレイヤーの状態を取得する
CXEnemy::EEnemyState CXEnemy::GetState()
{
	return mState;
}
	

