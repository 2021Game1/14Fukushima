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

class CMesh;//�t�����h��`�p

class CMaterial;

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet {
	friend CModelX;
	//�A�j���[�V�����Z�b�g��
	char* mpName;

public:
	CAnimationSet(CModelX* model);
	~CAnimationSet()
	{
		SAFE_DELETE_ARRAY(mpName);
	}
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
	char* mpFrameName; //�t���[����
	int mFrameindex;   //�t���[���ԍ�
	int mIndexNum;	   //���_�ԍ���
	int* mpIndex;   //���_�ԍ��z��
	float* mpWeight;   //���_�E�F�C�g�z��
	CMatrix mOffset;   //�I�t�Z�b�g�}�g���b�N�X
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
	const int& FrameIndex();
	const CMatrix& Offset();


};

//CMesh�N���X�̒�`
class CMesh{
	friend CModelX;
	friend CModelXFrame;
	friend CSkinWeights;

	int mVertexNum;		//���_��
	CVector* mpVertex;	//���_�f�[�^
	int mFaceNum;		//�搔
	int* mpVertexIndex;	//�ʂ��\�����钸�_���W
	int mNormalNum;		//�@����
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;	//�}�e���A���ԍ���(�ʐ�)
	int* mpMaterialIndex;//�}�e���A���ԍ�
	std::vector<CMaterial*>mMaterial;//�}�e���A���f�[�^
	std::vector<CSkinWeights*>mSkinWeights;//�X�L���E�F�C�g
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
		,mMaterialNum(0)
		,mMaterialIndexNum(0)
		,mpMaterialIndex(nullptr)
	{}
	//�f�X�g���N�^
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//�X�L���E�F�C�g�̍폜
		for (size_t i = 0; i < mSkinWeights.size(); i++)
		{
			delete mSkinWeights[i];
		}
	}
	//�ǂݍ��ݏ���
	void Init(CModelX* model);
	//�`��
	void Render();
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
	//�`��
	void Render();
};


/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX {
	friend CModelXFrame;
	friend CMesh;
	friend CSkinWeights;
	friend CAnimationSet;
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];  //���o�����P��̗̈�
	std::vector<CModelXFrame*>mFrame;	//�t���[���̔z��
	std::vector<CAnimationSet*>mAnimationSet; //�A�j���[�V�����Z�b�g�̔z��
public:
	CModelX();
	~CModelX();
	//���������_�f�[�^�̎擾
	float GetFloatToken();
	//�t�@�C���ǂݍ���
	void Load(char* file);
	//�`��
	void Render();
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//�����f�[�^�̎擾
	int GetIntToken();
	//
	char* Token();
	
	void Token(char* token);
};



#endif 

