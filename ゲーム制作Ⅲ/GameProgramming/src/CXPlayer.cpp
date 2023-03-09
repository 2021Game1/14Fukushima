#include"CXPlayer.h"
#include "CRes.h"

CXPlayer* CXPlayer::mpPlayer_Instance = nullptr;												//プレイヤのインスタンス変数の初期化

CXPlayer::CXPlayer()
//プレイヤの変数の初期化
	: mPlayer_ColCapsuleBody(this, nullptr, CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_TOP_Y, PLAYER_COLCAPSULE_BODY_Z), CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_BOTTOM_Y, PLAYER_COLCAPSULE_BODY_Z), PLAYER_COLCAPSULE_BODY_SIZE)
	, mPlayer_ColSphereBody(this, nullptr, CVector(), PLAYER_COLSPHERE_BODY_SIZE)
	, mPlayer_ColSphereShield(this, nullptr, CVector(PLAYER_COLSPHERE_SHIELD_X, PLAYER_COLSPHERE_SHIELD_Y, PLAYER_COLSPHERE_SHIELD_Z), PLAYER_COLSPHERE_SHIELD_SIZE)
	, mPlayer_ColSphereSword(this, nullptr, CVector(PLAYER_COLSPHERE_SWORD_HEAD_X, PLAYER_COLSPHERE_SWORD_HEAD_Y, PLAYER_COLSPHERE_SWORD_HEAD_Z), PLAYER_COLSPHERE_SWORD_SIZE)
	, mPlayer_Speed(PLAYER_SPEED_DEFAULT)
	, mPlayer_Hp(PLAYER_HP)
	, mPlayer_ComboCount(PLAYER_INT_INITIALIZATION)
	, mPlayer_Turnspeed(PLAYER_FLOAT_INITIALIZATION)
	, mPlayer_InvincibleFlag(false)
	, mPlayer_IsHit(false)
	, mPlayer_AttackFlag_1(false)
	, mPlayer_AttackFlag_2(false)
	, mPlayer_AttackFlag_3(false)
	, mPlayer_SeFlag(false)
	, mPlayer_AttackFlag_Once(false)
	, mPlayer_Flag(false)
	, mPlayer_FollowGaugeWid(PLAYER_GAUGE_WID_MAX)

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
	mPlayer_ColSphereShield.Tag(CCollider::ESHIERD);				//盾
	mPlayer_ColSphereSword.Tag(CCollider::ESWORD);					//剣
	//優先度を1に変更する
	mPriority = PLAYER_PRIORITY;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mPlayer_ColCapsuleBody.Matrix(&mpCombinedMatrix[3]);
	mPlayer_ColSphereBody.Matrix(&mpCombinedMatrix[16]);
	mPlayer_ColSphereShield.Matrix(&mpCombinedMatrix[41]);
	mPlayer_ColSphereSword.Matrix(&mpCombinedMatrix[71]);
	//プレイヤの位置,拡縮,回転の設定
	mPosition.Set(0.0f, 0.0f, 20.0);								//位置を設定
	mScale.Set(2.0f,2.0f,2.0f);										//スケール設定
	mRotation.Set(0.0f, 180.0f, 0.0f);								//回転を設定
}

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

	case EATTACK_3:													//攻撃3状態の時
		Attack_3();													//攻撃3の処理を呼ぶ
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
	if (mPlayer_Hp <= PLAYER_GAMEOVER_HP) {
		mPlayer_State = EDEATH;										//死亡状態へ移行
		mPlayer_Hp = PLAYER_GAMEOVER_HP;
	}
	if (mPlayer_EnemyDis >= PLAYER_ATTACK_DIS) {
		mPlayer_AttackDir = mPlayer_Point; //攻撃時の向きを求める
	}
	//カメラの設定
	Camera.SetTarget(mPosition);									//カメラをプレイヤの位置に設定
	//キャラクタの更新処理
	CXCharacter::Update();
}

void CXPlayer::Idle() 
{
	//左クリックで攻撃
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//WASDキーを押すと移動へ移行
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mPlayer_State = EMOVE;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else{
		mPlayer_ComboCount = PLAYER_INT_INITIALIZATION;
		ChangeAnimation(PLAYER_ANIMATION_No_IDLE, true, PLAYER_IDLE_ANIMATION_FRAME);
	}

}

