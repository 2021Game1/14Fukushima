#include"CXEnemy.h"
#include"CEnemyData.h"
#include"CRes.h"


CXEnemy* CXEnemy::mpEnemy_Instance = nullptr;





//コライダ初期化
CXEnemy::CXEnemy()
	:mEnemy_Type(CXEnemy::EEnemyType::ETYPE_TUTORIAL)
	, mEnemy_ColCapsuleBody(this, nullptr, CVector(ENEMY_COLCAPSULE_BODY_X, ENEMY_COLCAPSULE_BODY_TOP_Y, ENEMY_COLCAPSULE_BODY_Z), CVector(ENEMY_COLCAPSULE_BODY_X, ENEMY_COLCAPSULE_BODY_BOTTOM_Y, ENEMY_COLCAPSULE_BODY_Z), ENEMY_COLCAPSULE_BODY_SIZE)
	, mEnemy_ColSphereBody(this, nullptr, CVector(ENEMY_COLSPHERE_BODY_X, ENEMY_COLSPHERE_BODY_Y, ENEMY_COLSPHERE_BODY_Z), ENEMY_COLSPHERE_BODY_SIZE)
	, mEnemy_ColSphereRightarm(this, nullptr, CVector(), ENEMY_COLSPHERE_RIGHTARM_SIZE)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(), ENEMY_COLSPHERE_LEFTARM_SIZE)
	, mHp(NULL)
	, mDamage(NULL)
	, mAttack_Point(NULL)
	, mDefense_Point(NULL)
	, mStan_Damage(NULL)
	, mStan_Point(NULL)
	, mStanAccumulation(NULL)
	, mEnemy_Speed(ENEMY_SPEED)
	, mEnemy_Turnspeed(ENEMY_TURNSPEED)
	, mEnemy_PlayerDis(ENEMY_FLOAT_INITIALIZATION)
	, mEnemy_FollowGaugeWid(ENEMY_FLOAT_INITIALIZATION)
	, mEnemy_val(ENEMY_INT_INITIALIZATION)
	, mEnemy_IsHit(false)
	, mEnemy_Flag(false)
	, Enemy_Priority(NULL)
	, Enemy_Hp(NULL)
	, Enemy_Hp_Max(NULL)
	, Enemy_Attack_Point(NULL)
	, Enemy_Defense_Point(NULL)
	, Enemy_Stan_Point(NULL)
	, Enemy_Damage_Magnification(NULL)
	, Enemy_Death_Hp(NULL)
	, Enemy_Gravity(NULL)
	, Enemy_StanAccumulation(NULL)
	, Enemy_StanAccumulation_Max(NULL)
	, Enemy_Speed_WalkPattern(NULL)
	, Enemy_Speed_DashPattern(NULL)
	, Enemy_Speed_BackPattern(NULL)
	, Enemy_Walk_Dis(NULL)
	, Enemy_Dash_Dis(NULL)
	, Enemy_Walk_Dis_Max(NULL)
	, Enemy_Dash_Dis_Max(NULL)
	, Enemy_Attack_Dis(NULL)
	, Enemy_Attack_Reception(NULL)
	, Enemy_Attack_Outreception(NULL)
	, Enemy_Action_Rand(NULL)
	, Enemy_Attack_Walk_Rand(NULL)
	, Enemy_Attack_Dash_Rand(NULL)
	, Enemy_AttackSp1_Set(NULL)
	, Enemy_AttackSp2_Set(NULL)
	, Enemy_Idle_Animation_Frame(NULL)
	, Enemy_Move_Animation_Frame(NULL)
	, Enemy_Dash_Animation_Frame(NULL)
	, Enemy_BackStep_Animation_Frame(NULL)
	, Enemy_Attack1_Animation_Frame(NULL)
	, Enemy_Attack2_Animation_Frame(NULL)
	, Enemy_Knockback_Animation_Frame(NULL)
	, Enemy_Death_Animation_Frame(NULL)
	, Enemy_Animation_No_Attack_1(NULL)
	, Enemy_Animation_No_Attack_2(NULL)
	, Enemy_Animation_No_Walk(NULL)
	, Enemy_Animation_No_Dash(NULL)
	, Enemy_Animation_No_BackStep(NULL)
	, Enemy_Animation_No_Idle(NULL)
	, Enemy_Animation_No_Knockback(NULL)
	, Enemy_Animation_No_Death(NULL)
	, Enemy_Position_X(NULL)
	, Enemy_Position_Y(NULL)
	, Enemy_Position_Z(NULL)
	, Enemy_Scale_X(NULL)
	, Enemy_Scale_Y(NULL)
	, Enemy_Scale_Z(NULL)
	, Enemy_Rotation_X(NULL)
	, Enemy_Rotation_Y(NULL)
	, Enemy_Rotation_Z(NULL)
{
	//テーブルの呼び出し
	EnemyTable();

	//初期状態を設定
	mEnemy_State = CXEnemy::EEnemyState::EIDLE;	//待機状態

	//ポインタの設定
	mpEnemy_Instance = this;

	//敵のUIの追加
	gEnemy_Ui_Hp_BackBar.Load2D(ENEMY_UI_HP_BACKBAR);

	//3Dモデルファイルの読み込み
	gEnemy_Model_Mutant.Load(ENEMY_MODEL_FILE);

	//エネミーのアニメーションの追加
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP1);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_BACKSTEP);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);

	//モデルの設定
	Init(&gEnemy_Model_Mutant);

	//コライダのタグを設定
	mEnemy_ColCapsuleBody.Tag(CCollider::ETag::EBODY);	//体
	mEnemy_ColSphereBody.Tag(CCollider::ETag::EBODY);		//体
	mEnemy_ColSphereRightarm.Tag(CCollider::ETag::ERIGHTARM);	//右手
	mEnemy_ColSphereLeftarm.Tag(CCollider::ETag::ELEFTARM);	//左手


	//タスク処理
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mEnemy_ColCapsuleBody.Matrix(&mpCombinedMatrix[2]);
	mEnemy_ColSphereBody.Matrix(&mpCombinedMatrix[2]);
	mEnemy_ColSphereRightarm.Matrix(&mpCombinedMatrix[68]);
	mEnemy_ColSphereLeftarm.Matrix(&mpCombinedMatrix[41]);
}
void CXEnemy::Update() {
	//状態を判別
	switch (mEnemy_State)
	{
	case CXEnemy::EEnemyState::EIDLE:	//待機状態
		Idle();	//待機処理を呼ぶ
		break;

	case CXEnemy::EEnemyState::EATTACK_1:	//攻撃1状態の時
		Attack_1();	//攻撃1の処理を呼ぶ
		break;

	case CXEnemy::EEnemyState::EATTACK_2:	//攻撃2状態の時
		Attack_2();	//攻撃2の処理を呼ぶ
		break;

	case CXEnemy::EEnemyState::EMOVE:	//移動状態
		Move();	//移動状態の処理を呼ぶ
		break;

	case CXEnemy::EEnemyState::EDASH: //回避状態
		Dash(); //回避処理を呼ぶ
		break;
	case CXEnemy::EEnemyState::EBACKSTEP://後退状態
		BackStep();//後退処理を呼ぶ
		break;
	case CXEnemy::EEnemyState::EDEATH: //死亡状態
		Death(); //死亡処理を呼ぶ
		break;

	case CXEnemy::EEnemyState::EKNOCKBACK: //ノックバック状態
		KnockBack(); //ノックバック処理を呼ぶ
		break;
	}

	MovingCalculation();
	if (mEnemy_PlayerDis >= Enemy_Attack_Dis) {
		mEnemy_AttackDir = mEnemy_Player_Point; //攻撃時の向きを求める
	}
	//体力が0になると死亡
	if (mHp <= Enemy_Death_Hp)
	{
		mEnemy_State = CXEnemy::EEnemyState::EDEATH;	//死亡状態へ移行
		mHp = Enemy_Death_Hp;
	}
	//プレイヤーの攻撃判定が無効になると敵の無敵判定を解除する
	if (CXPlayer::GetInstance()->GetIsHit() == false) {
		mEnemy_Flag = false;
	}

	CXCharacter::Update();
}

