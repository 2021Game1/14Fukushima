//プレイヤークラスのインクルード
#include"CPlayer.h"
//キー入力クラスのインクルード
#include"CKey.h"
//タイム
#include<time.h>

extern CSound Se3;

//タスクマネージャクラスのインクルード
#include"CTaskManager.h"

#include"CSceneGame.h"

#define HP 10	//耐久値
#define ROTATION_YV CVector(0.0f,1.2f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,1.0f)//移動速度
#define MAX_VELOCITY 0.4f//最高速度
#define _VELOCITY  0.0f//初期化
#define ACCELERATION 0.001f    //加速度


CPlayer* CPlayer::spInstance = nullptr;





//デフォルトコンストラクタ
CPlayer::CPlayer()
	:mCollider(this, &mMatrix, CVector(0.0f, 1.0f, 0.0f), 0.5f),
	mHp(HP), Velocity(_VELOCITY),Acceleration(ACCELERATION)
	
{
	//テクスチャファイルの読み込み(1行64列)
	mText.LoadTexture("FontGreen.tga", 1, 64);
	//インスタンスの設定
	spInstance = this;
	mTag = EPLAYER;
}

//更新処理
void CPlayer::Update() 
{
	if (mHp <= 0) {

		mHp--;
		if (mHp % 15 == 0)
		{
			//エフェクト生成
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
	

	}
	

	if (mHp >= 0) {
		//Wキー入力で前進
		if (CKey::Push('W')) {
			//Z軸方向の値を回転させ移動させる
			if (Velocity < MAX_VELOCITY)
			{
				Velocity += Acceleration;
			}
			mPosition = mPosition + (VELOCITY * Velocity) * mMatrixRotate;
		}
		else if (!CKey::Push('S')) {
			if (Velocity > 0.001f) {
				Velocity -= Acceleration;
				mPosition = mPosition + (VELOCITY * Velocity) * mMatrixRotate;
			}
			Velocity -= Acceleration;
		}
		//Aキー入力で回転
		if (CKey::Push('A') && Velocity > _VELOCITY) {
			//Y軸の回転値を増加
			mRotation = mRotation + ROTATION_YV;

		}
		//Dキー入力で回転
		if (CKey::Push('D') && Velocity > _VELOCITY) {
			//Y軸の回転値を減少
			mRotation = mRotation - ROTATION_YV;
		}

		//Sキー入力で後退
		if (CKey::Push('S')) {
			if (Velocity > -0.1f) {
				Velocity -= Acceleration;
			}
			//Z軸方向の値を回転させ移動させる
			mPosition = mPosition + (VELOCITY * Velocity) * mMatrixRotate;

			//Aキー入力で回転
			if (CKey::Push('A') && Velocity <= _VELOCITY) {
				//Y軸の回転値を増加
				mRotation = mRotation + ROTATION_YV;

			}
			//Dキー入力で回転
			if (CKey::Push('D') && Velocity <= _VELOCITY) {
				//Y軸の回転値を減少
				mRotation = mRotation - ROTATION_YV;
			}
		}
		else if (!CKey::Push('W')) {
			if (Velocity < -0.001f) {
				Velocity += Acceleration;
				mPosition = mPosition + (VELOCITY * Velocity) * mMatrixRotate;
			}
			Velocity += Acceleration;
		}


		//Iキーでブレーキ
		if (CKey::Push('I')) {
			if (Velocity > 0.0f)
			{
				Velocity -= Acceleration + Acceleration;
				mPosition = mPosition - (VELOCITY * Acceleration) * mMatrixRotate;
			}
		}
	}

	CTransform::Update();
}


//衝突処理
void CPlayer::Collision(CCollider* m, CCollider* o) {
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
		if (o->Type() == CCollider::ESPHERE) {
			if (o->Parent()->Tag() == EENEMY && CCollider::Collision(m, o)) {
				Se3.Play(0.1);
				mHp--;//耐久値の減算
			}
		}
		break;
	}
	}

}

//衝突処理
void CPlayer::TaskCollision() 
{
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider,COLLISIONRANGE);
}
void CPlayer::Render()
{
	//親の描画処理
	CCharacter::Render();

	//2Dの描画開始
	CUtil::Start2D(-400, 400, -300, 300);
	//描画色の設定(緑色の半透明)
	glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
	//文字列編集エリアの作成
	char buf[64];
		//Y座標の表示
		//文字列の設定
		sprintf(buf, "PX:%7.2f", mPosition.X());
		//文字列の描画
		mText.DrawString(buf, 150, 30, 8, 16);

		//Y座標の表示
		//文字列の設定
		sprintf(buf, "PZ:%7.2f", mPosition.Z());
		//文字列の描画
		mText.DrawString(buf, 150, 0, 8, 16);

	//スコアの表示
	//文字列の設定
	sprintf(buf, "MONEY:%d", CSceneGame::Score);
	//文字列の描画
	mText.DrawString(buf, -350, 250, 16, 16);
	

	//2Dの描画終了
	CUtil::End2D();
}
CPlayer* CPlayer::Get() {
	return spInstance;
}