//移動処理
void CXPlayer::Move()
{
	//左クリックで攻撃1へ移行
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	} 
	else if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	//WASDキーを押すと移動へ移行
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		ChangeAnimation(PLAYER_ANIMATION_No_MOVE, true, PLAYER_MOVE_ANIMATION_FRAME);
		MoveCamera();												//カメラを基準にした移動処理を呼ぶ
	}
	//待機状態へ移行
	else {
		mPlayer_State = EIDLE;
	}

	if (mPlayer_State != EMOVE) {
		CRes::GetInstance()->GetinPlayerSeWalk().Stop();
	}
}

void CXPlayer::Avoidance()
{
	ChangeAnimation(PLAYER_ANIMATION_No_AVOIDANCE, false, PLAYER_AVOIDANCE_ANIMATION_FRAME);

	//ヒット判定発生
	if (IsAnimationFinished() == false)
	{
		MoveCamera();
	}
	//アニメーション終了時
	else if (IsAnimationFinished())
	{
		//左クリックで攻撃1へ移行
		if (CKey::Once(VK_LBUTTON)) {
			mPlayer_State = EATTACK_1;
		}
		else if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		//WASDキーを押すと移動へ移行
		else if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
			mPlayer_State = EMOVE;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else {
			mPlayer_State = EIDLE;
		}
	}
	if (mPlayer_State != EAVOIDANCE) {
		CRes::GetInstance()->GetinPlayerSeWalk().Stop();
	}
}


//攻撃1処理
void CXPlayer::Attack_1()
{
	//処理が呼び出されたら1度しか動かさない
	if (mPlayer_AttackFlag_1 == false) {							
		mPlayer_AttackFlag_1 = true;															//プレイヤの攻撃1のフラグをtrueにする
		mPlayer_AttackFlag_Once = true;															//プレイヤの攻撃フラグをtrueに設定
		mPlayer_IsHit = false;																	//ヒット判定終了
		ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_1, false, PLAYER_ATTACK1_ANIMATION_FRAME);	//プレイヤの攻撃1モーション
		CRes::GetInstance()->GetinPlayerSeAttackSp1().Play(PLAYER_SE);
	}
	//アニメーションインデックスが３の時
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_3) {
		//ヒット判定発生
		if (IsAnimationFinished() == false)
		{
			mPlayer_MoveDirKeep = mPlayer_AttackDir;
			mPlayer_MoveDir = mPlayer_AttackDir;
			//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
			if (mAnimationFrame <= PLAYER_INRECEPTION)
			{
				mPlayer_IsHit = false; //ヒット判定終了
			}
			//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
			else {
				mPlayer_IsHit = true;
			}
			//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
			if (mAnimationFrame > PLAYER_OUTRECEPTION)
			{
				mPlayer_IsHit = false; //ヒット判定終了
			}

			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//ヒット判定終了
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_1, false, PLAYER_ATTACK1_ANIMATION_FRAME);							//プレイヤの攻撃1モーション
			CRes::GetInstance()->GetinPlayerSeAttackSp1().Play(PLAYER_SE);
		}
	}
	//アニメーションインデックスが１の時
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_1)
	{
		//ヒット判定発生
		if (IsAnimationFinished() == false)
		{
			mPlayer_MoveDirKeep = mPlayer_AttackDir;
			mPlayer_MoveDir = mPlayer_AttackDir;
			if (CXEnemy::EEnemyState::EKNOCKBACK && CXEnemy::EEnemyState::EIDLE)
			{
				mPlayer_IsHit = false;
			}
			else {
				mPlayer_IsHit = true;
			}
			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{	
			mPlayer_IsHit = false;								//ヒット判定終了
		}
		//アニメーションのフレームが受付時間より小さい間
		if (mAnimationFrame < PLAYER_RECEPTION) {
			//左クリックされた場合
			if (CKey::Once(VK_LBUTTON)) {
				mPlayer_State = EATTACK_2;							//攻撃2モーションへ移行
			}
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
	mPlayer_State = EIDLE;											//待機状態へ移行
	mPlayer_AttackFlag_1 = false;									//プレイヤの攻撃1フラグをfalseにする
	}
}

//攻撃2処理
void CXPlayer::Attack_2()
{
	//処理が呼び出されたら1度しか動かさない
	if (mPlayer_AttackFlag_2 == false) {
		mPlayer_AttackFlag_2 = true;								//プレイヤの攻撃2のフラグをtrueにする
		mPlayer_AttackFlag_Once = true;								//プレイヤの攻撃フラグをtrueに設定
	}
	//アニメーションインデックスが1の時
	if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_1)
	{
		//ヒット判定発生
		if (IsAnimationFinished() == false) 
		{
			mPlayer_MoveDirKeep = mPlayer_AttackDir;
			mPlayer_MoveDir = mPlayer_AttackDir;
			//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
			if (mAnimationFrame <= PLAYER_INRECEPTION)
			{
				mPlayer_IsHit = false; //ヒット判定終了
			}
			//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
			else {
				mPlayer_IsHit = true;
			}
			//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
			if (mAnimationFrame > PLAYER_OUTRECEPTION)
			{
				mPlayer_IsHit = false; //ヒット判定終了
			}
			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
		}
		//アニメーション終了時
		else if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//ヒット判定終了
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_2, false, PLAYER_ATTACK2_ANIMATION_FRAME);							//プレイヤの攻撃2モーション
			CRes::GetInstance()->GetinPlayerSeAttackSp2().Play(PLAYER_SE);
		}
	}
	//アニメーションインデックスが2の時
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_2)
	{
		//アニメーションのフレームが受付時間より小さい間
		if (mAnimationFrame < PLAYER_RECEPTION) {
			//左クリックされた場合
			if (CKey::Once(VK_LBUTTON)) {
				mPlayer_State = EATTACK_3;							//攻撃3モーションへ移行
			}
		}
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
	mPlayer_State = EIDLE;											//待機状態へ移行
	mPlayer_AttackFlag_2 = false;									//プレイヤの攻撃2フラグをfalseにする
	}
}

