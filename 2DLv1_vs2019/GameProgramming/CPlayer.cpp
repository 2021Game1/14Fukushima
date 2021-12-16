#include "CPlayer.h"
#include "CKey.h"
//37
#include "CBullet.h"

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
//プレイヤーのポインタ
CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::mPlayer = 0;

CPlayer::CPlayer()
: mFx(0.0f), mFy(1.0f)
, FireCount(0)
{
	mTag = EPLAYER;
	mEnabled = true;
	spInstance = this;
	PlayerHit = true;
	
}

void CPlayer::Update() {
	//mEnabledがfalseなら戻る
	//staticメソッドはどこからでも呼べる
	if (CSceneGame::Remain > 0)
	{
		//37
				//スペースキーで弾発射
				//0より大きいとき1減算する
		if (FireCount > 0) {
			FireCount--;
		}
		//FireContが0で、かつ、スペースキーで弾発射
		else if (CKey::Once(' ')) {
			CBullet* Bullet = new CBullet();
			//発射位置の設定
			Bullet->x = x;
			Bullet->y = y;
			Bullet->w = 10;
			Bullet->h = 10;
			//弾の発射設定
			Bullet->mFx = mFx * 5;
			Bullet->mFy = mFy * 5;
			//有効にする
			Bullet->mEnabled = true;
			//プレイヤーの弾を設定
			Bullet->mTag = CRectangle::EPLAYERBULLET;

			FireCount = 20;

		}
	}
	if (CSceneGame::EnemyCount >= 14) {
		//mEnabledがfalseなら戻る
		//staticメソッドはどこからでも呼べる
		if (CSceneGame::Remain > 0) {
			//37
			//スペースキーで弾発射
			//0より大きいとき1減算する
			if (FireCount > 0) {
				FireCount--;
			}
			//FireContが0で、かつ、スペースキーで弾発射
			if (CKey::Once(' ')) {
			CBullet* Bullet2 = new CBullet();
			//発射位置の設定
			Bullet2->x = x + 5;
			Bullet2->y = y;
			Bullet2->w = 10;
			Bullet2->h = 10;
			//弾の発射設定
			Bullet2->mFx = mFx * 5;
			Bullet2->mFy = mFy * 5;
			//有効にする
			Bullet2->mEnabled = true;
			//プレイヤーの弾を設定
			Bullet2->mTag = CRectangle::EPLAYERBULLET;
			FireCount = 10;
			}

		}
	}


					if (CKey::Push('A')) {
						if (CSceneGame::EnemyCount < 14)
						{
							
							CPlayer::x -= 3;
						}

						if (CSceneGame::EnemyCount >= 14)
						{
							CPlayer::x -= 4;
						}
						if (x - w < -400) {
							CPlayer::x = -400 + w;
						}

					}
					if (CKey::Push('D')) {
						if (CSceneGame::EnemyCount < 14)
						{
							
							x += 3;
						}
						if (CSceneGame::EnemyCount >= 14)
						{
						
							x += 4;
						}
						if (x + w > 400) {
							x = 400 - w;
						}
					}
					if (CKey::Push('W')) {
						if (CSceneGame::EnemyCount < 14)
						{
							mFy = 1;
							y += 3;
						}
						if (y + h > 300) {
							y = 300 - h;
						}
						if (CSceneGame::EnemyCount >= 14)
						{
					
							y += 3;
						}
					}
					if (CKey::Push('S')) {
						y -= 3;
						if (y - h < -300) {
							y = -300 + h;
						}
					}
					if (CKey::Push('J'))
					{
						mFy = 1;
						mFx = -1;
					}
					if (CKey::Push('L'))
					{
						mFy = 1;
						mFx = 1;
					}
					if (!CKey::Push('J') && !CKey::Push('L')){
						if (CKey::Push('W'))
						{
							mFx = 0;
						}
					}
					if (HitCount > 0 && PlayerHit == false)
					{
						HitCount--;
					}
					if (HitCount == 0)
					{
						PlayerHit = true;
					}
}

	

void CPlayer::Render() {
	if (CSceneGame::Remain > 0 )
	{
		CRectangle::Render(Texture, 65, 115, 85, 25);
	}
}
	

//36
void CPlayer::Collision(CRectangle* ri, CRectangle* ry) {
	if ((*ry).mTag == EBOSSENEMY) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			int mx, my;
			if (CRectangle::Collision(ry, &mx, &my)) {
				//abs(x)xの絶対値を求める
				//移動量が少ない方向だけ移動させる
				if (abs(mx) < abs(my)) {
					//RectをXだけ移動する
					x += mx;
				}
				else {
					//Rectをyだけ移動する
					y += my;
				}
				if (PlayerHit == true)
				{
					if (CSceneGame::Time != 0 && CBossEnemy::mBossEnemyLife != 0)
					{
						CSceneGame::Remain -= 1;
					}
					PlayerHit = false;
					HitCount = 160;
				}
			}
		}
	}
	if ((*ry).mTag == EENEMYBULLET) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				(*ry).mEnabled = false;
				if (PlayerHit == true)
				{
					if (CSceneGame::Time != 0 && CBossEnemy::mBossEnemyLife != 0) {
						CSceneGame::Remain -= 1;
					}
					PlayerHit = false;
					HitCount = 80;
				}
				
			}
		}
	}
	if ((*ry).mTag == EENEMYITEM1) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
				{
					(*ry).mEnabled = false;
				}
			}
		}
	}
	if ((*ry).mTag == EENEMYITEM2) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
				{
					//ゲームのスコアが50増える
					CSceneGame::ScoreCount += 50;
					(*ry).mEnabled = false;
				}
				

			}
		}
	}
	if ((*ry).mTag == EENEMYITEM3) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
				{
					//制限時間延長(効果:少)
					CSceneGame::Time += 10 * 60;
					(*ry).mEnabled = false;
				}
			}
		}
	}
	if ((*ry).mTag == EENEMYITEM4) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
				{
					//制限時間延長(効果:大)
					CSceneGame::Time += 21 * 60;
					(*ry).mEnabled = false;
				}
			}
		}
	}if ((*ry).mTag == EENEMYITEM5) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
				{
					//制限時間延長(効果:大)
					CSceneGame::Time += 21 * 60;
					(*ry).mEnabled = false;
				}
				

			}
		}
	}
	if ((*ry).mTag == EBOSSBULLET) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				(*ry).mEnabled = false;
				if (CSceneGame::Time != 0 && CBossEnemy::mBossEnemyLife != 0) {
					CSceneGame::Remain -= 1;
					PlayerHit = false;
					HitCount = 80;
				}
			}
		}
	}

}

