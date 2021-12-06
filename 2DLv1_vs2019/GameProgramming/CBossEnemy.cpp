#include"CBossEnemy.h"

int CBossEnemy::CBossEnemyLife = 20;

extern CTexture Texture;

CBossEnemy::CBossEnemy()
	:mFx(0),mFy(0),mBossFireCount(0)
{
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
			for (int j = 0; j < 2; j++) {
				CBullet* BEBullet = new CBullet();
				//座標設定
				BEBullet->x = x;
				BEBullet->y = y - (h * 50 / 100);

				for (int i = 0; i < 1; i++) {
					if (CBossEnemy::x > CPlayer::spInstance->x || CBossEnemy::x < CPlayer::spInstance->x || CBossEnemy::x == CPlayer::spInstance->x) {
						BEBullet->mFx = 0;
						BEBullet->mFy = -2;
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
						BEBullet->mFx = -1;
						BEBullet->mFy = -1 * ((j / 1) + 2);
					if (CBossEnemy::y < CPlayer::spInstance->y){
						BEBullet->mFy *= -1;
						BEBullet->y += h;
					}
						//有効にする
						BEBullet->mEnabled = true;
						BEBullet->mTag = EBOSSBULLET;
						//発射間隔を60フレームにする
						break;
					}
					mBossFireCount = 30;
				}
				//移動量設定
				//敵弾数分繰り返し
				for (int i = 0; i < 1; i++) {
					if (CBossEnemy::x < CPlayer::spInstance->x) {
						BEBullet->mFx = +1;
						BEBullet->mFy = -1 * ((j / 1) + 2);
						if (CBossEnemy::y < CPlayer::spInstance->y) {
							BEBullet->mFy *= -1;
							BEBullet->y += h;
						}

						//有効にする
						BEBullet->mEnabled = true;
						BEBullet->mTag = EBOSSBULLET;
						//発射間隔を60フレームにする
						break;
					}
					mBossFireCount = 30;
				}
			}


		}
	
	if (x == 350 && y == 50) {
		//衝突していれば反転
			CBossEnemy::mFx = -2;
			CBossEnemy::mFy = 0;
	}
	if (y == 250 && x == 350)
	{
			CBossEnemy::mFy = -2;
			CBossEnemy::mFx = 0;
	}
	if (y == 50 && x == -350)
	{
			CBossEnemy::mFy = 2;
			CBossEnemy::mFx = 0;
	}
	if (x == -350 && y == 250) {
		
			CBossEnemy::mFx = 2;
			CBossEnemy::mFy = 0;
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
			CBossEnemy::CBossEnemyLife -= 1;
			if (CBossEnemy::CBossEnemyLife == 0)
			{
				//プレイヤーの弾に当たると、無効にする
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
				{
					mEnabled = false;
					r.mEnabled = false;
					CSceneGame::ScoreCount += 5000;
				}
			}
			break;

		case EPLAYER:

			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
			{
				CSceneGame::Remain -= 1;
			}
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