void CXEnemy::EnemyTable()
{

	//生成する敵の種類を判別
	switch (CXEnemy::mEnemy_Type) {
	case CXEnemy::EEnemyType::ETYPE_TUTORIAL:	//チュートリアル時の敵の強さ
	{
		OX::Table table(ENEMY_DATATABLE_TUTORIAL);
		Enemy_Priority = table["Enemy_Priority"]["Value"].iVal;
		Enemy_Hp = table["Enemy_Hp"]["Value"].iVal;
		Enemy_Hp_Max = table["Enemy_Hp_Max"]["Value"].iVal;
		Enemy_Attack_Point = table["Enemy_Attack_Point"]["Value"].iVal;
		Enemy_Defense_Point = table["Enemy_Defense_Point"]["Value"].iVal;
		Enemy_Stan_Point = table["Enemy_Stan_Point"]["Value"].iVal;
		Enemy_Damage_Magnification = table["Enemy_Damage_Magnification"]["Value"].fVal;
		Enemy_Death_Hp = table["Enemy_Death_Hp"]["Value"].iVal;
		Enemy_Gravity = table["Enemy_Gravity"]["Value"].fVal;
		Enemy_StanAccumulation = table["Enemy_StanAccumulation"]["Value"].iVal;
		Enemy_StanAccumulation_Max = table["Enemy_StanAccumulation_Max"]["Value"].iVal;
		Enemy_Speed_WalkPattern = table["Enemy_Speed_WalkPattern"]["Value"].fVal;
		Enemy_Speed_DashPattern = table["Enemy_Speed_DashPattern"]["Value"].fVal;
		Enemy_Speed_BackPattern = table["Enemy_Speed_BackPattern"]["Value"].fVal;
		Enemy_Walk_Dis = table["Enemy_Walk_Dis"]["Value"].fVal;
		Enemy_Dash_Dis = table["Enemy_Dash_Dis"]["Value"].fVal;
		Enemy_Walk_Dis_Max = table["Enemy_Walk_Dis_Max"]["Value"].fVal;
		Enemy_Dash_Dis_Max = table["Enemy_Dash_Dis_Max"]["Value"].fVal;
		Enemy_Attack_Dis = table["Enemy_Attack_Dis"]["Value"].fVal;
		Enemy_Attack_Reception = table["Enemy_Attack_Reception"]["Value"].fVal;
		Enemy_Attack_Outreception = table["Enemy_Attack_Outreception"]["Value"].fVal;
		Enemy_Action_Rand = table["Enemy_Action_Rand"]["Value"].iVal;
		Enemy_Attack_Walk_Rand = table["Enemy_Attack_Walk_Rand"]["Value"].iVal;
		Enemy_Attack_Dash_Rand = table["Enemy_Attack_Dash_Rand"]["Value"].iVal;
		Enemy_AttackSp1_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_AttackSp2_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_Idle_Animation_Frame = table["Enemy_Idle_Animation_Frame"]["Value"].fVal;
		Enemy_Move_Animation_Frame = table["Enemy_Move_Animation_Frame"]["Value"].fVal;
		Enemy_Dash_Animation_Frame = table["Enemy_Dash_Animation_Frame"]["Value"].fVal;
		Enemy_BackStep_Animation_Frame = table["Enemy_BackStep_Animation_Frame"]["Value"].fVal;
		Enemy_Attack1_Animation_Frame = table["Enemy_Attack1_Animation_Frame"]["Value"].fVal;
		Enemy_Attack2_Animation_Frame = table["Enemy_Attack2_Animation_Frame"]["Value"].fVal;
		Enemy_Knockback_Animation_Frame = table["Enemy_Knockback_Animation_Frame"]["Value"].fVal;
		Enemy_Death_Animation_Frame = table["Enemy_Death_Animation_Frame"]["Value"].fVal;
		Enemy_Animation_No_Attack_1 = table["Enemy_Animation_No_Attack_1"]["Value"].iVal;
		Enemy_Animation_No_Attack_2 = table["Enemy_Animation_No_Attack_2"]["Value"].iVal;
		Enemy_Animation_No_Walk = table["Enemy_Animation_No_Walk"]["Value"].iVal;
		Enemy_Animation_No_Dash = table["Enemy_Animation_No_Dash"]["Value"].iVal;
		Enemy_Animation_No_BackStep = table["Enemy_Animaton_No_BackStep"]["Value"].iVal;
		Enemy_Animation_No_Idle = table["Enemy_Animation_No_Idle"]["Value"].iVal;
		Enemy_Animation_No_Knockback = table["Enemy_Animation_No_Knockback"]["Value"].iVal;
		Enemy_Animation_No_Death = table["Enemy_Animation_No_Death"]["Value"].iVal;
		Enemy_Position_X = table["Enemy_Tutorial_Position_X"]["Value"].fVal;
		Enemy_Position_Y = table["Enemy_Tutoria_Position_Y"]["Value"].fVal;
		Enemy_Position_Z = table["Enemy_Tutoria_Position_Z"]["Value"].fVal;
		Enemy_Scale_X = table["Enemy_Scale_X"]["Value"].fVal;
		Enemy_Scale_Y = table["Enemy_Scale_Y"]["Value"].fVal;
		Enemy_Scale_Z = table["Enemy_Scale_Z"]["Value"].fVal;
		Enemy_Rotation_X = table["Enemy_Rotation_X"]["Value"].fVal;
		Enemy_Rotation_Y = table["Enemy_Rotation_Y"]["Value"].fVal;
		Enemy_Rotation_Z = table["Enemy_Rotation_Z"]["Value"].fVal;
		//タグの設定
		mTag = CCharacter::ETag::EENEMY;
		//優先度を1に変更する
		mPriority = Enemy_Priority;
		mHp = Enemy_Hp;
		mAttack_Point = Enemy_Attack_Point;
		mDefense_Point = Enemy_Defense_Point;
		mStan_Point = Enemy_Stan_Point;
		mStanAccumulation = Enemy_StanAccumulation;
		mPosition.Set(Enemy_Position_X, Enemy_Position_Y, Enemy_Position_Z);
		mScale.Set(Enemy_Scale_X, Enemy_Scale_Y, Enemy_Scale_Z);
		mRotation.Set(Enemy_Rotation_X, Enemy_Rotation_Y, Enemy_Rotation_Z);
	}
	break;

	case CXEnemy::EEnemyType::ETYPE_GAME_1:	//ゲーム本番の敵の強さ
	{
		OX::Table table(ENEMY_DATATABLE_MAINGAME1);
		Enemy_Priority = table["Enemy_Priority"]["Value"].iVal;
		Enemy_Hp = table["Enemy_Hp"]["Value"].iVal;
		Enemy_Hp_Max = table["Enemy_Hp_Max"]["Value"].iVal;
		Enemy_Attack_Point = table["Enemy_Attack_Point"]["Value"].iVal;
		Enemy_Defense_Point = table["Enemy_Defense_Point"]["Value"].iVal;
		Enemy_Stan_Point = table["Enemy_Stan_Point"]["Value"].iVal;
		Enemy_Damage_Magnification = table["Enemy_Damage_Magnification"]["Value"].fVal;
		Enemy_Death_Hp = table["Enemy_Death_Hp"]["Value"].iVal;
		Enemy_Gravity = table["Enemy_Gravity"]["Value"].fVal;
		Enemy_StanAccumulation = table["Enemy_StanAccumulation"]["Value"].iVal;
		Enemy_StanAccumulation_Max = table["Enemy_StanAccumulation_Max"]["Value"].iVal;
		Enemy_Speed_WalkPattern = table["Enemy_Speed_WalkPattern"]["Value"].fVal;
		Enemy_Speed_DashPattern = table["Enemy_Speed_DashPattern"]["Value"].fVal;
		Enemy_Speed_BackPattern = table["Enemy_Speed_BackPattern"]["Value"].fVal;
		Enemy_Walk_Dis = table["Enemy_Walk_Dis"]["Value"].fVal;
		Enemy_Dash_Dis = table["Enemy_Dash_Dis"]["Value"].fVal;
		Enemy_Walk_Dis_Max = table["Enemy_Walk_Dis_Max"]["Value"].fVal;
		Enemy_Dash_Dis_Max = table["Enemy_Dash_Dis_Max"]["Value"].fVal;
		Enemy_Attack_Dis = table["Enemy_Attack_Dis"]["Value"].fVal;
		Enemy_Attack_Reception = table["Enemy_Attack_Reception"]["Value"].fVal;
		Enemy_Attack_Outreception = table["Enemy_Attack_Outreception"]["Value"].fVal;
		Enemy_Action_Rand = table["Enemy_Action_Rand"]["Value"].iVal;
		Enemy_Attack_Walk_Rand = table["Enemy_Attack_Walk_Rand"]["Value"].iVal;
		Enemy_Attack_Dash_Rand = table["Enemy_Attack_Dash_Rand"]["Value"].iVal;
		Enemy_AttackSp1_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_AttackSp2_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_Idle_Animation_Frame = table["Enemy_Idle_Animation_Frame"]["Value"].fVal;
		Enemy_Move_Animation_Frame = table["Enemy_Move_Animation_Frame"]["Value"].fVal;
		Enemy_Dash_Animation_Frame = table["Enemy_Dash_Animation_Frame"]["Value"].fVal;
		Enemy_BackStep_Animation_Frame = table["Enemy_BackStep_Animation_Frame"]["Value"].fVal;
		Enemy_Attack1_Animation_Frame = table["Enemy_Attack1_Animation_Frame"]["Value"].fVal;
		Enemy_Attack2_Animation_Frame = table["Enemy_Attack2_Animation_Frame"]["Value"].fVal;
		Enemy_Knockback_Animation_Frame = table["Enemy_Knockback_Animation_Frame"]["Value"].fVal;
		Enemy_Death_Animation_Frame = table["Enemy_Death_Animation_Frame"]["Value"].fVal;
		Enemy_Animation_No_Attack_1 = table["Enemy_Animation_No_Attack_1"]["Value"].iVal;
		Enemy_Animation_No_Attack_2 = table["Enemy_Animation_No_Attack_2"]["Value"].iVal;
		Enemy_Animation_No_Walk = table["Enemy_Animation_No_Walk"]["Value"].iVal;
		Enemy_Animation_No_Dash = table["Enemy_Animation_No_Dash"]["Value"].iVal;
		Enemy_Animation_No_BackStep = table["Enemy_Animaton_No_BackStep"]["Value"].iVal;
		Enemy_Animation_No_Idle = table["Enemy_Animation_No_Idle"]["Value"].iVal;
		Enemy_Animation_No_Knockback = table["Enemy_Animation_No_Knockback"]["Value"].iVal;
		Enemy_Animation_No_Death = table["Enemy_Animation_No_Death"]["Value"].iVal;
		Enemy_Position_X = table["Enemy_MainGame1_Position_X"]["Value"].fVal;
		Enemy_Position_Y = table["Enemy_MainGame1_Position_Y"]["Value"].fVal;
		Enemy_Position_Z = table["Enemy_MainGame1_Position_Z"]["Value"].fVal;
		Enemy_Scale_X = table["Enemy_Scale_X"]["Value"].fVal;
		Enemy_Scale_Y = table["Enemy_Scale_Y"]["Value"].fVal;
		Enemy_Scale_Z = table["Enemy_Scale_Z"]["Value"].fVal;
		Enemy_Rotation_X = table["Enemy_Rotation_X"]["Value"].fVal;
		Enemy_Rotation_Y = table["Enemy_Rotation_Y"]["Value"].fVal;
		Enemy_Rotation_Z = table["Enemy_Rotation_Z"]["Value"].fVal;
		//タグの設定
		mTag = CCharacter::ETag::EENEMY;
		//優先度を1に変更する
		mPriority = Enemy_Priority;
		mHp = Enemy_Hp;
		mAttack_Point = Enemy_Attack_Point;
		mDefense_Point = Enemy_Defense_Point;
		mStan_Point = Enemy_Stan_Point;
		mStanAccumulation = Enemy_StanAccumulation;
		mPosition.Set(Enemy_Position_X, Enemy_Position_Y, Enemy_Position_Z);
		mScale.Set(Enemy_Scale_X, Enemy_Scale_Y, Enemy_Scale_Z);
		mRotation.Set(Enemy_Rotation_X, Enemy_Rotation_Y, Enemy_Rotation_Z);
	}
	break;

	case CXEnemy::EEnemyType::ETYPE_GAME_2:	//ゲーム本番時の敵の強さ
	{
		OX::Table table(ENEMY_DATATABLE_MAINGAME2);
		Enemy_Priority = table["Enemy_Priority"]["Value"].iVal;
		Enemy_Hp = table["Enemy_Hp"]["Value"].iVal;
		Enemy_Hp_Max = table["Enemy_Hp_Max"]["Value"].iVal;
		Enemy_Attack_Point = table["Enemy_Attack_Point"]["Value"].iVal;
		Enemy_Defense_Point = table["Enemy_Defense_Point"]["Value"].iVal;
		Enemy_Stan_Point = table["Enemy_Stan_Point"]["Value"].iVal;
		Enemy_Damage_Magnification = table["Enemy_Damage_Magnification"]["Value"].fVal;
		Enemy_Death_Hp = table["Enemy_Death_Hp"]["Value"].iVal;
		Enemy_Gravity = table["Enemy_Gravity"]["Value"].fVal;
		Enemy_StanAccumulation = table["Enemy_StanAccumulation"]["Value"].iVal;
		Enemy_StanAccumulation_Max = table["Enemy_StanAccumulation_Max"]["Value"].iVal;
		Enemy_Speed_WalkPattern = table["Enemy_Speed_WalkPattern"]["Value"].fVal;
		Enemy_Speed_DashPattern = table["Enemy_Speed_DashPattern"]["Value"].fVal;
		Enemy_Speed_BackPattern = table["Enemy_Speed_BackPattern"]["Value"].fVal;
		Enemy_Walk_Dis = table["Enemy_Walk_Dis"]["Value"].fVal;
		Enemy_Dash_Dis = table["Enemy_Dash_Dis"]["Value"].fVal;
		Enemy_Walk_Dis_Max = table["Enemy_Walk_Dis_Max"]["Value"].fVal;
		Enemy_Dash_Dis_Max = table["Enemy_Dash_Dis_Max"]["Value"].fVal;
		Enemy_Attack_Dis = table["Enemy_Attack_Dis"]["Value"].fVal;
		Enemy_Attack_Reception = table["Enemy_Attack_Reception"]["Value"].fVal;
		Enemy_Attack_Outreception = table["Enemy_Attack_Outreception"]["Value"].fVal;
		Enemy_Action_Rand = table["Enemy_Action_Rand"]["Value"].iVal;
		Enemy_Attack_Walk_Rand = table["Enemy_Attack_Walk_Rand"]["Value"].iVal;
		Enemy_Attack_Dash_Rand = table["Enemy_Attack_Dash_Rand"]["Value"].iVal;
		Enemy_AttackSp1_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_AttackSp2_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_Idle_Animation_Frame = table["Enemy_Idle_Animation_Frame"]["Value"].fVal;
		Enemy_Move_Animation_Frame = table["Enemy_Move_Animation_Frame"]["Value"].fVal;
		Enemy_Dash_Animation_Frame = table["Enemy_Dash_Animation_Frame"]["Value"].fVal;
		Enemy_BackStep_Animation_Frame = table["Enemy_BackStep_Animation_Frame"]["Value"].fVal;
		Enemy_Attack1_Animation_Frame = table["Enemy_Attack1_Animation_Frame"]["Value"].fVal;
		Enemy_Attack2_Animation_Frame = table["Enemy_Attack2_Animation_Frame"]["Value"].fVal;
		Enemy_Knockback_Animation_Frame = table["Enemy_Knockback_Animation_Frame"]["Value"].fVal;
		Enemy_Death_Animation_Frame = table["Enemy_Death_Animation_Frame"]["Value"].fVal;
		Enemy_Animation_No_Attack_1 = table["Enemy_Animation_No_Attack_1"]["Value"].iVal;
		Enemy_Animation_No_Attack_2 = table["Enemy_Animation_No_Attack_2"]["Value"].iVal;
		Enemy_Animation_No_Walk = table["Enemy_Animation_No_Walk"]["Value"].iVal;
		Enemy_Animation_No_Dash = table["Enemy_Animation_No_Dash"]["Value"].iVal;
		Enemy_Animation_No_BackStep = table["Enemy_Animaton_No_BackStep"]["Value"].iVal;
		Enemy_Animation_No_Idle = table["Enemy_Animation_No_Idle"]["Value"].iVal;
		Enemy_Animation_No_Knockback = table["Enemy_Animation_No_Knockback"]["Value"].iVal;
		Enemy_Animation_No_Death = table["Enemy_Animation_No_Death"]["Value"].iVal;
		Enemy_Position_X = table["Enemy_MainGame2_Position_X"]["Value"].fVal;
		Enemy_Position_Y = table["Enemy_MainGame2_Position_Y"]["Value"].fVal;
		Enemy_Position_Z = table["Enemy_MainGame2_Position_Z"]["Value"].fVal;
		Enemy_Scale_X = table["Enemy_Scale_X"]["Value"].fVal;
		Enemy_Scale_Y = table["Enemy_Scale_Y"]["Value"].fVal;
		Enemy_Scale_Z = table["Enemy_Scale_Z"]["Value"].fVal;
		Enemy_Rotation_X = table["Enemy_Rotation_X"]["Value"].fVal;
		Enemy_Rotation_Y = table["Enemy_Rotation_Y"]["Value"].fVal;
		Enemy_Rotation_Z = table["Enemy_Rotation_Z"]["Value"].fVal;
		//タグの設定
		mTag = CCharacter::ETag::EENEMY;
		//優先度を1に変更する
		mPriority = Enemy_Priority;
		mHp = Enemy_Hp;
		mAttack_Point = Enemy_Attack_Point;
		mDefense_Point = Enemy_Defense_Point;
		mStan_Point = Enemy_Stan_Point;
		mStanAccumulation = Enemy_StanAccumulation;
		mPosition.Set(Enemy_Position_X, Enemy_Position_Y, Enemy_Position_Z);
		mScale.Set(Enemy_Scale_X, Enemy_Scale_Y, Enemy_Scale_Z);
		mRotation.Set(Enemy_Rotation_X, Enemy_Rotation_Y, Enemy_Rotation_Z);
	}
	break;

	}
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


void CXEnemy::Render2D()
{
	//2D描画開始
	CUtil::Start2D(WINDOW_FIRST_WIDTH, WINDOW_WIDTH, WINDOW_FIRST_HEIGHT, WINDOW_HEIGHT);
	CVector tpos;
	CVector ret;
	tpos = mPosition + CVector(ret.X(), mPosition.Y() + ENEMY_GAUGE_HP_Y, ret.Z());
	Camera.WorldToScreen(&ret, tpos);
	float HpRate = (float)mHp / (float)Enemy_Hp_Max; //体力最大値に対する、現在の体力の割合
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
		if (mHp > Enemy_Death_Hp) {
			if (!CXPlayer::GetInstance()->GetHp() == NULL) {
				gEnemy_Ui_Hp_BackBar.Draw(ret.X() - ENEMY_GAUGE_WID_MAX, ret.X() + ENEMY_GAUGE_WID_MAX, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 0, 30);
				//被ダメージ分後追いするゲージを表示
				CRes::GetInstance()->GetInUiHpRedGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + mEnemy_FollowGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
				//体力ゲージ
				CRes::GetInstance()->GetInUiHpGreenGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + HpGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
			}
		}
	}
	//2Dの描画終了
	CUtil::End2D();
}

