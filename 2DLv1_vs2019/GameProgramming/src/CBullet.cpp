#include "CBullet.h"
#include "CTexture.h"
#include "CSceneGame.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture BulletTexture;

//デフォルトコンストラクタ
CBullet::CBullet()
	: mFx(0), mFy(0)
{
	mEnabled = false;
	//幅設定
	//高さ設定
}

//更新処理
void CBullet::Update() {
	if (CBullet::x >= 400 || CBullet::x <= -400 ||
		CBullet::y >= 285 || CBullet::y <= -285) {
		mEnabled = false;
	}
	//有効な時
	if (mEnabled) {
		//移動
		x += mFx;
		y += mFy;


	}
}

//描画処理
void CBullet::Render() {
	//有効な時
	if (mEnabled) {
		if (mTag == EPLAYERBULLET)
		{
			//親の描画メソッドを呼ぶ
			CRectangle::Render(BulletTexture, 17, 26, 99, 88);
		}
	}
	if (mEnabled) {
		if (mTag == EENEMYBULLET)
		{
			//親の描画メソッドを呼ぶ
			CRectangle::Render(BulletTexture, 206, 216, 114, 104);
		}
	}
	//有効な時
	if (mEnabled) {
		if (mTag == EBOSSBULLET)
		{
			//親の描画メソッドを呼ぶ
			CRectangle::Render(BulletTexture, 128, 135, 175, 158);
		}
	}
}

//36
void CBullet::Collision(CRectangle* i, CRectangle* y) {
	if (i->mEnabled && y->mEnabled) {
		if (y->mTag == EBLOCK) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		if (i->mTag == EENEMYBULLET && y->mTag == EPLAYER) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}

		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EENEMY) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
		if (i->mTag == EPLAYERBULLET && y->mTag == EBOSSENEMY) {
			if (i->Collision(*y)) {
				mEnabled = false;
				return;
			}
		}
	}
}
