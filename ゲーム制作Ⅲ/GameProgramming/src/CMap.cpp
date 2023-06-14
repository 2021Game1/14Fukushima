#include"CMap.h"




CMap* CMap::mpMap_Instance = nullptr;												//インスタンス変数の初期化
CSkyMap* CSkyMap::mpSkyMap_Instance = nullptr;												//インスタンス変数の初期化

CMap* CMap::GetInstance()
{
	return mpMap_Instance;
}

//コライダ初期化
CMap::CMap()
{
	mpMap_Instance = this;
	mTag = EMAP;
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
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//追加する
}
void CMap::Init() {

}

void CMap::Generate()
{
	mpMap_Instance = new CMap;
}
void CMap::Release()
{
	if (mpMap_Instance) {
		delete mpMap_Instance;
		mpMap_Instance = nullptr;
	}
}
void CMap::Collision(CCollider* m, CCollider* o) {
	switch (m->Type())
	{
	case CCollider::ESPHERE: {
		//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {
			//行列の更新
			CTransform::Update();
		}
	}
	case CCollider::ECAPSUL: {
		CVector adjust;//調整用ベクトル
		if (CCollider::CollisionCapsule(m, o, &adjust))
		{
			//行列の更新
			CTransform::Update();
		}
	}

	}
}

CSkyMap::CSkyMap()
{
	mTag = EMAP;
	mpSkyMap_Instance = this;
	//スカイモデルファイルの入力
	gSky_Map_Model.Load(MAP_MODEL_SKY);
	Model(&gSky_Map_Model);
	//優先度を設定
	mPriority = MAP_PRIORITY;
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//追加する
}
void CSkyMap::Init()
{

}

void CSkyMap::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::ESPHERE: {
		//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {

		}
	}
	}
}

void CSkyMap::Generate()
{
	mpSkyMap_Instance = new CSkyMap;
}

void CSkyMap::Release()
{
	if (mpSkyMap_Instance) {
		delete mpSkyMap_Instance;
		mpSkyMap_Instance = nullptr;
	}
}

CSkyMap* CSkyMap::GetInstance()
{
	return mpSkyMap_Instance;
}
