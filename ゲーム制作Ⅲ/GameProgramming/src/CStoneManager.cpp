#include "CStoneManager.h"

//ポインタの初期化
CStoneManager* CStoneManager::mInstance = nullptr;

//初期化
CStoneManager::CStoneManager()
	: mStoneList(NULL)
	, tmp1(NULL)
	, tmp2(NULL)
	, tmp3(NULL)
{
	mInstance = this;
	//タスクマネージャへの追加
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}

//終了時
CStoneManager::~CStoneManager()
{
	for (size_t i = NULL; i < mStoneList.size(); i++) {
		delete mStoneList[i];
	}
}

//敵のマネージャをで生成
void CStoneManager::Generate()
{
	mInstance = new CStoneManager;
}

//敵のマネージャを削除する
void CStoneManager::Release()
{
	if (mInstance) {
		mInstance = nullptr;
		delete mInstance;
	}
}

//外部クラスから敵マネージャインスタンスの取得用
CStoneManager* CStoneManager::GetInstance()
{
	return mInstance;
}



//敵の生成処理
//引数で生成数、種類を設定する
void CStoneManager::StoneGenerate(CStone::EStoneType type)
{

	//モデル設定
	//生成する敵の種類を判別
	switch (type) {
	case CStone::EStoneType::ETYPE_STONE_POS_1:	//プレイヤの初期位置から見て東に配置
	{
		//敵を生成
		tmp1 = new CStone;
		//敵の初期設定
		tmp1->SetIsType(CStone::EStoneType::ETYPE_STONE_POS_1);
		//テーブルでHPなどのパラメータの設定
		tmp1->StoneTable();
		//リストに追加
		mStoneList.push_back(tmp1);
	}
	break;

	case CStone::EStoneType::ETYPE_STONE_POS_2:	//プレイヤの初期位置から見て西に配置
	{
		//敵を生成
		tmp2 = new CStone;
		//敵の初期設定
		tmp2->SetIsType(CStone::EStoneType::ETYPE_STONE_POS_2);
		//テーブルでHPなどのパラメータの設定
		tmp2->StoneTable();
		//リストに追加
		mStoneList.push_back(tmp2);
	}
	break;

	case CStone::EStoneType::ETYPE_STONE_POS_3:	//プレイヤの初期位置から見て北に配置
	{
		//敵を生成
		tmp3 = new CStone;
		//敵の初期設定
		tmp3->SetIsType(CStone::EStoneType::ETYPE_STONE_POS_3);
		//テーブルでHPなどのパラメータの設定
		tmp3->StoneTable();
		//リストに追加
		mStoneList.push_back(tmp3);
	}
	break;

	}
}
//タスクマネージャに格納するためのメソッド(動かさない処理)
void CStoneManager::Update()
{
}

//タスクマネージャに格納するためのメソッド(動かさない処理)
void CStoneManager::Init()
{
}

//タスクマネージャに格納するためのメソッド(動かさない処理)
void CStoneManager::Render()
{
}


