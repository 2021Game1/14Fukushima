#include"CMap.h"



//ポインタをnullptrに設定する
CMap* CMap::mpMap_Instance = nullptr;												//インスタンス変数の初期化
CSkyMap* CSkyMap::mpSkyMap_Instance = nullptr;												//インスタンス変数の初期化

//ポインタを外部クラスから参照できるように設定
CMap* CMap::GetInstance()
{
	//ポインタを返す
	return mpMap_Instance;
}

//コライダ初期化
CMap::CMap()
{
	//マップのポインタをthisにする
	mpMap_Instance = this;
	mTag = CCharacter::ETag::EMAP;
	//マップモデルファイルの入力
	gMap_Model.Load(MAP_MODEL_MAP);
	Model(&gMap_Model);
	//マップのコライダファイルの入力
	gMap_Model_Collision.Load(MAP_COLLISION_MAP);
	//マップの移動行列
	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
	//親インスタンスと親行列はなし
	mColliderMesh.Set(this, &mBackGroundMatrix, &gMap_Model_Collision);

	//優先度を設定
	mPriority = MAP_PRIORITY;
	//タスクマネージャへの追加処理
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}
//生成処理
void CMap::Generate()
{
	mpMap_Instance = new CMap;
}
//削除処理
void CMap::Release()
{
	//ポインタを削除
	if (mpMap_Instance) {
		delete mpMap_Instance;
		mpMap_Instance = nullptr;
	}
}
//衝突処理
void CMap::Collision(CCollider* m, CCollider* o) {
	switch (m->Type())
	{
	//相手のコライダが球の場合
	case CCollider::EType::ESPHERE: {
		//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {
			//行列の更新
			CTransform::Update();
		}
	}
	//相手のコライダがカプセルの場合
	case CCollider::EType::ECAPSUL: {
		CVector adjust;//調整用ベクトル
		if (CCollider::CollisionCapsule(m, o, &adjust))
		{
			//行列の更新
			CTransform::Update();
		}
	}

	}
}
//デフォルトコンストラクタ
CSkyMap::CSkyMap()
{
	mTag = CCharacter::ETag::EMAP;
	mpSkyMap_Instance = this;
	//スカイモデルファイルの入力
	gSky_Map_Model.Load(MAP_MODEL_SKY);
	Model(&gSky_Map_Model);
	//優先度を設定
	mPriority = MAP_PRIORITY;
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//追加する
}
//衝突処理
void CSkyMap::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::EType::ESPHERE: {
		//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {

		}
	}
	}
}
//生成処理
//背景マップのモデルを生成する
void CSkyMap::Generate()
{
	mpSkyMap_Instance = new CSkyMap;
}
//削除処理
//ポインタを削除し、nullに設定する
void CSkyMap::Release()
{
	if (mpSkyMap_Instance) {
		delete mpSkyMap_Instance;
		mpSkyMap_Instance = nullptr;
	}
}
//ポインタを外部クラスから参照できるように設定
CSkyMap* CSkyMap::GetInstance()
{
	//ポインタを返す
	return mpSkyMap_Instance;
}
