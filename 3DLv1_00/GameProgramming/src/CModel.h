#ifndef CMODEL_H
#define CMODEL_H
//vector�̃C���N���[�h
#include<vector>
//CTriangle�̃C���N���[�h
#include"CTriangle.h"
//�}�e���A���N���X�̃C���N���[�h
#include"CMaterial.h"
/*
���f���N���X
���f���f�[�^�̓��͂�\��
*/
class CModel {
public:
	//���f���t�@�C���̓���
	//Load(���f���t�@�C�����A�}�e���A���t�@�C�����j
	void Load(char* obj, char* mtl);
	//�`��
	//Render(�s��)
	void Render(const CMatrix& m);
	~CModel();
private:
	//�O�p�`�̉ϒ��z��
	std::vector<CTriangle>mTriangles;
	//�}�e���A���|�C���^�̉ϒ��z��
	std::vector<CMaterial*>mpMaterials;
	
};

#endif 

