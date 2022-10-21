#ifndef CXENEMY_H
#define CEENEMY_H

#include"CXCharacter.h"
#include"CCollider.h"

class CXEnemy : public CXCharacter{
public:
	void Collision(CCollider* m, CCollider* o);
	void Init(CModelX* model);
	CXEnemy();

private:
	CCollider mColSphereHead;//頭
	CCollider mColSphereSword0;//剣
	CCollider mColSphereSword1;//剣
	CCollider mColSphereSword2;//剣
	//コライダの宣言
	CCollider mColSphereBody; //身体
};

#endif

