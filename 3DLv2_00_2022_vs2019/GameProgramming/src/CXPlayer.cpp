#include"CXPlayer.h"



void CXPlayer::Update() {
	//W�L�[���͂őO�i
	if (CKey::Push('W')) {
		mPosition = mPosition + (mMatrixRotate.VectorZ()* 0.1f);
		CXCharacter::ChangeAnimation(1,true,60);
	}
	else {
		CXCharacter::ChangeAnimation(0, true, 60);
	}
	//A�L�[�������ƂQ�x��]
	if (CKey::Push('A')) {
		mRotation = mRotation + (mMatrixRotate.VectorY() * 2.0f);
	}
	//D�L�[�������ƂQ�x��]
	if (CKey::Push('D')) {
		mRotation = mRotation - (mMatrixRotate.VectorY() * 2.0f);
	}

	CXCharacter::Update();
}