void CXEnemy::Idle()
{
	int random = ENEMY_INT_INITIALIZATION;
	//プレイヤーが死亡状態では無いとき
	if (CXPlayer::EPlayerState::EDEATH != CXPlayer::GetInstance()->GetState())
	{
		mEnemy_Flag = false;
		//プレイヤーが一定距離まで近づくと追跡状態へ移行
		if (mEnemy_PlayerDis <= Enemy_Walk_Dis)
		{
			mEnemy_State = CXEnemy::EEnemyState::EMOVE;
		}
		else if (mEnemy_PlayerDis <= Enemy_Dash_Dis)
		{
			mEnemy_State = CXEnemy::EEnemyState::EDASH;
		}
		else
		{
			//アニメーションの設定
			ChangeAnimation(Enemy_Animation_No_Idle, true, Enemy_Idle_Animation_Frame);
		}
	}
	else
	{
		//アニメーションの設定
		ChangeAnimation(Enemy_Animation_No_Idle, true, Enemy_Idle_Animation_Frame);
	}
}
void CXEnemy::Move() {
	//アニメーションの設定
	ChangeAnimation(Enemy_Animation_No_Walk, true, Enemy_Move_Animation_Frame);
	mEnemy_Speed = Enemy_Speed_WalkPattern;
	//目的地点までのベクトルを求める
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDirにプレイヤー方向のベクトルを入れる
	mEnemy_MoveDir.Y(ENEMY_FLOAT_INITIALIZATION);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//目標地点を更新
	int r = rand() % Enemy_Attack_Walk_Rand; //rand()は整数の乱数を返す
	//%Enemy_Attack_Walk_RandはEnemy_Attack_Walk_Randで割った余りを求める
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
			random = rand() % 2;
			switch (random)
			{
			case 0:
				mEnemy_State = CXEnemy::EEnemyState::EATTACK_1; //攻撃1状態へ移行
				break;
			case 1:
				mEnemy_State = CXEnemy::EEnemyState::EATTACK_2; //攻撃2状態へ移行
				break;
			}
		}
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mEnemy_PlayerDis >= Enemy_Walk_Dis_Max)
	{
		mEnemy_State = CXEnemy::EEnemyState::EIDLE; //待機状態へ移行
	}

}

