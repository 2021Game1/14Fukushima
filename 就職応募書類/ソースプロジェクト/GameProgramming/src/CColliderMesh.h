#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
/*
���f���f�[�^����O�p�R���C�_�̐���
*/
class CColliderMesh
{
public:
	//�C���X�^���X�̎擾
	static CColliderMesh* GetInstance();//static�ŏ��������
	//�O�p�R���C�_�̔z��쐬
	CColliderTriangle *mpColliderTriangles;
	CColliderMesh();
	~CColliderMesh();
	//Set(�e, �e�s��, ���f��)
	//���f������O�p�R���C�_�̐���
	void Set(CCharacter *parent, CMatrix *matrix, CModel *model);
private:
	//��̃��f���|�C���^
	static CColliderMesh* mpColliderMesh_Instance;	//�ʂ̃N���X����ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
};

#endif
