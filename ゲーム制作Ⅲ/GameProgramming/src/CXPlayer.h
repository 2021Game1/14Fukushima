#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CCollider.h"
/*
CXPlayer
*/

class CXPlayer : public CXCharacter {
public:
	void Update();
	void Init(CModelX* model);
	CXPlayer();
	CCollider mColSphereHead;//頭
	CCollider mColSphereSword;//剣

private:
	//コライダの宣言
	CCollider mColSphereBody; //身体
};
#endif 

