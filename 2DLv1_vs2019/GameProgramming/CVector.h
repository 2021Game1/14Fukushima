#ifndef CVECTOR_H
#define CVECOTR_H

//レクタングルクラス
#include"CRectangle.h"
/*
*ベクトルクラス
*ベクトルデータを扱います
*/
class CVector : public CRectangle {
public:
	//各自での値の設定
	//Set(X座標,Y座標)
	void Set(float x, float y);
	//Xの値を得る
	float X() const;
	//Yの値を得る
	float Y() const;
	//ベクトルの長さを返す
	float Length()const;
	//デフォルトコンストラクタ
	CVector();
	//コンストラクタ
	//CVector(X座標,Y座標)
	CVector(float x, float y);
	//+演算子のオーバーロード
	//CVector + CVectorの演算結果を返す
	CVector operator+(const CVector& v)const;
	//-演算子のバーロード
	//CVector - CVectorの演算結果を返す
	CVector operator-(const CVector& v)const;

private:
	//3D各軸での値を設定
	float mX, mY;
};
#endif //終了

