#include "CXEnemyManager.h"

//ポインタの初期化
CXEnemyManager* CXEnemyManager::mInstance = nullptr;

//初期化
CXEnemyManager::CXEnemyManager()
	: mEnemyDeathNum(NULL)
	, mEnemyList(NULL)
	, mPlayerPos(PLAYER_ATTACK_POS)
	, mEnemyPos(NULL)
	, tmp1(NULL)
	, tmp2(NULL)
	, tmp3(NULL)
{

}

//終了時
CXEnemyManager::~CXEnemyManager()
{
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		delete mEnemyList[i];
	}

	mInstance = this;
	//タスクマネージャへの追加
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
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
		delete mInstance;
	}
}

//外部クラスから敵マネージャインスタンスの取得用
CXEnemyManager* CXEnemyManager::GetInstance()
{
	return mInstance;
}



//敵の生成処理
//引数で生成数、種類を設定する
void CXEnemyManager::EnemyGenerate(int num, CXEnemy::EEnemyType type)
{
	//指定した生成数に応じて、生成を実行する
	for (int i = NULL; i < num; i++) {
		//生成する敵の種類を判別
		switch (type) {
		case CXEnemy::EEnemyType::ETYPE_TUTORIAL:	//チュートリアル時の敵の強さ
		{
			//敵を生成
			tmp1 = new CXEnemy;
			//敵の初期設定
			tmp1->SetIsType(CXEnemy::EEnemyType::ETYPE_TUTORIAL);
			//テーブルでHPなどのパラメータの設定
			tmp1->EnemyTable();
			//更新処理を設定
			tmp1->Update();
			//リストに追加
			mEnemyList.push_back(tmp1);
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_1:	//ゲーム本番時の敵の強さ(強い)
		{
			//敵を生成
			tmp2 = new CXEnemy;
			//敵の初期設定
			tmp2->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_1);
			//テーブルでHPなどのパラメータの設定
			tmp2->EnemyTable();
			//更新処理を設定
			tmp2->Update();
			//リストに追加
			mEnemyList.push_back(tmp2);
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_2:	//ゲーム本番時の敵の強さ(強い)
		{
			//敵を生成
			tmp3 = new CXEnemy;
			//敵の初期設定
			tmp3->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_2);
			//テーブルでHPなどのパラメータの設定
			tmp3->EnemyTable();
			//更新処理を設定
			tmp3->Update();
			//リストに追加
			mEnemyList.push_back(tmp3);
		}
		break;

		}
	}
}

void CXEnemyManager::Update()
{
	//リセット
	mEnemyDeathNum = NULL;
	//リストに格納されている敵が死亡状態か、どうかを判別する
	for (size_t i = NULL; i < mEnemyList.size(); i++) {
		//敵が生成されていなければスルー
		if (!tmp1 == NULL) {

			//ターゲット設定
			//敵の位置情報をプレイヤとの距離と参照
			mTarget = tmp1->Position() - CXPlayer::GetInstance()->Position();

			//敵が死亡時に実行
			if (tmp1->GetIsDeath())
			{
				mEnemyDeathNum++; //死亡状態の敵のカウント加算
				continue; //読み飛ばし
			}

			//敵の位置情報をベクトルに変換し、格納
			mEnemyPos = mTarget.Length();

			//敵の位置情報がプレイヤの攻撃距離より近い場合、実行する
			if (mPlayerPos > mEnemyPos) {
				//ターゲットに格納する
				mTargetEnemy = mTarget.Normalize();
			}
		}
		//生成されていなければスルー
		if (!tmp2 == NULL) {
			//ターゲット設定
			//敵の位置情報をプレイヤとの距離と参照
			mTarget = tmp2->Position() - CXPlayer::GetInstance()->Position();

			//敵が死亡時に実行
			if (tmp2->GetIsDeath())
			{
				mEnemyDeathNum++; //死亡状態の敵のカウント加算
				continue; //読み飛ばし
			}

			//敵の位置情報をベクトルに変換し、格納
			mEnemyPos = mTarget.Length();

			//敵の位置情報がプレイヤの攻撃距離より近い場合、実行する
			if (mPlayerPos > mEnemyPos) {
				//ターゲットに格納する
				mTargetEnemy = mTarget.Normalize();
			}
		}
		//生成されていなければスルー
		if (!tmp3 == NULL) {

			//ターゲット設定
			//敵のリ位置情報をプレイヤとの距離と参照
			mTarget = tmp3->Position() - CXPlayer::GetInstance()->Position();

			//敵が死亡時に実行
			if (tmp3->GetIsDeath())
			{
				mEnemyDeathNum++; //死亡状態の敵のカウント加算
				continue; //読み飛ばし
			}

			//敵の位置情報をベクトルに変換し、格納
			mEnemyPos = mTarget.Length();

			//敵の位置情報がプレイヤの攻撃距離より近い場合、実行する
			if (mPlayerPos > mEnemyPos) {
				//ターゲットに格納する
				mTargetEnemy = mTarget.Normalize();
			}
		}
	}
}

//タスクマネージャに格納するためのメソッド(動かさない処理)
void CXEnemyManager::Init()
{
}

//タスクマネージャに格納するためのメソッド(動かさない処理)
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
//ターゲットするべき敵を取得する
CVector CXEnemyManager::GetTargetEnemy()
{
	//格納した敵の位置情報を返す
	return mTargetEnemy;
}