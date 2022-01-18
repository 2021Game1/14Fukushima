#ifndef CEFFECT_H
#define CEFFECT_H

//レクタングルクラス
#include"CRectangle.h"
/*
* エフェクトクラス
* テクスチャのアニメーション
*/
class CEffect : public CRectangle{
public:

	//デフォルトコンストラクタ
	CEffect();
	//描画
	void Render();
private:
	//行数
	int mRows;
	//列数
	int mCols;
	//1コマのフレーム数
	int mFps;
	//フレームカウンタ
	int mFrame;

};

#endif //終了

