#ifndef CMAP_H
#define CMAP_H

#include"CCharacter.h"
#include"CCollider.h"

class CMap : public CCharacter{
public:
	void Collision(CCollider* m, CCollider* o);
	CMap();
	


};

#endif
