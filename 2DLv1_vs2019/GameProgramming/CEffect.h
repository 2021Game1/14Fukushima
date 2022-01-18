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
	//更新
	void Update();
	//描画
	void Render();
	int time = 0.3 * 60;

};

#endif //終了

