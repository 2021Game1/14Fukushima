#include"CModel.h"
//�W�����o�͂̃C���N���[�h
#include<stdio.h>
//CVector�̃C���N���[�h
#include"CVector.h"

//���f���t�@�C���̓���
//Load(���f���t�@�C����,�}�e���A���t�@�C����)
void CModel::Load(char* obj, char* mtl) {
	//���_�f�[�^�̕ۑ��iCVector�^�j
	std::vector<CVector>vertex;
	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp;
	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp2;
	//�t�@�C���̃I�[�v��
	//fopen(�t�@�C����,���[�h)
	//�I�[�v���o���Ȃ�����NULL��Ԃ�
	fp = fopen(mtl, "r");
	//�t�@�C���I�[�v���̃G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[���o�͂��Ė߂�
		printf("%s file open error\n", mtl);
		return;
	}
	//�t�@�C������f�[�^�����
	// ���̓G���A���쐬����
	char buf[256];
	//�t�@�C������P�s����
	// fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
	// �t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = { "","","","" };
		//�����񂩂�f�[�^���S�ϐ��֑������
		// sscanf(������,�ϊ��w��q,�ϐ�)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//������̔�r
		//strcmp(������P,������Q)
		//������P�ƕ�����Q�������Ƃ�0,�قȂ鎞�O�ȊO��Ԃ�
		// �擪��v�̎��A���_��vertex�ɒǉ�����
		if (strcmp(str[0], "v") == 0) {
			//�ϒ��z��vertex�ɒǉ�����
			//atof(������) �����񂩂�float�^�̒l��Ԃ�
			vertex.push_back(CVector(atof(str[1]), atof(str[2]),atof(str[3])));
		}
		//�擪��f�̎��A�O�p�`���쐬���Ēǉ�����
		else if(strcmp(str[0],"f")==0){
			//���_�Ɩ@���̔ԍ��쐬
			int v[3], n[3];
			//���_�Ɩ@���̔ԍ��擾
			sscanf(str[1], "%d//%d,&v[0],&n[0]");
			sscanf(str[2], "%d//%d,&v[1],&n[1]");
			sscanf(str[3], "%d//%d,&v[2],&n[2]");
			//�O�p�`�쐬
			CTriangle t;
			t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
			//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
			mTriangles.push_back(t);
		}
		//���͂����l���R���\�[���ɏo�͂���
		printf("%s", buf);
	}
		//�t�@�C���̃N���[�Y
		fclose(fp);
	
	//�t�@�C���̃I�[�v��
	//fopen(�t�@�C����,���[�h)
	//�I�[�v���o���Ȃ�����NULL��Ԃ�
	fp2 = fopen(obj, "r");
	//�t�@�C���I�[�v���̃G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp2 == NULL) {
		//�R���\�[���ɃG���[���o�͂��Ė߂�
		printf("%s file open error\n", obj);
		return;
	}
	//�t�@�C������P�s����
// fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
// �t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp2) != NULL) {
		//���͂����l���R���\�[���ɏo�͂���
		printf("%s", buf);
	}
	//�t�@�C���̃N���[�Y
	fclose(fp2);	
}
