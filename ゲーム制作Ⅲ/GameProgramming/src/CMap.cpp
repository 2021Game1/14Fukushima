#include"CMap.h"

//コライダ初期化
CMap::CMap()
{
	
}
void CMap::Collision(CCollider* m, CCollider* o) {
	switch (m->Type())
	{
	case CCollider::ESPHERE: {
		//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {

		}
	}

	}
}
