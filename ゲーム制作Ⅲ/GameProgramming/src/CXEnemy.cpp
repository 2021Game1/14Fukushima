#include"CXEnemy.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>
#include"CXPlayer.h"
#include "CRes.h"


CXEnemy* CXEnemy::mpEnemy_Instance = nullptr;

void CXEnemy::Load() {
	FILE* fp;
	ENEMYDATA data[ENEMY_NUM];
	char buf[256];
	int c;
	int col = 1;
	int row = 0;
	memset(buf, 0, sizeof(buf));
	fp = fopen("res\\Enemy\\EnemyData.csv", "r");
	//ヘッダ読み飛ばし
	while (fgetc(fp) != '\0');
	while (1) {
		while (1) {
			c = fgetc(fp);
			//末尾ならループを抜ける。
			if (c == EOF) {
				break;
			}
			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\0') {
				strcat(buf, (const char*)&c);
			}
			//カンマか改行ならループ抜ける。
			else
				break;
		}
		//ここに来たということは、1セル分の文字列が出来上がったということ
		switch (col) {
		//1列目は敵種類を表す。atoi関数で数値として代入
		case 1: data[row].Enemy_Type = atoi(buf); break;
		case 2: data[row].Enemy_Priority = atoi(buf); break;
		case 3: data[row].Enemy_Speed_WalkPattern = atoi(buf); break;
		case 4: data[row].Enemy_Speed_DashPattern = atoi(buf); break;
		case 5: data[row].Enemy_Walk_Dis = atoi(buf); break;
		case 6: data[row].Enemy_Dash_Dis = atoi(buf); break;
		case 7: data[row].Enemy_Walk_Dis_Max = atoi(buf); break;
		case 8: data[row].Enemy_Dash_Dis_Max = atoi(buf); break;
		case 9: data[row].Enemy_Attack_Dis = atoi(buf); break;
		case 10: data[row].Enemy_Attack_Reception = atoi(buf); break;
		case 11: data[row].Enemy_Attack_Outreception = atoi(buf); break;
		case 12: data[row].Enemy_Attack_Walk_Rand = atoi(buf); break;
		case 13: data[row].Enemy_Attack_Dash_Rand = atoi(buf); break;
		case 14: data[row].Enemy_Damage_PlayerSp1 = atoi(buf); break;
		case 15: data[row].Enemy_Damage_PlayerSp2 = atoi(buf); break;
		case 16: data[row].Enemy_Damage_PlayerSp3 = atoi(buf); break;
		case 17: data[row].Position_X = atoi(buf); break;
		case 18: data[row].Position_Y = atoi(buf); break;
		case 19: data[row].Position_Z = atoi(buf); break;
		case 20: data[row].Scale_X = atoi(buf); break;
		case 21: data[row].Scale_Y = atoi(buf); break;
		case 22: data[row].Scale_Z = atoi(buf); break;
		case 23: data[row].Rotation_X = atoi(buf); break;
		case 24: data[row].Rotation_Y = atoi(buf); break;
		case 25: data[row].Rotation_Z = atoi(buf); break;
		case 26: data[row].Hp = atoi(buf); break;
		case 27: data[row].Hp_Max = atoi(buf); break;
		case 28: data[row].Death_Hp = atoi(buf); break;
		}
		//バッファを初期化
		memset(buf, 0, sizeof(buf));
		//列数を足す
		++col;
		//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
		if (c == '\n') {
			col = 1;
			++row;
		}
		
	}
	for (int i = 0; i < ENEMY_NUM; ++i) {
		new CXEnemy(data[i].Enemy_Type, data[i].Enemy_Priority, data[i].Enemy_Speed_WalkPattern, data[i].Enemy_Speed_DashPattern, data[i].Enemy_Walk_Dis,
			data[i].Enemy_Dash_Dis, data[i].Enemy_Walk_Dis_Max, data[i].Enemy_Dash_Dis_Max, data[i].Enemy_Attack_Dis, data[i].Enemy_Attack_Reception,
			data[i].Enemy_Attack_Outreception, data[i].Enemy_Attack_Walk_Rand, data[i].Enemy_Attack_Dash_Rand, data[i].Enemy_Damage_PlayerSp1, data[i].Enemy_Damage_PlayerSp2,
			data[i].Enemy_Damage_PlayerSp3, data[i].Position_X, data[i].Position_Y, data[i].Position_Z, data[i].Scale_X, data[i].Scale_Y, data[i].Scale_Z, data[i].Rotation_X,
			data[i].Rotation_Y, data[i].Rotation_Z, data[i].Hp, data[i].Hp_Max, data[i].Death_Hp);
	}
}
CXEnemy::CXEnemy(int Enemy_Type, int Enemy_Priority, float Enemy_Speed_WalkPattern, float Enemy_Speed_DashPattern, float Enemy_Walk_Dis,
	float Enemy_Dash_Dis, float Enemy_Walk_Dis_Max, float Enemy_Dash_Dis_Max, float Enemy_Attack_Dis, float Enemy_Attack_Reception,
	float Enemy_Attack_Outreception, int Enemy_Attack_Walk_Rand, int Enemy_Attack_Dash_Rand, int Enemy_Damage_PlayerSp1, int Enemy_Damage_PlayerSp2,
	int Enemy_Damage_PlayerSp3, float Position_X, float Position_Y, float Position_Z, float Scale_X, float Scale_Y, float Scale_Z, float Rotation_X,
	float Rotation_Y, float Rotation_Z, int Hp, int Hp_Max, int Death_Hp) 
	:mEnemy_Hp(Hp)
	, mEnemy_Speed(ENEMY_SPEED)
	, mEnemy_Turnspeed(ENEMY_TURNSPEED)
	, mEnemy_PlayerDis(ENEMY_FLOAT_INITIALIZATION)
	, mEnemy_FollowGaugeWid(ENEMY_FLOAT_INITIALIZATION)
	, mEnemy_val(ENEMY_INT_INITIALIZATION)
	, mEnemy_IsHit(false)
	, mEnemy_Flag(false)
	, mEnemy_ColCapsuleBody(this, nullptr, CVector(ENEMY_COLCAPSULE_BODY_X, ENEMY_COLCAPSULE_BODY_TOP_Y, ENEMY_COLCAPSULE_BODY_Z), CVector(ENEMY_COLCAPSULE_BODY_X, ENEMY_COLCAPSULE_BODY_BOTTOM_Y, ENEMY_COLCAPSULE_BODY_Z), ENEMY_COLCAPSULE_BODY_SIZE)
	, mEnemy_ColSphereBody(this, nullptr, CVector(ENEMY_COLSPHERE_BODY_X, ENEMY_COLSPHERE_BODY_Y, ENEMY_COLSPHERE_BODY_Z), ENEMY_COLSPHERE_BODY_SIZE)
	, mEnemy_ColSphereRightarm(this, nullptr, CVector(), ENEMY_COLSPHERE_RIGHTARM_SIZE)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(), ENEMY_COLSPHERE_LEFTARM_SIZE)
{
	this->Enemy_Type = Enemy_Type;
	this->Enemy_Priority = Enemy_Priority;
	this->Enemy_Speed_WalkPattern = Enemy_Speed_WalkPattern;
	this->Enemy_Speed_DashPattern = Enemy_Speed_DashPattern;
	this->Enemy_Walk_Dis = Enemy_Walk_Dis;
	this->Enemy_Dash_Dis = Enemy_Dash_Dis;
	this->Enemy_Walk_Dis_Max = Enemy_Walk_Dis_Max;
	this->Enemy_Dash_Dis_Max = Enemy_Dash_Dis_Max;
	this->Enemy_Attack_Dis = Enemy_Attack_Dis;
	this->Enemy_Attack_Reception = Enemy_Attack_Reception;
	this->Enemy_Attack_Outreception = Enemy_Attack_Outreception;
	this->Enemy_Attack_Walk_Rand = Enemy_Attack_Walk_Rand;
	this->Enemy_Attack_Dash_Rand = Enemy_Attack_Dash_Rand;
	this->Enemy_Damage_PlayerSp1 = Enemy_Damage_PlayerSp1;
	this->Enemy_Damage_PlayerSp2 = Enemy_Damage_PlayerSp2;
	this->Enemy_Damage_PlayerSp3 = Enemy_Damage_PlayerSp3;
	this->Position_X = Position_X;
	this->Position_Y = Position_Y;
	this->Position_Z = Position_Z;
	this->Scale_X = Scale_X;
	this->Scale_Y = Scale_Y;
	this->Scale_Z = Scale_Z;
	this->Rotation_X = Rotation_X;
	this->Rotation_Y = Rotation_Y;
	this->Rotation_Z = Rotation_Z;
	this->Hp = Hp;
	this->Hp_Max = Hp_Max;
	this->Death_Hp = Death_Hp;

	mpEnemy_Instance = this;
	//初期状態を設定
	mEnemy_State = EIDLE;	//待機状態
		//コライダのタグを設定
	mEnemy_ColCapsuleBody.Tag(CCollider::EBODY);		//体
	mEnemy_ColSphereBody.Tag(CCollider::EBODY);		//体
	mEnemy_ColSphereRightarm.Tag(CCollider::ERIGHTARM);	//右手
	mEnemy_ColSphereLeftarm.Tag(CCollider::ELEFTARM);	//左手
	//タグの設定
	mTag = EENEMY;
	//優先度を1に変更する
	mPriority = Enemy_Priority;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}
