#include"CEnemy2.h"

#define OBJ "res\\f16.obj" //モデルのファイル
#define MTL "res\\f16.mtl" //モデルのマテリアルファイル

CModel CEnemy2::sModel;//モデルデータ作成

//デフォルトコンストラクタ
CEnemy2::CEnemy2()
:mCollider(this, &mMatrix,CVector(0.0f,0.0f,0.0f),0.4f)
{
	//モデルが無い時は読み込む
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &sModel;
}
//コンストラクタ
//CEnemy(位置,回転,拡縮)
CEnemy2::CEnemy2(const CVector& position,const CVector& rotation,const CVector& scale)
:CEnemy2()	//デフォルトコンストラクタを実行する
{
	//位置,回転,拡縮を設定する
	mPosition = position;	//位置の設定
	mRotation = rotation;	//回転の設定
	mScale = scale;			//拡縮の設定
	CTransform::Update();	//行列の更新
	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}
//更新処理
void CEnemy2::Update()
{

}
//衝突処理
//Collision(コライダ1,コライダ2)
void CEnemy2::Collision(CCollider* m, CCollider* o)
{
	//相手のコライダタイプの判定
	switch (o->Type())
	{
	case CCollider::ESPHERE: { //球コライダの時
			//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {
			//エフェクト生成
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//衝突している時は無効にする
			//削除mEnabled = false;
		}
		break;
	}

	case CCollider::ETRIANGLE: { //三角コライダの時
		CVector adjust; //調整値
		//三角コライダと球コライダの衝突判定
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//衝突しない位置まで戻す
			mPosition = mPosition + adjust;
		}
		break;
	}

	}
}
void CEnemy2::TaskCollision()
{
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}