#include"CXPlayer.h"



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