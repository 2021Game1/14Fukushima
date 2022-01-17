#ifndef CVECTOR_H
#define CVECOTR_H

//���N�^���O���N���X
#include"CRectangle.h"
/*
*�x�N�g���N���X
*�x�N�g���f�[�^�������܂�
*/
class CVector : public CRectangle {
public:
	//�e���ł̒l�̐ݒ�
	//Set(X���W,Y���W)
	void Set(float x, float y);
	//X�̒l�𓾂�
	float X() const;
	//Y�̒l�𓾂�
	float Y() const;
	//�x�N�g���̒�����Ԃ�
	float Length()const;
	//�f�t�H���g�R���X�g���N�^
	CVector();
	//�R���X�g���N�^
	//CVector(X���W,Y���W)
	CVector(float x, float y);
	//+���Z�q�̃I�[�o�[���[�h
	//CVector + CVector�̉��Z���ʂ�Ԃ�
	CVector operator+(const CVector& v)const;
	//-���Z�q�̃o�[���[�h
	//CVector - CVector�̉��Z���ʂ�Ԃ�
	CVector operator-(const CVector& v)const;

private:
	//3D�e���ł̒l��ݒ�
	float mX, mY;
};
#endif //�I��

