#include "CXPlayerManager.h"
#include "CPlayerData.h"
#include "CXEnemy.h"

//プレイヤマネージャクラスのポインタをnullptrに設定
CXPlayerManager* CXPlayerManager::mInstance = nullptr;

//デフォルトコンストラクタ
CXPlayerManager::CXPlayerManager()
	: mPlayerList(0)
{

}

//デストラクタ
//プレイヤを削除する
CXPlayerManager::~CXPlayerManager()
{
	for (size_t i = 0; i < mPlayerList.size(); i++) {
		delete mPlayerList[i];
	}
}

//プレイヤマネージャを生成する
void CXPlayerManager::Generate()
{
	mInstance = new CXPlayerManager;
}

//プレイヤマネージャを削除する
void CXPlayerManager::Release()
{
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}

//外部クラスからプレイヤマネージャのインスタンスを取得用
CXPlayerManager* CXPlayerManager::GetInstance()
{
	return mInstance;
}

//敵の生成処理
//引数で生成数、種類を設定する
void CXPlayerManager::PlayerGenerate() {
	//3Dモデルファイルの読み込み
	gPlayer_Model_Knight.Load(PLAYER_MODEL_FILE);
	//プレイヤのアニメーションの追加
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_AVOIDANCE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_DEATH);

	//プレイヤの生成
	CXPlayer* tmp = new CXPlayer;
	//敵の初期設定
	//プレイヤのテーブルを呼び出す
	//HPなどのステータスが呼び出される
	tmp->PlayerTable();
	//ポジションを設定する
	tmp->GetPos();
	//プレイヤのモデルの大きさを設定する
	tmp->GetScale();
	//プレイヤのモデルの回転を設定する
	tmp->GetRotation();
	//プレイヤのモデルを設定する
	tmp->Init(&gPlayer_Model_Knight);
	//更新処理を呼び出す
	tmp->Update();
	//当たり判定タスクを設定する
	tmp->TaskCollision();
	mPlayerList.push_back(tmp);	//リストに追加

}