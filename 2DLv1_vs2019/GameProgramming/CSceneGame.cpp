#include "CSceneGame.h"
#include <stdio.h>
#include "CSceneScreen.h"
#include"CEnemyData.h"
#include<stdlib.h>
#include<time.h>

#define WIDTH 800.0 //画面幅

#define HEIGHT 600.0 //画面高さ

#define SCROLL_SPEED -2.0


int Remain = 3;
//時間を表す変数

int val;

CEnemy Enemy[10];

int CSceneGame::GameTime;



void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;

	CSceneScreen* Screen = new CSceneScreen();
	Screen->x = 0;
	Screen->y = 250;
	Screen->speed = SCROLL_SPEED;
	Screen->mEnabled = true;

	CSceneScreen* Screen2 = new CSceneScreen();
	Screen2->x = 0;
	Screen2->y = 1700;
	Screen2->speed = SCROLL_SPEED;
	Screen2->mEnabled = true;
	
	//クラスのメンバ変数への代入
//37
	

	
	/*
	int EnemyMap[6][8] =
	{

			{ 1,2,3,4,2,4,3,1},
			{ 1,0,0,0,0,0,0,1},
			{ 1,0,0,0,0,0,0,1},
			{ 1,0,0,0,0,0,0,1},
			{ 1,0,0,0,0,0,0,1},
			{ 1,1,1,1,1,1,1,1},
	};
	
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
		
		}
	}
	*/
	
	for (int i = 0; i < 10; i = i + 1){
		//敵の座標を初期化する
		if (!Enemy[i].mEnabled) {
			//敵に値を設定
			Enemy[i].x = 0;
			Enemy[i].y = 0;
			Enemy[i].w = 50;
			Enemy[i].h = 50;
			//下へ移動
			Enemy[i].mFx = 0;
			Enemy[i].mFy = -1;
			//有効にする
			Enemy[i].mEnabled = true;
			GameTime = 0;
		}
			break;
	}


	



	//37






	CPlayer* Player = new CPlayer();
	Player->x = 0;
	Player->y = -255;
	Player->w = 25;
	Player->h = 25;
	Player->mEnabled = true;





	/*37
	for (int k = 0; k < 10; k++) {
		if (!Enemy[k].mEnabled) {
			//敵に値を設定
			Enemy[k].x = i * 100 - 350;
			Enemy[k].y = j * -100 + 250;
			//右へ移動
			Enemy[k].mFx = 0;
			Enemy[k].mFy = 1;
			//有効にする
			Enemy[k].mEnabled = true;
			break;
		}
	}
	*/
}




void CSceneGame::Update() {
	for (int i = 0; i < 10; i = i + 1) {
		if (GameTime % 360 == 0)
		{
			/*srand(time(NULL));*/
			//乱数値=rand()%乱数値の要素数+乱数値の最小値
			val = rand() % 501-250;
			Enemy[i].x = val;
			Enemy[i].y = 250;
			//有効にする
			Enemy[i].mEnabled = true;
			if (i>=10)
			{
				i = 0;
			}
		}
		if (Enemy[i].y>500)
		{
			//敵のフラグをfalseに
			Enemy[i].mEnabled = false;
		}
	}

	
	

	
	

	
	
	
		
	
	
	
	

	
	
	/*
	配列の要素分繰り返す
	配列名.size()
	配列の要素数を取得する
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		配列の参照
		配列名[添え字]
		通常の配列同様に添え字で要素にアクセスできる
		*/
		//更新処理
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//衝突処理
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//リストから削除する
	//イテレータの生成
	std::vector<CRectangle*>::iterator itr;
	//イテレータを先頭
	itr = VectorRect.begin();
	//最後まで繰り返し
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//次へ
			itr++;
		}
		else {
			//falseのインスタンスを削除
			delete *itr;
			//リストからも削除
			itr = VectorRect.erase(itr);
		}
	}

	

	for (int i = 0; i < VectorRect.size(); i++) {
		//描画処理
		VectorRect[i]->Render();
	}

	
	
/*
	CText::DrawChar('S', -350, 250, 16, 16);
	CText::DrawChar('c', -350 + 32, 250, 16, 16);
	CText::DrawChar('o', -350 + 32 * 2, 250, 16, 16);
	CText::DrawChar('r', -350 + 32 * 3, 250, 16, 16);
	CText::DrawChar('e', -350 + 32 * 4, 250, 16, 16);

	CText::DrawChar('P', 150, -250, 16, 16);
	CText::DrawChar('l', 150 + 32, -250, 16, 16);
	CText::DrawChar('a', 150 + 32 * 2, -250, 16, 16);
	CText::DrawChar('y', 150 + 32 * 3, -250, 16, 16);
	CText::DrawChar('e', 150 + 32 * 4, -250, 16, 16);
	CText::DrawChar('r', 150 + 32 * 5, -250, 16, 16);

	//文字列の描画
	CText::DrawString("Time", 150, 250, 16, 16);
	if (Time > 0) {
		Time--;
	}
	//整数を文字列に変換する
	char buf[10];//9文字までOK
	sprintf(buf, "%d", Time / 60);
	CText::DrawString(buf, 300, 250, 16, 16);

	sprintf(buf, "%d", Remain);
	CText::DrawString(buf, 150 + 32 * 7, -250, 16, 16);
*/

}


//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//デストラクタ
CSceneGame::~CSceneGame() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
