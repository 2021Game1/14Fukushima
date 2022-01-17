#include "CEffect.h"


//CEffect::CEffect(const CRectangle& pos, float w, float h, char* texture, int row, int col, int fps) : CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0) {
//	//�e�N�X�`����ǂ�łȂ��ꍇ�͓ǂ�
//	if (Texture()->Id() == 0)
//	{
//		sMaterial.Texture()->Load(texture);
//		sMaterial.Diffuse()[0] = 1.0f;
//		EMATERIAL.Diffuse()[1] = 1.0f;
//		EMATERIAL.Diffuse()[2] = 1.0f;
//		EMATERIAL.Diffuse()[3] = 1.0f;
//	}
//}



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
	//�X�V
	CRectangle::Update();
	if (mFrame == (mRows * mCols) * mFps)
	{
		mEnabled = false;
	}

}
void CEffect::Render()
{
	glDisable(GL_DEPTH_TEST);//�[�x�e�X�g����
	CRectangle::Render();
	glEnable(GL_DEPTH_TEST);//�[�x�e�X�g�L��
}
