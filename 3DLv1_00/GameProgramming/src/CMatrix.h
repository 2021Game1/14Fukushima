#ifndef CMATRIX_H
#define CMATRIX_H

/*
マトリクスクラス
4行4列の行列データを扱います
*/

class CMatrix{
public:
	//表示確認用
	//4×4の行列を画面出力
	void Print();
	//デフォルトコンストラクタ
	CMatrix();
	//単位行列の作成
	CMatrix Identity();
	//行列値の取得
	//M(行数,列数)
	float M(int r, int c)const;
	//拡大縮小行列の作成
	//Scale(倍率X,倍率Y,倍率Z)
	CMatrix Scale(float sx, float sy, float sz);
private:
	//4×4の行列データの設定
	float mM[4][4];
	

};
#endif

