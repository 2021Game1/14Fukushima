#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�g�����X�t�H�[���N���X�̃C���N���[�h
#include"CTransform.h"
//�^�X�N�N���X�̃C���N���[�h
#include"CTask.h"
//�R���W�����}�l�[�W���N���X�̐錾
class CCollisionManager;
/*
�R���C�_�N���X
�Փ˔���N���X
*/
class CCollider : public CTransform,public CTask {
public:
	//friend �R���W�����}�l�[�W���N���X
	friend CCollisionManager;
	//�R���X�g���N�^
	//CCollider(�e,�e�s��,�ʒu,���a)
	CCollider(CCharacter* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//�f�X�g���N�^
	~CCollider();
	//�e�|�C���^�̎擾
	CCharacter* Parent();
	//�`��
	void Render();
	//�Փ˔���
	//Collision(�R���C�_1,�R���C�_2)
	//retrun:true(�Փ˂��Ă���)false(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider* m, CCollider* o);

protected:
	CCharacter* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;//���a

};
#endif 

