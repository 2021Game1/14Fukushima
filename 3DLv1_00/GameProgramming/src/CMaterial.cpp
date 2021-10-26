#include "CMaterial.h"
//memset,strncpy�̃C���N���[�h
#include <string.h>
#include "glut.h"

//�f�t�H���g�R���X�g���N�^
CMaterial::CMaterial() {
	//���O��0�Ŗ���
	memset(mName, 0, sizeof(mName));
	//0�Ŗ��߂�
	memset(mDiffuse, 0, sizeof(mDiffuse));
}
//�}�e���A����L���ɂ���
void CMaterial::Enabled() {
	//�g�U���̐ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
}
//�}�e���A���̖��O���擾
char* CMaterial::Name()
{
	return mName;
}
//�}�e���A���̖��O��ݒ肷��
//Name(�}�e���A���̖��O)
void CMaterial::Name(char* name)
{
	strncpy(mName, name, MATERIAL_NAME_LEN - 1);
}
//mDiffuse�z��̎擾
float* CMaterial::Diffuse()
{
	return mDiffuse;
}
