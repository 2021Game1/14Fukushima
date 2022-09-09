#include "CXEnemy.h"
//�R���C�_������
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
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)) {
			if (o->Parent()->Tag() == EPLAYER && o->ESWORD)
			{
				//30�t���[���|���ă_�E�����A�J��Ԃ��Ȃ�
				ChangeAnimation(11, false, 30);
			}
		}
	}
	}
}
void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.Matrix(&mpCombinedMatrix[8]);
	mColSphereHead.Matrix(&mpCombinedMatrix[11]);
	mColSphereSword.Matrix(&mpCombinedMatrix[21]);
}