#include"CXPlayer.h"
#include"CXEnemyManager.h"
#include"CRes.h"


CXPlayer* CXPlayer::mpPlayer_Instance = nullptr;												//プレイヤのインスタンス変数の初期化

//テーブルのデータを変数に保存
void CXPlayer::PlayerTable() {
	OX::Table table(PLAYER_DATATABLE);

	Player_Priority = table["Player_Priority"]["Value"].iVal;
	Player_Hp = table["Player_Hp"]["Value"].iVal;
	Player_Hp_Max = table["Player_Hp_Max"]["Value"].iVal;
	Player_Attack_Point = table["Player_Attack_Point"]["Value"].iVal;
	Player_Defense_Point = table["Player_Defense_Point"]["Value"].iVal;
	Player_Stan_Point = table["Player_Stan_Point"]["Value"].iVal;
	Player_StanAccumulation = table["Player_StanAccumulation"]["Value"].iVal;
	Player_StanAccumulation_Max = table["Player_StanAccumulation_Max"]["Value"].iVal;
	Player_Damage_Magnification = table["Player_Damage_Magnification"]["Value"].fVal;
	Player_GameOver_Hp = table["Player_GameOver_Hp"]["Value"].iVal;
	Player_Speed_Default = table["Player_Speed_Default"]["Value"].fVal;
	Player_Speed_Avoid = table["Player_Speed_Avoid"]["Value"].fVal;
	Player_Avoid_Time = table["Player_Avoid_Time"]["Value"].fVal;
	Player_Gravity = table["Player_Gravity"]["Value"].fVal;
	Player_Thrust = table["Player_Thrust"]["Value"].fVal;
	Player_Se = table["Player_Se"]["Value"].fVal;
	Player_Damage_Se = table["Player_Damage_Se"]["Value"].fVal;
	Player_Push_Reception = table["Player_Push_Reception"]["Value"].fVal;
	Player_Attack_InReception = table["Player_Attack_InReception"]["Value"].fVal;
	Player_Attack_OutReception = table["Player_Attack_OutReception"]["Value"].fVal;
	Player_Attack_Dis = table["Player_Attack_Dis"]["Value"].fVal;
	Player_Position_X = table["Player_Position_X"]["Value"].fVal;
	Player_Position_Y = table["Player_Position_Y"]["Value"].fVal;
	Player_Position_Z = table["Player_Position_Z"]["Value"].fVal;
	Player_Scale_X = table["Player_Scale_X"]["Value"].fVal;
	Player_Scale_Y = table["Player_Scale_Y"]["Value"].fVal;
	Player_Scale_Z = table["Player_Scale_Z"]["Value"].fVal;
	Player_Rotation_X = table["Player_Rotation_X"]["Value"].fVal;
	Player_Rotation_Y = table["Player_Rotation_Y"]["Value"].fVal;
	Player_Rotation_Z = table["Player_Rotation_Z"]["Value"].fVal;
	Player_Idle_Animation_Frame = table["Player_Idle_Animation_Frame"]["Value"].fVal;
	Player_Move_Animation_Frame = table["Player_Move_Animation_Frame"]["Value"].fVal;
	Player_Avoidance_Animation_Frame = table["Player_Avoidance_Animation_Frame"]["Value"].fVal;
	Player_Attack1_Animation_Frame = table["Player_Attack1_Animation_Frame"]["Value"].fVal;
	Player_Attack1_Idle_Animation_Frame = table["Player_Attack1_Idle_Animation_Frame"]["Value"].fVal;
	Player_Attack2_Animation_Frame = table["Player_Attack2_Animation_Frame"]["Value"].fVal;
	Player_Attack2_Idle_Animation_Frame = table["Player_Attack2_Idle_Animation_Frame"]["Value"].fVal;
	Player_KnockBack_Animation_Frame = table["Player_KnockBack_Animation_Frame"]["Value"].fVal;
	Player_Death_Animation_Frame = table["Player_Death_Animation_Frame"]["Value"].fVal;
	Player_Animation_No_Move = table["Player_Animation_No_Move"]["Value"].iVal;
	Player_Animation_No_Attack1 = table["Player_Animation_No_Attack1"]["Value"].iVal;
	Player_Animation_No_Attack1_Idle = table["Player_Animation_No_Attack1_Idle"]["Value"].iVal;
	Player_Animation_No_Attack2 = table["Player_Animation_No_Attack2"]["Value"].iVal;
	Player_Animation_No_Attack2_Idle = table["Player_Animation_No_Attack2_Idle"]["Value"].iVal;
	Player_Animation_No_AvoidDance = table["Player_Animation_No_AvoidDance"]["Value"].iVal;
	Player_Animation_No_Idle = table["Player_Animation_No_Idle"]["Value"].iVal;
	Player_Animation_No_Knockback = table["Player_Animation_No_Knockback"]["Value"].iVal;
	Player_Animation_No_Death = table["Player_Animation_No_Death"]["Value"].iVal;
	Player_Gauge_Hp_Shake_X = table["Player_Gauge_Hp_Shake_X"]["Value"].iVal;
	Player_Gauge_Hp_Shake_Y = table["Player_Gauge_Hp_Shake_Y"]["Value"].iVal;
	Player_Gauge_Hp_Shake_Range_X = table["Player_Gauge_Hp_Shake_Range_X"]["Value"].iVal;
	Player_Gauge_Hp_Shake_Range_Y = table["Player_Gauge_Hp_Shake_Range_Y"]["Value"].iVal;
	Player_Gauge_Hp_Rate = table["Player_Gauge_Hp_Rate"]["Value"].fVal;
	Player_Trun_Set = table["Player_Trun_Set"]["Value"].fVal;
	Player_Trun_Speeds_Set = table["Player_Trun_Speeds_Set"]["Value"].fVal;
	Player_Trun_Check_Speeds_Set = table["Player_Trun_Check_Speeds_Set"]["Value"].fVal;
	Player_Trun_Check_Set = table["Player_Trun_Check_Set"]["Value"].fVal;

	//優先度を1に変更する
	mPriority = Player_Priority;
	//テーブル取得データを代入
	mPlayer_Gauge_Hp_Shake_X = Player_Gauge_Hp_Shake_X;
	mPlayer_Gauge_Hp_Shake_Y = Player_Gauge_Hp_Shake_Y;
	mPlayer_Gauge_Hp_Shake_Range_X = Player_Gauge_Hp_Shake_Range_X;
	mPlayer_Gauge_Hp_Shake_Range_Y = Player_Gauge_Hp_Shake_Range_Y;
	mPlayer_FollowGaugeWid = Player_Gauge_Wid;
	mPlayer_Speed = Player_Speed_Default;
	mAttack_Point = Player_Attack_Point;
	mDefense_Point = Player_Defense_Point;
	mStan_Point = Player_Stan_Point;
	mStanAccumulation = Player_StanAccumulation;
	mPlayer_Hp = Player_Hp;
	mPlayer_Hp_Max = Player_Hp_Max;
	mPlayer_Gauge_Hp_Rate = Player_Gauge_Hp_Rate;
	mPlayer_Attack_Dis = Player_Attack_Dis;
}
//デフォルトコンストラクタ
CXPlayer::CXPlayer()
//プレイヤの変数の初期化
	: mPlayer_ColCapsuleBody(this, nullptr, CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_TOP_Y, PLAYER_COLCAPSULE_BODY_Z), CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_BOTTOM_Y, PLAYER_COLCAPSULE_BODY_Z), PLAYER_COLCAPSULE_BODY_SIZE)
	,mPlayer_ColSphereHead(this,nullptr,CVector(0.0f,16.0f,0.0f),PLAYER_COLSPHER_HEAD_SIZE)
	, mPlayer_ColSphereBody(this, nullptr, CVector(), PLAYER_COLSPHERE_BODY_SIZE)
	, mPlayer_ColSphereLowerBody(this, nullptr, CVector(PLAYER_COLSPHERE_LOWERBODY_X, PLAYER_COLSPHERE_LOWERBODY_Y, PLAYER_COLSPHERE_LOWERBODY_Z), PLAYER_COLSPHERE_LOWERBODY_SIZE)
	, mPlayer_ColSphereSword(this, nullptr, CVector(PLAYER_COLSPHERE_SWORD_X, PLAYER_COLSPHERE_SWORD_Y, PLAYER_COLSPHERE_SWORD_Z), PLAYER_COLSPHERE_SWORD_SIZE)
	, mPlayer_ComboCount(PLAYER_INT_INITIALIZATION)
	, mPlayer_Turnspeed(PLAYER_FLOAT_INITIALIZATION)
	, mPlayer_InvincibleFlag(false)
	, mPlayer_IsHit(false)
	, mPlayer_AttackFlag_1(false)
	, mPlayer_SeFlag(false)
	, mPlayer_AttackFlag_Once(false)
	, mPlayer_Flag(false)
	, mPlayer_Avoid(false)
{
	//プレイヤのインスタンスを設定
	mpPlayer_Instance = this;										//プレイヤのインスタンスを自身に設定する
	//タグの紐づけ
	mTag = EPLAYER;													//タグをプレイヤに設定
	//初期状態を設定
	mPlayer_State = EIDLE;											//プレイヤの初期状態を待機状態に設定する
	//コライダのタグを設定
	mPlayer_ColCapsuleBody.Tag(CCollider::EBODY);					//体
	mPlayer_ColSphereBody.Tag(CCollider::EBODY);					//体
	mPlayer_ColSphereLowerBody.Tag(CCollider::EBODY);				//下半身
	mPlayer_ColSphereHead.Tag(CCollider::EHEAD);					//頭
	mPlayer_ColSphereSword.Tag(CCollider::ESWORD);					//剣
	//プレイヤのテーブルを呼び出し
	PlayerTable();
	//タスクマネージャへの追加
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}

