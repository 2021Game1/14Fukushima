#define ENEMY_ATTACKMODEL 50
#define EENEMY_COUNT 1
#define ENEMY_MOVEMODEL 60
#define ENEMY_FLUG_COUNT 0

#include "CEnemy.h"
#include "CTexture.h"
#include "CBullet.h"

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture EnemyAttackTexture1; //スライム(攻撃)モーション
extern CTexture EnemyMoveTexture1; //スライム(移動)モーション
extern CTexture EnemyAttackTexture2; //スケルトン(攻撃)モーション
extern CTexture EnemyMoveTexture2; //スケルトン(移動)モーション
extern CTexture EnemyAttackTexture3; //ゾンビ(攻撃)モーション
extern CTexture EnemyMoveTexture3; //ゾンビ(攻撃)モーション




CEnemy1::CEnemy1()
: mFx(0.0f), mFy(0.0f),m_Hp(20), m_EnemyAttackRenderCount(ENEMY_ATTACKMODEL), m_EnemyStandbyCount(ENEMY_MOVEMODEL),mEnemyflag(ENEMY_FLUG_COUNT),m_EnemyDrawCount(ENEMY_FLUG_COUNT),mEnemytype(ENEMY_FLUG_COUNT)
{
	mTag = EENEMY;
	mPriority = 6;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CEnemy1::Update() {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return;


		//移動
		x += mFx;
		y += mFy;
		if (--m_EnemyStandbyCount < 0)
		{
			m_EnemyStandbyCount = ENEMY_MOVEMODEL;
			if (mEnemyflag  !=3)
			{
				mEnemyflag++;
			}
		}

		if (mEnemyflag == 3)
		{
			if (--m_EnemyAttackRenderCount < 0) {
				//弾を4発四方へ発射する
				for (int i = 0; i < 1; i++) {
					CBullet* EBullet = new CBullet();
					//座標設定
					EBullet->x = x - (w * 260 / 360);
					EBullet->y = y - (h * 60 / 120);
					EBullet->z = z;
					EBullet->w = 60;
					EBullet->h = 60;
					//移動量設定
					EBullet->mFx = -5;
					EBullet->mFy = 0;
					EBullet->mEnemyTipeBul = mEnemytype;
					//有効にする
					EBullet->mEnabled = true;
					EBullet->mTag = ESLIMEBULLET;
				}
				mEnemyflag = ENEMY_FLUG_COUNT;
				m_EnemyAttackRenderCount = ENEMY_ATTACKMODEL;
			}
		}



}
/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
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

void CEnemy1::Render() {
	if (mEnabled) {
		switch (mEnemytype) {
		case 0: {
			if (mEnemyflag != 3)
			{
				if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 4 / 5)
				{
					m_EnemyDrawCount = 1;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 3 / 5)
				{
					m_EnemyDrawCount = 2;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 2 / 5)
				{
					m_EnemyDrawCount = 3;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 1 / 5)
				{
					m_EnemyDrawCount = 4;
				}
				if (mEnabled) {
					CRectangle::Render(EnemyMoveTexture1, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 512, 0);
				}
			}
			

			if (mEnemyflag == 3)
			{
				if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 4 / 5)
				{
					m_EnemyDrawCount = 1;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 3 / 5)
				{
					m_EnemyDrawCount = 2;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 2 / 5)
				{
					m_EnemyDrawCount = 3;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 1 / 5)
				{
					m_EnemyDrawCount = 4;
				}
				if (mEnabled) {
						CRectangle::Render(EnemyAttackTexture1, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 512, 0);
				}
			}
			break;
		}
		case 1: {
			if (mEnemyflag != 3)
			{
				if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 4 / 5)
				{
					m_EnemyDrawCount = 1;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 3 / 5)
				{
					m_EnemyDrawCount = 2;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 2 / 5)
				{
					m_EnemyDrawCount = 3;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 1 / 5)
				{
					m_EnemyDrawCount = 4;
				}
				if (mEnabled) {
					CRectangle::Render(EnemyMoveTexture1, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 1024, 512);
				}
			}
			if (mEnemyflag == 3)
			{
				if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 4 / 5)
				{
					m_EnemyDrawCount = 1;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 3 / 5)
				{
					m_EnemyDrawCount = 2;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 2 / 5)
				{
					m_EnemyDrawCount = 3;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 1 / 5)
				{
					m_EnemyDrawCount = 4;
				}
				if (mEnabled) {
					CRectangle::Render(EnemyAttackTexture1, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 1024, 512);
				}
			}
			break;
		}
		case 2: {
			if (mEnemyflag != 3)
			{
				if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 4 / 5)
				{
					m_EnemyDrawCount = 1;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 3 / 5)
				{
					m_EnemyDrawCount = 2;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 2 / 5)
				{
					m_EnemyDrawCount = 3;
				}
				else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 1 / 5)
				{
					m_EnemyDrawCount = 4;
				}
				if (mEnabled) {
					CRectangle::Render(EnemyMoveTexture1, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 1538, 1024);
				}


			}


			if (mEnemyflag == 3)
			{
				if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 4 / 5)
				{
					m_EnemyDrawCount = 1;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 3 / 5)
				{
					m_EnemyDrawCount = 2;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 2 / 5)
				{
					m_EnemyDrawCount = 3;
				}
				else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 1 / 5)
				{
					m_EnemyDrawCount = 4;
				}
				if (mEnabled) {
					CRectangle::Render(EnemyAttackTexture1, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 1538, 1024);
				}
			}
			break;
		}


		}
	}
}