//コライダ初期化
CXEnemy::CXEnemy()


{


}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mEnemy_ColCapsuleBody.Matrix(&mpCombinedMatrix[2]);
	mEnemy_ColSphereBody.Matrix(&mpCombinedMatrix[2]);
	mEnemy_ColSphereRightarm.Matrix(&mpCombinedMatrix[68]);
	mEnemy_ColSphereLeftarm.Matrix(&mpCombinedMatrix[41]);
	mPosition.Set(Position_X, Position_Y, Position_Z);
	mScale.Set(Scale_X, Scale_Y, Scale_Z);
	mRotation.Set(Rotation_X, Rotation_Y, Rotation_Z);
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
	}
	MovingCalculation();
	if (mEnemy_PlayerDis >= Enemy_Attack_Dis) {
		mEnemy_AttackDir = mEnemy_Player_Point; //攻撃時の向きを求める
	}
	//体力が0になると死亡
	if (mEnemy_Hp <= Death_Hp)
	{
		mEnemy_State = EDEATH;	//死亡状態へ移行
		mEnemy_Hp = Death_Hp;
	}
	CXCharacter::Update();
}
void CXEnemy::Render2D()
{
	//2D描画開始
	CUtil::Start2D(WINDOW_FIRST_WIDTH, WINDOW_WIDTH, WINDOW_FIRST_HEIGHT, WINDOW_HEIGHT);
	CVector tpos;
	CVector ret;
	tpos = mPosition + CVector(ret.X(), ret.Y()+ 7.0f, 0.0f);
	Camera.WorldToScreen(&ret, tpos);
	float HpRate = (float)mEnemy_Hp / (float)Hp_Max; //体力最大値に対する、現在の体力の割合
	float HpGaugeWid = ENEMY_GAUGE_WID_MAX * HpRate; //体力ゲージの幅
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より大きい時
	if (mEnemy_FollowGaugeWid > HpGaugeWid) {
		//線形補間で被ダメージ分後追いするゲージの幅を設定する
		mEnemy_FollowGaugeWid = Camera.mHpLerp(mEnemy_FollowGaugeWid, HpGaugeWid, ENEMY_GAUGE_HP_RATE);
	}
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より小さいとき
	else if (mEnemy_FollowGaugeWid < HpGaugeWid) {
		//被ダメージ分後追いするゲージの幅に体力ゲージの幅を設定する
		mEnemy_FollowGaugeWid = HpGaugeWid;
	}
	//画面外の時に表示しない
	if (ret.X() > WINDOW_FIRST_WIDTH && ret.X() < WINDOW_WIDTH) {
		if (!mEnemy_Hp <= Death_Hp)
		{
			CRes::GetInstance()->GetInEnemyUiHpBackBar().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, ret.X() + ENEMY_GAUGE_WID_MAX, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 0, 30);
			//被ダメージ分後追いするゲージを表示
			CRes::GetInstance()->GetInUiHpRedGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + mEnemy_FollowGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
			//体力ゲージ
			CRes::GetInstance()->GetInUiHpGreenGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + HpGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
		}
	}
	//2Dの描画終了
	CUtil::End2D();
}

