#include"CXEnemy.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>
#include"CXPlayer.h"
#include "CRes.h"

#define DAMAGE_BODY 10		//ダメージ(体)

#define ENEMY_ATTACK_DIS 3.2f		//攻撃可能になる距離
#define ENEMY_SPEED_MOVE 0.1f		//通常移動のスピード
#define ENEMY_SPEED_DASH 0.15f	//走行の移動速度
#define ENEMY_SPEED_STOP 0.0f		//停止
#define ENEMY_WALK_DIS 30.0f		//歩行を開始する距離
#define ENEMY_SEARCH_DIS 60.0f		//走行を開始する距離
#define ENEMY_WALK_DIS_MAX 50.0f	//歩行可能な最大距離
#define ENEMY_CHASE_DIS_MAX 80.0f   //走行可能な最大距離
#define ENEMY_GRAVITY 0.1			//重力

#define ENEMY_HP_MAX 200;	//HPの最大値
//敵のHPフレーム,HPゲージ座標,幅,高さ
#define ENEMY_GAUGE_WID_MAX 100.0f	//ゲージの幅の最大値
#define ENEMY_GAUGE_HEIGHT 20.0f //ゲージ描画時の高さ
#define ENEMY_GAUGE_HP_TOP -10.0f //HPゲージ描画時の上座標
#define ENEMY_GAUGE_HP_BOTTOM (ENEMY_GAUGE_HP_TOP - ENEMY_GAUGE_HEIGHT) //HPゲージ描画時の下座標


CXEnemy* CXEnemy::mpEnemy_Instance = nullptr;

//コライダ初期化
CXEnemy::CXEnemy()
	:mEnemy_Hp(200)
	,mEnemy_Speed(0.0f)
	,mEnemy_Turnspeed(0.0f)
	,mEnemy_PlayerDis(0.0f)
	, mEnemy_FollowGaugeWid(0.0f)
	,mEnemy_val(0)
	,mEnemy_IsHit(false)
	,mEnemy_Flag(false)
	, mEnemy_ColCapsuleBody(this, nullptr, CVector(0.0f, 90.0f, 0.0f), CVector(0.0f, -130.0f, 30.0f), 1.3)
	,mEnemy_ColSphereRightarm(this, nullptr, CVector(), 1.0)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(), 1.0)

{
	mpEnemy_Instance = this;
	//初期状態を設定
	mEnemy_State = EIDLE;	//待機状態
		//コライダのタグを設定
	mEnemy_ColCapsuleBody.Tag(CCollider::EBODY);		//体
	mEnemy_ColSphereRightarm.Tag(CCollider::ERIGHTARM);	//右手
	mEnemy_ColSphereLeftarm.Tag(CCollider::ELEFTARM);	//左手
	//タグの設定
	mTag = EENEMY;
	//優先度を1に変更する
	mPriority = 80;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}



void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mEnemy_ColCapsuleBody.Matrix(&mpCombinedMatrix[24]);
	mEnemy_ColSphereRightarm.Matrix(&mpCombinedMatrix[68]);
	mEnemy_ColSphereLeftarm.Matrix(&mpCombinedMatrix[41]);
	mPosition.Set(0.0f, -4.0f, -20.0);	//位置を設定
	mScale.Set(3.0f, 3.0f, 2.0f);//スケール設定
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
	//case EREPELLED: //はじかれた時の状態
	//	Repelled(); //はじかれた場合の処理を呼ぶ
	//	break;
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
	tpos = mPosition + CVector(ret.X(), ret.Y()+ 7.0f, 0.0f);
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
		CRes::GetInstance()->GetInEnemyUiHpBackBar().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, ret.X() + ENEMY_GAUGE_WID_MAX, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 0, 30);
		//被ダメージ分後追いするゲージを表示
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + mEnemy_FollowGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
		//体力ゲージ
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + HpGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
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
		mEnemy_Flag = false;
		//プレイヤーが一定距離まで近づくと追跡状態へ移行
		if (mEnemy_PlayerDis <= ENEMY_WALK_DIS)
		{
			mEnemy_State = EAUTOMOVE;
		}
		else if (mEnemy_PlayerDis <= ENEMY_SEARCH_DIS)
		{
			mEnemy_State = EDASH;
		}
		else
		{
			//アニメーションの設定
			ChangeAnimation(5, true, 60);
		}
	}
	else 
	{
		//アニメーションの設定
		ChangeAnimation(5, true, 60);
	}
}
void CXEnemy::Move(){
	//アニメーションの設定
	ChangeAnimation(3, true, 60);
	mEnemy_Speed = ENEMY_SPEED_MOVE;
	//目的地点までのベクトルを求める
	CVector Point = mEnemy_Point - mPosition;
	//mMoveDirにプレイヤー方向のベクトルを入れる
	mEnemy_MoveDir = Point.Normalize();
	//およそ1秒毎に目標地点を更新
	int r = rand() % 30; //rand()は整数の乱数を返す
						 //%10は10で割った余りを求める
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
			random = rand() % 4;
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
			case 3:
				mEnemy_State = EIDLE;
			break;
			}
		}
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mEnemy_PlayerDis >= ENEMY_WALK_DIS_MAX)
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}

}

