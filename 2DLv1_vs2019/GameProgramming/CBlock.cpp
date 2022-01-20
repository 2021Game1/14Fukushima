#include"CBlock.h"
#include"CSceneGame.h"
#include"CBullet.h"
//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture MoonBlock;



CBlock::CBlock() 
	: mFx(0), mFy(0)
{
	mTag = CRectangle::EBLOCK;
	
}

void CBlock::Update() 
{
	//mEnabledがfalseなら戻る
	if (!mEnabled)return;

	if (y < -450)
	{
		
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

		}
		return true;
	}
	return false;
}

void CBlock::Render()
{
	if (mEnabled) {
		CRectangle::Render(MoonBlock, 0, 320, 320, 0);
	}

}

void CBlock::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}

int CComet::speed = 0;

CComet::CComet() 
	: mFx(0), mFy(0)
{
	mTag = CRectangle::ECOMET;
}

void CComet::Update()
{
	//mEnabledがfalseなら戻る
	if (!mEnabled)return;

	if (y > 650) {
		CComet::speed -= 1;
	}

	if (y < 650) {
		CComet::speed == 0;
	}
	
		//有効な時
	
	if (mEnabled) {
		//移動
		x += mFx * 0;
		y += mFy * 1;
	}
	

}

bool CComet::Collision(CRectangle& r) {
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


			break;
		case EPLAYER:
			//プレイヤーに当たると、無効にする
			mEnabled = false;
			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0 && CBossEnemy::mBossEnemyLife != 0)
			{
				CSceneGame::ScoreCount += 25;
				CSceneGame::Remain -= 1;
			}
			break;
		}
		return true;
	}
	return false;
}

void CComet::Render()
{
	if (mEnabled) {
		CRectangle::Render(MoonBlock, 0, 445, 1285, 825);
	}

}

void CComet::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}