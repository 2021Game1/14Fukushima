#ifndef CMATRIX_H
#define CMATRIX_H
/*
�}�g���N�X�N���X
4�s4��̍s��f�[�^�������܂�
*/
class CMyShader;

class CVector;

class CMatrix {
	friend CMyShader;
public:

	//2�����z���mM�̗v�f����Ԃ����\�b�h
	int Size();
	//�\���m�F�p
	//4�~4�̍s�����ʏo��
	void Print();
	//�f�t�H���g�R���X�g���N�^
	CMatrix();
	//�P�ʍs��̍쐬
	CMatrix Identity();
	//�s��̎擾
	float* M() const;
	//�s��l�̎擾
	//M(�s��, ��)
	float M(int row, int col) const;
	//�s��l�̐ݒ�
	//M(�s��, ��, �l)
	void M(int row, int col, float value);
	//�g��k���s��̍쐬
	//Scale(�{��X, �{��Y, �{��Z)
	CMatrix Scale(float sx, float sy, float sz);
	//��]�s��iY���j�̍쐬
	//RotateY(�p�x)
	CMatrix RotateY(float degree);
	//��]�s��iZ���j�̍쐬
	//RotateZ(�p�x)
	CMatrix RotateZ(float degree);
	//��]�s��iX���j�̍쐬
	//RotateX(�p�x)
	CMatrix RotateX(float degree);
	//X���̃x�N�g���𓾂�
	CVector VectorX();
	//Y���̃x�N�g���𓾂�
	CVector VectorY();
	//Z���̃x�N�g���𓾂�
	CVector VectorZ();

	//�ړ��s��̍쐬
	//Translate(�ړ���X, �ړ���Y, �ړ���Z)
	CMatrix Translate(float mx, float my, float mz);
	//*���Z�q�̃I�[�o�[���[�h
	//CMatrix * CMatrix �̉��Z���ʂ�Ԃ�
	CMatrix operator*(const CMatrix &m);
	//*���Z�q�̃I�[�o�[���[�h
	//CMatrix * float�̉��Z���ʂ�Ԃ�
	CMatrix operator*(const float& x);
	//+���Z�q�̃I�[�o�[���[�h
	//CMatrix1 + CMatrix2�̉��Z���ʂ�Ԃ�
	CMatrix operator+(const CMatrix& m);
	//+=���Z�q�̃I�[�o�[���[�h
	//CMatrix1 += CMatrix2�̉��Z���s��
	void operator+=(const CMatrix& m);
	CVector operator*(const CVector& v);
	//�N�H�[�^�j�I��
	CMatrix Quaternion(float x, float y, float z, float w);
	CMatrix Inverse(void);
	CVector GetXVec();
	CVector GetYVec();
	CVector GetZVec();
	CVector GetPos();
private:
	union {
		//4�~4�̍s��f�[�^��ݒ�
		float mM[4][4];
		//1�����z��Ƃ��Ďg��
		float mF[16];
		struct
		{
			float	m00, m10, m20, m30,
				m01, m11, m21, m31,
				m02, m12, m22, m32,
				m03, m13, m23, m33;
		};
	};

};
#endif