void CXEnemy::Idle()
{
	int random = ENEMY_INT_INITIALIZATION;
	//プレイヤーが死亡状態では無いとき
	if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH) 
	{
		mEnemy_Flag = false;
		//プレイヤーが一定距離まで近づくと追跡状態へ移行
		if (mEnemy_PlayerDis <= Enemy_Walk_Dis)
		{
			mEnemy_State = EAUTOMOVE;
		}
		else if (mEnemy_PlayerDis <= Enemy_Dash_Dis)
		{
			mEnemy_State = EDASH;
		}
		else
		{
			//アニメーションの設定
			ChangeAnimation(ENEMY_ANIMATION_No_IDLE, true, ENEMY_IDLE_ANIMATION_FRAME);
		}
	}
	else 
	{
		//アニメーションの設定
		ChangeAnimation(ENEMY_ANIMATION_No_IDLE, true, ENEMY_IDLE_ANIMATION_FRAME);
	}
}
void CXEnemy::Move(){
	//アニメーションの設定
	ChangeAnimation(ENEMY_ANIMATION_No_WALK, true, ENEMY_MOVE_ANIMATION_FRAME);
	mEnemy_Speed = Enemy_Speed_WalkPattern;
	//目的地点までのベクトルを求める
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDirにプレイヤー方向のベクトルを入れる
	mEnemy_MoveDir.Y(ENEMY_FLOAT_INITIALIZATION);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//およそ1秒毎に目標地点を更新
	int r = rand() % Enemy_Attack_Walk_Rand; //rand()は整数の乱数を返す
						 //%10は10で割った余りを求める
	//攻撃出来る距離にいなければ目標地点に移動
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = ENEMY_INT_INITIALIZATION;
	//プレイヤーが攻撃可能な距離にいるとき
	if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
	{
		if (random == ENEMY_INT_INITIALIZATION)
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
	if (mEnemy_PlayerDis >= Enemy_Walk_Dis_Max)
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}

}

