#ifndef CMATRIX_H
#define CMATRIX_H

/*
�}�g���N�X�N���X
4�s4��̍s��f�[�^�������܂�
*/

class CMatrix{
public:
	//�\���m�F�p
	//4�~4�̍s�����ʏo��
	void Print();
	//�f�t�H���g�R���X�g���N�^
	CMatrix();
	//�P�ʍs��̍쐬
	CMatrix Identity();
	//�s��l�̎擾
	//M(�s��,��)
	float M(int r, int c)const;
	//�g��k���s��̍쐬
	//Scale(�{��X,�{��Y,�{��Z)
	CMatrix Scale(float sx, float sy, float sz);
private:
	//4�~4�̍s��f�[�^�̐ݒ�
	float mM[4][4];
	

};
#endif

