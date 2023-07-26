#ifndef CSTONEMANAGER_H
#define CSTONEMANAGER_H

#include"CStone.h"

/*
CStoneManagerクラス
障害物の生成クラス
*/


class CStoneManager :public CCharacter {
public:

	CStoneManager();	//デフォルトコンストラクタ

	~CStoneManager();	//デストラクタ

	static CStoneManager* GetInstance(); //インスタンス取得

	static void Generate(); //生成

	static void Release(); //破棄

	void Update();	//タスクマネージャに格納するためのメソッド(動かさない処理)

	void Init();	//タスクマネージャに格納するためのメソッド(動かさない処理)

	void Render();  //タスクマネージャに格納するためのメソッド(動かさない処理)



	//敵生成
	void StoneGenerate(CStone::EStoneType type); //障害物生成、障害物の種類を指定する

private:
	//障害物管理のインスタンス
	static CStoneManager* mInstance;
	//障害物の格納
	std::vector<CStone*> mStoneList;
	//障害物の生成
	CStone* tmp1;
	CStone* tmp2;
	CStone* tmp3;
};

#endif