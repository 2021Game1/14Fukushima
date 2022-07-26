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
		//W�L�[���͂őO�i
		if (CKey::Push('W')) {
			mPosition = mPosition + (mMatrixRotate.VectorZ() * 0.1f);
			ChangeAnimation(1, true, 60);

		}
		else if (mAnimationIndex == 1)
		{
			ChangeAnimation(0, true, 60);
		}
		//A�L�[�������ƂQ�x��]
		if (CKey::Push('A')) {
			mRotation = mRotation + (mMatrixRotate.VectorY() * 2.0f);
		}
		//D�L�[�������ƂQ�x��]
		if (CKey::Push('D')) {
			mRotation = mRotation - (mMatrixRotate.VectorY() * 2.0f);
		}
	}




	CXCharacter::Update();
}