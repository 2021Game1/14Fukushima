#include"CModel.h"
//�W�����o�͂̃C���N���[�h
#include<string.h>
//CVector�̃C���N���[�h
#include"CVector.h"
//CTriangle�̃C���N���[�h
#include"CTriangle.h"



//���f���t�@�C���̓���
//Load(���f���t�@�C����,�}�e���A���t�@�C����)
void CModel::Load(char* obj, char* mtl) {
	//���_�f�[�^�̕ۑ��iCVector�^�j
	std::vector<CVector>vertex;
	//�@���f�[�^�̕ۑ��iCVector�^�j
	std::vector<CVector>normal;
	//�e�N�X�`���}�b�s���O�̕ۑ� (CVector�^)
	std::vector<CVector>uv;
	//�t�@�C���|�C���^�ϐ��̍쐬
	FILE* fp;
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
	//�}�e���A���C���f�b�N�X
	int idx = 0;
	//�t�@�C������P�s����
	// fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
	// �t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = { "","","","" };
		//�����񂩂�f�[�^��4�ϐ��֑������
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//�擪��newmtl�̎��A�}�e���A����ǉ�����
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//�}�e���A�����̐ݒ�
			pm->Name(str[1]);
			//�}�e���A���̉ϒ��z��ɒǉ�
			mpMaterials.push_back(pm);
			//�z��̒������擾
			idx = mpMaterials.size() - 1;
		}
	
	
		//�擪��Kd�̎��ADiffuse��ݒ肷��
		else if (strcmp(str[0], "Kd") == 0) {
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		//�擪��d�̎��Aa�l��ݒ肷��
		else if (strcmp(str[0], "d") == 0) {
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		//�擪��map_Kd�̎��A�e�N�X�`������͂���
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->Texture()->Load(str[1]);
		}
	}
	//�t�@�C���̃N���[�Y
	fclose(fp);
	
	//�t�@�C���̃I�[�v��
	//fopen(�t�@�C����,���[�h)
	//�I�[�v���o���Ȃ�����NULL��Ԃ�
	fp = fopen(obj, "r");
	//�t�@�C���I�[�v���̃G���[�̔���
	//fp��NULL�̎��̓G���[
	if (fp == NULL) {
		//�R���\�[���ɃG���[���o�͂��Ė߂�
		printf("%s file open error\n", obj);
		return;
	}
	//�t�@�C������P�s����
// fgets(���̓G���A,�G���A�T�C�Y,�t�@�C���|�C���^)
// �t�@�C���̍Ō�ɂȂ��NULL��Ԃ�
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//�f�[�^�𕪊�����
		char str[4][64] = { "","","","" };
		//�����񂩂�f�[�^���S�ϐ��֑������
		// sscanf(������,�ϊ��w��q,�ϐ�)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//�擪��newmtl�̎��A�}�e���A����ǉ�����
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//�}�e���A�����̐ݒ�
			pm->Name(str[1]);
			//�}�e���A���̉ϒ��z��ɒǉ�
			mpMaterials.push_back(pm);
			//�z��̒������擾
			idx = mpMaterials.size() - 1;
		}
		//������̔�r
		//strcmp(������P,������Q)
		//������P�ƕ�����Q�������Ƃ�0,�قȂ鎞�O�ȊO��Ԃ�
		// �擪��vn�̎��A���_��normal�ɒǉ�����
		if (strcmp(str[0], "vn") == 0) {
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		if (strcmp(str[0], "v") == 0) {
			//�ϒ��z��vertex�ɒǉ�����
			//atof(������) �����񂩂�float�^�̒l��Ԃ�
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//�擪��vt�̎��Auv�ɒǉ�����
		else if (strcmp(str[0], "vt") == 0) {
			//�ϒ��z��uv�ɒǉ�����
			//atof(������)�@�����񂩂�float�^�̒l��Ԃ�
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
		//�擪��usemtl�̎��A�}�e���A���C���f�b�N�X���擾����
		else if (strcmp(str[0], "usemtl") == 0) {
			//�ϒ��z����ォ���r
			for (idx = mpMaterials.size() - 1; idx > 0; idx--) {
				//�������O�̃}�e���A��������΃��[�v�I��
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0) {
					break; //���[�v����o��
				}
			}
		}
		//�擪��f�̎��A�O�p�`���쐬���Ēǉ�����
		else if (strcmp(str[0], "f") == 0) {
			//���_�Ɩ@���̔ԍ��쐬
			int v[3], n[3];
			//�e�N�X�`���}�b�s���O�̗L���𔻒�
			if (strstr(str[1], "//")) {
				//���_�Ɩ@���̔ԍ��擾
				sscanf(str[1], "%d//%d", &v[0], &n[0]);
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);
				//�O�p�`�쐬
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�}�e���A���ԍ��̐ݒ�
				t.MaterialIdx(idx);
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
			else {
				//�e�N�X�`���}�b�s���O�L��
				int u[3];//�e�N�X�`���}�b�s���O�̔ԍ��擾
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				//�O�p�`�쐬
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//�e�N�X�`���}�b�s���O�̐ݒ�
				t.SetUv(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]);
				//�}�e���A���ԍ��̐ݒ�
				t.MaterialIdx(idx);
				//�ϒ��z��mTriangles�ɎO�p�`��ǉ�
				mTriangles.push_back(t);
			}
		}
	}
	//�t�@�C���̃N���[�Y
	fclose(fp);

}
//�`��
void CModel::Render(const CMatrix&m) {
	//�ϒ��z��̗v�f�������J��Ԃ�
	for (int i = 0; i < mTriangles.size(); i++){
		//�}�e���A���̓K�p
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		//�ϒ��z��ɓY�����ŃA�N�Z�X����
		mTriangles[i].Render(m);
		//�}�e���A���𖳌�
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}
CModel::~CModel()
{
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		delete mpMaterials[i];
	}
}