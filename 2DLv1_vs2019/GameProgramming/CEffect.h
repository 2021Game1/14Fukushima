#ifndef CEFFECT_H
#define CEFFECT_H
//レクタングルクラスのインクルード
#include "CRectangle.h"

/*
* エフェクトクラス
* テクスチャのアニメーション
*/
class CEffect : public CRectangle{
public:
	//コンストラクタ
	//CEffect(位置,幅,高さ,テクスチャ名,行数,列数,1コマあたりのフレーム数)行数,列数,フレーム数はデフォルト引数で呼出し時省略可能
	CEffect(const  &pos,float w,float h,char *texture,int row = 1,int col = 1,int fps = 1,)

private:

};

#endif //終了

