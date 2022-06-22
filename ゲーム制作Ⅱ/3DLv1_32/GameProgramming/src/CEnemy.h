#ifndef CENEMY_H
#define CENEMY_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
//�^�X�N�}�l�[�W���̃C���N���[�h
#include"CTaskManager.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include"CCollisionManager.h"
//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"



/*
�G�l�~�[�N���X
�L�����N�^�N���X�̃C���N���[�h
*/
class CEnemy : public CCharacter{
public:
	//�R���X�g���N�^
	//CEnemy(���f��,�ʒu,��],�g�k)
	CEnemy(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	//�X�V����
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1,�R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	//�Փˏ���
	void TaskCollision();

private:
	int mFireCount;
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};
#endif // !CENEMY_H