//攻撃3処理
void CXPlayer::Attack_3()
{
	//処理が呼び出されたら1度しか動かさない
	if (mPlayer_AttackFlag_3 == false) {
		mPlayer_AttackFlag_3 = true;								//プレイヤの攻撃2のフラグをtrueにする								
		mPlayer_AttackFlag_Once = true;								//プレイヤの攻撃フラグをtrueに設定
	}
	if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_2)
	{
		//ヒット判定発生
		if (IsAnimationFinished() == false) 
		{
			mPlayer_MoveDirKeep = mPlayer_AttackDir;
			mPlayer_MoveDir = mPlayer_AttackDir;
			//アニメーションフレームの当たり判定が受付外の時は、当たり判定をfalseにする
			if (mAnimationFrame <= PLAYER_INRECEPTION)
			{
				mPlayer_IsHit = false; //ヒット判定終了
			}
			//アニメーションフレームの当たり判定が受付時間のため、当たり判定をtrueにする
			else {
				mPlayer_IsHit = true;
			}
			//アニメーションフレームが当たり判定の終了の時は、当たり判定をfalseにする
			if (mAnimationFrame > PLAYER_OUTRECEPTION)
			{
				mPlayer_IsHit = false; //ヒット判定終了
			}
			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//ヒット判定終了
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_3, false, PLAYER_ATTACK3_ANIMATION_FRAME);
			CRes::GetInstance()->GetinPlayerSeAttackSp3().Play(PLAYER_SE);
		}
	}
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_3)
	{
		if (mAnimationFrame < PLAYER_RECEPTION) 
		{
			//左クリックされた場合
			if (CKey::Once(VK_LBUTTON)) 
			{
				mPlayer_State = EATTACK_1;							//攻撃1モーションへ移行
			}
		}
	}

	if (IsAnimationFinished())
	{
		mPlayer_State = EIDLE;											//待機状態へ移行
		mPlayer_AttackFlag_3 = false;									//プレイヤの攻撃3のフラグをfalseに設定
	}
}
//ノックバック処理
void CXPlayer::KnockBack()
{
	ChangeAnimation(PLAYER_ANIMATION_No_KNOCKBACK, false, PLAYER_KNOCKBACK_ANIMATION_FRAME);	//のけ反りアニメーション

	if (IsAnimationFinished() == true)
	{
		mPlayer_IsHit = false;
	}
		if (mPlayer_Flag == false)
		{
			mPlayer_Flag = true;
			if (CXEnemy::EEnemyState::EATTACK_1)
			{
				mPlayer_Hp = mPlayer_Hp - PLAYER_DAMAGE_ENEMYSP1;
			}
			else if (CXEnemy::EEnemyState::EATTACK_2)
			{
				mPlayer_Hp = mPlayer_Hp - PLAYER_DAMAGE_ENEMYSP2;
			}
			else if (CXEnemy::EEnemyState::EATTACK_3)
			{
				mPlayer_Hp = mPlayer_Hp - PLAYER_DAMAGE_ENEMYSP3;
			}
		}


	if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //無敵状態を終了する
		//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //無敵状態を終了する
		//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //無敵状態を終了する
		//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //無敵状態を終了する
		//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	//アニメーション終了時
	if (IsAnimationFinished())
	{
		//左クリックで攻撃1へ移行
		if (CKey::Once(VK_LBUTTON)) {
			mPlayer_State = EATTACK_1;
		}
		else if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		//WASDキーを押すと移動へ移行
		else if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
			mPlayer_State = EMOVE;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else {
			mPlayer_State = EIDLE;
		}
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //無敵状態を終了する
	}
}

