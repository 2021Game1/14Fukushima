#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include"CModel.h"
#include"CColliderTriangle.h"
/*
���f���f�[�^����O�p�R���C�_�̐���
*/
class CColliderMash
{
public:
	
	//�O�p�R���C�_�̔z��쐬
	CColliderTriangle* mpColliderTriangles;
	CColliderMash();
	~CColliderMash();
	//Set(�e,�e�s��,���f��)
	//���f������O�p�R���C�_�̍쐬
	void Set(CCharacter* parent, CMatrix* matrix, CModel* model);
};
#endif //�I��

