#include "CMapModel.h"
//�W�����o�͂̃C���N���[�h
#include <stdio.h>
#include"CBlock.h"





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
	int i = 0;
	//�t�@�C������1�s����
	//fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
	//�t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//���񂩂�f�[�^��9�ϐ��֑������
		//�f�[�^�𕪊�
		int seq[9];
		//ssccanf(����,�ϊ��w��q,�ϐ�)
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4], &seq[5], &seq[6], &seq[7], &seq[8]);

		for (int j = 0; j < 9; j++)
		{
			switch (seq[j]) {
			case 0: {
				printf("%d", seq[j]);
			}
				  break;
			case 1: {
				printf("%d", seq[j]);
				CBlock* Block = new CBlock();
				Block->x = j * 90 + -360;
				Block->y = i * -90 + 3180;
				Block->w = 45;
				Block->h = 45;
				Block->mEnabled = true;
				Block->mTag = CRectangle::EBLOCK;
			}
				  break;

			case 2: {
				printf("%d", seq[j]);
				CComet* Comet = new CComet();
				Comet->x = j * 90 + -370;
				Comet->y = i * -90 + 3180;
				Comet->w = 45;
				Comet->h = 45;
				Comet->mEnabled = true;
				Comet->mTag = CRectangle::ECOMET;
			}
				  break;
			case 3: {
				printf("%d", seq[j]);
				CEnemy* Enemy = new CEnemy();
				Enemy->x = j * 90 + -370;
				Enemy->y = i * -90 + 3180;
				Enemy->w = 25;
				Enemy->h = 25;
				Enemy->mFx = 0;
				Enemy->mFy = -1;
				Enemy->mEnabled = true;
				Enemy->mTag = CRectangle::EENEMY;
			}
				  break;
			}
		}













		i = i + 1;

	}
	//�t�@�C���̃N���[�Y
	fclose(fp);


}
	
	