//モデルの設定
void CXPlayer::Init(CModelX* model)
{
	//プレイヤSE
	Se_Player_AttackSp1.Load(SE_PLAYER_ATTACK1);
	Se_Player_AttackSp2.Load(SE_PLAYER_ATTACK2);
	Se_Player_Walk.Load(SE_PLAYER_WALK);
	Se_Player_Death.Load(SE_PLAYER_DEATH);
	//敵SE
	Se_Enemy_AttackSp.Load(SE_ENEMY_ATTACK);
	//プレイヤのUIの追加
	gPlayer_Ui_Hp_Frame.Load2D(PLAYER_UI_HP_FRAME);

	CXCharacter::Init(model);
	//合成行列の設定
	mPlayer_ColSphereLowerBody.Matrix(&mpCombinedMatrix[2]);
	mPlayer_ColCapsuleBody.Matrix(&mpCombinedMatrix[3]);
	mPlayer_ColSphereBody.Matrix(&mpCombinedMatrix[15]);
	mPlayer_ColSphereHead.Matrix(&mpCombinedMatrix[16]);
	mPlayer_ColSphereSword.Matrix(&mpCombinedMatrix[71]);
	//プレイヤの位置,拡縮,回転の設定
	mPosition.Set(Player_Position_X, Player_Position_Y, Player_Position_Z);								//位置を設定
	mScale.Set(Player_Scale_X, Player_Scale_Y, Player_Scale_Z);										//スケール設定
	mRotation.Set(Player_Rotation_X, Player_Rotation_Y, Player_Rotation_Z);								//回転を設定
}
//更新処理
void CXPlayer::Update() {
	//剣コライダの座標を参照
	CVector tpos = mPlayer_ColSphereSword.GetIsMatrix()->GetPos();
	//状態を判別
	switch (mPlayer_State) {
	case EIDLE:														//待機状態
		Idle();														//待機処理を呼ぶ
		break;

	case EATTACK_1:													//攻撃1状態の時
		Attack_1();													//攻撃1の処理を呼ぶ
		break;

	case EATTACK_2:													//攻撃2状態の時
		Attack_2();													//攻撃2の処理を呼ぶ
		break;

	case EMOVE:														//移動状態
		Move();														//移動状態の処理を呼ぶ
		break;

	case EAVOIDANCE:												//回避状態
		Avoidance();												//回避処理を呼ぶ
		break;

	case EDEATH:													//死亡状態
		Death();													//死亡処理を呼ぶ
		break;

	case EKNOCKBACK:												//ノックバック状態
		KnockBack();												//ノックバック処理を呼ぶ
		break;
	}
	MovingCalculation();
	//体力が0になると死亡
	if (mPlayer_Hp <= Player_GameOver_Hp) {
		mPlayer_State = EDEATH;										//死亡状態へ移行
		mPlayer_Hp = Player_GameOver_Hp;
	}
	if (mPlayer_EnemyDis >= mPlayer_Attack_Dis) {
		mPlayer_AttackDir = mPlayer_Point; //攻撃時の向きを求める
	}
	//カメラアングルの変更
	if (CKey::Push(VK_F1)) {
		Camera.CameraAngleChange();
	}
	//カメラアングルの変更
	else if(CKey::Push(VK_F2)) {
		Camera.CameraAngleDefault();
	}
	//カメラの設定
	Camera.SetTarget(mPosition);									//カメラをプレイヤの位置に設定
	//キャラクタの更新処理
	CXCharacter::Update();
}
//待機状態の処理
void CXPlayer::Idle() 
{
	mPlayer_AttackFlag_1 = false;					//プレイヤの攻撃1フラグをfalseにする
	mPlayer_Flag = false;							//ダメージフラグの解除
	//左クリックで攻撃
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//回避状態へ移行
	if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	//WASDキーを押すと移動へ移行
	else if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
		mPlayer_State = EMOVE;
		Se_Player_Walk.Repeat(Player_Se);
	}
	//何も入力されなかったので待機処理を動かす
	else{
		mPlayer_ComboCount = PLAYER_INT_INITIALIZATION;
		ChangeAnimation(Player_Animation_No_Idle, true, Player_Idle_Animation_Frame);
	}
}