void CXEnemy::Dash()
{
	//アニメーションの設定
	ChangeAnimation(4, true, 50);
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
			random = rand() % 4;
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
			case 3:
				mEnemy_State = EIDLE;
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
	//アニメーションの設定
	ChangeAnimation(1, false, 85);
	//ヒット判定発生
	if (IsAnimationFinished() == false)
	{
		mEnemy_IsHit = true;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //ヒット判定終了
		mEnemy_State = EIDLE;
		if (mEnemy_val >= 21 && mEnemy_val <= 100)
		{
			if (CXPlayer::GetInstance()->GetIsHit() == true) {
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
			}
		}
	}
}

void CXEnemy::Attack_2()
{
	//アニメーションの設定
	ChangeAnimation(2, false, 95);
	//ヒット判定発生
	if (IsAnimationFinished() == false) 
	{
		mEnemy_IsHit = true;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //ヒット判定終了
		mEnemy_State = EIDLE;
		if (mEnemy_val >= 36 && mEnemy_val <= 100)
		{
			if (CXPlayer::GetInstance()->GetIsHit() == true) {
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
				{
					mEnemy_Hp = mEnemy_Hp - 10;
				}
			}
		}
	}
}

void CXEnemy::Attack_3()
{
	//アニメーションの設定
	ChangeAnimation(0, false, 95);
	//ヒット判定発生
	if (IsAnimationFinished() == false) 
	{
		mEnemy_IsHit = true;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //ヒット判定終了
		mEnemy_State = EIDLE;
		if (mEnemy_val >= 36 && mEnemy_val <= 100)
		{
			if (CXPlayer::GetInstance()->GetIsHit() == true) {
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
				{
					mEnemy_Hp = mEnemy_Hp - 5;
				}
				if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
				{
					mEnemy_Hp = mEnemy_Hp - 10;
				}
			}
		}
	}
}


void CXEnemy::KnockBack()
{
	//アニメーションの設定
	ChangeAnimation(6, false, 60);
	//ダメージ処理
	//1度しか動かさないためのカウンタ
	if (mEnemy_Flag == false)
	{
		mEnemy_Flag = true;
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
		{
			mEnemy_Hp -= DAMAGE_BODY * 2;
		}
		else
		{
			mEnemy_Hp -= DAMAGE_BODY;	//ダメージを受ける(体)

		}
	}
	//アニメーションが再生中時
	if (IsAnimationFinished() == false)
	{
		mEnemy_IsHit = false;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}
}


//void CXEnemy::Repelled()
//{
//	ChangeAnimation(6, false, 50);
//	//アニメーション終了時
//	if (IsAnimationFinished())
//	{
//		mEnemy_State = EIDLE; //待機状態へ移行
//	}
//}

void CXEnemy::Death()
{
	ChangeAnimation(7, false, 60);
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
						if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH)
						{
							//乱数値=rand()%乱数値の要素数+乱数値の最小値
							srand((unsigned)time(NULL));
							mEnemy_val = (rand() % 100) + 1;
							if (mEnemy_val >= 0 && mEnemy_val <= 35) {
								if (CXPlayer::GetInstance()->GetIsHit() == true) {
									mEnemy_State = EKNOCKBACK;
								}
							}
						}
					}
					//else if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EGUARD)
					//{
					//	if (CXPlayer::GetInstance()->GetIsHit() == true)
					//	{
					//		mEnemy_State = EREPELLED;
					//	}
					//}
					else if (m->Tag() == CCollider::EBODY && o->Tag() == CCollider::EBODY)
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
	mEnemy_ColCapsuleBody.ChangePriority();
	mEnemy_ColSphereRightarm.ChangePriority();
	mEnemy_ColSphereLeftarm.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mEnemy_ColCapsuleBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereRightarm, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereLeftarm, COLLISIONRANGE);
}
//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXEnemy* CXEnemy::GetInstance()
{
	return mpEnemy_Instance;
}
bool CXEnemy::GetHp()
{
	return mEnemy_Hp;
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
//攻撃の当たり判定フラグを設定
void CXEnemy::SetIsHit(bool hitflag)
{
	mEnemy_IsHit = hitflag;
}

//プレイヤーの状態を取得する
CXEnemy::EEnemyState CXEnemy::GetState()
{
	return mEnemy_State;
}
	

