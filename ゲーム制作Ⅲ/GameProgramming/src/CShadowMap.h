#ifndef CSHADOWMAP_H
#define CSHADOWMAP_H


//�V���h�E�}�b�v�N���X
class CShadowMap
{
public:
	//�V���h�[�}�b�v�̏��
	enum EShadowMap_State
	{
		ENORENDER = 0,	//Render����Ă��Ȃ�
		EDEPTHTEX,		//�f�v�X
		ESUNNYTEX,		//����
		ESHADOW,		//�e
	};
	//����������
	void Init();
	/* ����������
	void Init(int width, int height, void (*funcRender)(), float shadowCol[], float lightPos[])
	width:�f�v�X�e�N�X�`���̕�
	height:�f�v�X�e�N�X�`���̍���
	funcRender:�`��֐��̃|�C���^
	shadowCol:�e�̐F
	lightPos:�����̈ʒu
	*/
	void Init(int width, int height, void (*funcRender)(), float shadowCol[], float lightPos[]);
	//�`�揈��
	void Render();
	//�e�̃C���X�^���X�擾�֐�
	static CShadowMap* GetInstance();		//static�ŏ��������
	//�e�̏�Ԏ擾�֐�
	CShadowMap::EShadowMap_State GetState();	//�v���C���̏�Ԃ��擾����
private:
	GLfloat mLightPos[3]; //�����̈ʒu
	GLfloat mShadowCol[4]; //�e�̐F
	int mTextureWidth; //�f�v�X�e�N�X�`���̕�
	int mTextureHeight; //�f�v�X�e�N�X�`���̍���
	GLuint mDepthTextureID; //�f�v�X�e�N�X�`��ID
	GLuint mFb; //�t���[���o�b�t�@���ʎq
	void (*mpRender)(); //Render�֐��̃|�C���^
	EShadowMap_State mShadow_State;			//�e�̏�Ԕ��f�p
	//�e�̃|�C���^
	static CShadowMap* mpShadowMap_Instance;	//�ʂ̃N���X�ŉe�̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
};
#endif 