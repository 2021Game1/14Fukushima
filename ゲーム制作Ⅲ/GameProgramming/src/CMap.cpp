#include"CMap.h"

//�R���C�_������
CMap::CMap()
{
	//�D��x��ݒ�
	mPriority = 90;
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//�ǉ�����
}
void CMap::Collision(CCollider* m, CCollider* o) {
	switch (m->Type())
	{
	case CCollider::ESPHERE: {
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)) {

		}
	}

	}
}
