#include "CEffect.h"
CMaterial CEffect::sMaterial;//マテリアル.テクスチャ



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

	if (mFrame == (mRows * mCols) * mFps)
	{
		mEnabled = false;
	}

}
void CEffect::Render()
{
	glDisable(GL_DEPTH_TEST);//深度テスト無効
	
	glEnable(GL_DEPTH_TEST);//深度テスト有効
}
