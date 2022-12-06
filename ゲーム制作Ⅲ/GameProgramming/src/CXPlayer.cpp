#include"CXPlayer.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CCamera.h"
#include"CRes.h"

//プレイヤのパラメータマクロ
#define PLAYER_SPEED_DEFAULT 0.5f																//スピード(通常時)
#define PLAYER_GRAVITY 0.9f																		//重力
#define PLAYER_THRUST 0.01																		//推力
#define PLAYER_RECEPTION 120																	//入力の受付時間
#define PLAYER_INRECEPTION 30																	//入力の当たり判定の受付時間
#define PLAYER_HP_MAX 100;																		//HPの最大値
#define PLAYER_INITIALIZATION 0																	//初期化
//プレイヤのHPフレーム,HPゲージ座標,幅,高さ
#define PLAYER_GAUGE_FRAME_TEX_WID 480	//ゲージ枠の画像の幅
#define PLAYER_GAUGE_FRAME_TEX_HEI 80	//ゲージ枠の画像の高さ
#define PLAYER_GAUGE_FRAME_LEFT 0	//ゲージ枠左座標
#define PLAYER_GAUGE_FRAME_RIGHT 400 //ゲージ枠右座標
#define PLAYER_GAUGE_FRAME_TOP PLAYER_GAUGE_FRAME_TEX_HEI //ゲージ枠上座標
#define PLAYER_GAUGE_FRAME_BOTTOM (PLAYER_GAUGE_FRAME_TOP-PLAYER_GAUGE_FRAME_TEX_HEI) //ゲージ枠下座標
#define PLAYER_GAUGE_LEFT -80	//ゲージ描画時の左座標
#define PLAYER_GAUGE_WID_MAX 480	//ゲージの幅の最大値
#define GAUGE_HEIGHT 20 //ゲージ描画時の高さ
#define PLAYER_GAUGE_HP_TOP 30 //HPゲージ描画時の上座標
#define PLAYER_GAUGE_HP_BOTTOM (PLAYER_GAUGE_HP_TOP-GAUGE_HEIGHT) //HPゲージ描画時の下座標


CXPlayer* CXPlayer::mpPlayer_Instance = nullptr;												//プレイヤのインスタンス変数の初期化




CXPlayer::CXPlayer()
//プレイヤの変数の初期化
	:mPlayer_ColSphereBody(this, nullptr, CVector(0.0f, 80.0f, 0.0f), CVector(0.0f, -80.0f, 0.0f), 0.7)
	, mPlayer_ColSphereShield(this, nullptr, CVector(0.0f, 0.0f, -5.0f), CVector(0.0f, 0.0f, 0.0f), 0.5f)
	, mPlayer_ColSphereSword(this, nullptr, CVector(-13.0f, 0.0f, 90.0f), CVector(0.0f, 0.0f, 10.0f), 0.3f)
	, mPlayer_Speed(PLAYER_SPEED_DEFAULT)
	, mPlayer_Hp(100)
	, mPlayer_ComboCount(0)
	, mPlayer_Turnspeed(0.0f)
	, mPlayer_IsHit(false)
	, mPlayer_AttackFlag_1(false)
	, mPlayer_AttackFlag_2(false)
	, mPlayer_AttackFlag_3(false)
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
	mPlayer_ColSphereBody.Tag(CCollider::EBODY);					//体
	mPlayer_ColSphereShield.Tag(CCollider::ESHIERD);				//盾
	mPlayer_ColSphereSword.Tag(CCollider::ESWORD);					//剣
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mPlayer_ColSphereBody.Matrix(&mpCombinedMatrix[14]);
	mPlayer_ColSphereShield.Matrix(&mpCombinedMatrix[41]);
	mPlayer_ColSphereSword.Matrix(&mpCombinedMatrix[71]);
	//プレイヤの位置,拡縮,回転の設定
	mPosition.Set(0.0f, 0.0f, 0.0);									//位置を設定
	mScale.Set(2.0f,2.0f,2.0f);										//スケール設定
	mRotation.Set(0.0f, 180.0f, 0.0f);								//回転を設定
}

