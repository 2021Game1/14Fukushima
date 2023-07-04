#ifndef CXPLAYERMANAGER_H
#define CXPLAYERMANAGER_H

#include "CXPlayer.h"
#include"CRes.h"
/*
CXPlayerManagerクラス
プレイヤ生成クラス
*/


class CXPlayerManager : public CXCharacter{
public:
	CXPlayerManager();	//デフォルトコンストラクタ
	~CXPlayerManager();	//デストラクタ
	static CXPlayerManager* GetInstance(); //インスタンス取得

	void Generate(); //生成

	void Release(); //破棄

	void Update();	//タスクマネージャに格納するためのメソッド(動かさない処理)

	void Init();	//タスクマネージャに格納するためのメソッド(動かさない処理)

	void Render();  //タスクマネージャに格納するためのメソッド(動かさない処理)

	void PlayerGenerate(); //敵生成、引数で生成数と敵の種類を指定する


private:

	static CXPlayerManager* mInstance; //プレイヤ管理のインスタンス

	std::vector<CXPlayer*> mPlayerList; //プレイヤ格納

	//プレイヤモデル
	CModelX gPlayer_Model_Knight;

};

#endif