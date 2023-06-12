#include "CXEnemyManager.h"
#include "CEnemyData.h"
#include "CXPlayer.h"

CXEnemyManager* CXEnemyManager::mInstance = nullptr;

//初期化
CXEnemyManager::CXEnemyManager()
	: mEnemyDeathNum(0)
	, mEnemyList(0)
	, mPlayerPos(5.3)
	, mEnemyPos(0)
{

}

//終了時
CXEnemyManager::~CXEnemyManager()
{
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		delete mEnemyList[i];
	}
}
//敵のマネージャをで生成
void CXEnemyManager::Generate()
{
	mInstance = new CXEnemyManager;
}
//敵のマネージャを削除する
void CXEnemyManager::Release()
{
	if (mInstance) {
		mInstance = nullptr;
	}
}

//外部クラスから敵マネージャインスタンスの取得用
CXEnemyManager* CXEnemyManager::GetInstance()
{
	return mInstance;
}

//敵の生成処理
//引数で生成数、種類を設定する
void CXEnemyManager::EnemyGenerate(int num, CXEnemy::EEnemyType type){
	for (int i = 0; i < num; i++) {
		Init();
		//生成する敵の種類を判別
		switch (type) {
		case CXEnemy::EEnemyType::ETYPE_TUTORIAL:	//チュートリアル時の敵の強さ
		{
			//敵を生成
			CXEnemy* tmp1 = new CXEnemy;
			//敵の初期設定
			//敵のタイプを設定
			tmp1->SetIsType(CXEnemy::EEnemyType::ETYPE_TUTORIAL);
			//敵にモデルを設定する
			tmp1->Init(&gEnemy_Model_Mutant);
			//テーブルでHPなどのパラメータの設定
			tmp1->EnemyTable();
			//ポジションの取得
			tmp1->GetPos();
			//モデルの大きさを取得
			tmp1->GetScale();
			//モデルの回転を取得
			tmp1->GetRotation();
			//更新処理を設定
			tmp1->Update();
			//当たり判定のタスクに追加
			tmp1->TaskCollision();
			mEnemyList.push_back(tmp1);	//リストに追加
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_1:	//ゲーム本番時の敵の強さ(強い)
		{
			//敵を生成
			CXEnemy* tmp2 = new CXEnemy;
			//敵の初期設定
			//敵のタイプを設定
			tmp2->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_1);
			//テーブルでHPなどのパラメータの設定
			tmp2->EnemyTable();
			//ポジションの取得
			tmp2->GetPos();
			//モデルの大きさを取得
			tmp2->GetScale();
			//モデルの回転を取得
			tmp2->GetRotation();
			//敵にモデルを設定する
			tmp2->Init(&gEnemy_Model_Mutant);
			//更新処理を設定
			tmp2->Update();
			//当たり判定のタスクに追加
			tmp2->TaskCollision();
			mEnemyList.push_back(tmp2);	//リストに追加
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_2:	//ゲーム本番時の敵の強さ(弱い)
		{
			//敵を生成
			CXEnemy* tmp3 = new CXEnemy;
			//敵の初期設定
			//敵のタイプを設定
			tmp3->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_2);
			//テーブルでHPなどのパラメータの設定
			tmp3->EnemyTable();
			//ポジションの取得
			tmp3->GetPos();
			//モデルの大きさを取得
			tmp3->GetScale();
			//モデルの回転を取得
			tmp3->GetRotation();
			//敵にモデルを設定する
			tmp3->Init(&gEnemy_Model_Mutant);
			//更新処理を設定
			tmp3->Update();
			//当たり判定のタスクに追加
			tmp3->TaskCollision();
			mEnemyList.push_back(tmp3);	//リストに追加
		}
		break;

		}
	}
}
//初期化
void CXEnemyManager::Init()
{
	//3Dモデルファイルの読み込み
	gEnemy_Model_Mutant.Load(ENEMY_MODEL_FILE);
	//エネミーのアニメーションの追加
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP1);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_BACKSTEP);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);
}

void CXEnemyManager::Update()
{
	//リセット
	mEnemyDeathNum = 0;
	//リストに格納されている敵が死亡状態か、どうかを判別する
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		//死亡状態だった時
		if (CXEnemy::GetInstance()->GetIsDeath()) {
			mEnemyDeathNum++; //死亡状態の敵のカウント加算
			continue; //読み飛ばし
		}
		mTarget = mEnemyList[i]->GetInstance()->Position() - CXPlayer::GetInstance()->Position();
		mEnemyPos = mTarget.Length();
		if (mPlayerPos > mEnemyPos) {
			mTargetEnemy = mTarget.Normalize();
		}
	}
}


//描画しない
void CXEnemyManager::Render()
{
}

//敵が全て死亡状態のときtrueを返す
bool CXEnemyManager::GetIsEnemyAllDeath()
{
	//リストに登録されている敵が死亡状態の敵の数と一致したらtrue
	if (mEnemyList.size() == mEnemyDeathNum)return true;
	//一致しなければfalse
	else return false;
}
CVector CXEnemyManager::GetTargetEnemy()
{
	return mTargetEnemy;
}