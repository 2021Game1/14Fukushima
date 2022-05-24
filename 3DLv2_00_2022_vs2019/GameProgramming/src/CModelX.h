#ifndef CMODELX_H
#define CMODELX_H

#include <vector>	 //vector�N���X�̃C���N���[�h(���I�z��)
#include "CMatrix.h" //�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"

#define MODEL_FILE "res\\sample.blend.x"

//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}

//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

class CModelX; //CModel�N���X�̐錾

class CModelXFrame;

//CMesh�N���X�̒�`
class CMesh{
	friend CModelX;
	friend CModelXFrame;

	int mVertexNum;		//���_��
	CVector* mpVertex;	//���_�f�[�^
	int mFaceNum;		//�搔
	int* mpVertexIndex;	//�ʂ��\�����钸�_���W
	int mNormalNum;		//�@����
	CVector* mpNormal;	//�@���x�N�g��

public:
	//�R���X�g���N�^
	CMesh()
		:mVertexNum(0)
		, mpVertex(nullptr)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		,mNormalNum(0)
		,mpNormal(nullptr)
	{}
	//�f�X�g���N�^
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
	}
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
};


//CModelXFrame�N���X�̒�`
class CModelXFrame {
	friend CModelX;
	friend CMesh;
	std::vector<CModelXFrame*>mChild; //�q�t���[���̔z��
	CMatrix mTransformMatrix;		  //�ϊ��s��
	CMesh mMesh;					  //Mesh�f�[�^
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
	friend CMesh;
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];  //���o�����P��̗̈�
	std::vector<CModelXFrame*>mFrame;	//�t���[���̔z��
public:
	CModelX();
	~CModelX();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	//�t�@�C���ǂݍ���
	void Load(char* file);
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//�����f�[�^�̎擾
	int GetIntToken();
	
};

#endif 

