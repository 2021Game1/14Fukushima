#include "CEffect.h"
CMaterial CEffect::sMaterial;//�}�e���A��.�e�N�X�`��



void CEffect::Update() {
	//�R�}���̌v�Z
	int frame = mFrame++ / mFps;
	frame %= (mRows * mCols);
	//UV��
	float left = 1.0f / mCols * (frame % mCols);
	//UV�E
	float right = left + 1.0f / mCols;
	//UV��
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV��
	float bot = top - 1.0f / mRows;
	//�e�N�X�`���}�b�s���O

	if (mFrame == (mRows * mCols) * mFps)
	{
		mEnabled = false;
	}

}
void CEffect::Render()
{
	glDisable(GL_DEPTH_TEST);//�[�x�e�X�g����
	
	glEnable(GL_DEPTH_TEST);//�[�x�e�X�g�L��
}
