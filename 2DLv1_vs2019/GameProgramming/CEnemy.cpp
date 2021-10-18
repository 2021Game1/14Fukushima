#include "CEnemy.h"
#include "CTexture.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

//CBullet CEnemy::EBullet[20];

CEnemy::CEnemy()

{
	//37
//	mEnabled = true;
	mTag = EENEMY;
	w = 25;
	h = 25;
}

void CEnemy::Update() {
	
		//37e
		/* 37
		//敵弾数分繰り返し
		for (int i = 0; i < 20; i++) {
			//無効な弾なら発射する
			if (!EBullet[i].mEnabled) {
				//座標設定
				EBullet[i].x = x;
				EBullet[i].y = y;
				//移動量設定
				EBullet[i].mFx = 2;
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
	}
	
}
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
		}
		return true;
	}
	return false;
}

void CEnemy::Render() {
	if (mEnabled) {
		CRectangle::Render(Texture, 146 - 16, 146 + 16, 178 + 16, 178 - 16);
		
	}
}

//36
void CEnemy::Collision(CRectangle *i, CRectangle *y) {
	Collision(*y);
}
