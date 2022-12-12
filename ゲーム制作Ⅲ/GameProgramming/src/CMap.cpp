#include"CMap.h"

//コライダ初期化
CMap::CMap()
{
	//優先度を設定
	mPriority = 90;
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//追加する
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
