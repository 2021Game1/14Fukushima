#ifndef CMAP_H
#define CMAP_H

#include"CCharacter.h"
#include"CCollider.h"
#include"CTaskManager.h"

class CMap : public CCharacter{
	static CMap* mMap_Instance; //マップのインスタンス
public:
	void Collision(CCollider* m, CCollider* o);
	CMap();
	static void Generate();	//生成
	static void Release();	//解放
};

#endif