//移動処理
void CXPlayer::Move()
{
	mPlayer_AttackFlag_1 = false;					//プレイヤの攻撃1フラグをfalseにする
	//左クリックで攻撃1へ移行
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	} 
	//回避状態へ移行
	if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	//WASDキーを押すと移動へ移行
	else if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
		ChangeAnimation(Player_Animation_No_Move, true, Player_Move_Animation_Frame);
		MoveCamera();												//カメラを基準にした移動処理を呼ぶ
		Se_Player_Walk.Repeat(Player_Se);
	}
	//待機状態へ移行
	else {
		mPlayer_State = EIDLE;
	}
	//歩行状態では無いので歩行SEを停止する
	if (mPlayer_State != EMOVE) {
		Se_Player_Walk.Stop();
	}
}
//回避状態
void CXPlayer::Avoidance()
{
	//回避時一度だけ通る
	if (mPlayer_Avoid == false) {
		ChangeAnimation(Player_Animation_No_AvoidDance, false, Player_Avoidance_Animation_Frame);
		mPlayer_Avoid = true;							//回避中
		mPlayer_Speed_Avoid = Player_Speed_Avoid;
		mPlayer_Avoid_Time = Player_Avoid_Time;
		MoveCamera();
	}
	//ヒット判定発生
	if (IsAnimationFinished() == false)
	{
		mPlayer_AttackFlag_1 = false;					//プレイヤの攻撃1フラグをfalseにする
		mPlayer_Flag = false;							//ダメージフラグの解除
		{
			//回避時間をカウントダウン
			mPlayer_Avoid_Time--;
			//回避時間0になった時
			if (mPlayer_Avoid_Time == 0) {
				mPlayer_Avoid = false;	//回避終了
			}
			//回避時の移動値を代入
			mPlayer_Move = mPlayer_MoveDirKeep * mPlayer_Speed_Avoid;

			//回避状態が終了したとき
			if (mPlayer_Avoid == false) {
				//回避終了時WASDキーが押されていると移動
				if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
					mPlayer_State = EMOVE;
				}
				//待機状態へ移行
				else {
					mPlayer_State = EIDLE;
				}
			}
		}
	}
}