//36
void CEnemy1::Collision(CRectangle *i, CRectangle *y) {
	Collision(*y);
}

CEnemy2::CEnemy2()
	: mFx(0.0f), mFy(0.0f),m_Hp(20),m_EnemyAttackRenderCount(ENEMY_ATTACKMODEL), m_EnemyStandbyCount(ENEMY_MOVEMODEL), mEnemyflag(ENEMY_FLUG_COUNT)
{
	mTag = EENEMY;
	mPriority = 5;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CEnemy2::Update() {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return;

	//移動
	x += mFx;
	y += mFy;
	if (--m_EnemyStandbyCount < 0)
	{
		m_EnemyStandbyCount = ENEMY_MOVEMODEL;
		if (mEnemyflag != 2)
		{
			mEnemyflag++;
		}
	}

	if (mEnemyflag == 2)
	{
		if (--m_EnemyAttackRenderCount < 0) {
			//弾を4発四方へ発射する
			for (int i = 0; i < 1; i++) {
				CBullet* EBullet = new CBullet();
				//座標設定
				EBullet->x = x - (h * 70 / 140);
				EBullet->y = y;
				EBullet->z = z;
				EBullet->w = 40;
				EBullet->h = 40;
				//移動量設定
				EBullet->mFx = -5;
				EBullet->mFy = 0;
				//有効にする
				EBullet->mEnabled = true;
				EBullet->mTag = ESKELETONBULLET;
			}
			mEnemyflag = ENEMY_FLUG_COUNT;
			m_EnemyAttackRenderCount = ENEMY_ATTACKMODEL;
		}
	}




}
/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CEnemy2::Collision(const CRectangle& r) {
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

void CEnemy2::Render() {
	if (mEnabled) {
		if (mEnemyflag != 2)
		{
			if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 3 / 4)
			{
				m_EnemyDrawCount = 1;
			}
			else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 2 / 4)
			{
				m_EnemyDrawCount = 2;
			}
			else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 1 / 4)
			{
				m_EnemyDrawCount = 3;
			}
			if (mEnabled) {
				CRectangle::Render(EnemyMoveTexture2, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 512, 0);
			}

		}
		if (mEnemyflag == 2)
		{
			if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 2 / 3)
			{
				m_EnemyDrawCount = 1;
			}
			else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 1 / 3)
			{
				m_EnemyDrawCount = 2;
			}
			if (mEnabled) {
				CRectangle::Render(EnemyAttackTexture2, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 512, 0);
			}

		}
	}
}

//36
void CEnemy2::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}

CEnemy3::CEnemy3()
	: mFx(0.0f), mFy(0.0f),m_Hp(20), m_EnemyAttackRenderCount(ENEMY_ATTACKMODEL), m_EnemyStandbyCount(ENEMY_MOVEMODEL), mEnemyflag(ENEMY_FLUG_COUNT)
{
	mTag = EENEMY;
	mPriority = 4;
	CTaskManager::Get()->Remove(this);
	CTaskManager::Get()->Add(this);
}

void CEnemy3::Update() {
	//mEnabledがfalseなら戻る
	if (!mEnabled) return;
	
	x += mFx;
	y += mFy;

	if (--m_EnemyStandbyCount < 0)
	{
		m_EnemyStandbyCount = ENEMY_MOVEMODEL;
		if (mEnemyflag != 2)
		{
			mEnemyflag++;
		}
	}

	if (mEnemyflag == 2)
	{
		if (--m_EnemyAttackRenderCount < 0) {
			//弾を4発四方へ発射する
			for (int i = 0; i < 1; i++) {
				CBullet* EBullet = new CBullet();
				//座標設定
				EBullet->x = x - (h * 70 / 140);
				EBullet->y = y - (w * 50 / 100);
				EBullet->z = z;
				//移動量設定
				EBullet->mFx = -5;
				EBullet->mFy = 0;
				//有効にする
				EBullet->mEnabled = true;
				EBullet->mTag = EZOMIBIEBULLET;
			}
			mEnemyflag = ENEMY_FLUG_COUNT;
			m_EnemyAttackRenderCount = ENEMY_ATTACKMODEL;
		}
	}
}
/*
親のCollisionをオーバーライドする
衝突すると移動方向を反対にする
*/
bool CEnemy3::Collision(const CRectangle& r) {
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

void CEnemy3::Render() {
	if (mEnabled) {
		if (mEnemyflag != 2)
		{
			if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 3 / 4)
			{
				m_EnemyDrawCount = 1;
			}
			else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 2 / 4)
			{
				m_EnemyDrawCount = 2;
			}
			else if (m_EnemyStandbyCount > ENEMY_MOVEMODEL * 1 / 4)
			{
				m_EnemyDrawCount = 3;
			}
			if (mEnabled) {
				CRectangle::Render(EnemyMoveTexture3, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 512, 0);
			}


		}
		if (mEnemyflag == 2)
		{
			if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 2 / 3)
			{
				m_EnemyDrawCount = 1;
			}
			else if (m_EnemyAttackRenderCount > ENEMY_ATTACKMODEL * 1 / 3)
			{
				m_EnemyDrawCount = 2;
			}if (mEnabled) {
				CRectangle::Render(EnemyAttackTexture3, m_EnemyDrawCount * 512, (m_EnemyDrawCount + 1) * 512, 512, 0);
			}
		}
	}
}

//36
void CEnemy3::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}