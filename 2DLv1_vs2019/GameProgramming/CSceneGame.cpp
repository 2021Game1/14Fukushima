#include"CSceneGame.h"
#include<stdio.h>
#include"CSceneScreen.h"
#include<stdlib.h>
#include<time.h>
#include"CBlock.h"
#include"CItem.h"
#include"CMapModel.h"

CMapModel mMapModel;

#define WIDTH 800.0 //画面幅

#define HEIGHT 600.0 //画面高さ

//スクリーンのスクロールスピード
#define SCROLL_SPEED -2.0

CBlock mBlockModel;

//モデルデータの指定
#define MODEL_OBJ "MapDate.csv","Test.csv"

//プレイヤーの残機
int CSceneGame::Remain = 3;

//残り時間（30秒）
int CSceneGame::Time = 31 * 60;

//ゲームクリア
int CSceneGame::CLEAR = 0;

//ゲームオーバー
int CSceneGame::OVER = 0;

//ゲームスコアのカウンタ変数
int CSceneGame::ScoreCount = 0;

//ボスが出現しているか、判別するフラグ
int CSceneGame::Bossflug = 0;

//ボスのカウンタ
int CSceneGame::BossCount = 0;

//敵のカウンタ
int CSceneGame::EnemyCount = 0;

//９文字まで描画できる変数
char CSceneGame::buf[10];

int vel;


int val;

//敵が出現するまでの時間
int CSceneGame::GameTime;




void CSceneGame::Init() 
{
		//シーンの設定
		mScene = EGAME;
		//モデルファイルの入力
		mMapModel.Load(MODEL_OBJ);
		
		//スクリーン一枚目
	//スクリーンクラスのメンバ変数への代入
		CSceneScreen* Screen = new CSceneScreen();
		//スクリーンに値を設定
		Screen->x = 0;
		Screen->y = 240;
		//スクロールスピード
		Screen->speed = SCROLL_SPEED;
		//有効にする
		Screen->mEnabled = true;

		//スクリーン２枚目
		//スクリーンクラスのメンバ変数への代入
		CSceneScreen* Screen2 = new CSceneScreen();
		//スクリーンに値を設定
		Screen2->x = 0;
		Screen2->y = 1700;
		//スクロールスピード
		Screen2->speed = SCROLL_SPEED;
		//有効にする
		Screen2->mEnabled = true;

		
		


		//プレイヤークラスのメンバ変数への代入
		CPlayer* Player = new CPlayer();
		//プレイヤーに値を設定
		Player->x = 0;
		Player->y = -225;
		Player->w = 20;
		Player->h = 20;
		//有効にする
		Player->mEnabled = true;



	
	
	

			
}