//攻撃1処理
void CXPlayer::Attack_1()
{
	mPlayer_Flag = false;							//ダメージフラグの解除
	//処理が呼び出されたら1度しか動かさない
	if (mPlayer_AttackFlag_1 == false) {
		mPlayer_AttackFlag_1 = true;															//プレイヤの攻撃1のフラグをtrueにする
		mPlayer_AttackFlag_Once = true;															//プレイヤの攻撃フラグをtrueに設定
		ChangeAnimation(Player_Animation_No_Attack1, false, Player_Attack1_Animation_Frame);	//プレイヤの攻撃1モーション
		Se_Player_AttackSp1.Play(Player_Se);
	}
	//アニメーションが終了しているかつ、攻撃2のアニメーションだった場合、実行する
	if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack2) {
		mPlayer_AttackFlag_Once = true;															//プレイヤの攻撃フラグをtrueに設定
		ChangeAnimation(Player_Animation_No_Attack1, false, Player_Attack1_Animation_Frame);	//プレイヤの攻撃1モーション
		Se_Player_AttackSp1.Play(Player_Se);													//プレイヤの攻撃SEを再生
	}
		//敵の距離がプレイヤの攻撃範囲に入ったら自動的に敵に攻撃が追従する
		if (mPlayer_EnemyDis <= mPlayer_Attack_Dis) {
			mPlayer_MoveDirKeep = mPlayer_MoveDir;							  //MoveDir保存
			mPlayer_MoveDir = CXEnemyManager::GetInstance()->GetTargetEnemy();//敵のリストに入っている敵の位置を代入
		}

		//ヒット判定発生
		if (IsAnimationFinished() == false)
		{

			//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
			if (mAnimationFrame <= Player_Attack_InReception)
			{
				mPlayer_IsHit = false; //ヒット判定終了
			}
			//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
			else {
				mPlayer_IsHit = true;
			}
			//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
			if (mAnimationFrame > Player_Attack_OutReception)
			{
				mPlayer_IsHit = false; //ヒット判定終了
			}

		}

		
			//左クリックされた場合
			if (CKey::Once(VK_LBUTTON)) {
				//アニメーションが攻撃1でかつ、入力制限時間内でクリックされれば実行する
				if (mAnimationIndex == Player_Animation_No_Attack1) {
					if (mAnimationFrame < Player_Push_Reception) {
						//攻撃2モーションへ移行
						mPlayer_State = EATTACK_2;							
					}
				}
			}
			//移動状態へ移行
			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
			}
		//アニメーション終了時
		//攻撃1から待機モーションの間のアニメーションを描画する
		if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack1) {
			ChangeAnimation(Player_Animation_No_Attack1_Idle, false, Player_Attack1_Idle_Animation_Frame);
		}
		//攻撃1から待機モーションの間のアニメーションを描画が終了時
		//待機状態へ移行
		if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack1_Idle) {
				mPlayer_IsHit = false;								//ヒット判定終了
				mPlayer_State = EIDLE;								//待機状態へ移行
				mPlayer_AttackFlag_1 = false;						//プレイヤの攻撃1フラグをfalseにする
		}
}

