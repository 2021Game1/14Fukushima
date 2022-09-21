#ifndef CXENEMY_H
#define CEENEMY_H

#include"CXCharacter.h"
#include"CCollider.h"

class CXEnemy : public CXCharacter{
public:
	void Collision(CCollider* m, CCollider* o);
	void Init(CModelX* model);
	CXEnemy();
	CCollider mColSphereHead;//��
	CCollider mColSphereSword0;//��
	CCollider mColSphereSword1;//��
	CCollider mColSphereSword2;//��
private:
	//�R���C�_�̐錾
	CCollider mColSphereBody; //�g��
};

#endif

