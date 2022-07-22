#include"CXPlayer.h"



void CXPlayer::Update() {

	if (CKey::Once(' ')) {
		ChangeAnimation(3, false, 30);
	}
	else if (IsAnimationFinished() && mAnimationIndex == 3){
		ChangeAnimation(4, false, 30);
	}
	//W�L�[���͂őO�i
	if (CKey::Push('W') && !CKey::Push(' ')) {
		mPosition = mPosition + (mMatrixRotate.VectorZ()* 0.1f);
		ChangeAnimation(1,true,60);

	}
	else if (IsAnimationFinished() || mAnimationIndex == 1)
	{
		ChangeAnimation(0, true, 60);
	}
	//A�L�[�������ƂQ�x��]
	if (CKey::Push('A') && !CKey::Push(' ')) {
		mRotation = mRotation + (mMatrixRotate.VectorY() * 2.0f);
	}
	//D�L�[�������ƂQ�x��]
	if (CKey::Push('D') && !CKey::Push(' ')) {
		mRotation = mRotation - (mMatrixRotate.VectorY() * 2.0f);
	}



	CXCharacter::Update();
}