//攻撃2処理
void CXPlayer::Attack_2()
{
	//アニメーションが終了しているかつ、プレイヤの攻撃1がアニメーションされたら
	//攻撃2の行動処理を実行する
	if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack1) {
		mPlayer_AttackFlag_Once = true;																//プレイヤの攻撃フラグをtrueに設定
		ChangeAnimation(Player_Animation_No_Attack2, false, Player_Attack2_Animation_Frame);		//プレイヤの攻撃2モーション
		Se_Player_AttackSp2.Play(Player_Se);														//攻撃2のSEを再生する		
	}

	//敵の距離がプレイヤの攻撃範囲に入ったら自動的に敵に攻撃が追従する
	if (mPlayer_EnemyDis <= mPlayer_Attack_Dis) {
		mPlayer_MoveDirKeep = mPlayer_MoveDir;							  //MoveDir保存
		mPlayer_MoveDir = CXEnemyManager::GetInstance()->GetTargetEnemy();//敵のリストに入っている敵の位置を代入
	}


	//ヒット判定発生
	//アニメーションが終了していないかつ、そのアニメーションが攻撃2であれば、処理を実行する
	if (IsAnimationFinished() == false && mAnimationIndex == Player_Animation_No_Attack2) {

		//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
		if (mAnimationFrame <= Player_Attack_InReception)
		{
			mPlayer_IsHit = false; //ヒット判定終了
		}
		//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
		else {
			mPlayer_IsHit = true; //ヒット判定を発生させる
		}
		//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
		if (mAnimationFrame > Player_Attack_OutReception)
		{
			mPlayer_IsHit = false; //ヒット判定終了
		}
	}

	//左クリックされた場合
	//攻撃2のアニメーションかつ、、入力制限時間内でクリックされれば実行する
	if (CKey::Once(VK_LBUTTON)) {
		if (mAnimationIndex == Player_Animation_No_Attack2) {
			if (mAnimationFrame < Player_Push_Reception) {
				//攻撃1モーションへ移行
				mPlayer_State = EATTACK_1;						
			}
		}
	}
	//移動状態へ移行
	if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	//アニメーション終了時
	//攻撃2と待機状態の間のアニメーションを描画する
	if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack2) {
		ChangeAnimation(Player_Animation_No_Attack2_Idle, false, Player_Attack2_Idle_Animation_Frame);
	}	
	//攻撃2と待機状態の間のアニメーションを描画が終了時
	//待機状態へ移行
	if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack2_Idle) {
			mPlayer_IsHit = false;								//ヒット判定終了
			mPlayer_State = EIDLE;								//待機状態へ移行
	}
}

//ノックバック処理
void CXPlayer::KnockBack()
{
	//ノックバックのアニメーション
	ChangeAnimation(Player_Animation_No_Knockback, false, Player_KnockBack_Animation_Frame);	//ノックバックアニメーション
	mPlayer_AttackFlag_1 = false;																//プレイヤの攻撃1フラグをfalseにする
	//アニメーションが描画時
	//プレイヤの攻撃判定を停止する
	if (IsAnimationFinished() == true)
	{
		mPlayer_IsHit = false;			//プレイヤの攻撃判定フラグをfalse	
	}
	//アニメーションの描画が終了した場合
	//当たり判定のフラグをtrueにし、当たり判定を停止
	if (mPlayer_Flag == false)
	{
		mPlayer_Flag = true;			//当たり判定を停止する
	}

		//左クリックで攻撃1へ移行
		if (CKey::Once(VK_LBUTTON)) {
			mPlayer_State = EATTACK_1;		//攻撃1状態へ移行
			mPlayer_InvincibleFlag = false; //無敵状態を終了する
		}
		else if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
			mPlayer_State = EAVOIDANCE;		//回避状態へ移行
			mPlayer_InvincibleFlag = false; //無敵状態を終了する
		}
		else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
			mPlayer_State = EAVOIDANCE;		//回避状態へ移行
			mPlayer_InvincibleFlag = false; //無敵状態を終了する
		}
		else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
			mPlayer_State = EAVOIDANCE;		//回避状態へ移行
			mPlayer_InvincibleFlag = false; //無敵状態を終了する
		}
		else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {

			mPlayer_State = EAVOIDANCE;		//回避状態へ移行
			mPlayer_InvincibleFlag = false; //無敵状態を終了する
		}

	//アニメーション終了時
	if (IsAnimationFinished()){
		mPlayer_State = EIDLE;			//待機状態へ移行
		mPlayer_Flag = false;			//フラグをfalseにする
		mPlayer_InvincibleFlag = false; //無敵状態を終了する
	}
}

//死亡処理
void CXPlayer::Death()
{
	//移動計算処理
	MovingCalculation();
	//死亡状態SEを再生
	Se_Player_Death.Play(Player_Se);
	//死亡状態のアニメーションを再生する
	ChangeAnimation(Player_Animation_No_Death, false, Player_Death_Animation_Frame);	//死亡アニメーション
}

