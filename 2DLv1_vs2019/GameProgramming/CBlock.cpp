#include"CBlock.h"

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture BulletTexture;

CBlock::CBlock() 
	: mFx(0), mFy(0)
{
	w = 25;
	h = 25;
	mTag = CRectangle::EBLOCK;
}

void CBlock::Update() 
{
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


}
bool CBlock::Collision(CRectangle& r) {
	//mEnabledがfalseなら戻る
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//親のCollisionメソッドを呼び出す
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYERBULLET:
			//プレイヤーの弾に当たると、無効にする
			mEnabled = false;
			r.mEnabled = false;
		case EPLAYER:
			//プレイヤーに当たると、無効にする
			mEnabled = false;
			break;
		}
		return true;
	}
	return false;
}

void CBlock::Render()
{
	if (mEnabled) {
		CRectangle::Render(BulletTexture, 106, 116, 106, 112);
	}

}

void CBlock::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}