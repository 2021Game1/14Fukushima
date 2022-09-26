#include "CXEnemy.h"
//�R���C�_������
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
	mColSphereBody.Matrix(&mpCombinedMatrix[1]);
	//��
	mColSphereHead.Matrix(&mpCombinedMatrix[1]);
	//��
	mColSphereSword0.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword1.Matrix(&mpCombinedMatrix[26]);
	mColSphereSword2.Matrix(&mpCombinedMatrix[26]);
}