//カメラを基準にした移動処理
void CXPlayer::MoveCamera()
{
	//カメラ視点移動　通称無双移動
	//カメラの左右と前後のベクトルを取得
	mPlayer_SideVec = Camera.GetMat().GetXVec();
	mPlayer_FrontVec = Camera.GetMat().GetZVec();
	//高さ移動はカットする
	mPlayer_SideVec.Y(PLAYER_FLOAT_INITIALIZATION);
	mPlayer_FrontVec.Y(PLAYER_FLOAT_INITIALIZATION);
	//正規化する
	mPlayer_SideVec.Normalize();
	mPlayer_FrontVec.Normalize();

	//移動状態時の場合
	//移動量を代入
	if (mPlayer_State == EMOVE) {
		if (CKey::Push(VK_A)) {
			mPlayer_MoveDir -= mPlayer_SideVec;
		}
		else if (CKey::Push(VK_D)) {
			mPlayer_MoveDir += mPlayer_SideVec;
		}
		if (CKey::Push(VK_W)) {
			mPlayer_MoveDir += mPlayer_FrontVec;
		}
		else if (CKey::Push(VK_S)) {
			mPlayer_MoveDir -= mPlayer_FrontVec;
		}
		//ジャンプ時などはY軸を正規化しないよう注意
		mPlayer_MoveDir = mPlayer_MoveDir.Normalize();
		mPlayer_MoveDirKeep = mPlayer_MoveDir;	//MoveDir保存
		mPlayer_Move = mPlayer_MoveDir * mPlayer_Speed;	//移動量を設定
	}
	//回避状態の場合
	//移動量を代入
	else if (mPlayer_State == EAVOIDANCE)
	{
		if (CKey::Push(VK_A)) {
			mPlayer_MoveDir -= mPlayer_SideVec;
		}
		else if (CKey::Push(VK_D)) {
			mPlayer_MoveDir += mPlayer_SideVec;
		}
		if (CKey::Push(VK_W)) {
			mPlayer_MoveDir += mPlayer_FrontVec;
		}
		else if (CKey::Push(VK_S)) {
			mPlayer_MoveDir -= mPlayer_FrontVec;
		}
		//ジャンプ時などはY軸を正規化しないよう注意
		mPlayer_MoveDir = mPlayer_MoveDir.Normalize();//移動量の代入
		mPlayer_MoveDirKeep = mPlayer_MoveDir;	      //MoveDir保存
	}
	//移動状態でも回避状態でもない場合
	else {
		//ジャンプ時などはY軸を正規化しないよう注意
		mPlayer_MoveDir = mPlayer_MoveDir.Normalize();//移動量の代入
		mPlayer_MoveDirKeep = mPlayer_MoveDir;		  //MoveDir保存
	}
}

//2D描画
void CXPlayer::Render2D()
{
	//2D描画開始
	CUtil::Start2D(WINDOW_FIRST_WIDTH, WINDOW_WIDTH, WINDOW_FIRST_HEIGHT, WINDOW_HEIGHT);
	//ゲージを揺らす用
	int shakeX = PLAYER_INT_INITIALIZATION;
	int shakeY = PLAYER_INT_INITIALIZATION;
	//ノックバック状態のとき
	if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EKNOCKBACK) {
		//ゲージを揺らす値を設定
		shakeX = mPlayer_Gauge_Hp_Shake_X + rand() % mPlayer_Gauge_Hp_Shake_Range_X;
		shakeY = mPlayer_Gauge_Hp_Shake_Y + rand() % mPlayer_Gauge_Hp_Shake_Range_Y;
	}
	//体力ゲージ
	float HpRate = (float)mPlayer_Hp / (float)mPlayer_Hp_Max;	//体力最大値に対する、現在の体力の割合
	float HpGaugeWid = PLAYER_GAUGE_WID_MAX * HpRate;	//体力ゲージの幅
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より大きい時
	if (mPlayer_FollowGaugeWid > HpGaugeWid) {
		//線形補間で被ダメージ分後追いするゲージの幅を設定する
		mPlayer_FollowGaugeWid = Camera.mHpLerp(mPlayer_FollowGaugeWid, HpGaugeWid, mPlayer_Gauge_Hp_Rate);
	}
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より小さいとき
	else if (mPlayer_FollowGaugeWid < HpGaugeWid) {
		//被ダメージ分後追いするゲージの幅に体力ゲージの幅を設定する
		mPlayer_FollowGaugeWid = HpGaugeWid;
	}
	//プレイヤのHPがゲームオーバーの条件HPと同じになってしまった場合
	if(mPlayer_Hp >= Player_GameOver_Hp){
		//HP赤ゲージ
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + mPlayer_FollowGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_FIRST_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
		//HP緑ゲージ
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + HpGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_FIRST_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
		//プレイヤのHPフレーム
		gPlayer_Ui_Hp_Frame.Draw(PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_RIGHT, PLAYER_GAUGE_FRAME_BOTTOM, PLAYER_GAUGE_FRAME_TOP, PLAYER_GAUGE_FRAME_TEX_FIRST_WID, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
	}
	//2Dの描画終了
	CUtil::End2D();
}


