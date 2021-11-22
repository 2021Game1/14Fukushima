#include "CPlayer.h"
#include "CKey.h"
//37
#include "CBullet.h"

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::CPlayerLevel = 0;

CPlayer::CPlayer()
: mFx(0.0f), mFy(1.0f)
, FireCount(0)
{
	mTag = EPLAYER;
	mEnabled = true;
	spInstance = this;
	
}

void CPlayer::Update() {
	//mEnabledがfalseなら戻る
	//staticメソッドはどこからでも呼べる
	if (CKey::Push('A')) {
		x -= 3;
		if (x - w < -400) {
			x = -400 + w;
		}
	}
	if (CKey::Push('D')) {
		x += 3;
		if (x + w > 400) {
			x = 400 - w;
		}
	}
	if (CKey::Push('W')) {
		y += 3;
		mFx = 0;
		mFy = 1;
		if (y + h > 300) {
			y = 300 - h;
		}
	}
	if (CKey::Push('S')) {
		y -= 3;
		if (y - h < -300) {
			y = -300 + h;
		}
	}
	//37
	//スペースキーで弾発射
	//0より大きいとき1減算する
	if (FireCount > 0) {
		FireCount--;
	}
	//FireContが0で、かつ、スペースキーで弾発射
	else if (CKey::Once(' ')) {
		if (CPlayerLevel >= 0) {
			CBullet* Bullet = new CBullet();
			//発射位置の設定
			Bullet->x = x;
			Bullet->y = y;
			//移動の値を設定
			Bullet->mFx = mFx * 5;
			Bullet->mFy = mFy * 5;
			//有効にする
			Bullet->mEnabled = true;
			//プレイヤーの弾を設定
			Bullet->mTag = CRectangle::EPLAYERBULLET;
			
		}
		FireCount = 15;
	}
	
}

void CPlayer::Render() {
	CRectangle::Render(Texture, 65, 115, 85, 25);
}

//36
void CPlayer::Collision(CRectangle* ri, CRectangle* ry) {
	if ((*ry).mTag == EBLOCK) {
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
			}
		}
	}
	if ((*ry).mTag == EENEMYBULLET) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				(*ry).mEnabled = false;
				if (CSceneGame::Time != 0) {
					CSceneGame::Remain -= 1;
				}
			}
		}
	}
	if ((*ry).mTag == EENEMYITEM) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				(*ry).mEnabled = false;
			
			}
		}
	}
}

