#define PLAYER_SPEED_X 5
#define PLAYER_SPEED_Y 10
#define PLAYER_SHOTTIME 10


#include "CPlayer.h"
#include "CKey.h"
#include"CTaskManager.h"
#include "CBullet.h"
#include"CDriverFukushima.h"

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;
extern CTexture PlayerTexture0;
extern CTexture PlayerTexture1;
extern CTexture PlayerTexture2;
extern CTexture PlayerTexture3;
extern CTexture PlayerTexture4;
//プレイヤーのポインタ
CPlayer* CPlayer::spInstance = nullptr;

CPlayer::CPlayer()
: mFx(1.0f), mFy(0.0f)
, FireCount(0)
{
	x = -850;
	y = -200;
	w = 175;
	h = 175;
	z = 2;
	mPriority = 8;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
	 mHp = 5;
	mTag = EPLAYER;
	spInstance = this;
	mPlayerMotion = 0;
	mMotionCnt = 0;
	mLoopCnt = 0;
	mJumpFlag = 0;
	mJumpCnt = 0;
}

void CPlayer::Update() {

	//staticメソッドはどこからでも呼べる
	if (CKey::Push('A')) {
		x -= PLAYER_SPEED_X;
		mFx = -1;
		//mFy = 0;
		if (x - w < -960) {
			x = -960 + w;
		}
		if (mPlayerMotion != 2) {
			mPlayerMotion = 1;
		}
	}
	if (CKey::Push('D')) {
		x += PLAYER_SPEED_X;

		mFx = 1;
		//mFy = 0;
		if (x + w > 960) {
			x = 960 - w;
		}
		if (mPlayerMotion != 2) {
			mPlayerMotion = 1;
		}

	}
	if (mPlayerMotion != 2) {

		if (CKey::Once('W')) {
			mPlayerMotion = 1;
			//mFx = 0;
			//mFy = 1;
			if (z >= 2) {
				z -= 1;
			}
			y = -100 * z;

		}

		if (CKey::Once('S')) {
			mPlayerMotion = 1;
			y -= PLAYER_SPEED_Y;
			//mFx = 0;
			//mFy = -1;
			if (z <= 2) {
				z += 1;
			}
			y = -100 * z;
		}


		if (!CKey::Push('D')) {
			x -= 2;
		}
		//37
		//スペースキーで弾発射
		//0より大きいとき1減算する
		if (FireCount > 0) {
			FireCount--;
		}
		//FireContが0で、かつ、スペースキーで弾発射
		else if (CKey::Once('K')) {
			mPlayerMotion = 3;
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
			Bullet->mTag = EPLAYERBULLET;
			FireCount = PLAYER_SHOTTIME;
		}
		if (CKey::Once('J')) //ジャンプ
		{
			mPlayerMotion = 2;
			mJumpFlag = 1;
		}

	}
	if (mJumpFlag ==1) {

		if (mJumpCnt >= 60) {
			mJumpCnt = 0;
			mJumpFlag = 0;
			mV = 75;
		}
		else if (mJumpCnt % 5 == 0 && mJumpCnt != 0) {
			y += mV;
			mV += mGRAVITY;
			mJumpCnt += 1;
		}
		else {
			mJumpCnt += 1;
		}
	}
	
}

void CPlayer::Render() {
	switch (mPlayerMotion)
	{
	case 0:
		CRectangle::Render(PlayerTexture0, 0, 512, 512, 0);
		break;
	case 1:
		if (mFx == 1) {
			CRectangle::Render(PlayerTexture1, mMotionCnt * 512, (mMotionCnt + 1) * 512, 512, 10);
		}
		else {
			CRectangle::Render(PlayerTexture1, (mMotionCnt + 1) * 512, mMotionCnt * 512, 512, 0);
		}
		if (mLoopCnt == 5) {
			mMotionCnt = (mMotionCnt + 1) % 4;
			mLoopCnt = 0;
		}
		else {
			mLoopCnt += 1;
		}

		break;
	case 2:
		if (mFx == 1) {
			CRectangle::Render(PlayerTexture2, mMotionCnt * 512, (mMotionCnt + 1) * 512, 512, 10);
		}
		else {
			CRectangle::Render(PlayerTexture2, (mMotionCnt + 1) * 512, mMotionCnt * 512, 512, 0);
		}
		if (mLoopCnt >= 60) {
			mPlayerMotion = 1;
			mMotionCnt = 0;
			mLoopCnt = 0;
		}
		else if (mLoopCnt % 10 == 0 && mLoopCnt != 0) {
			mMotionCnt += 1;
			mLoopCnt += 1;
		}
		else {
			mLoopCnt += 1;
		}
		break;

	case 3:
		if (mFx == 1) {
			CRectangle::Render(PlayerTexture3, mMotionCnt * 512, (mMotionCnt + 1) * 512, 512, 10);
		}
		else {
			CRectangle::Render(PlayerTexture3, (mMotionCnt + 1) * 512, mMotionCnt * 512, 512, 0);
		}
		if (mLoopCnt >= 20) {
			mPlayerMotion = 1;
			mMotionCnt = 0;
			mLoopCnt = 0;
		}
		else if (mLoopCnt % 4 == 0 && mLoopCnt != 0) {
			mMotionCnt += 1;
			mLoopCnt += 1;
		}
		else {
			mLoopCnt += 1;
		}
		break;
	case 4:
		if (mFx == 1) {
			CRectangle::Render(PlayerTexture4, mMotionCnt * 512, (mMotionCnt + 1) * 512, 512, 10);
		}
		else {
			CRectangle::Render(PlayerTexture4, (mMotionCnt + 1) * 512, mMotionCnt * 512, 512, 0);
		}
		if (mLoopCnt >= 20) {
			mPlayerMotion = 1;
			mMotionCnt = 0;
			mLoopCnt = 0;
		}
		else if (mLoopCnt % 4 == 0 && mLoopCnt != 0) {
			mMotionCnt += 1;
			mLoopCnt += 1;
		}
		else {
			mLoopCnt += 1;
		}
		break;
	}

}


////36
//void CPlayer::Collision(CRectangle *ri, CRectangle *ry) //ブロックにぶつかったとき
//{
//	if (ry->mTag == EBLOCK) {
//		int mx, my;
//		if (CRectangle::Collision(ry, &mx, &my)) {
//			//abs(x) xの絶対値を求める
//			//移動量が少ない方向だけ移動させる
//			if (abs(mx) < abs(my)) {
//				//Rectをxだけ移動する
//				x += mx;
//			}
//			else {
//				//Rectをyだけ移動する
//				y += my;
//			}
//		}
//	}
//}
void CPlayer::Collision(const CRectangle& r) //攻撃されたとき
{
	if (mPlayerMotion != 2) {
		if (CRectangle::Conflict(r)) {
			switch (r.mTag) {

			case ESLIMEBULLET:
				//エネミーの弾に当たると、HPが1減る
				mHp -= 1;
				mPlayerMotion = 4;
				break;
			case ESKELETONBULLET:
				//エネミーの弾に当たると、HPが1減る
				mHp -= 1;
				mPlayerMotion = 4;
				break;
			case EZOMIBIEBULLET:
				//エネミーの弾に当たると、HPが1減る
				mHp -= 1;
				mPlayerMotion = 4;
				break;
			case EENEMY:
				//エネミーに当たると、HPが1減る
				mHp -= 1;
				mPlayerMotion = 4;
				break;
			} 
		}
	}
}
/*
bool CEnemy1::Collision(const CRectangle &r) {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
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
*/
int CPlayer::GetPlayerHP()
{
	//return 5;
	return mHp;
}
