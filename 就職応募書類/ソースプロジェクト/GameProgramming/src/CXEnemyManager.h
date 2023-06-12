#ifndef CXENEMYMANAGER_H
#define CXENEMYMANAGER_H

#include "CXEnemy.h"
#include"CRes.h"
//敵マネージャのデータテーブル
/*
CXEnemyManagerクラス
*/

#define ENEMY_A 1
#define ENEMY_B 2

class CXEnemyManager{
public:
	CXEnemyManager();	//デフォルトコンストラクタ
	~CXEnemyManager();	//デストラクタ
	static CXEnemyManager* GetInstance(); //インスタンス取得

	static void Generate(); //生成

	static void Release(); //破棄

	void Update();	//更新

	void Init();    //初期化

	void Render();	//描画(描画はしない)

	void EnemyGenerate(int num, CXEnemy::EEnemyType type); //敵生成、引数で生成数と敵の種類を指定する

	bool GetIsEnemyAllDeath(); //敵が全て死亡状態になるとtrueを返す

	CVector GetTargetEnemy(); //一番近い敵を取得する

private:
	//敵管理のインスタンス
	static CXEnemyManager* mInstance;
	//敵格納
	std::vector<CXEnemy*> mEnemyList;
	//死亡状態の敵の数
	int mEnemyDeathNum;
	//敵モデル
	CModelX gEnemy_Model_Mutant;
	//ターゲット設定
	CVector mTargetEnemy; //一番プレイヤから近い敵を格納
	//ターゲット設定保存
	CVector mTarget; 
	//ターゲット設定保存
	CVector mTargetGame1; 
	//ターゲット設定保存
	CVector mTargetGame2;
	//プレイヤ座標
	float mPlayerPos;
	//敵座標
	float mEnemyPos;
	//敵座標
	float mEnemyPosGame1;
	//敵座標
	float mEnemyPosGame2;
};
#endif

