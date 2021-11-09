#include "CEnemy.h"
#include "CTexture.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
#include "CSceneGame.h"
#include "CPlayer.h"
extern CTexture Texture;

CEnemy* CEnemy::spInstance = nullptr;
//CBullet CEnemy::EBullet[20];


//敵のデータ//
CEnemy::CEnemy() 
	: mFx(0), mFy(0)
{
	{
		spInstance = this;
		w = 25;
		h = 25;
		//37
	//	mEnabled = true;
		mTag = CRectangle::EENEMY;
		
	}
}



void CEnemy::Update() {


	//mEnabledがfalseなら戻る
	if (!mEnabled)return;

	if (y < -280)
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
		for (int j = 0; j < 2; j++) {
			CBullet* EBullet = new CBullet();
			//座標設定
			EBullet->x = x;
			EBullet->y = y;
			//移動量設定
			if (CEnemy::x < CPlayer::spInstance->x) {
				EBullet->mFx = +1;
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
		mFireCount = 40;


	}
}
	
	
	





	
	
	

		/*
		//敵弾数分繰り返し
		for (int i = 0; i < 20; i++) {
			//無効な弾なら発射する
			if (!EBullet[i].mEnabled) {
				//座標設定
				EBullet[i].x = x;
				EBullet[i].y = y;
				//移動量設定
				EBullet[i].mFx = -2;
				EBullet[i].mFy = 0;
				//有効にする
				EBullet[i].mEnabled = true;
				EBullet[i].mTag = EENEMYBULLET;
				//発射間隔を60フレームにする
				break;
			}
			mFireCount = 60;
		}
		//敵弾数分繰り返し
		for (int i = 0; i < 20; i++) {
			//無効な弾なら発射する
			if (!EBullet[i].mEnabled) {
				//座標設定
				EBullet[i].x = x;
				EBullet[i].y = y;
				//移動量設定
				EBullet[i].mFx = 0;
				EBullet[i].mFy = 2;
				//有効にする
				EBullet[i].mEnabled = true;
				EBullet[i].mTag = EENEMYBULLET;
				//発射間隔を60フレームにする
				break;
			}
			mFireCount = 60;
		}
		//敵弾数分繰り返し
		for (int i = 0; i < 20; i++) {
			//無効な弾なら発射する
			if (!EBullet[i].mEnabled) {
				//座標設定
				EBullet[i].x = x;
				EBullet[i].y = y;
				//移動量設定
				EBullet[i].mFx = 0;
				EBullet[i].mFy = -2;
				//有効にする
				EBullet[i].mEnabled = true;
				EBullet[i].mTag = EENEMYBULLET;
				//発射間隔を60フレームにする
				break;
			}
			mFireCount = 60;
		}
		*/
	
	

/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CEnemy::Collision(const CRectangle &r) {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EBLOCK:
			//衝突していれば反転
			mEnabled = false;
			break;
		case EPLAYERBULLET:
			//プレイヤーの弾に当たると、無効にする
			mEnabled = false;
			break;
		case EPLAYER:
			mEnabled = false;
			break;
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
