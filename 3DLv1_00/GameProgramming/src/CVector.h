#ifndef CVECTOR_H
#define CVECTOR_H
/*
�x�N�g���N���X
�x�N�g���f�[�^�������܂�
*/
class CVector {
public:
	//�e�n�ł̒l�̑I��
	//Set(X���W�AY���W�AZ���W)
	void Set(float x, float y, float z);
	//X�̒l�𓾂�
	float X()const;
	//Y�̒l�𓾂�
	float Y()const;
	//Z�̒l�𓾂�
	float Z()const;
private:
	//3D�e���ł̒l��ݒ�
	float mX, mY, mZ;

};

#endif 
