#ifndef CXENEMYMANAGER_H
#define CXENEMYMANAGER_H

#include "CXEnemy.h"
#include"CRes.h"
//敵マネージャのデータテーブル
/*
CXEnemyManagerクラス
*/


class CXEnemyManager{
public:
	CXEnemyManager();	//デフォルトコンストラクタ
	~CXEnemyManager();	//デストラクタ
	static CXEnemyManager* GetInstance(); //インスタンス取得

	void Generate(); //生成

	void Release(); //破棄

	void Update();	//更新

	void Render();

	void EnemyGenerate(int num, CXEnemy::EEnemyType type); //敵生成、引数で生成数と敵の種類を指定する

	bool GetIsEnemyAllDeath(); //敵が全て死亡状態になるとtrueを返す

private:

	static CXEnemyManager* mInstance; //敵管理のインスタンス

	std::vector<CXEnemy*> mEnemyList; //敵格納

	int mEnemyDeathNum; //死亡状態の敵の数
	//敵モデル
	CModelX gEnemy_Model_Mutant;

};
#endif

