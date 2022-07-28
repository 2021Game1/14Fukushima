#include "CMoney.h"
#include <time.h>


#define OBJ "res\\goldbar.obj" //モデルのファイル
#define MTL "res\\goldbar.mtl" //モデルのマテリアルファイル

#include"CSceneGame.h"
#include"CSound.h"

extern CSound Se2;

CModel CMoney::mModel;//モデルデータ作成

//デフォルトコンストラクタ
CMoney::CMoney()
	:mCollider(this, &mMatrix, CVector(0.0f, 1.5f, 0.0f), 1.0f)
{
	//モデルが無い時は読み込む
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &mModel;
	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
	mTag = EITEM;
}







//コンストラクタ
//CMoney(位置,回転,拡縮)
CMoney::CMoney(const CVector& position, const CVector& rotation, const CVector& scale)
	:CMoney()	//デフォルトコンストラクタを実行する
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





//衝突処理
//Collision(コライダ1,コライダ2)
void CMoney::Collision(CCollider* m, CCollider* o)
{
	//相手のコライダタイプの判定
	switch (o->Type())
	{
	case CCollider::ESPHERE: { //球コライダの時
				//コライダのmとoが衝突しているかの判定
				if (CCollider::Collision(m, o)) {
					if (o->Parent()->Tag() == EPLAYER)
					{
						//エフェクト生成
						new CEffect(o->Parent()->Position(), 4.0f, 4.0f, "item.png", 4, 5, 2);
						Se2.Play();
						CSceneGame::Score += 100;
						mEnabled = false;
					}
					if (o->Parent()->Tag() == EITEM)
					{
						mEnabled = false;
					}

				}
			break;
		}
	}

}

void CMoney::Update() {
	mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f);//右へ回転
	CTransform::Update();
}

void CMoney::TaskCollision()
{
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}



