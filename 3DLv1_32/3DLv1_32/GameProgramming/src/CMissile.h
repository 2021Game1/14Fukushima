#ifndef CMISSILE_H
#define CMISSILE_H

//�L�����N�^�N���X�̃C���N���[�h
#include"CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include"CCollider.h"
//�^�X�N�}�l�[�W���̃C���N���[�h
#include"CTaskManager.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include"CCollisionManager.h"


/*
*�~�T�C���N���X
*���f���f�[�^���g�����e������
*/

class CMissile : public CCharacter{
public:

	//CEnemy(�ʒu,��],�g�k)
	CMissile(const CVector& position, const CVector& rotation, const CVector& scale);
	//�X�V
	void Update();
	//�e�̐�������
	int mLife;
	//�`��
	//�Փˏ���
	//Collision(�R���C�_1,�R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	//�Փˏ���
	void TaskCollision();
	//�f�t�H���g�R���X�g���N�^
	CMissile();

private:
	//���f���f�[�^
	static CModel cpModel;
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};
#endif // !



