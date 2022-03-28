#ifndef CDRUVERFUKUSHIMA_H
#define CDRUVERFUKUSHIMA_H


//背景スクロールスピード
#define SCROLL_SPEED -2.0
//1枚目の背景
#define BACKGROUND1_X 0
//2枚目の背景
#define BACKGROUND2_X 3840
//奥の背景Y座標
#define BACKGROUND1_Y 25
//真ん中の背景Y座標
#define BACKGROUND2_Y -125


#include"CDriverFukushima.h"
#include"CEnemy.h"
#include "CBackground.h"
#include"CTaskManager.h"
#include<time.h>
#include<stdlib.h>



class CDriverFukushima {
private:
	int mSceneDrawCount;
	int mEnemyTypeRand;
	int mEnemyMakeRand;
	int mMakeRand;
	int mEy;
	int mEnemydepth;
	int mMakeTime;
public:

	void Init()
	{
		//奥の背景
		//背景クラスのメンバ変数への代入
		CBackground* Background = new CBackground();
		//スクリーンに値を設定
		Background->x = BACKGROUND1_X;
		Background->y = BACKGROUND1_Y;
		//有効にする
		Background->mEnabled = true;


		//スクロールする手前の背景
		//背景クラスのメンバ変数への代入
		CBackground2* Background2 = new CBackground2();
		//スクリーンに値を設定
		Background2->x = BACKGROUND1_X;
		Background2->y = BACKGROUND2_Y;
		Background2->speed = SCROLL_SPEED;
		//有効にする
		Background2->mEnabled = true;

		//スクロールする手前の背景
		//背景クラスのメンバ変数への代入
		CBackground2* Background3 = new CBackground2();
		//スクリーンに値を設定
		Background3->x = BACKGROUND2_X;
		Background3->y = BACKGROUND2_Y;
		Background3->speed = SCROLL_SPEED;
		//有効にする
		Background3->mEnabled = true;

		//マップの背景(ステージ)
		//背景クラスのメンバ変数への代入
		CBackground3* Background4 = new CBackground3();
		//スクリーンに値を設定
		Background4->x = BACKGROUND1_X;
		Background4->y = BACKGROUND2_Y;
		Background4->speed = SCROLL_SPEED;
		//有効にする
		Background4->mEnabled = true;

		//マップの背景(ステージ)
		//背景クラスのメンバ変数への代入
		CBackground3* Background5 = new CBackground3();
		//スクリーンに値を設定
		Background5->x = BACKGROUND2_X;
		Background5->y = BACKGROUND2_Y;
		Background5->speed = SCROLL_SPEED;
		//有効にする
		Background5->mEnabled = true;
		

	}

	void Update() {
		mEnemyMakeRand = rand() % 3 + 1;
		mMakeRand = (rand() % 100) - 1;
		srand((unsigned)time(NULL));
		if (mEnemyMakeRand == 1)
		{
			mEy = -60;
			mEnemydepth = 1;
		}
		if (mEnemyMakeRand == 2)
		{
			mEy = -180;
			mEnemydepth = 2;
		}
		if (mEnemyMakeRand == 3)
		{
			mEy = -360;
			mEnemydepth = 3;
		}
			if (mMakeRand >= 0 && mMakeRand <= 33 && mMakeTime % 120 == 60) {
				//スライム
				//エネミークラスのメンバ変数への代入
				for (int i = 0; i < 1; i++)
				{
				CEnemy1* Enemy = new CEnemy1();
				//乱数値=rand()%乱数値の要素数+乱数値の最小値
				srand((unsigned)time(NULL));
				mEnemyTypeRand = rand() % 3 - 1;
				Enemy->mEnemytype = mEnemyTypeRand;
				//敵に値を設定
				Enemy->x = 980;
				Enemy->y = mEy;
				Enemy->z = mEnemydepth;
				Enemy->w = 100;
				Enemy->h = 100;
				Enemy->mFx = -2;
				//有効にする
				Enemy->mEnabled = true;
				break;
				}
			}
		
			if (mMakeRand >= 34 && mMakeRand <= 66 && mMakeTime % 210 == 70) {
				//スケルトン
				for (int i = 0; i < 1; i++)
				{
					//エネミークラスのメンバ変数への代入
					CEnemy2* Enemy2 = new CEnemy2();
					//敵に値を設定
					Enemy2->x = 980;
					Enemy2->y = mEy;
					Enemy2->z = mEnemydepth;
					Enemy2->w = 160;
					Enemy2->h = 120;
					Enemy2->mFx = -2;
					//有効にする
					Enemy2->mEnabled = true;
					break;
				}
			}
		
		
			if (mMakeRand >= 67 && mMakeRand <= 99 && mMakeTime % 270 == 90) {
				//ゾンビ
				//エネミークラスのメンバ変数への代入
				for (int i = 0; i < 1; i++)
				{
					CEnemy3* Enemy3 = new CEnemy3();
					//敵に値を設定
					Enemy3->x = 980;
					Enemy3->y = mEy;
					Enemy3->z = mEnemydepth;
					Enemy3->w = 160;
					Enemy3->h = 120;
					Enemy3->mFx = -2;
					//有効にする
					Enemy3->mEnabled = true;
					break;
				}
			}
			mMakeTime = mMakeTime + 1;
		
	}
	






	
};
#endif 

