#include"CXPlayer.h"



void CXPlayer::Update() {
	//W�L�[���͂őO�i
	if (CKey::Push('W')) {
		mPosition = mPosition + (CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate);
		CXCharacter::ChangeAnimation(1,true,60);
	}
	else {
		CXCharacter::ChangeAnimation(0, true, 60);
	}
	CXCharacter::Update();
}