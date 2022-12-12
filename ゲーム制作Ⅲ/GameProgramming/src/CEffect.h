#ifndef CEFFECT_H
#define CEFFECT_H
//ビルボードクラスのインクルード
#include "CBillBoard.h"
/*
エフェクトクラス
テクスチャのアニメーション
*/
class CEffect : public CBillBoard {
public:
	//コンストラクタ
	//CEffect(位置, 幅, 高さ, テクスチャ名, 行数, 列数, 1コマあたりのフレーム数)　行数、列数、フレーム数はデフォルト引数で呼出し時省略可能
	CEffect(const CVector &pos, float w, float h, char *texture, int row = 1, int col = 1, int fps = 1);
	//更新
	void Update();
	//描画
	void Render();
	CMaterial* GetIsMaterial();
	//他のクラスで参照用の関数
	static CEffect* GetInstance();				//staticで処理を作る
private:
	//行数
	int mRows;
	//列数
	int mCols;
	//1コマのフレーム数
	int mFps;
	//フレームカウンタ
	int mFrame;
	//マテリアル
	static CMaterial sMaterial;
	static CEffect* mpEffect_Instance;//別のクラスでエフェクトの変数を呼び出す場合,staticでポインタを作る
};
#endif

