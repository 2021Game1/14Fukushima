#ifndef CXENEMY_H
#define CEENEMY_H

#include"CXCharacter.h"
#include"CCollider.h"

class CXEnemy : public CXCharacter{
public:
	void Init(CModelX* model);
	CXEnemy();
	CCollider mColSphereHead;//頭
	CCollider mColSphereSword;//剣
private:
	//コライダの宣言
	CCollider mColSphereBody; //身体
};

#endif

