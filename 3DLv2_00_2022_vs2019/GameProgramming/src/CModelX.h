#ifndef CMODELX_H
#define CMODELX_H

#define MODEL_FILE "res\\sample.blend.x"

//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}
/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����Ŋm�F����
*/

class CModelX {
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];	//���o�����P��̈ʒu
public:
	CModelX();
	//�t�@�C���̓ǂݍ���
	void Load(char* file);
	//�P��̎��o��
	void GetToken();
};



#endif 

