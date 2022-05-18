#include "CMissile.h"

#define OBJ "res\\missile.obj" //モデルのファイル
#define MTL "res\\missile.mtl" //モデルのマテリアルファイル

CModel CMissile::cpModel;//モデルデータ作成



CMissile::CMissile()
:mLife(90),mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.2f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 0.0f, 1.5f), 0.2f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 0.0f, -2.0f), 0.2f)
{
	//モデルが無い時は読み込む
	if (cpModel.Triangles().size() == 0) {
		cpModel.Load(OBJ, MTL);
		//モデルのポインタ設定
		mpModel = &cpModel;
	}
}

//コンストラクタ
//CEnemy(位置,回転,拡縮)
CMissile::CMissile(const CVector& position, const CVector& rotation, const CVector& scale)
: CMissile()	//デフォルトコンストラクタを実行する
{
	//位置,回転,拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定
	//優先度を1に変更する
	mPriority = 2;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}



//更新処理
void CMissile::Update() {
	////生存時間の判定
	//if (mLife-- > 0)
	//{
	//	CTransform::Update();
	//	//位置更新
	//	mPosition = CVector(0.0f, -0.1f, 0.9f) * mMatrix;
	//}
	//else {
	//	//無効にする
	//	mEnabled = false;
	//}
	CTransform::Update();
}


//衝突処理
//Collision(コライダ1,コライダ2)
void CMissile::Collision(CCollider* m, CCollider* o) {
	//コライダのmとoが衝突しているかを判定
	if (CCollider::Collision(m, o)) {
		//衝突している時は無効にする
		mEnabled = false;
	}
}

//衝突処理
void CMissile::TaskCollision()
{
	//コライダの優先度変更
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);

}