#ifndef CMAP_H
#define CMAP_H

#include"CCharacter.h"
#include"CCollider.h"
#include"CTaskManager.h"

class CMap : public CCharacter{
	static CMap* mMap_Instance; //�}�b�v�̃C���X�^���X
public:
	void Collision(CCollider* m, CCollider* o);
	CMap();
	static void Generate();	//����
	static void Release();	//���
};

#endif
