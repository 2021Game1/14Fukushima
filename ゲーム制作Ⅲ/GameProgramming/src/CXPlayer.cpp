#include"CXPlayer.h"
#include"CSceneGame.h"
#include "CCamera.h"
#define GRAVITY 0.1f//重力

CXPlayer* CXPlayer::mpPlayerInstance;
//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayerInstance;
}

//コライダ初期化
CXPlayer::CXPlayer()
	:mColSphereBody(this,nullptr,CVector(),0.5)
	,mColSphereHead(this,nullptr,CVector(0.0f,5.0f,-3.0f),0.5f)
	,mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
	mTag = EPLAYER;
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[9]);
	mColSphereHead.Matrix(&mpCombinedMatrix[12]);
	mColSphereSword.Matrix(&mpCombinedMatrix[22]);

}
void CXPlayer::Update() {
	CSceneGame* tSceneGame = CSceneGame::GetInstance();
	if (CKey::Once(' ')) {
		ChangeAnimation(3, false, 30);
	}
	else if (IsAnimationFinished() && mAnimationIndex == 3) {
		ChangeAnimation(4, false, 30);
	}
	if (IsAnimationFinished())
	{
		ChangeAnimation(0, true, 60);
	}


	if (mAnimationIndex == 1 || mAnimationIndex == 0)
	{
		//Wキー入力で前進
		if (CKey::Push('W')) {
			mPosition = mPosition + (mMatrixRotate.VectorZ() * 0.1f);
			ChangeAnimation(0, true, 60);

		}
		else if (mAnimationIndex == 1)
		{
			ChangeAnimation(1, true, 60);
		}
		//Aキーを押すと２度回転
		if (CKey::Push('A')) {
			mRotation = mRotation + (mMatrixRotate.VectorY() * 2.0f);
		}
		//Dキーを押すと２度回転
		if (CKey::Push('D')) {
			mRotation = mRotation - (mMatrixRotate.VectorY() * 2.0f);
		}
	}


	CXCharacter::Update();
}
void CXPlayer::Collision(CCollider* m, CCollider* o) {
	//自身のコライダタイプの判定
	switch (m->Type()) {
	case CCollider::ESPHERE: {//球コライダ
		//相手のコライダが三角コライダの時
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//調整用ベクトル
			//三角形と球の衝突判定
			CCollider::CollisionTriangleSphere(o, m, &adjust);
			//位置の更新(mPosition + adjust)
			mPosition = mPosition + adjust;
			//行列の更新
			CTransform::Update();
		}
	}
	}
}