void CXEnemy::Dash()
{
	//アニメーションの設定
	ChangeAnimation(ENEMY_ANIMATION_No_DASH, true, ENEMY_DASH_ANIMATION_FRAME);
	//移動スピードを変更
	mEnemy_Speed = Enemy_Speed_DashPattern;
	//目的地点までのベクトルを求める
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDirに目標地点方向のベクトルを入れる
	mEnemy_MoveDir.Y(ENEMY_FLOAT_INITIALIZATION);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//およそ1秒毎に目標地点を更新
	int r = rand() % Enemy_Attack_Dash_Rand; //rand()は整数の乱数を返す
						  //%25は25で割った余りを求める
	//攻撃出来る距離にいなければ目標地点に移動
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = ENEMY_INT_INITIALIZATION;
	//プレイヤーが攻撃可能な距離にいるとき
	if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
	{
		if (random == ENEMY_INT_INITIALIZATION)
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
	if (mEnemy_PlayerDis >= Enemy_Dash_Dis_Max)
	{
		mEnemy_State = EIDLE; //待機状態へ移行
	}

	CTransform::Update();

}

void CXEnemy::Attack_1()
{
	//アニメーションの設定
	ChangeAnimation(ENEMY_ANIMATION_No_ATTACK_1, false, ENEMY_ATTACK1_ANIMATION_FRAME);
	//ヒット判定発生
	if (IsAnimationFinished() == false)
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
		if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
		else {
			mEnemy_IsHit = true;
		}
		//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //ヒット判定終了
		mEnemy_State = EIDLE; //待機状態に移行

		//1度しか動かさないためのカウンタ
		if (mEnemy_Flag == false)
		{
			mEnemy_Flag = true;
			//スーパーアーマが発動時のダメージ参照
			if (mEnemy_val >= 61 && mEnemy_val <= 100)
			{
				if (CXPlayer::GetInstance()->GetIsHit() == true) {
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp1;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //エフェクトを生成する
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp2;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //エフェクトを生成する
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp3;
						new CEffectEnemyDamageSp3(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP3, 4, 5, 2); //エフェクトを生成する
					}
				}
			}
		}
	}
}

