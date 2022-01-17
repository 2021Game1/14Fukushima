//ベクトルクラスのインクルード
#include"CVector.h"
//<math.h>のインクルード
#include<math.h>
//デフォルトコンストラクタ
CVector::CVector()
	:mX(0.0f)
	, mY(0.0f)
{}
//コンストラクタ
//CVector(X座標,Y座標)
CVector::CVector(float x, float y)
	: mX(x)
	, mY(y)
{}
//+演算子のオーバーロード
//CVector + CVectorの演算結果を返す
CVector CVector::operator+(const CVector& v)const
{
	return CVector(mX + v.mX, mY + v.mY);
}
//-演算子のオーバーロード
//CVector - CVectorの演算結果を返す
CVector CVector::operator-(const CVector& v)const
{
	return CVector(mX - v.mX, mY - v.mY);
}
//Set(X座標,Y座標,Z座標)
void CVector::Set(float x, float y)
{
	mX = x;
	mY = y;
}
float CVector::X()const
{
	return mX;
}

float CVector::Y()const
{
	return mY;
}
//ベクトルの長さを返す
float CVector::Length()const {
	//sprt関数で平方根を返す
	return sqrtf(mX * mX + mY * mY);
}