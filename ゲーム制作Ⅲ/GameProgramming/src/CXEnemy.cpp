#include"CXEnemy.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"CXPlayer.h"
#include "CRes.h"

#define ENEMY_ATTACK_DIS 3.2f		//攻撃可能になる距離
#define ENEMY_SPEED_MOVE 0.1f		//通常移動のスピード
#define ENEMY_SPEED_DASH 0.15f	//走行の移動速度
#define ENEMY_SPEED_STOP 0.0f		//停止
#define ENEMY_RECEPTION 10	//入力の当たり判定の受付時間
#define ENEMY_OUTRECEPTION 60 //当たり判定の受付終了
#define ENEMY_SEARCH_DIS 20.0f	//走行を開始する距離
#define ENEMY_WALK_DIS 24.0f		//歩行を開始する距離
#define ENEMY_GRAVITY 0.1			//重力
#define ENEMY_CHASE_DIS_MAX 25.0f	//走行可能な最大距離
#define ENEMY_HP_MAX 100;	//HPの最大値
//敵のHPフレーム,HPゲージ座標,幅,高さ
#define ENEMY_GAUGE_WID_MAX 50.0f	//ゲージの幅の最大値
#define ENEMY_GAUGE_HEIGHT 20.0f //ゲージ描画時の高さ
#define ENEMY_GAUGE_HP_TOP -10.0f //HPゲージ描画時の上座標
#define ENEMY_GAUGE_HP_BOTTOM (ENEMY_GAUGE_HP_TOP - ENEMY_GAUGE_HEIGHT) //HPゲージ描画時の下座標


CXEnemy* CXEnemy::mpEnemy_Instance = nullptr;

//コライダ初期化
CXEnemy::CXEnemy()
	:mEnemy_Hp(100)
	,mEnemy_Speed(0.0f)
	,mEnemy_Turnspeed(0.0f)
	,mEnemy_PlayerDis(0.0f)
	,mEnemy_IsHit(false)
	,mEnemy_ColSphereBody(this, nullptr, CVector(0.0f, 90.0f, 0.0f), CVector(0.0f, -130.0f, 30.0f), 1.3)
	,mEnemy_ColSphereRightarm(this, nullptr, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, -90.0f, 0.0f), 1.5)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(0.0f, 0.0f, 0.0f), CVector(-30.0f, -90.0f, 30.0f), 0.8)

{
	mpEnemy_Instance = this;
	//初期状態を設定
	mEnemy_State = EIDLE;	//待機状態
		//コライダのタグを設定
	mEnemy_ColSphereBody.Tag(CCollider::EBODY);		//体
	mEnemy_ColSphereRightarm.Tag(CCollider::EARM);	//手
	mEnemy_ColSphereLeftarm.Tag(CCollider::EARM);	//手
	//優先度を1に変更する
	mPriority = 80;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}



void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mEnemy_ColSphereBody.Matrix(&mpCombinedMatrix[24]);
	mEnemy_ColSphereRightarm.Matrix(&mpCombinedMatrix[83]);
	mEnemy_ColSphereLeftarm.Matrix(&mpCombinedMatrix[41]);
	mPosition.Set(10.0f, -4.0f, 0.0);	//位置を設定
	mScale.Set(4.0f, 4.0f, 4.0f);//スケール設定
	mRotation.Set(0.0f, 0.0f, 0.0f);	//回転を設定
}

