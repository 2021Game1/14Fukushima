#include"CBossEnemy.h"
#include<time.h>

int CBossEnemy::mBossEnemyLife = 15;

extern CTexture Texture;

CBossEnemy::CBossEnemy()
	:mFx(0),mFy(0),mBossFireCount(0)
{
	Hit = true;
	Count = 0;
	mEnabled = false;
	w = 50;
	h = 50;
	mTag = CRectangle::EBOSSENEMY;
}

void CBossEnemy::Update() {

	//mEnabledがfalseなら戻る
	if (!mEnabled)return;
	//有効な時
	if (mEnabled) {
		//移動
		x += mFx * 1;
		y += mFy * 1;
	}
	//60フレームに1回発射
	if (mBossFireCount > 0) {
		mBossFireCount--;
	}

	else {
		for (int j = 0; j < 1; j++) {
			CBullet* BEBullet = new CBullet();
			//座標設定
			BEBullet->x = x;
			BEBullet->y = y - (h * 50 / 100);
			BEBullet->w = 10;
			BEBullet->h = 10;
			for (int i = 0; i < 1; i++) {
				if (CBossEnemy::x == CPlayer::spInstance->x) {
					BEBullet->mFx = 0;
					BEBullet->mFy = -2;
					if (BEBullet->y == -100)
					{
						BEBullet->mFy = 2;
					}
					//有効にする
					BEBullet->mEnabled = true;
					BEBullet->mTag = EBOSSBULLET;
					//発射間隔を60フレームにする
					break;
				}
				mBossFireCount = 30;
			}
			for (int i = 0; i < 1; i++) {
				if (CBossEnemy::x > CPlayer::spInstance->x) {
					BEBullet->mFx = -3;
					BEBullet->mFy = -3;
				
					if (CBossEnemy::y < CPlayer::spInstance->y) {
					BEBullet->mFx = -3;
					BEBullet->mFy = 3;
					}
				}
				//有効にする
				BEBullet->mEnabled = true;
				BEBullet->mTag = EBOSSBULLET;
				//発射間隔を60フレームにする
				break;
			}
			mBossFireCount = 30;

			//移動量設定
			//敵弾数分繰り返し
			for (int i = 0; i < 1; i++) {
				if (CBossEnemy::x < CPlayer::spInstance->x) {
					BEBullet->mFx = +3;
					BEBullet->mFy = -3;
				
					if (CBossEnemy::y < CPlayer::spInstance->y) {
					BEBullet->mFx = 3;
					BEBullet->mFy = +3;
					}
				}
				//有効にする
				BEBullet->mEnabled = true;
				BEBullet->mTag = EBOSSBULLET;
				//発射間隔を60フレームにする
				break;

				mBossFireCount = 40;




			}
		}
	}
		if (CSceneGame::BossCount == 0)
		{

			if (CBossEnemy::y == 250 && CBossEnemy::x == 350)
			{
				CBossEnemy::mFy = -2;
				CBossEnemy::mFx = 0;
			}
			if (CBossEnemy::y == 50 && CBossEnemy::x == 350)
			{
				CBossEnemy::mFy = 0;
				CBossEnemy::mFx = -2;

			}
			if (CBossEnemy::y == 50 && CBossEnemy::x == -350)
			{
				CBossEnemy::mFy = -2;
				CBossEnemy::mFx = 0;
			}
			if (CBossEnemy::x == -350 && CBossEnemy::y == -250)
			{
				CBossEnemy::mFx = 2;
				CBossEnemy::mFy = 0;

			}
			if (CBossEnemy::x == 350 && CBossEnemy::y == -250)
			{
				CBossEnemy::mFx = 0;
				CBossEnemy::mFy = 2;
			}
			if (CBossEnemy::x == 350 && CBossEnemy::y == -50)
			{
				CBossEnemy::mFx = -2;
				CBossEnemy::mFy = 0;

			}
			if (CBossEnemy::y == -50 && CBossEnemy::x == -300)
			{
				CBossEnemy::mFx = 0;
				CBossEnemy::mFy = 2;
			}
			if (CBossEnemy::y == 250 && CBossEnemy::x == -300)
			{
				CBossEnemy::mFx = 2;
				CBossEnemy::mFy = 0;

			}
		}
		if (Count > 0 && Hit == false)
		{
			Count--;
		}
		if (Count == 0)
		{
			Hit = true;
		}
}




bool CBossEnemy::Collision(CRectangle& r) {
	//mEnabledがfalseなら戻る
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYERBULLET:
			if (Hit == true) {
				CBossEnemy::mBossEnemyLife -= 1;

				if (CBossEnemy::mBossEnemyLife == 0)
				{
					//プレイヤーの弾に当たると、無効にする
					if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
					{
						mEnabled = false;
						r.mEnabled = false;
						CSceneGame::ScoreCount += 2000;
						CSceneGame::BossCount += 1;
					}

				}
				Hit = false;
				Count = 150;
			}
			break;

		case EPLAYER:

			break;
		}
		return true;
	}
	return false;
}

void CBossEnemy::Render() {
	if (mEnabled) {
		CRectangle::Render(Texture,145,185,224,183);
	}

}

//36
void CBossEnemy::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}