//プレイヤの当たり判定
void CXPlayer::Collision(CCollider* m, CCollider* o) {
	//相手の親が自分の時はリターン
	if (o->Parent() == this)return;
	//自身のコライダタイプの判定
	switch (m->CCollider::Type()) {
	case CCollider::ESPHERE: {//球コライダ
		//相手のコライダが球コライダの時
		if (o->CCollider::Type() == CCollider::ESPHERE) {
			//球の衝突判定
			if (CCollider::Collision(m, o)) {
				//相手の親のタグがプレイヤー
				if (o->Parent()->Tag() == CCharacter::ETag::EENEMY)
				{
					if (m->CCollider::Tag() == CCollider::EBODY) {
						//相手のコライダのタグが右手
						if (o->CCollider::Tag() == CCollider::ERIGHTARM)
						{
							if (((CXEnemy*)(o->Parent()))->GetState() != CXEnemy::EEnemyState::EATTACK_2) {
								//プレイヤーが無敵状態ではないとき
								if (mPlayer_InvincibleFlag == false)
								{
									//親のポインタが敵かつ、攻撃状態であれば
									if (((CXEnemy*)(o->Parent()))->GetIsHit() == true)
									{
										//敵の攻撃判定を停止する
										((CXEnemy*)(o->Parent()))->SetIsHit(false);
										//ダメージ計算処理
										mDamage = CXEnemy::GetInstance()->GetIsAttackPoint() * (CXEnemy::GetInstance()->GetIsAttackPoint() / mDefense_Point) + (CXEnemy::GetInstance()->GetIsAttackPoint() * Player_Damage_Magnification);
										//プレイヤのHPが減算
										mPlayer_Hp = mPlayer_Hp - mDamage;
										//プレイヤを無敵状態にする
										mPlayer_InvincibleFlag = true;
										mPlayer_IsHit = false;		//ヒット判定終了
										//プレイヤ被弾時のSEを再生
										Se_Enemy_AttackSp.Play(Player_Damage_Se);
										//ノックバック状態へ移行
										mPlayer_State = EKNOCKBACK;
										//スタン蓄積値が上限を超えていれば
										//ノックバックし、蓄積したスタン値を初期化する
										if (Player_StanAccumulation_Max < mStanAccumulation)
										{
											//スタン蓄積値の初期化
											mStanAccumulation = Player_StanAccumulation;
										}
										//スタン蓄積値が上限を超えていなければ
										//ノックバックせず、プレイヤのスタン蓄積値は、敵の攻撃スタン値を参照し蓄積する
										else {
											//スタンダメージを参照
											mStan_Damage = CXEnemy::GetInstance()->GetIsStanPoint() * (CXEnemy::GetInstance()->GetIsStanPoint() / mDefense_Point);
											//スタンダメージをスタン蓄積値に蓄積させる
											mStanAccumulation = mStanAccumulation + mStan_Damage;
										}
									}

								}
							}
						}
						//コライダのポインタが左手であれば
						else if (o->CCollider::Tag() == CCollider::ELEFTARM)
						{
							//ポインタが敵かつ、攻撃1の状態で
							if (((CXEnemy*)(o->Parent()))->GetState() != CXEnemy::EEnemyState::EATTACK_1) {
								//プレイヤーが無敵状態ではないとき
								if (mPlayer_InvincibleFlag == false)
								{
									//親のポインタが敵かつ、攻撃状態であれば
									if (((CXEnemy*)(o->Parent()))->GetIsHit() == true)
									{
										//敵の攻撃判定を停止する
										((CXEnemy*)(o->Parent()))->SetIsHit(false);
										//ダメージ計算処理
										mDamage = CXEnemy::GetInstance()->GetIsAttackPoint() * (CXEnemy::GetInstance()->GetIsAttackPoint() / mDefense_Point) + (CXEnemy::GetInstance()->GetIsAttackPoint() * Player_Damage_Magnification);
										//プレイヤのHPが減算
										mPlayer_Hp = mPlayer_Hp - mDamage;
										//プレイヤを無敵状態にする
										mPlayer_InvincibleFlag = true;
										mPlayer_IsHit = false;		//ヒット判定終了
										//プレイヤ被弾時のSEを再生
										Se_Enemy_AttackSp.Play(Player_Damage_Se);
										//ノックバック状態へ移行
										mPlayer_State = EKNOCKBACK;
										//スタン蓄積値が上限を超えていれば
										//ノックバックし、蓄積したスタン値を初期化する
										if (Player_StanAccumulation_Max < mStanAccumulation)
										{
											//スタン蓄積値の初期化
											mStanAccumulation = Player_StanAccumulation;
										}
										//スタン蓄積値が上限を超えていなければ
										//ノックバックせず、プレイヤのスタン蓄積値は、敵の攻撃スタン値を参照し蓄積する
										else {
											//スタンダメージを参照
											mStan_Damage = CXEnemy::GetInstance()->GetIsStanPoint() * (CXEnemy::GetInstance()->GetIsStanPoint() / mDefense_Point);
											//スタンダメージをスタン蓄積値に蓄積させる
											mStanAccumulation = mStanAccumulation + mStan_Damage;
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
	break;

	case CCollider::ECAPSUL: {//カプセルコライダ
		//相手のコライダがカプセルコライダの時
		if (o->Type() == CCollider::ECAPSUL) {
			CVector adjust;//調整用ベクトル
			if (CCollider::CollisionCapsule(m, o, &adjust))
			{
				//位置の更新(mPosition + adjust)
				mPosition = mPosition + adjust;
				//行列の更新
				CTransform::Update();
			}
		}
	}
	}

	if (m->Type() == CCollider::ESPHERE && o->Type() == CCollider::ETRIANGLE) {
		CVector adjust;//調整用ベクトル
		//相手の親のタグがマップ
		if (o->Parent()->Tag() == EMAP)
		{
			//自分のコライダのタグが頭or体
			if (m->Tag() == CCollider::EBODY) {
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
}
//移動計算処理
void CXPlayer::MovingCalculation() {
	//減速させる
	mPlayer_Move = mPlayer_Move * Player_Thrust;							//プレイヤの移動量に推力を掛ける
	//重力をプレイヤに掛ける
	mPosition.Y(mPosition.Y() * Player_Gravity);							//プレイヤのY軸に重力を掛ける
	//座標移動
	mPosition += mPlayer_Move;												//プレイヤの位置にプレイヤの移動量を足す

	//普通に3次元ベクトル計算で算出したほうが正確だが計算量を懸念する場合は擬似計算で軽量化
	//擬似ベクトル計算
	CVector ChackVec; //チェック用ベクトル
	//回避状態のとき
	if (mPlayer_State == EAVOIDANCE) {
		ChackVec = mPlayer_MoveDirKeep.Normalize(); //保存された移動時の方向ベクトルを代入
	}
	else {
		ChackVec = mPlayer_MoveDir.Normalize(); //移動時の方向ベクトルを代入
	}
	//プレイヤの回転値をチェック
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / Player_Trun_Set));

	//回転速度　degreeに直す
	mPlayer_Turnspeed = (Player_Trun_Set / M_PI) * Player_Trun_Speeds_Set;

	//急な振り返りを抑制
	if (tCheck.turn > Player_Trun_Check_Speeds_Set) tCheck.turn = Player_Trun_Check_Speeds_Set;

	//移動方向へキャラを向かせる
	if (tCheck.cross > Player_Trun_Check_Set) {
		mRotation = mRotation + CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}
	if (tCheck.cross < Player_Trun_Check_Set) {
		mRotation = mRotation - CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}

	//リセット
	mPlayer_MoveDir = CVector(0.0f, 0.0f, 0.0f);


}
//タスクに当たり判定を格納する
void CXPlayer::TaskCollision()
{
	//コライダの優先度変更
	mPlayer_ColCapsuleBody.ChangePriority();
	mPlayer_ColSphereBody.ChangePriority();
	mPlayer_ColSphereLowerBody.ChangePriority();
	mPlayer_ColSphereHead.ChangePriority();
	mPlayer_ColSphereSword.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mPlayer_ColCapsuleBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereLowerBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereHead, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereSword, COLLISIONRANGE);
}

//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayer_Instance;
}
//プレイヤのHPの取得
int CXPlayer::GetHp()
{
	return mPlayer_Hp;
}
//アニメーションフレームの取得
bool CXPlayer::GetIsAnimationFrame() {
	return mAnimationFrame;
}
//攻撃の当たり判定を取得する
bool CXPlayer::GetIsHit()
{
	return mPlayer_IsHit; //攻撃の当たり判定を返す
}
//プレイヤの攻撃力を取得する
int CXPlayer::GetIsAttackPoint()
{
	return mAttack_Point;
}
//プレイヤのスタン値を取得する
int CXPlayer::GetIsStanPoint()
{
	return mStan_Point;
}
//プレイヤーの状態を取得する
CXPlayer::EPlayerState CXPlayer::GetState()
{
	return mPlayer_State;
}
//剣のコライダの座標を取得する
CVector CXPlayer::GetSwordColPos()
{
	return mPlayer_ColSphereSword.GetIsMatrix()->GetPos();	//剣のコライダの座標を返す
}
//移動量取得
CVector CXPlayer::GetInMoveDir()
{
	return mPlayer_Move;
}
//プレイヤの初期位置を取得
void CXPlayer::GetPos()
{
	mPosition.Set(Player_Position_X, Player_Position_Y, Player_Position_Z);								//位置を設定

}
//プレイヤのモデルの大きさを取得
void CXPlayer::GetScale()
{
	mScale.Set(Player_Scale_X, Player_Scale_Y, Player_Scale_Z);										  //スケール設定

}
//プレイヤのモデルの初期回転値を取得
void CXPlayer::GetRotation()
{
	mRotation.Set(Player_Rotation_X, Player_Rotation_Y, Player_Rotation_Z);								//回転を設定
}