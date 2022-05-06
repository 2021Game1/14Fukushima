#ifndef CMODELX_H
#define CMODELX_H

#include <vector>	 //vector�N���X�̃C���N���[�h(���I�z��)
#include "CMatrix.h" //�}�g���N�X�N���X�̃C���N���[�h


#define MODEL_FILE "res\\sample.blend.x"

//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}

class CModelX; //CModel�N���X�̐錾
//CModelXFrame�N���X�̒�`
class CModelXFrame {
	friend CModelX;
	std::vector<CModelXFrame*>mChild; //�q�t���[���̔z��
	CMatrix mTransformMatrix;		  //�ϊ��s��
	char* mpName;					  //�t���[�����O
	int mIndex;						  //�t���[���ԍ�
public:
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	//�f�X�g���N�^
	~CModelXFrame() {
		//�q�t���[����S�ĊJ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++) {
			delete* itr;
		}
		//���O�̃G���A���J������
		SAFE_DELETE_ARRAY(mpName);
	}
};
/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
	friend CModelXFrame;
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];  //���o�����P��̗̈�
	std::vector<CModelXFrame*>mFrame;	//�t���[���̔z��
public:
	CModelX();
	~CModelX();

	//�t�@�C���ǂݍ���
	void Load(char* file);
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
};

#endif 