//死亡処理
void CXPlayer::Death()
{
	MovingCalculation();
	ChangeAnimation(PLAYER_ANIMATION_No_DEATH, false, PLAYER_DEATH_ANIMATION_FRAME);	//死亡アニメーション
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

	if (CKey::Push(VK_A))
	{
		mPlayer_MoveDir -= mPlayer_SideVec;
	}
	else if (CKey::Push(VK_D))
	{
		mPlayer_MoveDir += mPlayer_SideVec;
	}
	if (CKey::Push(VK_W))
	{
		mPlayer_MoveDir += mPlayer_FrontVec;
	}
	else if (CKey::Push(VK_S))
	{
		mPlayer_MoveDir -= mPlayer_FrontVec;
	}
	//ジャンプ時などはY軸を正規化しないよう注意
	mPlayer_MoveDir = mPlayer_MoveDir;
	mPlayer_MoveDirKeep = mPlayer_MoveDir;	//MoveDir保存
	mPlayer_Move = mPlayer_MoveDir * mPlayer_Speed;	//移動量を設定
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
		shakeX = PLAYER_GAUGE_HP_SHAKE_X + rand() % PLAYER_GAUGE_HP_SHAKE_RANGE_X;
		shakeY = PLAYER_GAUGE_HP_SHAKE_Y + rand() % PLAYER_GAUGE_HP_SHAKE_RANGE_Y;
	}
	//体力ゲージ
	float HpRate = (float)mPlayer_Hp / (float)PLAYER_HP_MAX;	//体力最大値に対する、現在の体力の割合
	float HpGaugeWid = PLAYER_GAUGE_WID_MAX * HpRate;	//体力ゲージの幅
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より大きい時
	if (mPlayer_FollowGaugeWid > HpGaugeWid) {
		//線形補間で被ダメージ分後追いするゲージの幅を設定する
		mPlayer_FollowGaugeWid = Camera.mHpLerp(mPlayer_FollowGaugeWid, HpGaugeWid, PLAYER_GAUGE_HP_RATE);
	}
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より小さいとき
	else if (mPlayer_FollowGaugeWid < HpGaugeWid) {
		//被ダメージ分後追いするゲージの幅に体力ゲージの幅を設定する
		mPlayer_FollowGaugeWid = HpGaugeWid;
	}
	if(mPlayer_Hp >= PLAYER_GAMEOVER_HP)
	{
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + mPlayer_FollowGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_FIRST_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + HpGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_FIRST_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
		CRes::GetInstance()->GetInPlayerUiHpFrame().Draw(PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_RIGHT, PLAYER_GAUGE_FRAME_BOTTOM, PLAYER_GAUGE_FRAME_TOP, PLAYER_GAUGE_FRAME_TEX_FIRST_WID, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
	}
	//2Dの描画終了
	CUtil::End2D();
}



