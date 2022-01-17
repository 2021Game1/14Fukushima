//�x�N�g���N���X�̃C���N���[�h
#include"CVector.h"
//<math.h>�̃C���N���[�h
#include<math.h>
//�f�t�H���g�R���X�g���N�^
CVector::CVector()
	:mX(0.0f)
	, mY(0.0f)
{}
//�R���X�g���N�^
//CVector(X���W,Y���W)
CVector::CVector(float x, float y)
	: mX(x)
	, mY(y)
{}
//+���Z�q�̃I�[�o�[���[�h
//CVector + CVector�̉��Z���ʂ�Ԃ�
CVector CVector::operator+(const CVector& v)const
{
	return CVector(mX + v.mX, mY + v.mY);
}
//-���Z�q�̃I�[�o�[���[�h
//CVector - CVector�̉��Z���ʂ�Ԃ�
CVector CVector::operator-(const CVector& v)const
{
	return CVector(mX - v.mX, mY - v.mY);
}
//Set(X���W,Y���W,Z���W)
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
//�x�N�g���̒�����Ԃ�
float CVector::Length()const {
	//sprt�֐��ŕ�������Ԃ�
	return sqrtf(mX * mX + mY * mY);
}