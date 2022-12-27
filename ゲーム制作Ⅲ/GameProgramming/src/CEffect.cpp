#include "CEffect.h"

CMaterial CEffect::sMaterial; //マテリアル.テクスチャ
CEffect* CEffect::mpEffect_Instance = nullptr;

CEffect::CEffect(const CVector &pos, float w, float h, char *texture, int row, int col, int fps)
: CBillBoard(pos, w, h), mRows(row), mCols(col), mFps(fps), mFrame(0)
{
	//テクスチャを読んでない場合は読む
	if (sMaterial.Texture()->Id() == 0)
	{
		sMaterial.Texture()->Load(texture);
		sMaterial.Diffuse()[0] = 1.0f;
		sMaterial.Diffuse()[1] = 1.0f;
		sMaterial.Diffuse()[2] = 1.0f;
		sMaterial.Diffuse()[3] = 1.0f;
	}
	//優先度を1に変更する
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}
void CEffect::Update() {
	//コマ数の計算
	int frame = mFrame++ / mFps;
	if (frame == mRows*mCols)
	{
		mEnabled = false;
		return;
	}
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
	mT[0].SetUv(CVector(right, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, bot, 0.0f));
	mT[1].SetUv(CVector(left, top, 0.0f), CVector(left, bot, 0.0f), CVector(right, top, 0.0f));
	//ビルボード更新
	CBillBoard::Update();
}
void CEffect::Render()
{
	glDisable(GL_DEPTH_TEST); //深度テスト無効
	CBillBoard::Render(&sMaterial);
	glEnable(GL_DEPTH_TEST); //深度テスト有効
}