void CXPlayer::Collision(CCollider* m, CCollider* o) {
	//相手の親が自分の時はリターン
	if (o->Parent() == this)return;
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ESPHERE: {//球コライダ
		//相手のコライダが球コライダの時
		if (o->Type() == CCollider::ESPHERE) {
			//球の衝突判定
			if (CCollider::Collision(m, o)) {
				//相手の親のタグがプレイヤー
				if (o->Parent()->Tag() == EENEMY)
				{
					//相手のコライダのタグが右手
					if (o->Tag() == CCollider::ERIGHTARM)
					{
						//プレイヤーが無敵状態ではないとき
						if (mPlayer_InvincibleFlag == false)
						{
							if (CXEnemy::EEnemyState::EATTACK_1 || CXEnemy::EEnemyState::EATTACK_3)
							{
								if (((CXEnemy*)(o->Parent()))->GetIsHit() == true)
								{
									((CXEnemy*)(o->Parent()))->SetIsHit(false);
									mPlayer_InvincibleFlag = true;
									mPlayer_State = EKNOCKBACK;
									CRes::GetInstance()->GetinEnemySeAttackSp().Play(PLAYER_DAMAGE_SE);
								}
							}
						}
					}
					else if (o->Tag() == CCollider::ELEFTARM)
					{
						//プレイヤーが無敵状態ではないとき
						if (mPlayer_InvincibleFlag == false)
						{
							if (CXEnemy::EEnemyState::EATTACK_2)
							{
								if (((CXEnemy*)(o->Parent()))->GetIsHit() == true)
								{
									((CXEnemy*)(o->Parent()))->SetIsHit(false);
									mPlayer_InvincibleFlag = true;
									mPlayer_State = EKNOCKBACK;
									CRes::GetInstance()->GetinEnemySeAttackSp().Play(PLAYER_DAMAGE_SE);
								}
							}
						}
					}
				}
			}
		}
		break;
	}

	case CCollider::ECAPSUL: {//カプセルコライダ
		//相手のコライダがカプセルコライダの時
		if (o->Type() == CCollider::ECAPSUL) {
			CVector adjust;//調整用ベクトル
			if (!mPlayer_Hp <= PLAYER_GAMEOVER_HP) {
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
}
void CXPlayer::MovingCalculation() {
	//プレイヤーまでの距離を求める
	mPlayer_EnemyDis = mPlayer_Point.Length();
	//座標移動
	mPosition += mPlayer_Move;												//プレイヤの位置にプレイヤの移動量を足す
	//減速させる
	mPlayer_Move = mPlayer_Move * PLAYER_THRUST;							//プレイヤの移動量に推力を掛ける
	//重力をプレイヤに掛ける
	mPosition.Y(mPosition.Y() * PLAYER_GRAVITY);							//プレイヤのY軸に重力を掛ける

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
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / PLAYER_TURN_SET));

	//回転速度　degreeに直す
	mPlayer_Turnspeed = (PLAYER_TURN_SET / M_PI) * PLAYER_TURN_SPEEDS_SET;

	//急な振り返りを抑制
	if (tCheck.turn > PLAYER_TRUN_CHECK_SPEEDS_SET) tCheck.turn = PLAYER_TRUN_CHECK_SPEEDS_SET;

	//移動方向へキャラを向かせる
	if (tCheck.cross > PLAYER_TRUN_CHECK_SET) {
		mRotation = mRotation + CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}
	if (tCheck.cross < PLAYER_TRUN_CHECK_SET){
		mRotation = mRotation - CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}
	//リセット
	mPlayer_MoveDir = CVector(0.0f, 0.0f, 0.0f);
}
void CXPlayer::TaskCollision()
{
	//コライダの優先度変更
	mPlayer_ColCapsuleBody.ChangePriority();
	mPlayer_ColSphereBody.ChangePriority();
	mPlayer_ColSphereShield.ChangePriority();
	mPlayer_ColSphereSword.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mPlayer_ColCapsuleBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereShield, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereSword, COLLISIONRANGE);
}

//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayer_Instance;
}
//プレイヤのHPの取得
bool CXPlayer::GetHp()
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