void CXPlayer::Update() {
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

	case EGUARD:													//回避状態
		Guard();													//回避処理を呼ぶ
		break;

	case EDEATH:													//死亡状態
		Death();													//死亡処理を呼ぶ
		break;

	case EKNOCKBACK:												//ノックバック状態
		KnockBack();												//ノックバック処理を呼ぶ
		break;
	}
	//座標移動
	mPosition += mPlayer_Move;										//プレイヤの位置にプレイヤの移動量を足す
	//減速させる
	mPlayer_Move = mPlayer_Move * PLAYER_THRUST;							//プレイヤの移動量に推力を掛ける
	//重力をプレイヤに掛ける
	mPosition.Y(mPosition.Y() * PLAYER_GRAVITY);							//プレイヤのY軸に重力を掛ける

	//普通に3次元ベクトル計算で算出したほうが正確だが計算量を懸念する場合は擬似計算で軽量化
	//擬似ベクトル計算
	CVector ChackVec;												//チェック用ベクトル
	ChackVec = mPlayer_MoveDirKeep.Normalize();						//保存された移動時の方向ベクトルを代入
	ChackVec = mPlayer_MoveDir.Normalize();							//移動時の方向ベクトルを代入
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / 180.0f));

	//回転速度　degreeに直す
	mPlayer_Turnspeed = (180.0f / M_PI) * 0.3f;

	//急な振り返りを抑制
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//移動方向へキャラを向かせる
	if (tCheck.cross > 0.0f) {
		mRotation = mRotation + CVector(0.0f,tCheck.turn * mPlayer_Turnspeed,0.0f);
	}
	if (tCheck.cross < 0.0f) {
		mRotation = mRotation - CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}

	//リセット
	mPlayer_MoveDir = CVector(0.0f, 0.0f, 0.0f);

	//体力が0になると死亡
	if (mPlayer_Hp <= 0) {
		mPlayer_State = EDEATH;										//死亡状態へ移行
		mPlayer_Hp = 0;
	}
	//カメラの設定
	Camera.SetTarget(mPosition);									//カメラをプレイヤの位置に設定
	//キャラクタの更新処理
	CXCharacter::Update();

}

void CXPlayer::Idle() 
{
	mPlayer_ComboCount = 0;
	ChangeAnimation(6, true, 20);
	//左クリックで攻撃
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//WASDキーを押すと移動へ移行
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mPlayer_State = EMOVE;
	}
	else if (CKey::Once(VK_SPACE)) {
		mPlayer_State = EGUARD;
	}
}

//移動処理
void CXPlayer::Move()
{
	//左クリックで攻撃1へ移行
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//スペースでガードへ移行
	else if (CKey::Once(VK_SPACE)) {
		mPlayer_State = EGUARD;
	}
	//WASDキーを押すと移動
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		MoveCamera();												//カメラを基準にした移動処理を呼ぶ
		ChangeAnimation(0, true, 20);
	}
	//待機状態へ移行
	else {
		mPlayer_State = EIDLE;
	}
}


