#include "CMoney.h"
#include <time.h>


#define OBJ "res\\goldbar.obj" //モデルのファイル
#define MTL "res\\goldbar.mtl" //モデルのマテリアルファイル


CModel CMoney::mModel;//モデルデータ作成

//デフォルトコンストラクタ
CMoney::CMoney()
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
{
	//モデルが無い時は読み込む
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//モデルのポインタ設定
	mpModel = &mModel;

	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
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
				//エフェクト生成
				new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
				mEnabled = false;
				mMoney = mMoney + 1;
			}
			break;
		}
	}
	
}

void CMoney::Update() {
		if (mRepop % 100 == 50) {
			//乱数値=rand()%乱数値の要素数+乱数値の最小値
			srand((unsigned)time(NULL));
			vel = (rand() % 100) + 1;
			for (int i = 0; i < 1; i++) {
				if (vel >= 0 && vel <= 7) {
					new CMoney(CVector(75.0f, -0.5f, 76.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 8 && vel <= 15) {
					new CMoney(CVector(71.0f, -0.5f, 153.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 16 && vel <= 23) {
					new CMoney(CVector(0.0f, -0.5f, 159.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 24 && vel <= 31) {
					new CMoney(CVector(-61.5f, -0.5f, 158.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 32 && vel <= 39) {
					new CMoney(CVector(-60.0f, -0.5f, 105.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 40 && vel <= 47) {
					new CMoney(CVector(-16.0f, -0.5f, 0.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 48 && vel <= 55) {
					new CMoney(CVector(25.0f, -0.5f, 49.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 56 && vel <= 63) {
					new CMoney(CVector(73.5f, -0.5f, -35.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 64 && vel <= 71) {
					new CMoney(CVector(-63.0f, -0.5f, -30.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 78 && vel <= 85) {
					new CMoney(CVector(-100.0f, -0.5f, 35.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 86 && vel <= 93) {
					new CMoney(CVector(20.0f, -0.5f, 58.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 94 && vel <= 101) {
					new CMoney(CVector(50.0f, -0.5f, 50.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
		}
		mRepop = mRepop + 1;

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


