//プレイヤークラスのインクルード
#include"CPlayer.h"
//キー入力クラスのインクルード
#include"CKey.h"
//タスクマネージャクラスのインクルード
#include"CTaskManager.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//回転速度
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,0.1f)//移動速度


CPlayer* CPlayer::spInstance = nullptr;

//デフォルトコンストラクタ
CPlayer::CPlayer()
	:mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f)),
	mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f)),
	mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f)),
	mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f),
	mHp(10)
{
	//テクスチャファイルの読み込み(1行64列)
	mText.LoadTexture("FontWhite.tga", 1, 64);

	//インスタンスの設定
	spInstance = this;
	mTag = EPLAYER;
}

//更新処理
void CPlayer::Update() 
{
	if (mHp >= 0)
	{
		//スペースキーを入力で弾を発射
		//スペースキーを入力で弾を発射
		if (CKey::Push(VK_SPACE)) {
			CBullet* bullet = new CBullet();
			bullet->Set(0.1f, 1.5f);
			bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
			bullet->Rotation(mRotation);
			bullet->Update();
			//TaskManager.Add(bullet);
		}
		//Dキー入力で回転
		if (CKey::Push('D')) {
			//Y軸の回転値を減少
			mRotation = mRotation - ROTATION_YV;
		}
		//Aキー入力で回転
		if (CKey::Push('A')) {
			//Y軸の回転値を増加
			mRotation = mRotation + ROTATION_YV;
		}
		//Iキー入力で前進
		if (CKey::Push('I')) {
			//Z軸方向の値を回転させ移動させる
			mPosition = mPosition + VELOCITY * mMatrixRotate;
		}
		//Sキー入力で上向き
		if (CKey::Push('S'))
		{
			//X軸の回転値を減算
			mRotation = mRotation - ROTATION_XV;
		}
		//Wキー入力で下向き
		if (CKey::Push('W'))
		{
			//X軸の回転値を加算
			mRotation = mRotation + ROTATION_XV;
		}
	}
	CTransform::Update();
	//HPが0以下の時　撃破
	if (mHp <= 0)
	{
		mHp--;
		//15フレーム毎にエフェクト
		if (mHp % 15 == 0)
		{
			//エフェクト生成
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
	}
}


//衝突処理
void CPlayer::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ELINE: {//線分コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と線分の衝突判定
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition + adjust;
			//行列の更新
			CTransform::Update();
		}
		break;
	}
	}
	switch (o->Type()) {
	case CCollider::ESPHERE: { //球コライダの時
				//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			if (mHp >= 0)
			{
				mHp--;
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
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mLine,COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
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
	if (mHp >= 0)
	{
	//Y座標の表示
	//文字列の設定
	sprintf(buf, "PY:%7.2f", mPosition.Y());
	//文字列の描画
	mText.DrawString(buf, 100, 30, 8, 16);

	//X軸回転値の表示
	//文字列の設定
	sprintf(buf, "RX:%7.2f", mRotation.X());
	//文字列の描画
	mText.DrawString(buf, 100, 0, 8, 16);

	//Y軸回転値の表示
	//文字列の設定
	sprintf(buf, "RY:%7.2f", mRotation.Y());
	//文字列の描画
	mText.DrawString(buf, 100, -100, 8, 16);
	}

	if (mHp <= 0)
	{
		//文字列の描画
		mText.DrawString("GAMEOVER", -210, 85, 30, 30);
		if (CKey::Push(VK_END)) {

		}

	}

	//2Dの描画終了
	CUtil::End2D();
}
CPlayer* CPlayer::Get() {
	return spInstance;
}