//攻撃1処理
void CXPlayer::Attack_1()
{
	//処理が呼び出されたら1度しか動かさない
	if (mPlayer_AttackFlag_1 == false) {							
		mPlayer_AttackFlag_1 = true;								//プレイヤの攻撃1のフラグをtrueにする
		mPlayer_AttackFlag_Once = true;								//プレイヤの攻撃フラグをtrueに設定
		ChangeAnimation(5, false, 1);								//待機モーション
	}
	//アニメーションインデックスが５の時
	if (mAnimationIndex == 5)
	{
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//ヒット判定終了
			ChangeAnimation(1, false, 30);							//プレイヤの攻撃1モーション
		}
	}
	//アニメーションインデックスが３の時
	else if (mAnimationIndex == 3) {
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
				mPlayer_IsHit = true;									//プレイヤーのヒット判定をtrueにする
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//ヒット判定終了
			ChangeAnimation(1, false, 30);							//プレイヤの攻撃1モーション
		}
	}
	//アニメーションインデックスが１の時
	else if (mAnimationIndex == 1)
	{
		//ヒット判定発生
		if (IsAnimationFinished() == false) 
		{
			if (mAnimationFrame > PLAYER_INRECEPTION) {
				mPlayer_IsHit = true;									//ヒット判定有効
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
			//スペースキーを押された場合
			else if(CKey::Once(VK_SPACE)) {
				mPlayer_State = EGUARD;								//ガードモーションへ移行
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
	if (mAnimationIndex == 1)
	{
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
				mPlayer_IsHit = true;									//ヒット判定有効
		}
		//アニメーション終了時
		else if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//ヒット判定終了
			ChangeAnimation(2, false, 60);							//プレイヤの攻撃2モーション
		}
	}
	//アニメーションインデックスが2の時
	else if (mAnimationIndex == 2)
	{
		//アニメーションのフレームが受付時間より小さい間
		if (mAnimationFrame < PLAYER_RECEPTION) {
			//左クリックされた場合
			if (CKey::Once(VK_LBUTTON)) {
				mPlayer_State = EATTACK_3;							//攻撃3モーションへ移行
			}
			//スペースキーを押された場合
			else if (CKey::Once(VK_SPACE)) {
				mPlayer_State = EGUARD;								//ガードモーションへ移行
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
	if (mAnimationIndex == 2)
	{
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
				mPlayer_IsHit = true;
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//ヒット判定終了
			ChangeAnimation(3, false, 80);
		}
	}
	else if (mAnimationIndex == 3)
	{
		if (mAnimationFrame < PLAYER_RECEPTION) {
			//左クリックされた場合
			if (CKey::Once(VK_LBUTTON)) {
				mPlayer_State = EATTACK_1;							//攻撃1モーションへ移行
			}
			//スペースキーを押された場合
			else if(CKey::Once(VK_SPACE)) {
				mPlayer_State = EGUARD;								//ガードモーションへ移行
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
	ChangeAnimation(7, false, 30);	//のけ反りアニメーション
		//アニメーション終了時
	if (IsAnimationFinished())
	{
		mPlayer_State = EIDLE; //待機状態へ移行
		mPlayer_Hp = mPlayer_Hp - 10;
	}
}
//ガード
void CXPlayer::Guard()
{
	if (mPlayer_Flag == false) {
		ChangeAnimation(6, false, 1);//待機モーション
		mPlayer_Flag = true;
	}
	
	if (mAnimationIndex == 6){
		//ヒット判定発生
		if (IsAnimationFinished() == false) {
				mPlayer_IsHit = true;
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
			if (mAnimationFrame > PLAYER_INRECEPTION) {
				mPlayer_IsHit = true;
			}
		}
		//アニメーション終了時
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false; //ヒット判定終了
			ChangeAnimation(5, false, 30);//ガードアニメーション
		}

	}
	//アニメーション終了時
	else if (IsAnimationFinished())
	{
		mPlayer_State = EIDLE;
		mPlayer_Flag = false;
	}

}

//死亡処理
void CXPlayer::Death()
{
	ChangeAnimation(8, false, 60);	//死亡アニメーション
}

//カメラを基準にした移動処理
void CXPlayer::MoveCamera()
{
	//カメラ視点移動　通称無双移動
	//カメラの左右と前後のベクトルを取得
	mPlayer_SideVec = Camera.GetMat().GetXVec();
	mPlayer_FrontVec = Camera.GetMat().GetZVec();
	//高さ移動はカットする
	mPlayer_SideVec.Y(0.0f);
	mPlayer_FrontVec.Y(0.0f);
	//正規化する
	mPlayer_SideVec.Normalize();
	mPlayer_FrontVec.Normalize();

	if (CKey::Push('A'))
	{
		mPlayer_MoveDir -= mPlayer_SideVec;
	}
	else if (CKey::Push('D'))
	{
		mPlayer_MoveDir += mPlayer_SideVec;
	}
	if (CKey::Push('W')) {
		mPlayer_MoveDir += mPlayer_FrontVec;
	}
	else if (CKey::Push('S'))
	{
		mPlayer_MoveDir -= mPlayer_FrontVec;
	}

	//ジャンプ時などはY軸を正規化しないよう注意
	mPlayer_MoveDir = mPlayer_MoveDir.Normalize();
	mPlayer_MoveDirKeep = mPlayer_MoveDir;	//MoveDir保存
	mPlayer_Move = mPlayer_MoveDir * mPlayer_Speed;	//移動量を設定
}
void CXPlayer::Render2D()
{
	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);
	//ゲージを揺らす用
	int shakeX = 0;
	int shakeY = 0;
	//ノックバック状態のとき
	if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EKNOCKBACK) {
		//ゲージを揺らす値を設定
		shakeX = -5 + rand() % 6;
		shakeY = -2 + rand() % 2;
	}
	//体力ゲージ
	float HpRate = (float)mPlayer_Hp / (float)PLAYER_HP_MAX;	//体力最大値に対する、現在の体力の割合
	float HpGaugeWid = PLAYER_GAUGE_WID_MAX * HpRate;	//体力ゲージの幅
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より大きい時
	if (mPlayer_FollowGaugeWid > HpGaugeWid) {
		//線形補間で被ダメージ分後追いするゲージの幅を設定する
		mPlayer_FollowGaugeWid = Camera.mLerp(mPlayer_FollowGaugeWid, HpGaugeWid, 0.05f);
	}
	//被ダメージ分後追いするゲージの幅が体力ゲージの幅より小さいとき
	else if (mPlayer_FollowGaugeWid < HpGaugeWid) {
		//被ダメージ分後追いするゲージの幅に体力ゲージの幅を設定する
		mPlayer_FollowGaugeWid = HpGaugeWid;
	}
	CRes::GetInstance()->GetInUiHpRedGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + mPlayer_FollowGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, 0, 480, 0, 10);
	CRes::GetInstance()->GetInUiHpGreenGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + HpGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, 0, 480, 0, 10);
	CRes::GetInstance()->GetInPlayerUiHpFrame().Draw(PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_RIGHT, PLAYER_GAUGE_FRAME_BOTTOM, PLAYER_GAUGE_FRAME_TOP, 0, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_HEI, 0);
	//2Dの描画終了
	CUtil::End2D();
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
			if (!mPlayer_Hp <= 0) {
				if (CCollider::CollisionCapsule(m, o, &adjust))
				{
					//相手のコライダのタグが手
					if (o->Tag() == CCollider::EARM) {
							if (CXEnemy::GetInstance()->GetIsHit() == true)
							{
								if (CXEnemy::GetInstance()->GetIsAnimationFrame() >= mAnimationFrame)
								{
									mPlayer_State = EKNOCKBACK;
								}
							}
					}
					else {
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
		break;
	}
	}		
}

//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayer_Instance;
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