void CXEnemy::Update() {
	//状態を判別
	switch (mEnemy_State) 
	{
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
	case EREPELLED: //はじかれた時の状態
		Repelled(); //はじかれた場合の処理を呼ぶ
		break;
	}
	MovingCalculation();
	//体力が0になると死亡
	if (mEnemy_Hp <= 0) 
	{
		mEnemy_State = EDEATH;	//死亡状態へ移行
		mEnemy_Hp = 0;
	}
	CXCharacter::Update();
}
void CXEnemy::Render2D()
{
	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);
	CVector tpos;
	CVector ret;
	tpos = mPosition + CVector(-2.0f, 8.0f, -4.0f);
	Camera.WorldToScreen(&ret, tpos);
	float HpRate = (float)mEnemy_Hp / (float)ENEMY_HP_MAX; //体力最大値に対する、現在の体力の割合
	float HpGaugeWid = ENEMY_GAUGE_WID_MAX * HpRate; //体力ゲージの幅
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より大きい時
	if (mEnemy_FollowGaugeWid > HpGaugeWid) {
		//線形補間で被ダメージ分後追いするゲージの幅を設定する
		mEnemy_FollowGaugeWid = Camera.mLerp(mEnemy_FollowGaugeWid, HpGaugeWid, 0.05f);
	}
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より小さいとき
	else if (mEnemy_FollowGaugeWid < HpGaugeWid) {
		//被ダメージ分後追いするゲージの幅に体力ゲージの幅を設定する
		mEnemy_FollowGaugeWid = HpGaugeWid;
	}
	//画面外の時に表示しない
	if (ret.X() > 0 && ret.X() < 800) {
		//被ダメージ分後追いするゲージを表示
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(ret.X() + ENEMY_GAUGE_WID_MAX, (ret.X() + ENEMY_GAUGE_WID_MAX) + mEnemy_FollowGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
		//体力ゲージ
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(ret.X() + ENEMY_GAUGE_WID_MAX, (ret.X() + ENEMY_GAUGE_WID_MAX) + HpGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
	}
	//2Dの描画終了
	CUtil::End2D();
}

void CXEnemy::Idle()
{
	int random = 0;
	//プレイヤーが死亡状態では無いとき
	if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH) 
	{
		//プレイヤーが一定距離まで近づくと追跡状態へ移行
		if (mEnemy_PlayerDis <= ENEMY_SEARCH_DIS)
		{
			mEnemy_State = EDASH;
		}
		else if (mEnemy_PlayerDis <= ENEMY_WALK_DIS)
		{
			mEnemy_State = EAUTOMOVE;
		}
		else
		{
			ChangeAnimation(5, true, 60);
		}
	}
	else 
	{
		ChangeAnimation(5, true, 60);
	}
}
void CXEnemy::Move(){
	ChangeAnimation(3, true, 50);
	mEnemy_Speed = ENEMY_SPEED_MOVE;
	//目的地点までのベクトルを求める
	CVector Point = mEnemy_Point - mPosition;
	//mMoveDirにプレイヤー方向のベクトルを入れる
	mEnemy_MoveDir = Point.Normalize();
	//およそ1秒毎に目標地点を更新
	int r = rand() % 30; //rand()は整数の乱数を返す
						 //%10は10で割った余りを求める
	if (r == 0)	
	{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
	}
	int random = 0;
	//プレイヤーが攻撃可能な距離にいるとき
	if (mEnemy_PlayerDis <= ENEMY_ATTACK_DIS)
	{
		if (random == 0) 
		{
			//ランダムで攻撃の種類を決める
			random = rand() % 3;
			switch (random) 
			{
			case 0:
				mEnemy_State = EATTACK_1; //攻撃1状態へ移行
			break;
			case 1:
				mEnemy_State = EATTACK_2; //攻撃2状態へ移行
			break;
			case 2:
				mEnemy_State = EATTACK_3; //攻撃3状態へ移行
			break;
			}
		}
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mEnemy_PlayerDis >= ENEMY_CHASE_DIS_MAX)
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}

}

void CXEnemy::Dash()
{
	ChangeAnimation(4, true, 40);
	//移動スピードを変更
	mEnemy_Speed = ENEMY_SPEED_DASH;
	//目的地点までのベクトルを求める
	CVector Point = mEnemy_Point - mPosition;
	//mMoveDirに目標地点方向のベクトルを入れる
	mEnemy_MoveDir = Point.Normalize();
	//およそ1秒毎に目標地点を更新
	int r = rand() % 25; //rand()は整数の乱数を返す
						  //%25は25で割った余りを求める
	if (mEnemy_PlayerDis > ENEMY_ATTACK_DIS)
	{
		if (r == 0)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = 0;
	//プレイヤーが攻撃可能な距離にいるとき
	if (mEnemy_PlayerDis <= ENEMY_ATTACK_DIS)
	{
		if (random == 0) 
		{
			//ランダムで攻撃の種類を決める
			random = rand() % 3;
			switch (random) 
			{
			case 0:
				mEnemy_State = EATTACK_1; //攻撃1状態へ移行
			break;
			case 1:
				mEnemy_State = EATTACK_2; //攻撃2状態へ移行
			break;
			case 2:
				mEnemy_State = EATTACK_3; //攻撃3状態へ移行
			break;
			}
		}
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mEnemy_PlayerDis >= ENEMY_CHASE_DIS_MAX)
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}

	CTransform::Update();

}

void CXEnemy::Attack_1()
{
	ChangeAnimation(1, false, 60);
	mEnemy_IsHit = false; //ヒット判定終了
	//プレイヤーが追跡可能な距離にいないとき
	if (mEnemy_PlayerDis >= ENEMY_CHASE_DIS_MAX)
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}

	//ヒット判定発生
	if (IsAnimationFinished() == false) 
	{
		if (mAnimationFrame >= ENEMY_RECEPTION) 
		{
			mEnemy_IsHit = true;
		}
		else if (mAnimationFrame == ENEMY_OUTRECEPTION)
		{
			mEnemy_IsHit = false;
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE;
	}
}

void CXEnemy::Attack_2()
{
	ChangeAnimation(2, false, 60);
	mEnemy_IsHit = false; //ヒット判定終了
	//プレイヤーが追跡可能な距離にいないとき
	if (mEnemy_PlayerDis >= ENEMY_CHASE_DIS_MAX)
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}
	//ヒット判定発生
	if (IsAnimationFinished() == false) 
	{
		if (mAnimationFrame >= ENEMY_RECEPTION) 
		{
			mEnemy_IsHit = true;
		}
		else if (mAnimationFrame == ENEMY_OUTRECEPTION)
		{
			mEnemy_IsHit = false;
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE;
	}
}

