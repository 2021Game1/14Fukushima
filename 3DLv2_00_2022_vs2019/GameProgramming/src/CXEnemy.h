#ifndef CXENEMY_H
#define CEENEMY_H

#include"CXCharacter.h"
#include"CCollider.h"

class CXEnemy : public CXCharacter{
public:
	void Init(CModelX* model);
	CXEnemy();
	CCollider mColSphereHead;//��
	CCollider mColSphereSword;//��
private:
	//�R���C�_�̐錾
	CCollider mColSphereBody; //�g��
};

#endif

