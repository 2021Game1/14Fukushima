#include"CXPlayer.h"



void CXPlayer::Update() {
	//Wキー入力で前進
	if (CKey::Push('W')) {
		mPosition = mPosition + (mMatrixRotate.VectorZ()* 0.1f);
		CXCharacter::ChangeAnimation(1,true,60);
	}
	else {
		CXCharacter::ChangeAnimation(0, true, 60);
	}
	//Aキーを押すと２度回転
	if (CKey::Push('A')) {
		mRotation = mRotation + (mMatrixRotate.VectorY() * 2.0f);
	}
	//Dキーを押すと２度回転
	if (CKey::Push('D')) {
		mRotation = mRotation - (mMatrixRotate.VectorY() * 2.0f);
	}

	CXCharacter::Update();
}