#include"CSceneGame.h"
#include<stdio.h>
#include"CSceneScreen.h"
#include<stdlib.h>
#include<time.h>
#include"CBlock.h"
#define WIDTH 800.0 //画面幅

#define HEIGHT 600.0 //画面高さ

#define SCROLL_SPEED -2.0


int CSceneGame::Remain = 3;
//残り時間（30秒）
int CSceneGame::Time = 31 * 60;

int CSceneGame::CLEAR = 0;

int CSceneGame::OVER = 0;

int CSceneGame::ScoreCount = 0;

int CSceneGame::Bossflug = 0;

int CSceneGame::BossCount = 0;

int CSceneGame::EnemyCount = 0;

char CSceneGame::buf[10];


//時間を表す変数

int val;

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



	CPlayer* Player = new CPlayer();
	Player->x = 0;
	Player->y = -225;
	Player->w = 20;
	Player->h = 20;
	Player->mEnabled = true;
	//クラスのメンバ変数への代入
//37


}




void CSceneGame::Update() {


	for (int k = 0; k < 3; k = k + 1) {
		if (GameTime % 240 == 0 && ScoreCount < 1000)
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
	for (int i = 0; i < 2; i++)
	{
		if (GameTime % 420 == 0 && ScoreCount >= 1000)
		{
			/*srand(time(NULL));*/
			//乱数値=rand()%乱数値の要素数+乱数値の最小値
			val = rand() % 501 - 250;
			CEnemy* Enemy2 = new CEnemy();
			Enemy2->x = val;
			Enemy2->y = 250;
			Enemy2->mFy = -1;
			//敵に値を設定
			//有効にする
			Enemy2->mEnabled = true;
			
		}
	}
			
		

		//時間を加算する
		GameTime = GameTime + 1;


		if (Bossflug != 2)
		{
			if (ScoreCount >= 1000)
			{
				CBossEnemy* EBossEnemy = new CBossEnemy();
				Bossflug += 1;
				EBossEnemy->x = 0;
				EBossEnemy->y = 250;
				EBossEnemy->mFx = 2;
				EBossEnemy->mFy = 0;
				EBossEnemy->mEnabled = true;
				Bossflug = 2;
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
						//次へ
			
		}
	}
	if (Time > 0 && Remain > 0) {
		Time--;
	}

	

	for (int i = 0; i < VectorRect.size(); i++) {
		//描画処理
		VectorRect[i]->Render();
	}
	if (CSceneGame::Remain < 0) {
		CSceneGame::Remain = 0;
	}

	if (Remain != 0 && Time != 0)
	{
		CText::DrawString("Score", -350, 250, 12, 12);
		sprintf(buf, "%d", ScoreCount);
		CText::DrawString(buf, -350 + 32 * 4.0, 250, 12, 12);
	}
	
	//文字列の描画
	CText::DrawString("Player", 200, -250, 12, 12);
	sprintf(buf, "%d", Remain);
	CText::DrawString(buf, 360, -250, 12, 12);
	
		//文字列の描画
		CText::DrawString("Time", 200, 250, 12, 12);
		sprintf(buf, "%d", Time / 60);
		CText::DrawString(buf, 300, 250, 12, 12);
	
	

	if (Remain == 0 && Time != 0 ) {
		CText::DrawString("GAME SCORE", -180, 0, 16, 16);
		sprintf(buf, "%d", ScoreCount);
		CText::DrawString(buf, 160, 0, 16, 16);
		CText::DrawString("GAME OVER!", -140, 100, 16, 16);
		CText::DrawString("Push ENETER Key", -210, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			Remain = 3;
			ScoreCount = 0;
			Time = 31 * 60;
			Bossflug = 0;
			EnemyCount = 0;
			BossCount = 0;
			CBossEnemy::CBossEnemyLife = 20;
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
			ScoreCount = 0;
			Time = 31 * 60;
			Bossflug = 0;
			EnemyCount = 0;
			BossCount = 0;
			CBossEnemy::CBossEnemyLife = 20;
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
