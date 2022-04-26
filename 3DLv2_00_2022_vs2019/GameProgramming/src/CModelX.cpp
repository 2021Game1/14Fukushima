#include <stdio.h>
#include <string.h>
#include "CModelX.h"
#include "glut.h"



CModelX::CModelX() 
	:mpPointer(nullptr)
{
	//mToken��������
	memset(mToken, 0, sizeof(mToken));
}
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
			printf("%s", mToken);//Frame�o��
			GetToken();			//Frame�����擾
			printf("%s\n", mToken);//Frame�����擾
		}
		//�P�ꂪAnimationSet�̏ꍇ
		if (strcmp(mToken, "AnimationSet") == 0) {
			printf("%s", mToken);//AnimationSet�o��
			GetToken();			//AnimationSet�����擾
			printf("%s\n", mToken);//AnimationSet�����擾
		}
	}
	SAFE_DELETE_ARRAY(buf);	//�m�ۂ����̈���J������
}
/*
GetToken
������f�[�^����A�P���1�擾����
*/




