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
	if (fp == NULL) {
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
	//�f�[�^�𕪊�
	char seq[20][9] = { "","","","","","","","","" };

	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//���񂩂�f�[�^��9�ϐ��֑������
		//ssccanf(����,�ϊ��w��q,�ϐ�)
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[0][], &seq[1][], &seq[2][], &seq[3][], &seq[4][], &seq[5][], &seq[6][], &seq[7][], &seq[8][]);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 20; j++){
			switch (seq[j][i]) {
			case 0: {
				printf("%d\n", seq[i][j]);

			}
				  break;
			case 1: {
				printf("%d\n", seq[i][j]);
			CBlock* Block = new CBlock();
			Block->x = i * 100 - 250;
			Block->y = -500 + 250;
			Block->h = 25;
			Block->w = 25;
			Block->mTag = CRectangle::EBLOCK;
			Block->mEnabled = true;
			}
				  break;

			case 2: {
				printf("%d\n", seq[i][j]);
		
			}
				  break;
			}
		}

		}
		
	}

	//�t�@�C���̃N���[�Y
	fclose(fp);
	
}