#include"CXPlayer.h"



void CXPlayer::Update() {

	if (CKey::Once(' ')) {
		ChangeAnimation(3, false, 30);
	}
	else if (IsAnimationFinished() && mAnimationIndex == 3){
		ChangeAnimation(4, false, 30);
	}
	//Wキー入力で前進
	if (CKey::Push('W') && !CKey::Push(' ')) {
		mPosition = mPosition + (mMatrixRotate.VectorZ()* 0.1f);
		ChangeAnimation(1,true,60);

	}
	else if (IsAnimationFinished() || mAnimationIndex == 1)
	{
		ChangeAnimation(0, true, 60);
	}
	//Aキーを押すと２度回転
	if (CKey::Push('A') && !CKey::Push(' ')) {
		mRotation = mRotation + (mMatrixRotate.VectorY() * 2.0f);
	}
	//Dキーを押すと２度回転
	if (CKey::Push('D') && !CKey::Push(' ')) {
		mRotation = mRotation - (mMatrixRotate.VectorY() * 2.0f);
	}



	CXCharacter::Update();
}