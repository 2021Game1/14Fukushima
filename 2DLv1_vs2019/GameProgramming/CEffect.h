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
	////コンストラクタ
	////CEffect(位置,幅,高さ,テクスチャ名,行数,列数,1コマあたりのフレーム数)行数,列数,フレーム数はデフォルト引数で呼出し時省略可能
	//CEffect(const CRectangle pos, float w, float h, char* texture, int row = 1, int col = 1, int fps = 1);
	//更新
	void Update();
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