void CXEnemy::Dash()
{
	//アニメーションの設定
	ChangeAnimation(Enemy_Animation_No_Dash, true, Enemy_Dash_Animation_Frame);
	//移動スピードを変更
	mEnemy_Speed = Enemy_Speed_DashPattern;
	//目的地点までのベクトルを求める
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDirに目標地点方向のベクトルを入れる
	mEnemy_MoveDir.Y(ENEMY_FLOAT_INITIALIZATION);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//目標地点を更新
	int r = rand() % Enemy_Attack_Dash_Rand; //rand()は整数の乱数を返す
	//%Enemy_Attack_Dash_RandはEnemy_Attack_Dash_Randで割った余りを求める
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
			random = rand() % Enemy_Action_Rand;
			switch (random)
			{
			case 0:
				mEnemy_State = CXEnemy::EEnemyState::EATTACK_1; //攻撃1状態へ移行
				break;
			case 1:
				mEnemy_State = CXEnemy::EEnemyState::EATTACK_2; //攻撃2状態へ移行
				break;
			}
		}
	}
	//プレイヤーが追跡可能な距離にいないとき
	if (mEnemy_PlayerDis >= Enemy_Dash_Dis_Max)
	{
		mEnemy_State = CXEnemy::EEnemyState::EIDLE; //待機状態へ移行
	}

	CTransform::Update();

}

