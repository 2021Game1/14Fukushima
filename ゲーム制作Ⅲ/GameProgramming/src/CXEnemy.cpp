#include "CXEnemy.h"
//コライダ初期化
CXEnemy::CXEnemy()
:mColSphereBody(this, nullptr, CVector(0.5,-1.0f,0.0f), 1.0f)
, mColSphereHead(this, nullptr, CVector(0.0f, 1.f, 0.0f), 1.5f)
, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)
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
	mColSphereBody.Matrix(&mpCombinedMatrix[1]);
	//頭
	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	//剣
	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);
}