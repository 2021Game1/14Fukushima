#include <stdio.h>
#include <string.h>

#include "CModelX.h"
#include "glut.h"

#define COUNT_SET 1

CModelX::CModelX() 
	:mpPointer(nullptr)
{
	//mToken��������
	memset(mToken, 0, sizeof(mToken));
}
CModelX::~CModelX() {
	if (mFrame.size() > 0)
	{
		delete mFrame[0];
	}
}

/*
CModelXFrame
model:CModelX�C���X�^���X�ւ̃|�C���^
�t���[�����쐬����
�ǂݍ��ݒ���Frame��������΁A
�t���[�����쐬���A�q�t���[���ɒǉ�����
*/
CModelXFrame::CModelXFrame(CModelX* model) {
	//���݂̃t���[���z��̗v�f�����擾���ݒ肷��
	mIndex = model->mFrame.size();
	//CModelX�̃t���[���z��ɒǉ�����
	model->mFrame.push_back(this);
	//�ϊ��s���P�ʍs��ɂ���
	mTransformMatrix.Identity();
	//���̒P��(�t���[�����̗\��)���擾����
	model->GetToken();//frame name
	//�t���[�������G���A���m�ۂ���
	mpName = new char[strlen(model->mToken) + 1];
	//�t���[�������R�s�[����
	strcpy(mpName, model->mToken);
	//���̒P���({�̗\��)���擾����
	model->GetToken();//{
	//�����������Ȃ�����I���
	while (*model->mpPointer != '\0') {
		//���̒P��擾
		model->GetToken();//Frame
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}'))break;
		//�V���ȃt���[���̏ꍇ�́A�q�t���[���ɒǉ�
		if (strcmp(model->mToken, "Frame") == 0) {
			//�t���[�����쐬���A �q�t���[���̔z��ɒǉ�
			mChild.push_back(new CModelXFrame(model));

		}
		//FrameTransformMatrix�v�f����������,mTransformMatrix�ɐݒ肷��
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0)
		{
			model->GetToken();//{
			for (int i = 0; i < mTransformMatrix.Size(); i++)
			{
				mTransformMatrix.M()[i] = model->GetFloatToken();
			}
			model->GetToken();//}
		}
		else if (strcmp(model->mToken, "Mesh") == 0) {
			mMesh.Init(model);
		}
		else {
			//��L�ȊO�̗v�f�͓ǂݔ�΂�
			model->SkipNode();
		}

	}
	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	printf("%s\n", mpName);
	mTransformMatrix.Print();
	
#endif //DEBUG
}


/*
SkipNode
�m�[�h��ǂݔ�΂�
*/
void CModelX::SkipNode() {
	//�������I�������I��
	while (*mpPointer != '\0') {
		GetToken();		//���̒P����擾
		//{�����������烋�[�v�I��
		if (strchr(mToken, '{'))break;
	}
	int count = COUNT_SET;
	//�������I��邩�A�J�E���g�_�E����0�ɂȂ�����I��
	while (*mpPointer != '\0' && count > 0) {
		GetToken();
		//{��������ƃJ�E���g�A�b�v
		if (strchr(mToken, '{'))count++;
		//}��������ƃJ�E���g�_�E��
		else if (strchr(mToken, '}'))count--;
	}
}

