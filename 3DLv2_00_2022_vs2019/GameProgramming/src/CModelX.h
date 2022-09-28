#ifndef CMODELX_H
#define CMODELX_H

#include <vector>	 //vector�N���X�̃C���N���[�h(���I�z��)
#include "CMatrix.h" //�}�g���N�X�N���X�̃C���N���[�h
#include "CVector.h"
#include"CMyShader.h"//�V�F�[�_�[�̃C���N���[�h


#define MODEL_FILE "res\\���O�i.x"

//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}

//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))



class CModelX;//�t�����h�N���X�p

class CModelXFrame;//�t�����h�N���X�p

class CMesh;//�t�����h�N���X�p

class CMaterial;//�t�����h�N���X�p

class CAnimationSet;//�t�����h�N���X�p

class CAnimation;//�t�����h�N���X�p
/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey{
	friend CAnimation;
	friend CAnimationSet;
	friend CModelX;

	//����
	float mTime;
	//�s��
	CMatrix mMatrix;
};

/*
CAnimation
�A�j���[�V�����N���X
*/
class CAnimation {
	friend CAnimationSet;
	friend CModelX;
	friend CAnimationKey;
	char* mpFrameName;//�t���[����
	int mFrameIndex; //�t���[���ԍ�
	int mKeyNum;	//�L�[��(���Ԑ�)
	CAnimationKey* mpKey;	//�L�[�̔z��
public:
	CAnimation(CModelX* model);
	CAnimation();
	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
	}
};

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet {
	friend CModelX;
	friend CAnimation;
	friend CAnimationKey;
	//�A�j���[�V�����Z�b�g��
	char* mpName;
	float mTime;    //���݂̎���
	float mWeight;  //�d��
	float mMaxTime; //�ő厞��

	//�A�j���[�V����
	std::vector<CAnimation*>mAnimation;
public:
	CAnimationSet(CModelX* model);
	CAnimationSet();
	~CAnimationSet()
	{
		SAFE_DELETE_ARRAY(mpName);
		//�A�j���[�V�����v�f�̍폜
		for (size_t i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}
	void CAnimationSet::Time(float time)
	{
		mTime = time;
	}
	void CAnimationSet::Weught(float weight)
	{
		mWeight = weight;
	}

	float Time();

	float MaxTime();
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
	char* mpFrameName; //�t���[����
	int mFrameIndex;   //�t���[���ԍ�
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
	//���_�o�b�t�@���ʎq
	GLuint mMyVertexBufferId;
	//���_�o�b�t�@�̍쐬
	void CreateVertexBuffer();
	int mVertexNum;		//���_��
	CVector* mpVertex;	//���_�f�[�^
	int mFaceNum;		//�搔
	int* mpVertexIndex;	//�ʂ��\�����钸�_���W
	int mNormalNum;		//�@����
	int mMaterialNum;	//�}�e���A����
	int mMaterialIndexNum;	//�}�e���A���ԍ���(�ʐ�)
	int* mpMaterialIndex;//�}�e���A���ԍ�
	float* mpTextureCoords;//�e�N�X�`���t�@�C�����W�f�[�^
	std::vector<int>mMaterialVertexCount;//�}�e���A�����̖ʐ�
	std::vector<CMaterial*>mMaterial;//�}�e���A���f�[�^
	std::vector<CSkinWeights*>mSkinWeights;//�X�L���E�F�C�g
	CVector* mpNormal;	//�@���x�N�g��
	CVector* mpAnimateVertex; //�A�j���[�V�����p���_
	CVector* mpAnimateNormal; //�A�j���[�V�����p�@��
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
		,mpAnimateVertex(nullptr)
		,mpAnimateNormal(nullptr)
		,mpTextureCoords(nullptr)
		, mMyVertexBufferId(0)
	{}
	//�f�X�g���N�^
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
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
	//���_�ɃA�j���[�V�����K�p
	void AnimateVertex(CModelX* model);
	//�A�j���[�V�����̒��_�v�Z���w�肵�������s����g���Čv�Z
	void AnimateVertex(CMatrix*);
};


//CModelXFrame�N���X�̒�`
class CModelXFrame { //�t���[��=�{�[��
	friend CModelX;
	friend CMesh;
	friend CAnimation;
	std::vector<CModelXFrame*>mChild; //�q�t���[���̔z��
	CMatrix mTransformMatrix;		  //�ϊ��s��
	CMatrix mCombinedMatrix;		  //�����s��
	CMesh mMesh;					  //Mesh�f�[�^
	char* mpName;					  //�t���[�����O
	int mIndex;						  //�t���[���ԍ�
public:
	//�R���X�g���N�^
	CModelXFrame(CModelX* model);
	CModelXFrame()
		:mpName(nullptr)
		, mIndex(0) {}
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
	//�����s��̍쐬
	void AnimateCombined(CMatrix* parent);
	const CMatrix& CombinedMatrix();
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
	friend CAnimation;
	friend CAnimationKey;
	//�V�F�[�_�[�p�X�L���}�g���b�N�X
	CMatrix* mpSkinningMatrix;
	CMyShader mShader; //�V�F�[�_�[�̃C���X�^���X
	char* mpPointer;	//�ǂݍ��݈ʒu
	char mToken[1024];  //���o�����P��̗̈�
	std::vector<CModelXFrame*>mFrame;	//�t���[���̔z��
	std::vector<CAnimationSet*>mAnimationSet; //�A�j���[�V�����Z�b�g�̔z��
	std::vector<CMaterial*>mMaterial; //�}�e���A���̔z��
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
	//�t���[���̕ϊ��s����A�j���[�V�����f�[�^�ōX�V����
	void AnimateFrame();
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	//���_�ɃA�j���[�V�����K�p
	void AnimeteVertex();
	//�A�j���[�V�����̒��_�v�Z���w�肵�������s����g���Čv�Z
	void AnimateVertex(CMatrix*);
	//�V�F�[�_�[���g�����`��
	void RenderShader(CMatrix* m);
	/*
	�A�j���[�V�����𔲂��o��
	idx:�����������A�j���[�V�����̔ԍ�
	start:�����������A�j���[�V�����̊J�n����
	end:�����������A�j���[�V�����̏I������
	name:�ǉ�����A�j���[�V�����̃Z�b�g��
	*/
	void CModelX::SeparateAnimationSet(int idx, int strat, int end, char* name);
	//�����f�[�^�̎擾
	int GetIntToken();
	//
	char* Token();
	//�t���[�����ɊY������t���[���ɃA�h���X��Ԃ�
	CModelXFrame* FindFrame(char* name);
	//�}�e���A���̌���
	CMaterial* FindMaterial(char* name);

	std::vector<CAnimationSet*>& AnimationSet();
	std::vector<CModelXFrame*>& Frames();
	std::vector<CMaterial*>& Material();
	

};



#endif 

