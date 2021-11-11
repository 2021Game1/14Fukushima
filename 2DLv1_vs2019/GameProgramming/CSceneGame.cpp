#include"CSceneGame.h"
#include<stdio.h>
#include"CSceneScreen.h"
#include<stdlib.h>
#include<time.h>

#define WIDTH 800.0 //画面幅

#define HEIGHT 600.0 //画面高さ

#define SCROLL_SPEED -2.0


int CSceneGame::Remain = 3;
//残り時間（30秒）
int CSceneGame::Time = 30 * 60;

int CSceneGame::CLEAR = 0;

int CSceneGame::OVER = 0;

int CSceneGame::ScoreCount;

char CSceneGame::buf[10];

//時間を表す変数

int val;



int CSceneGame::GameTime;

int CSceneGame::EnemyPattern;

int EnemyPattern = 0;

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
	//配列の宣言と初期値の設定
	int map[6][8] =
	{
		{ 0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0},
		{ 1,1,1,1,1,1,1,1},
	};
	//MapSize = 0; //0を代入する
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 8; i++) {
			//mapの要素が１の時、四角形配置
			if (map[j][i] == 1) {
				CMap* Map = new CMap;
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 5;
			}
		}
	}
	

	
	
	
	
	
	



	//37






	

	

	CPlayer* Player = new CPlayer();
	Player->x = 0;
	Player->y = -225;
	Player->w = 20;
	Player->h = 20;
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

	for (int k = 0; k < 3; k = k + 1) {
		if (GameTime % 240 == 0)
		{
			/*srand(time(NULL));*/
			//乱数値=rand()%乱数値の要素数+乱数値の最小値
			val = rand() % 501 - 250;
			CEnemy* Enemy = new CEnemy();
			Enemy->x = val;
			Enemy->y = 250;
			Enemy->mFy = -1;
			//敵に値を設定
			//有効にする
			Enemy->mEnabled = true;


		}
	}
	//時間を加算する
	GameTime = GameTime + 1;
	

	
	

	
	
	
		
	
	
	
	

	
	
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
						//次へ
			
		}
	}
	if (Time > 0) {
		Time--;
	}
	

	for (int i = 0; i < VectorRect.size(); i++) {
		//描画処理
		VectorRect[i]->Render();
	}
	if (CSceneGame::Remain < 0) {
		CSceneGame::Remain = 0;
	}
	CText::DrawString("Score", -350, 250, 12, 12);
	sprintf(buf, "%d", ScoreCount);
	CText::DrawString(buf, -350 + 32 * 4.0, 250, 12, 12);
	
	//文字列の描画
	CText::DrawString("Player", 200, -250, 12, 12);
	sprintf(buf, "%d", Remain);
	CText::DrawString(buf, 360, -250, 12, 12);

	//文字列の描画
	CText::DrawString("Time", 200, 250, 12, 12);
	sprintf(buf, "%d", Time / 60);
	CText::DrawString(buf, 300, 250, 12, 12);

	if (Remain == 0) {
		CText::DrawString("GAME OVER!", -270, 0, 32, 32);
		CText::DrawString("Push ENETER Key", -225, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			Remain = 3;
			ScoreCount = 0;
			Time = 30 * 60;
			mScene = ETITLE;
		}
	}
	if (Time == 0 && Remain != 0) {
		CText::DrawString("GAME SCORE", -225, 0, 16, 16);
		sprintf(buf, "%d", ScoreCount);
		CText::DrawString(buf, 140, 0, 16, 16);
		CText::DrawString("GAME CLEAR!", -165, 100, 16, 16);
		CText::DrawString("Push ENETER Key", -225, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			Remain = 3;
			Time = 30 * 60;
			mScene = ETITLE;
		}
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