void CSceneGame::Update() {

	
		//敵の出現する条件
		if (GameTime % 280 == 140 && ScoreCount < 1000 && GameTime != 0)
		{
			/*srand(time(NULL));*/
			//乱数値=rand()%乱数値の要素数+乱数値の最小値
			val = rand() % 501 - 250;
			CEnemy* Enemy = new CEnemy();
			//敵に値を設定
			Enemy->x = val;
			Enemy->y = 250;
			Enemy->mFy = -1;
			//有効にする
			Enemy->mEnabled = true;
			
		}

		if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
		{
				if (GameTime % 100 == 50)
				{
					/*srand(time(NULL));*/
					//乱数値=rand()%乱数値の要素数+乱数値の最小値
					val = rand() % 501 - 250;
					/*srand(time(NULL));*/
					//乱数値=rand()%乱数値の要素数+乱数値の最小値
					srand((unsigned)time(NULL));
					vel = (rand() % 100) + 1;
					for (int i = 0; i < 1; i++)
					{
						//アイテム1の出現確率(外れアイテム)
						if (vel >= 0 && vel <= 70) {
							CItemA* ItemA = new CItemA;
							ItemA->x = val;
							ItemA->y = 250;
							ItemA->mFy = -3;
							ItemA->mEnabled = false;
							ItemA->mTag = CRectangle::EENEMYITEM1;
						}
					}
					for (int i = 0; i < 1; i++)
					{
						//アイテム2の出現確率
						if (vel > 70 && vel <= 80) {
							CItemB* ItemB = new CItemB;
							ItemB->x = val;
							ItemB->y = 250;
							ItemB->mFy = -3;
							ItemB->mEnabled = true;
							ItemB->mTag = CRectangle::EENEMYITEM2;
						}
					}
					for (int i = 0; i < 1; i++)
					{
						//アイテム4の出現確率
						if (vel > 80 && vel <= 90) {
							CItemD* ItemD = new CItemD;
							ItemD->x = val;
							ItemD->y = 250;
							ItemD->mFy = -3;
							ItemD->mEnabled = true;
							ItemD->mTag = CRectangle::EENEMYITEM3;
						}
					}
					for (int i = 0; i < 1; i++)
					{
						//アイテム5の出現確率
						if (vel > 90 && vel <= 95) {
							CItemE* ItemE = new CItemE;
							ItemE->x = val;
							ItemE->y = 250;
							ItemE->mFy = -3;
							ItemE->mEnabled = true;
							ItemE->mTag = CRectangle::EENEMYITEM4;
						}
					}
					for (int i = 0; i < 1; i++)
					{
						//アイテム3の出現確率
						if (vel > 95 && vel <= 100) {
							CItemC* ItemC = new CItemC;
							ItemC->x = val;
							ItemC->y = 250;
							ItemC->mFy = -3;
							ItemC->mEnabled = true;
							ItemC->mTag = CRectangle::EENEMYITEM5;
						}
					}

				}
		}

	//ボスのフラグが2以外の時に出現する
	if (Bossflug != 2)
	{
		//スコアが1000以上か、等しいか
		if (ScoreCount >= 1000)
		{
			//ボスエネミークラスのメンバ変数への代入
			CBossEnemy* EBossEnemy = new CBossEnemy();
			Bossflug += 1;
			//ボスエネミーに値を設定
			EBossEnemy->x = 0;
			EBossEnemy->y = 250;
			EBossEnemy->mFx = 2;
			EBossEnemy->mFy = 0;
			//有効にする
			EBossEnemy->mEnabled = true;
			//処理をしたらフラグを2にする
			Bossflug = 2;
		}

	}
		//敵の出現する条件
		if (GameTime % 140 == 70 && GameTime != 0)
		{
			/*srand(time(NULL));*/
			//乱数値=rand()%乱数値の要素数+乱数値の最小値
			val = rand() % 501 - 250;
			//エネミークラスのメンバ変数への代入
			CEnemy* Enemy2 = new CEnemy();
			//敵に値を設定
			Enemy2->x = val;
			Enemy2->y = 250;
			Enemy2->mFy = -1;
			//有効にする
			Enemy2->mEnabled = true;
			
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

	//制限時間が0ではなく、プレイヤーの残機が0では無い時に有効にする
	if (Time > 0 && Remain > 0) {
		//制限時間を減算していく
		Time--;
	}

	

	for (int i = 0; i < VectorRect.size(); i++) {
		//描画処理
		VectorRect[i]->Render();
	}

	if (CSceneGame::Remain < 0) {
		CSceneGame::Remain = 0;
	}

	//プレイヤーの残機が0ではなく、制限時間が0ではない時に有効にする
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
	
	
	//プレイヤーの残機が0の時または、制限時間が0の時に有効にする
	if (Remain == 0 || Time == 0 ) {
		CText::DrawString("GAME SCORE", -180, 0, 16, 16);
		sprintf(buf, "%d", ScoreCount);
		CText::DrawString(buf, 160, 0, 16, 16);
		CText::DrawString("GAME OVER!", -140, 100, 16, 16);
		CText::DrawString("Push ENETER Key", -210, -100, 16, 16);
		if (CKey::Once(VK_RETURN)) {
			Remain = 3;
			OVER = 0;
			ScoreCount = 0;
			Time = 31 * 60;
			Bossflug = 0;
			EnemyCount = 0;
			BossCount = 0;
			CBossEnemy::mBossEnemyLife = 20;
			mScene = ETITLE;
		}
	}

	if (Remain != 0) {
		if (BossCount == 1){
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
			CBossEnemy::mBossEnemyLife = 20;
			mScene = ETITLE;
			}
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
