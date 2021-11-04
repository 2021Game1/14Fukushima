#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include"CVector.h"

/*
�O�p�`�N���X
*/
class CTriangle {
public:
	//���_���W�ݒ�
	//Vertex(���_1�C���_2,���_3,)
	void Vertex(const CVector& v0, const CVector& v1, const CVector& v2);
	//�@���ݒ�
	//Normal(�@���x�N�g��)
	void Normal(const CVector& n);
	//Normal(�@���x�N�g��1,�@���x�N�g��2,�@���x�N�g��3)
	void Normal(const CVector& v0, const CVector& v1, const CVector& v2);
	//�`��
	void Render();
	//�}�e���A���ԍ��̎擾
	int MaterialIdx();
	//�}�e���A���ԍ��̐ݒ�
	//Matrial(�}�e���A���ԍ�)
	void MaterialIdx(int idx);
	//UV�ݒ�
	void SetUv(const CVector& v0, const CVector& v1, const CVector& v2);
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);
private:
	CVector mV[3]; //���_���W
	CVector mN[3]; //�@��
	CVector mUv[3]; //�e�N�X�`���}�b�s���O
	int mMaterialIdx; //�}�e���A���ԍ�
};
#endif 