/*
GetToken
������f�[�^����A�P���1�擾����
*/
void CModelX::GetToken() {
	char* p = mpPointer;
	char* q = mToken;
	//��( )�^�u(\t)���s(\r)(\n),;"�ȊO�̕����ɂȂ�܂œǂݔ�΂�
	/*
	strchr(������,����)
	������ɕ������܂܂�Ă���΁A�������������ւ̃|�C���^��Ԃ�
	������Ȃ�������NULL��Ԃ�
	*/
	while (*p != '\0' && strchr(" \t\r\n,;\"", *p))p++;
	if (*p == '{'|| *p == '}')
	{
		//{�܂���}�Ȃ�mToken�ɑ�������̕�����
		*q++ = *p++;
	}
	else
	{
		//��( )(\t)���s(\r)(\n),;" }�̕����ɂȂ�܂�mToken�ɑ������
		while (*p != '\0' && !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0';	//mToken�̍Ō��\0��������
	mpPointer = p;//���̓ǂݍ��ރ|�C���g���X�V����
	//����mToken��//�̏ꍇ�́A�R�����g�Ȃ̂ŉ��s�܂œǂݔ�΂�
	/*
	strcmp(������1,������2)
	������1�ƕ�����2���������ꍇ,0��Ԃ��܂�
	������1�ƕ�����2���������Ȃ��ꍇ�A0��Ԃ��܂��B
	*/
	if (!strcmp("//", mToken)) {
		//���s�܂œǂݔ�΂�
		while (*p != '\0' && !strchr("\r\n", *p))p++;
		//�ǂݍ��݈ʒu�̍X�V
		mpPointer = p;
		//�P����擾����(�ċN�Ăяo��)
		GetToken();
	}
}

/*
* GetIntToken
* �P��𐮐��^�̃f�[�^�ŕԂ�
*/
int CModelX::GetIntToken() {
	GetToken();
	return atoi(mToken);
}

/*
* GetFloatToken
* �P��𕂓������_�^�̃f�[�^�ŕԂ�
*/
float CModelX::GetFloatToken() {
	GetToken();
	//atof
	//�������float�^�֕ϊ�
	return atof(mToken);
}

/*
* Init
* Mesh�̃f�[�^����荞��
*/
void CMesh::Init(CModelX* model) {
	model->GetToken();	//{or ���O
	if (!strchr(model->mToken, '{')) {
		//���O�̏ꍇ�A����{
		model->GetToken();		   //{
	}
	//���_���̎擾
	mVertexNum = model->GetIntToken();
	//���_�����G���A�m��
	mpVertex = new CVector[mVertexNum];
#ifdef _DEBUG
	printf("%s%d \n", "VertexNum:",mVertexNum);
#endif //DEBUG
	//���_�����f�[�^����荞��
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].X(model->GetFloatToken());
		mpVertex[i].Y(model->GetFloatToken());
		mpVertex[i].Z(model->GetFloatToken());
		
		//�f�o�b�O�o�[�W�����̂ݗL��
		#ifdef _DEBUG
		printf("%10f %10f %10f \n", mpVertex[i].X(), mpVertex[i].Y(), mpVertex[i].Z());
		#endif //DEBUG
	}
		mFaceNum = model->GetIntToken();		//�ʐ��ǂݍ���
		#ifdef _DEBUG
		printf("%s%d \n", "FaceNum:", mFaceNum);
		#endif //DEBUG
		//���_����1�ʂɂR���_
		mpVertexIndex = new int[mFaceNum * 3];
		for (int i = 0; i < mFaceNum*3; i+= 3)
		{
			model->GetToken();//���_���ǂݔ�΂�
			mpVertexIndex[i] = model->GetIntToken();
			mpVertexIndex[i + 1] = model->GetIntToken();
			mpVertexIndex[i + 2] = model->GetIntToken();
			//�f�o�b�O�o�[�W�����̂ݗL��
			#ifdef _DEBUG
			
			printf("%d %d %d \n", mpVertexIndex[i], mpVertexIndex[i + 1], mpVertexIndex[i + 2]);
			#endif //DEBUG
		}

}



void CModelX::Load(char* file) {
	//
	//�t�@�C���T�C�Y���擾
	//
	FILE* fp;	//�t�@�C���|�C���^
	fp = fopen(file, "rb");//�t�@�C���|�C���^�ϐ��̍쐬
	if (fp == NULL) {
		printf("fopen error:%s\n",file);
		return;
	}
	//�t�@�C���̍Ō�ֈړ�
	fseek(fp, 0L, SEEK_END);
	//�t�@�C���T�C�Y�̎擾
	int size = ftell(fp);
	//�t�@�C���T�C�Y�{1�o�C�g���̗̈���m��
	char* buf = mpPointer = new char[size + 1];
	//
	//�t�@�C������3D���f���̃f�[�^��ǂݍ���
	//
	//�t�@�C���̐擪�ֈړ�
	fseek(fp, 0L, SEEK_SET);
	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���̃f�[�^��ǂݍ���
	fread(buf, size, 1, fp);
	//�Ō��\0��ݒ肷��(������̏I�[)
	buf[size] = '\0';
	fclose(fp);		//�t�@�C�����N���[�Y����

	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0') {
		GetToken();		//�P��̎擾
		//�P�ꂪFrame�̏ꍇ
		if (strcmp(mToken, "Frame") == 0) {
			//�t���[�����쐬����
			new CModelXFrame(this);
		}
	}
	SAFE_DELETE_ARRAY(buf);	//�m�ۂ����̈���J������
}