void CXEnemy::Attack_2()
{
	//アニメーションの設定
	ChangeAnimation(ENEMY_ANIMATION_No_ATTACK_2, false, ENEMY_ATTACK2_ANIMATION_FRAME);
	//ヒット判定発生
	if (IsAnimationFinished() == false) 
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
		if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
		else {
			mEnemy_IsHit = true;
		}
		//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //ヒット判定終了
		mEnemy_State = EIDLE; //待機状態に移行

		//1度しか動かさないためのカウンタ
		if (mEnemy_Flag == false)
		{
			mEnemy_Flag = true;
			//スーパーアーマが発動時のダメージ参照
			if (mEnemy_val >= 61 && mEnemy_val <= 100)
			{
				if (CXPlayer::GetInstance()->GetIsHit() == true) {
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp1;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //エフェクトを生成する
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp2;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //エフェクトを生成する
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp3;
						new CEffectEnemyDamageSp3(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP3, 4, 5, 2); //エフェクトを生成する
					}
				}
			}
		}
	}
}

void CXEnemy::Attack_3()
{
	//アニメーションの設定
	ChangeAnimation(ENEMY_ANIMATION_No_ATTACK_3, false, ENEMY_ATTACK3_ANIMATION_FRAME);
	//ヒット判定発生
	if (IsAnimationFinished() == false) 
	{
		mEnemy_MoveDirKeep = mEnemy_AttackDir;
		mEnemy_MoveDir = mEnemy_AttackDir;
		//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
		if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
		else {
			mEnemy_IsHit = true;
		}
		//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //ヒット判定終了
		mEnemy_State = EIDLE; //待機状態に移行
		//1度しか動かさないためのカウンタ
		if (mEnemy_Flag == false)
		{
			mEnemy_Flag = true;
			//スーパーアーマが発動時のダメージ参照
			if (mEnemy_val >= ENEMY_PROBABILITY_LOW_SET2 && mEnemy_val <= ENEMY_PROBABILITY_MAX_SET2)
			{
				if (CXPlayer::GetInstance()->GetIsHit() == true) {
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp1;
						new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //エフェクトを生成する
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp2;
						new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //エフェクトを生成する
					}
					if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
					{
						mEnemy_Hp = mEnemy_Hp - Enemy_Damage_PlayerSp3;
						new CEffectEnemyDamageSp3(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP3, 4, 5, 2); //エフェクトを生成する
					}
				}
			}
		}
	}
}


