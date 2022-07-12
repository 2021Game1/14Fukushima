#include"CXCharacter.h"

/*
Init
����������
*/
void CXCharacter::Init(CModelX* model) {
	mpModel = model;
	//�Đ��̃A�j���[�V����
	mAnimationIndex = 0;
	//�J��Ԃ��Đ�����
	mAnimationLoopFlg = true;
	//1�A�j���[�V�����ڂ̍ő�t���[����
	mAnimationFramesize =
		model->AnimationSet()[0]->MaxTime();
	//�A�j���[�V�����t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSet()[mAnimationIndex]->
		Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weught(1.0f);
}
/*
ChangeAnimation
�A�j���[�V������؂�ւ���
index:�A�j���[�V�����̔ԍ�
loop:ture �J��Ԃ�
framesize:�Ō�܂ōĐ�����̂Ɏg�p�����t���[����
*/
void CXCharacter::ChangeAnimation(int index, bool loop, float framesize) {
	//�����ꍇ�́A�؂�ւ��Ȃ�
	if (mAnimationIndex == index)return;
	//���̃A�j���[�V�����̏d�݂�0.0(0%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weught(0.0f);
	//�ԍ�,�J��Ԃ�,�t���[������ݒ�
	mAnimationIndex = index % mpModel->AnimationSet().size();
	mAnimationLoopFlg = loop;
	mAnimationFramesize = framesize;
	//�A�j���[�V�����̃t���[�����ŏ��ɂ���
	mAnimationFrame = 0.0f;
	mpModel->AnimationSet()[mAnimationIndex]->Time(mAnimationFrame);
	//�A�j���[�V�����̏d�݂�1.0(100%)�ɂ���
	mpModel->AnimationSet()[mAnimationIndex]->Weught(1.0f);
}

/*
Update
matrix:�ړ��A��]�A�g��k���̍s��
*/
void CXCharacter::Update(CMatrix& matrix) {
	//�Ō�܂ōĐ����Ă��Ȃ�
	if (mAnimationFrame < mAnimationFramesize){
		//�A�j���[�V�����̎��Ԃ��v�Z
		mpModel->AnimationSet()[mAnimationIndex]->Time(
			mpModel->AnimationSet()[mAnimationIndex]->MaxTime() * 
			mAnimationFrame / mAnimationFramesize);
		//�t���[����i�߂�
		mAnimationFrame++;
	}
	else {
		//�J��Ԃ��̏ꍇ�́A�t���[����0�ɖ߂�
		if (mAnimationLoopFlg){
			//�A�j���[�V�����̃t���[�����ŏ��ɂ���
			mAnimationFrame = 0.0f;
			mpModel->AnimationSet()[mAnimationIndex]->
				Time(mAnimationFrame);
		}
		else {
			mpModel->AnimationSet()[mAnimationIndex]->
				Time(mpModel->AnimationSet()[mAnimationIndex]->
					MaxTime());
		}
	}
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	mpModel->AnimateFrame();
	//�t���[���̍����s����v�Z����
	mpModel->Frames()[0]->AnimateCombined(&matrix);
	//���_�ɃA�j���[�V������K�p����
	mpModel->AnimeteVertex();
}

/*
�`�悷��
*/
void CXCharacter::Render() {
	mpModel->Render();
}

bool CXCharacter::IsAnimationFinished() {
	return mAnimationFrame >=
		mAnimationFramesize;
}

int CXCharacter::AnimationIndex()
{
	return mAnimationIndex;
}