#include "CMapModel.h"
//�W�����o�͂̃C���N���[�h
#include <stdio.h>

//���f���t�@�C���̓���
//Load(���f���t�@�C����,�}�e���A���t�@�C����)
void CMapModel::Load(char* csv, char* mtl) {
	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp;

	//�t�@�C���̃I�[�v��
	//fopen(�t�@�C����,���[�h)
	fp = fopen(csv, "r");
	//�t�@�C���I�[�v���G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL){
		//�R���\�[���ɃG���[�o�͂��Ė߂�
		printf("%s file open error\n", csv);
		return;
	}

	//�t�@�C������f�[�^�����
	//���̓G���A���쐬����
	char buf[256];
	//�t�@�C������1�s����
	//fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
	//�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf,sizeof(buf),fp)!= NULL){
		//�f�[�^�𕪊�
		int seq[8];
		//�����񂩂�f�[�^��4�ϐ��֑������
		//ssccanf(������,�ϊ��w��q,�ϐ�)
		sscanf(buf,"%d, %d, %d, %d, %d, %d, %d, %d,",&seq[0],&seq[1],&seq[2],&seq[3],&seq[4],&seq[5],&seq[6],&seq[7]);
		//����̔�r
		//strcmp(��1,��2)
		
		if (seq[7] == 1);
		
		//���͂����l���R���\�[���ɏo�͂���
		printf("%s", buf);
	}

	//�t�@�C���̃N���[�Y
	fclose(fp);
}