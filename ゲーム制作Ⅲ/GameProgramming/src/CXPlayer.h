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
	CCollider mColSphereHead;//��
	CCollider mColSphereSword;//��

private:
	//�R���C�_�̐錾
	CCollider mColSphereBody; //�g��
};
#endif 

