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
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//���񂩂�f�[�^��9�ϐ��֑������
		//�f�[�^�𕪊�
		int seq[9];
		//ssccanf(����,�ϊ��w��q,�ϐ�)
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4], &seq[5], &seq[6], &seq[7], &seq[8]);
		int map[1][9] =
		{
				{seq[0],seq[1],seq[2],seq[3],seq[4],seq[5],seq[6],seq[7],seq[8]}
		};
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				switch (map[i][j]) {
				case 0: {
					printf("%d", map[i][j]);
				}
				case 1: {
					printf("%d", map[i][j]);
					CBlock* Block = new CBlock();
					Block->x = j * 100 + -400;
					Block->y = i + 50 + -300;
					Block->w = 25;
					Block->h = 25;
					Block->mFx = 0;
					Block->mFy = -1;
					Block->mEnabled = true;
					Block->mTag = CRectangle::EBLOCK;
					break;

				}
				case 2: {
					printf("%d", map[i][j]);
					CBlock* Block2 = new CBlock();
					Block2->x = j * 100 + -400;
					Block2->y = i + 150 + -200;
					Block2->w = 25;
					Block2->h = 25;
					Block2->mFx = 0;
					Block2->mFy = -1;
					Block2->mEnabled = true;
					Block2->mTag = CRectangle::EBLOCK;
					break;




				}

				}
			}





		}









	}
	//�t�@�C���̃N���[�Y
	fclose(fp);


}
	
	