void CXEnemy::BackStep()
{
	if (mEnemy_Flag == false)
	{
		ChangeAnimation(Enemy_Animation_No_BackStep, false, Enemy_BackStep_Animation_Frame);
		mEnemy_Flag = true;
	}
	if (IsAnimationFinished() == false && mAnimationIndex == Enemy_Animation_No_BackStep) {
		//バック方向
		CVector BackVec = mEnemy_Player_Point.Normalize();
		//バック量
		float BackAmount = Enemy_Speed_BackPattern;
		//バックさせる
		mPosition -= BackVec * BackAmount;
	}
	if (IsAnimationFinished()) {
		//プレイヤーが攻撃可能な距離にいないとき
		if (mEnemy_PlayerDis >= Enemy_Attack_Dis)
		{
			mEnemy_State = CXEnemy::EEnemyState::EDASH;
		}
		else if (mEnemy_PlayerDis < Enemy_Attack_Dis)
		{
			mEnemy_State = CXEnemy::EEnemyState::EATTACK_1;
		}
	}
}

void CXEnemy::Attack_1()
{
	//アニメーションの設定
	ChangeAnimation(Enemy_Animation_No_Attack_1, false, Enemy_Attack1_Animation_Frame);

	//攻撃出来る距離に居れば追従して攻撃
	int r = rand() % Enemy_AttackSp1_Set; //rand()は整数の乱数を返す
	//%Enemy_AttackSp1_SetはEnemy_AttackSp1_Setで割った余りを求める
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	//ヒット判定発生
	if (IsAnimationFinished() == false)
	{
		//目的地点までのベクトルを求める
		mEnemy_Player_Point = mEnemy_Point - mPosition;
		mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
		else if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
		else{
			mEnemy_IsHit = true;
		}
		//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}

	}

	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //ヒット判定終了
		int random = ENEMY_INT_INITIALIZATION;
		//プレイヤーが攻撃可能な距離にいるとき
		if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
		{
			if (random == ENEMY_INT_INITIALIZATION)
			{
				//ランダムで攻撃の種類を決める
				random = rand() % Enemy_Action_Rand;
				switch (random)
				{
				case 0:
					mEnemy_State = CXEnemy::EEnemyState::EBACKSTEP; //バックステップへ移行
					break;
				case 1:
					mEnemy_State = CXEnemy::EEnemyState::EATTACK_2; //攻撃2状態へ移行
					break;
				}
			}
		}
		else {
			mEnemy_State = CXEnemy::EEnemyState::EDASH; //走行へ移行
		}
	}
}

