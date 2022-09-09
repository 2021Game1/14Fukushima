#include "CXEnemy.h"
//コライダ初期化
CXEnemy::CXEnemy()
:mColSphereBody(this, nullptr, CVector(), 0.5)
, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
{
}
void CXEnemy::Collision(CCollider* m, CCollider* o){
	switch (m->Type(),o->Type())
	{
	case CCollider::ESPHERE: {
		//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {
			if (o->Parent()->Tag() == EPLAYER && o->ESWORD)
			{
				//30フレーム掛けてダウンし、繰り返さない
				ChangeAnimation(11, false, 30);
			}
		}
	}
	}
}
void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.Matrix(&mpCombinedMatrix[8]);
	mColSphereHead.Matrix(&mpCombinedMatrix[11]);
	mColSphereSword.Matrix(&mpCombinedMatrix[21]);
}