void CXEnemy::Attack_3()
{
	ChangeAnimation(0, false, 60);
	mEnemy_IsHit = false; //ヒット判定終了
	//ヒット判定発生
	if (IsAnimationFinished() == false) 
	{
		if (mAnimationFrame >= ENEMY_RECEPTION) 
		{
			mEnemy_IsHit = true;
		}
		else if (mAnimationFrame == ENEMY_OUTRECEPTION)
		{
			mEnemy_IsHit = false;
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE;
	}
}


void CXEnemy::KnockBack()
{
	ChangeAnimation(6, false, 50);
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE; //待機状態へ移行
		mEnemy_Hp -= 10;
	}
}


void CXEnemy::Repelled()
{
	ChangeAnimation(6, false, 50);
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}
}

void CXEnemy::Death()
{
	ChangeAnimation(7, false, 30);
	mEnemy_IsHit = false;
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//相手の親が自分の時はリターン
	if (o->Parent() == this)return;

	if (!mEnemy_Hp <= 0)
	{
		if (m->Type() == CCollider::ECAPSUL && o->Type() == CCollider::ECAPSUL)
		{
			CVector adjust;//調整用ベクトル
			//コライダのmとoが衝突しているかの判定
			if (CCollider::CollisionCapsule(m, o, &adjust))
			{
				//相手の親のタグがプレイヤー
				if (o->Parent()->Tag() == EPLAYER)
				{
					//相手のコライダのタグが剣
					if (o->Tag() == CCollider::ESWORD)
					{
						if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EGUARD)
						{
							if (CXPlayer::GetInstance()->GetIsHit() == true) {
								mEnemy_State = EKNOCKBACK;
							}
						}
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EGUARD)
					{
						if (CXPlayer::GetInstance()->GetIsHit() == true)
						{
							mEnemy_State = EREPELLED;
						}
					}
					else
					{
						//位置の更新(mPosition + adjust)
						mPosition = mPosition + adjust;
						//行列の更新
						CTransform::Update();
					}
				}

			}
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

		}
	}
}
void CXEnemy::MovingCalculation() {
	//プレイヤー方向のベクトルを求める
	mEnemy_PlayerPos = CXPlayer::GetInstance()->Position() - mPosition;
	//プレイヤーまでの距離を求める
	mEnemy_PlayerDis = mEnemy_PlayerPos.Length();
	//普通に3次元ベクトル計算で算出したほうが正確だが計算量を懸念する場合は擬似計算で軽量化
	//擬似ベクトル計算
	CVector ChackVec; //チェック用ベクトル
	ChackVec = mEnemy_MoveDirKeep.Normalize(); //保存された移動時の方向ベクトルを代入
	ChackVec = mEnemy_MoveDir.Normalize(); //移動時の方向ベクトルを代入
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / 180.0f));

	//回転速度　degreeに直す
	mEnemy_Turnspeed = (180.0f / M_PI) * 0.3f;

	//急な振り返りを抑制
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//移動方向へキャラを向かせる
	if (tCheck.cross > 0.0f)
	{
		mRotation.Y(mRotation.Y() + tCheck.turn * mEnemy_Turnspeed);
	}
	if (tCheck.cross < 0.0f)
	{
		mRotation.Y(mRotation.Y() - tCheck.turn * mEnemy_Turnspeed);
	}
	//移動する
	mPosition += mEnemy_MoveDir * mEnemy_Speed;
	mPosition.Y(mPosition.Y() * ENEMY_GRAVITY);

	//移動方向リセット
	mEnemy_MoveDir = CVector(0.0f, 0.0f, 0.0f);
	//移動スピードリセット
	mEnemy_Speed = 0.0f;
}
void CXEnemy::TaskCollision()
{
	//コライダの優先度変更
	mEnemy_ColSphereBody.ChangePriority();
	mEnemy_ColSphereRightarm.ChangePriority();
	mEnemy_ColSphereLeftarm.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereRightarm, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereLeftarm, COLLISIONRANGE);
}
//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXEnemy* CXEnemy::GetInstance()
{
	return mpEnemy_Instance;
}
//アニメーションフレームの取得
bool CXEnemy::GetIsAnimationFrame() {
	return mAnimationFrame;
}
//攻撃の当たり判定を取得する
bool CXEnemy::GetIsHit()
{
	return mEnemy_IsHit; //攻撃の当たり判定を返す
}

//死亡状態のときtrueを返す
bool CXEnemy::mIsDeath()
{
	return (mEnemy_State == EDEATH);
}

//プレイヤーの状態を取得する
CXEnemy::EEnemyState CXEnemy::GetState()
{
	return mEnemy_State;
}
	