void CXEnemy::Attack_2()
{
	//アニメーションの設定
	ChangeAnimation(Enemy_Animation_No_Attack_2, false, Enemy_Attack2_Animation_Frame);

	//攻撃出来る距離に居れば追従して攻撃
	int r = rand() % Enemy_AttackSp2_Set; //rand()は整数の乱数を返す
	//%Enemy_AttackSp2_SetはEnemy_AttackSp2_Setで割った余りを求める
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}

	//ヒット判定発生
	if (IsAnimationFinished() == false)
	{
		//目的地点までのベクトルを求める
		mEnemy_Player_Point = mEnemy_Point - mPosition;
		mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //ヒット判定終了
		}
		//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
		else if (mAnimationFrame <= Enemy_Attack_Reception)
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

	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //ヒット判定終了
		int random = ENEMY_INT_INITIALIZATION;
		//プレイヤーが攻撃可能な距離にいるとき
		if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
		{
			if (random == ENEMY_INT_INITIALIZATION)
			{
				//ランダムで攻撃の種類を決める
				random = rand() % Enemy_Action_Rand;
				switch (random)
				{
				case 0:
					mEnemy_State = CXEnemy::EEnemyState::EATTACK_1; //攻撃1状態へ移行
					break;
				case 1:
					mEnemy_State = CXEnemy::EEnemyState::EBACKSTEP; //バックステップへ移行
					break;
				}
			}
		}
		else {
			mEnemy_State = CXEnemy::EEnemyState::EDASH; //走行へ移行
		}
	}
}


