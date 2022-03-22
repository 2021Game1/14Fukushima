#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"



class CEnemy1 : public CRectangle {
public:
	int mFx; //X軸方向の移動 -1:左 0:移動しない 1:右へ移動
	int mFy; //Y軸方向の移動 -1:下 0:移動しない 1:上へ移動
	int mEnemytype;
	


	CEnemy1();
private:
	int m_EnemyDrawCount;
	int m_Hp; //HP
	int m_EnemyStandbyCount;//敵の待機モーションのカウンタ
	int m_EnemyAttackRenderCount;//敵の攻撃モーションのカウンタ
	int mEnemyflag; //敵のアニメーションのカウントフラグ
	void Update();
	bool Collision(const CRectangle& r);
	void Render();
	//36
	void Collision(CRectangle* i, CRectangle* y);
};

class CEnemy2 : public CRectangle {

public:
	int mFx; //X軸方向の移動 -1:左 0:移動しない 1:右へ移動
	int mFy; //Y軸方向の移動 -1:下 0:移動しない 1:上へ移動
	

	void Update();
	bool Collision(const CRectangle& r);
	void Render();

	//36
	void Collision(CRectangle* i, CRectangle* y);
	CEnemy2();
private:
	int m_EnemyDrawCount;
	int m_Hp; //HP
	int m_EnemyStandbyCount;//敵の待機モーションのカウンタ
	int m_EnemyAttackRenderCount;//敵の攻撃モーションのカウンタ
	int mEnemyflag; //敵のアニメーションのカウントフラグ
};

class CEnemy3 : public CRectangle {

public:
	int mFx; //X軸方向の移動 -1:左 0:移動しない 1:右へ移動
	int mFy; //Y軸方向の移動 -1:下 0:移動しない 1:上へ移動
	

	void Update();
	bool Collision(const CRectangle& r);
	void Render();

	//36
	void Collision(CRectangle* i, CRectangle* y);
	CEnemy3();
private:
	int m_EnemyDrawCount;
	int m_Hp; //HP
	int m_EnemyStandbyCount;//敵の待機モーションのカウンタ
	int m_EnemyAttackRenderCount;//敵の攻撃モーションのカウンタ
	int mEnemyflag; //敵のアニメーションのカウントフラグ
};
#endif
