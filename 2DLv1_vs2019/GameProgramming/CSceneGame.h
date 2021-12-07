#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
// テクスチャクラスのインクルード
#include "CTexture.h"
#include "CSceneScreen.h"
#include "CBossEnemy.h"
#include "CSceneTitle.h"
/*
ゲームのシーン
*/
//CSceneクラスを継承する
class CSceneGame : public CScene {
public:
	//37
	//CTexture Texture; //マップの画像
	//CPlayer Player;
	//CMap Map[48];
	//int MapSize;
	//CBullet Bullet[10];
	//int FireCount = 10;
	//CEnemy Enemy[10];
	//37
	

	//初期化処理のオーバーライド
	void Init();
	
	//更新処理のオーバーライド
	void Update();

	static int GameTime;

	

	static int Remain;

	//残り時間（30秒）
	static int Time;
	//スコア
	static int ScoreCount;
	//ゲームクリア
	static int CLEAR;
	//ゲームオーバー
	static int OVER;
	//ボスのフラグ管理
	static int Bossflug;
	//エネミーのカウンタ
	static int EnemyCount;
	//ボスのカウンタ
	static int BossCount;
	//整数を文字列に変換する
	static char buf[10];//9文字までOK

	EScene GetNextScene();
	//デストラクタの宣言
	~CSceneGame();

};

#endif
