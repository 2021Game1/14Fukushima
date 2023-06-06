#include "CXEnemyManager.h"
#include "CEnemyData.h"

CXEnemyManager* CXEnemyManager::mInstance = nullptr;


CXEnemyManager::CXEnemyManager()
	: mEnemyDeathNum(0)
	, mEnemyList(0)
{

}

CXEnemyManager::~CXEnemyManager()
{
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		delete mEnemyList[i];
	}
}

void CXEnemyManager::Generate()
{
	mInstance = new CXEnemyManager;
}

void CXEnemyManager::Release()
{
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}


CXEnemyManager* CXEnemyManager::GetInstance()
{
	return mInstance;
}

//敵の生成処理
//引数で生成数、種類を設定する
void CXEnemyManager::EnemyGenerate(int num, CXEnemy::EEnemyType type){
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

	for (int i = 0; i < num; i++) {
		//生成する敵の種類を判別
		switch (type) {
		case CXEnemy::EEnemyType::ETYPE_TUTORIAL:	//チュートリアル時の敵の強さ
		{
			CXEnemy* tmp = new CXEnemy;
			//敵の初期設定
			tmp->SetIsType(CXEnemy::EEnemyType::ETYPE_TUTORIAL);
			tmp->EnemyTable();
			tmp->GetPos();
			tmp->GetScale();
			tmp->GetRotation();
			tmp->Init(&gEnemy_Model_Mutant);
			tmp->Update();
			tmp->TaskCollision();
			mEnemyList.push_back(tmp);	//リストに追加
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_1:	//ゲーム本番時の敵の強さ(強い)
		{
			CXEnemy* tmp = new CXEnemy;
			//敵の初期設定
			tmp->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_1);
			tmp->EnemyTable();
			tmp->SetIsPriority();
			tmp->GetPos();
			tmp->GetScale();
			tmp->GetRotation();
			tmp->Init(&gEnemy_Model_Mutant);
			tmp->Update();
			tmp->TaskCollision();
			mEnemyList.push_back(tmp);	//リストに追加
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_2:	//ゲーム本番時の敵の強さ(弱い)
		{
			CXEnemy* tmp = new CXEnemy;
			//敵の初期設定
			tmp->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_2);
			tmp->EnemyTable();
			tmp->GetPos();
			tmp->GetScale();
			tmp->GetRotation();
			tmp->Init(&gEnemy_Model_Mutant);
			tmp->Update();
			tmp->TaskCollision();
			mEnemyList.push_back(tmp);	//リストに追加
		}
		break;

		}
	}
}

void CXEnemyManager::Update()
{
	//リセット
	mEnemyDeathNum = 0;

	for (size_t i = 0; i < mEnemyList.size(); i++) {
		//死亡状態だった時
		if (CXEnemy::GetInstance()->GetIsDeath()) {
			mEnemyDeathNum++; //死亡状態の敵のカウント加算
			continue; //読み飛ばし
		}
	}
}

void CXEnemyManager::Render()
{
}

//敵が全て死亡状態のときtrueを返す
bool CXEnemyManager::GetIsEnemyAllDeath()
{
	if (mEnemyList.size() == mEnemyDeathNum)return true;
	else return false;
}
