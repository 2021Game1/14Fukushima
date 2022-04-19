#include"CEnemy2.h"
//プレイヤークラスのインクルード
#include "CPlayer.h"

#define OBJ "res\\f16.obj" //モデルのファイル
#define MTL "res\\f16.mtl" //モデルのマテリアルファイル
#define HP 3	//耐久値

CModel CEnemy2::sModel;//モデルデータ作成

//デフォルトコンストラクタ
CEnemy2::CEnemy2()
:mCollider(this, &mMatrix,CVector(0.0f,0.0f,0.0f),0.4f),mHp(HP)
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
			if (mHp >= 0)
			{
				mHp--;
			}
		}
		break;
	}

	case CCollider::ETRIANGLE: { //三角コライダの時
		CVector adjust; //調整値
		//三角コライダと球コライダの衝突判定
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			if (mHp <= 0)
			{
				mEnabled = false;
			}
			//衝突しない位置まで戻す
			mPosition = mPosition + adjust;
		}

		break;
	}

	}
}
//更新処理
void CEnemy2::Update()
{
	//左向き(X軸)のベクトルを求める
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//上向き(Y軸)のベクトルを求める
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//前方向(Z軸)のベクトルを求める
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//プレイヤーのポインタが0以外の時
	CPlayer* player = CPlayer::Get();
	if (player != nullptr)
	{
		//プレイヤーまでのベクトルを求める
		CVector vp = player->Position() - mPosition;
		float dx = vp.Dot(vx); //左ベクトルとの内積を求める
		float dy = vp.Dot(vy); //上ベクトルとの内積を求める
		float dz = vp.Dot(vz); //前方向のベクトルとの内積を求める
		if (0.0f < dz && dz < 30.0f)
		{
			//X軸のズレが2.0以下
			if (-2.0f < dx && dx < 2.0f)
			{
				//Y軸のズレが2.0以下
				if (-2.0f < dy && dy < 2.0f)
				{
					//弾を発射します
					CBullet* bullet = new CBullet();
					bullet->Set(0.1f, 1.5f);
					bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
					bullet->Rotation(mRotation);
					bullet->Update();
				}
			}
		}
	}
	//HPが0以下の時　撃破
	if (mHp <= 0)
	{
		mHp--;
		//15フレーム毎にエフェクト
		if (mHp % 15 == 0)
		{
			//エフェクト生成
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		//下降させる
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();
		return;
	}
}
void CEnemy2::TaskCollision()
{
	//コライダの優先度変更
	mCollider.ChangePriority();
	//衝突処理を実行
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}