void CXEnemy::KnockBack()
{
	//アニメーションの設定
	ChangeAnimation(ENEMY_ANIMATION_No_KNOCKBACK, false, ENEMY_KNOCKBACK_ANIMATION_FRAME);
	//ダメージ処理
	//1度しか動かさないためのカウンタ
	if (mEnemy_Flag == false)
	{
		if (mEnemy_val >= ENEMY_PROBABILITY_LOW_SET1 && mEnemy_val <= ENEMY_PROBABILITY_MAX_SET1) {
			if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
			{
				new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 3, 5, 2); //エフェクトを生成する
			}
			if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
			{
				new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 3, 5, 2); //エフェクトを生成する
			}
			if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
			{
				new CEffectEnemyDamageSp3(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP3, 4, 5, 2); //エフェクトを生成する
			}
		}
		mEnemy_Flag = true;
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_3)
		{
			mEnemy_Hp -= Enemy_Damage_PlayerSp3 * 2;
		}
		else
		{
			mEnemy_Hp -= Enemy_Damage_PlayerSp3;	//ダメージを受ける(体)

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

void CXEnemy::Death()
{
	ChangeAnimation(ENEMY_ANIMATION_No_DEATH, false, ENEMY_KNOCKBACK_ANIMATION_FRAME);
	mEnemy_IsHit = false;
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//相手の親が自分の時はリターン
	if (o->Parent() == this)return;

	if (!mEnemy_Hp <= Death_Hp)
	{
		if (m->Type() == CCollider::ECAPSUL && o->Type() == CCollider::ECAPSUL)
		{
			CVector adjust;//調整用ベクトル
			//コライダのmとoが衝突しているかの判定
			if (CCollider::CollisionCapsule(m, o, &adjust))
			{
			if (m->Tag() == CCollider::EBODY && o->Tag() == CCollider::EBODY)
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();
			}
			}
		}
	}

	if (m->Type() == CCollider::ECAPSUL && o->Type() == CCollider::ETRIANGLE) {
		CVector adjust;//調整用ベクトル
		if (CCollider::CollisionTriangleLine(o, m, &adjust))
		{
			//位置の更新(mPosition + adjust)
			mPosition = mPosition + adjust;
			//行列の更新
			CTransform::Update();
		}

	}



	if (!mEnemy_Hp <= Death_Hp)
	{
		//自身のコライダタイプの判定
		if (m->Type() == CCollider::ESPHERE) {
			//相手のコライダが球コライダの時
			if (o->Type() == CCollider::ESPHERE) {
				//球の衝突判定
				if (CCollider::Collision(m, o)) {
					//相手の親のタグがプレイヤー
					if (o->Parent()->Tag() == EPLAYER)
					{
						//相手のコライダのタグが右手
						if (o->Tag() == CCollider::ESWORD)
						{
							if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH)
							{
								//乱数値=rand()%乱数値の要素数+乱数値の最小値
								srand((unsigned)time(NULL));
								mEnemy_val = (rand() % ENEMY_PROBABILITY_MAX_SET2) + 1;
								if (mEnemy_val >= ENEMY_PROBABILITY_LOW_SET1 && mEnemy_val <= ENEMY_PROBABILITY_MAX_SET1) {
									if (CXPlayer::GetInstance()->GetIsHit() == true) {
											mEnemy_State = EKNOCKBACK;
									}
								}
							}
						}
					}
				}
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
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / ENEMY_TURN_SET));

	//回転速度　degreeに直す
	mEnemy_Turnspeed = (ENEMY_TURN_SET / M_PI) * ENEMY_TURN_SPEEDS_SET;

	//急な振り返りを抑制
	if (tCheck.turn > ENEMY_TRUN_CHECK_SPEEDS_SET) tCheck.turn = ENEMY_TRUN_CHECK_SPEEDS_SET;

	//移動方向へキャラを向かせる
	if (tCheck.cross > ENEMY_TRUN_CHECK_SET)
	{
		mRotation.Y(mRotation.Y() + tCheck.turn * mEnemy_Turnspeed);
	}
	if (tCheck.cross < ENEMY_TRUN_CHECK_SET)
	{
		mRotation.Y(mRotation.Y() - tCheck.turn * mEnemy_Turnspeed);
	}
	//移動する
	mPosition += mEnemy_MoveDir * mEnemy_Speed;
	mPosition.Y(mPosition.Y() * ENEMY_GRAVITY);

	//移動方向リセット
	mEnemy_MoveDir = CVector(0.0f, 0.0f, 0.0f);
	//移動スピードリセット
	mEnemy_Speed = ENEMY_SPEED;
}
void CXEnemy::TaskCollision()
{
	//コライダの優先度変更
	mEnemy_ColCapsuleBody.ChangePriority();
	mEnemy_ColSphereBody.ChangePriority();
	mEnemy_ColSphereRightarm.ChangePriority();
	mEnemy_ColSphereLeftarm.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mEnemy_ColCapsuleBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereBody, COLLISIONRANGE);
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
	

