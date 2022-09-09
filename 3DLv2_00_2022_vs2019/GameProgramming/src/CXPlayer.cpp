#include"CXPlayer.h"

//コライダ初期化
CXPlayer::CXPlayer()
	:mColSphereBody(this,nullptr,CVector(),0.5)
	,mColSphereHead(this,nullptr,CVector(0.0f,5.0f,-3.0f),0.5f)
	,mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[8]);
	mColSphereHead.Matrix(&mpCombinedMatrix[11]);
	mColSphereSword.Matrix(&mpCombinedMatrix[21]);
}
void CXPlayer::Update() {
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
			ChangeAnimation(1, true, 60);

		}
		else if (mAnimationIndex == 1)
		{
			ChangeAnimation(0, true, 60);
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