//プレイヤークラスのインクルード
#include"CPlayer.h"
//キー入力クラスのインクルード
#include"CKey.h"
//タイム
#include<time.h>

//タスクマネージャクラスのインクルード
#include"CTaskManager.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,1.0f)//移動速度



CPlayer* CPlayer::spInstance = nullptr;





//デフォルトコンストラクタ
CPlayer::CPlayer()
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f),
	mHp(10), mVelocity(0.0f),mAcceleration(0.1f),mTime(0.0f)
	
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
	if (CKey::Push(VK_SPACE)) {
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
	}
	


		//Wキー入力で前進
	if (CKey::Push('W')) {
		//Z軸方向の値を回転させ移動させる
		if (mVelocity < 0.6f)
		{
			mVelocity += mAcceleration;
		}
		mPosition = mPosition + (VELOCITY * mVelocity) * mMatrixRotate;
	}
	else{ 
		if (mVelocity > 0.0f) {
			mVelocity -= mAcceleration;
			mPosition = mPosition + (VELOCITY * mVelocity) * mMatrixRotate;
		}
	}
	//Aキー入力で回転
	if (CKey::Push('W') && CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation = mRotation  + ROTATION_YV;
	}
	//Dキー入力で回転
	if (CKey::Push('W') && CKey::Push('D')) {
		//Y軸の回転値を減少
		mRotation = mRotation - ROTATION_YV;
	}
	

		//Sキー入力で後退
		if (CKey::Push('S')) {
			if (mVelocity <= 0.0f)
			{
				//Z軸方向の値を回転させ移動させる
				mPosition = mPosition - (VELOCITY * mAcceleration) * mMatrixRotate;
			}
			//Aキー入力で回転
			if (CKey::Push('A')) {
				//Y軸の回転値を増加
				mRotation = mRotation + ROTATION_YV;
			}
			//Dキー入力で回転
			if (CKey::Push('D')) {
				//Y軸の回転値を減少
				mRotation = mRotation - ROTATION_YV;
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
		mText.DrawString(buf, 100, 30, 8, 16);

		//Y座標の表示
		//文字列の設定
		sprintf(buf, "PZ:%7.2f", mPosition.Z());
		//文字列の描画
		mText.DrawString(buf, 100, 0, 8, 16);

	

	//2Dの描画終了
	CUtil::End2D();
}
CPlayer* CPlayer::Get() {
	return spInstance;
}