void CXEnemy::KnockBack()
{
	//アニメーションの設定
	ChangeAnimation(Enemy_Animation_No_Knockback, false, Enemy_Knockback_Animation_Frame);
	//アニメーションが再生中時
	if (IsAnimationFinished() == false)
	{
		mEnemy_IsHit = false;
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		//当たり判定のフラグを判定するように変更
		mEnemy_Flag = false;
		mEnemy_State = CXEnemy::EEnemyState::EATTACK_2; //攻撃2
	}
}

void CXEnemy::Death()
{
	//死亡アニメーション
	ChangeAnimation(Enemy_Animation_No_Death, false, Enemy_Death_Animation_Frame);
	//敵の攻撃判定をfalseにする
	mEnemy_IsHit = false;
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//相手の親が自分の時はリターン
	if (o->Parent() == this)return;

	if (m->CCollider::Type() == CCollider::EType::ECAPSUL && o->CCollider::Type() == CCollider::EType::ECAPSUL)
	{
		CVector adjust;//調整用ベクトル
		//コライダのmとoが衝突しているかの判定
		if (CCollider::CollisionCapsule(m, o, &adjust))
		{
			if (m->CCollider::Tag() == CCollider::ETag::EBODY && o->CCollider::Tag() == CCollider::ETag::EBODY)
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();
			}
		}
	}

	//カプセルと三角形の衝突処理
	if (m->Type() == CCollider::EType::ECAPSUL && o->Type() == CCollider::EType::ETRIANGLE) {
		CVector adjust;//調整用ベクトル
		//三角形コライダとカプセルの衝突処理
		if (CCollider::CollisionTriangleLine(o, m, &adjust))
		{
			mPosition.Y(NULL);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition + adjust;
			//行列の更新
			CTransform::Update();
		}

	}
	if (m->Type() == CCollider::EType::ESPHERE && o->Type() == CCollider::EType::ETRIANGLE) {
		CVector adjust;//調整用ベクトル
		//相手の親のタグがマップ
		if (o->Parent()->Tag() == CCharacter::ETag::EMAP)
		{
			//自分のコライダのタグが頭or体
			if (m->Tag() == CCollider::ETag::EBODY) {
				if (CCollider::CollisionTriangleSphere(o, m, &adjust))
				{
					//位置の更新(mPosition + adjust)
					mPosition = mPosition + adjust;
					//行列の更新
					CTransform::Update();
				}
			}
		}
	}

	//敵が死亡していないとき
	if (mEnemy_State != EEnemyState::EDEATH) {
		//自身のコライダタイプの判定
		if (m->Type() == CCollider::EType::ESPHERE) {
			//相手のコライダが球コライダの時
			if (o->Type() == CCollider::EType::ESPHERE) {
				//球の衝突判定
				if (CCollider::Collision(m, o)) {
					//相手の親のタグがプレイヤー
					if (o->Parent()->Tag() == CCharacter::ETag::EPLAYER)
					{
						//相手のコライダのタグが剣
						if (o->Tag() == CCollider::ETag::ESWORD)
						{
							if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH)
							{
								if (CXPlayer::GetInstance()->GetIsHit() == true) {
									//ダメージ処理
									//1度しか動かさないためのカウンタ
									if (mEnemy_Flag == false)
									{
										if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
										{
											//ダメージ計算
											mDamage = CXPlayer::GetInstance()->GetIsAttackPoint() * (CXPlayer::GetInstance()->GetIsAttackPoint() / mDefense_Point) + (CXPlayer::GetInstance()->GetIsAttackPoint() * Enemy_Damage_Magnification);
											//ダメージ処理
											mHp = mHp - mDamage;
											//攻撃判定をfalseにする
											mEnemy_IsHit = false;
											//当たったときのエフェクト
											new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 2, 5, 2);
											new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 4, 5, 2);
											//怯み値が上限を超えたら、ひるむ
											if (Enemy_StanAccumulation_Max <= mStanAccumulation)
											{
												//ノックバックする
												mEnemy_State = CXEnemy::EEnemyState::EKNOCKBACK;
												mStanAccumulation = Enemy_StanAccumulation;
											}
											else {
												//敵のひるみ値設定
												mStan_Damage = CXPlayer::GetInstance()->GetIsStanPoint() * (CXPlayer::GetInstance()->GetIsStanPoint() / mDefense_Point) + (CXPlayer::GetInstance()->GetIsStanPoint() * Enemy_Damage_Magnification);
												mStanAccumulation = mStanAccumulation + mStan_Damage;
											}

										}
										else if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
										{
											//ダメージ計算
											mDamage = CXPlayer::GetInstance()->GetIsAttackPoint() * (CXPlayer::GetInstance()->GetIsAttackPoint() / mDefense_Point) + (CXPlayer::GetInstance()->GetIsAttackPoint() * Enemy_Damage_Magnification);
											//ダメージ処理
											mHp = mHp - mDamage;
											//攻撃判定をfalseにする
											mEnemy_IsHit = false;
											//当たったときのエフェクト
											new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 2, 5, 2);
											new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 4, 5, 2);
											//怯み値が上限を超えたら、ひるむ
											if (Enemy_StanAccumulation_Max <= mStanAccumulation)
											{
												//ノックバックする
												mEnemy_State = CXEnemy::EEnemyState::EKNOCKBACK;
												mStanAccumulation = Enemy_StanAccumulation;
											}
											else {
												//敵のひるみ値設定
												mStan_Damage = CXPlayer::GetInstance()->GetIsStanPoint() * (CXPlayer::GetInstance()->GetIsStanPoint() / mDefense_Point) + (CXPlayer::GetInstance()->GetIsStanPoint() * Enemy_Damage_Magnification);
												mStanAccumulation = mStanAccumulation + mStan_Damage;
											}

										}
										//プレイヤとの衝突処理を停止する
										mEnemy_Flag = true;
									}

								}
							}
						}
					}
				}
			}

		}
	}
	//死亡しているときは、衝突判定をスルーする
	else if (mHp <= Enemy_Death_Hp) {

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

	//移動方向にキャラを向かせる
	if (tCheck.cross > ENEMY_TRUN_CHECK_SET)
	{
		mRotation.Y(mRotation.Y() + tCheck.turn * mEnemy_Turnspeed);
	}
	//移動方向にキャラを向かせる
	if (tCheck.cross < ENEMY_TRUN_CHECK_SET)
	{
		mRotation.Y(mRotation.Y() - tCheck.turn * mEnemy_Turnspeed);
	}
	//移動する
	mPosition += mEnemy_MoveDir * mEnemy_Speed;
	//キャラに重力を掛ける
	mPosition.Y(mPosition.Y() * Enemy_Gravity);

	//移動方向リセット
	mEnemy_MoveDir = CVector(0.0f, 0.0f, 0.0f);
	//移動スピードリセット
	mEnemy_Speed = ENEMY_SPEED;
}
//インスタンスの取得
CXEnemy* CXEnemy::GetInstance()
{
	//インスタンスの設定
	return mpEnemy_Instance;
}
//HPの取得
int CXEnemy::GetHp() {
	//HPの取得
	return mHp;
}
//敵のタイプを取得
CXEnemy::EEnemyType CXEnemy::GetIsType()
{
	return mEnemy_Type;
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
bool CXEnemy::GetIsDeath()
{
	return (mEnemy_State == CXEnemy::EEnemyState::EDEATH);
}
//攻撃の当たり判定フラグを設定
void CXEnemy::SetIsHit(bool hitflag)
{
	mEnemy_IsHit = hitflag;
}
//攻撃力を取得する
int CXEnemy::GetIsAttackPoint()
{
	return mAttack_Point;
}
//スタン値を取得する
int CXEnemy::GetIsStanPoint()
{
	return mStan_Point;
}
//敵の状態を取得する
CXEnemy::EEnemyState CXEnemy::GetState()
{
	return mEnemy_State;
}
void CXEnemy::SetIsType(EEnemyType type) {
	mEnemy_Type = type;
}
//位置を設定する
void CXEnemy::GetPos()
{
	mPosition.Set(Enemy_Position_X, Enemy_Position_Y, Enemy_Position_Z);
}
//敵のスケールを取得
void CXEnemy::GetScale()
{
	mScale.Set(Enemy_Scale_X, Enemy_Scale_Y, Enemy_Scale_Z);
}
//敵の回転値を取得する
void CXEnemy::GetRotation()
{
	mRotation.Set(Enemy_Rotation_X, Enemy_Rotation_Y, Enemy_Rotation_Z);
}
	

