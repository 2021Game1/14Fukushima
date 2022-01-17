#include "CEffect.h"


//CEffect::CEffect(const CRectangle& pos, float w, float h, char* texture, int row, int col, int fps) : CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0) {
//	//テクスチャを読んでない場合は読む
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
	//コマ数の計算
	int frame = mFrame++ / mFps;
	frame %= (mRows * mCols);
	//UV左
	float left = 1.0f / mCols * (frame % mCols);
	//UV右
	float right = left + 1.0f / mCols;
	//UV上
	float top = 1.0f - 1.0f / mRows * (frame / mCols);
	//UV下
	float bot = top - 1.0f / mRows;
	//テクスチャマッピング
	//更新
	CRectangle::Update();
	if (mFrame == (mRows * mCols) * mFps)
	{
		mEnabled = false;
	}

}
void CEffect::Render()
{
	glDisable(GL_DEPTH_TEST);//深度テスト無効
	CRectangle::Render();
	glEnable(GL_DEPTH_TEST);//深度テスト有効
}
