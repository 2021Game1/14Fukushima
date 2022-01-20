#include "CEnemy.h"
#include "CTexture.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
#include "CSceneGame.h"
#include "CPlayer.h"
#include"CItem.h"
#include"CSceneTitle.h"
#include"CEffect.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

//CSoundクラスのインクルード
#include "CSound.h"
//外部変数の参照の作成
extern CSound Se;
//CBullet CEnemy::EBullet[20];

//敵のデータ//
CEnemy::CEnemy() 
	: mFx(0), mFy(0),mFireCount(0)
{
	{
		//37
	//	mEnabled = true;
		mTag = CRectangle::EENEMY;
		
	}
}
void CEnemy::Update() {


	//mEnabledがfalseなら戻る
	if (!mEnabled)return;

	if (y < -425)
	{
		//敵のフラグをfalseに
		mEnabled = false;
	}

	//有効な時
	if (mEnabled) {
		//移動
		x += mFx * 0;
		y += mFy * 1;
	}

	//60フレームに1回発射
	if (mFireCount > 0) {
		mFireCount--;
	}
	//37e
	/**/

	else {
		for (int j = 0; j < 1; j++) {
			CBullet* EBullet = new CBullet();
			//座標設定
			EBullet->x = x;
			EBullet->y = y;
			EBullet->w = 8;
			EBullet->h = 8;
			//移動量設定
			if (CEnemy::x < CPlayer::spInstance->x) {
				EBullet->mFx = +1;
				EBullet->mFy = -3 * ((j / 2) + 1);
			}
			if (CEnemy::x == CPlayer::spInstance->x) {
				EBullet->mFx = 0;
				EBullet->mFy = -3 * ((j / 2) + 1);
			}
			if (CEnemy::x > CPlayer::spInstance->x) {
				EBullet->mFx = -1;
				EBullet->mFy = -3 * ((j / 2) + 1);
			}
			//有効にする
			EBullet->mEnabled = true;
			EBullet->mTag = EENEMYBULLET;

		}
		mFireCount = 55;


	}



}


	

/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CEnemy::Collision(CRectangle& r) {
	//mEnabledがfalseなら戻る
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYERBULLET: {
			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0 && CBossEnemy::mBossEnemyLife != 0)
			{
			//プレイヤーの弾に当たると、無効にする
			mEnabled = false;
			r.mEnabled = false;
			//サウンド再生
			Se.Play();
			CEffect* Effect = new CEffect();
			//有効にする
			Effect->x = x;
			Effect->y = y;
			Effect->w = 25;
			Effect->h = 25;
			Effect->mEnabled = true;
			Effect->mTag = EEFFECT;

			
				CSceneGame::ScoreCount += 100;
				CSceneGame::EnemyCount += 1;
			}
			break;
		}
		
			
			
		case EPLAYER: {
			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0 && CBossEnemy::mBossEnemyLife != 0)
			{
			//プレイヤーに当たると、無効にする
			mEnabled = false;
			//サウンド再生
			Se.Play();
			CEffect* Effect2 = new CEffect();
			//有効にする
			Effect2->x = x;
			Effect2->y = y;
			Effect2->w = 25;
			Effect2->h = 25;
			Effect2->mEnabled = true;
			Effect2->mTag = EEFFECT;
			
				CSceneGame::ScoreCount += 25;
				CSceneGame::Remain -= 1;
			}
			break;
		}


			CSceneGame::GameTime = CSceneGame::GameTime + 1;
		}
			return true;
	}
		return false;
}

void CEnemy::Render() {
		if (mEnabled) {
			CRectangle::Render(Texture, 140, 190, 75, 25);
		}
		
	
}
//36
void CEnemy::Collision(CRectangle *i, CRectangle *y) {
	Collision(*y);
}
