#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�g�����X�t�H�[���N���X�̃C���N���[�h
#include "CTransform.h"
class CCollisionManager;
/*
�R���C�_�N���X
�Փ˔���f�[�^
*/
class CCollider : public CTransform, public CTask {
	friend CCollisionManager;
public:
	//�R���C�_�^�C�v
	enum EType {
		ESPHERE,//���R���C�_
		ETRIANGLE,//�O�p�R���C�_
		ELINE, //�����R���C�_
		ECAPSUL, //�J�v�Z���R���C�_
	};
	//�e�|�C���^�̎擾
	CCharacter* Parent();
	enum ETag
	{
		EBODY,			//�{��
		EHEAD,			//��
		ESWORD,			//��
		ERIGHTARM,		//�E�r
		ELEFTARM,		//���r
	};

	//�f�t�H���g�R���X�g���N�^
	CCollider();

	//�R���X�g���N�^
	//CCollider(�e, �s��, �ʒu, ���a)
	CCollider(CCharacter *parent, CMatrix *matrix, const CVector& position, float radius);
	//�`��
	void Render();
	~CCollider();
	//�Փ˔���
	//Collision(�R���C�_1, �R���C�_2)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider *m, CCollider *o);
	//CollisionTriangleLine(�O�p�R���C�_, �����R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CCollider *triangle, CCollider *line, CVector *adjust);
	//CollisionTriangleSphere(�O�p�R���C�_, ���R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleSphere(CCollider *triangle, CCollider *sphere, CVector *adjust);
	//�J�v�Z���R���C�_���m�̏Փ˔���
	//CollisionCapsule(�R���C�_1, �R���C�_2, �����x�N�g��)
	static bool CollisionCapsule(CCollider* m, CCollider* o, CVector* adjust);
	//2���Ԃ̍ŒZ�x�N�g�������߂�
	//VectorLineMinDist(��1�n�_, ��1�I�_, ��2�n�_, ��2�I�_)
	static CVector VectorLineMinDist(const CVector& Start1, const CVector& End1, const CVector& Start2, const CVector& End2);
	//�D��x�̕ύX
	virtual void ChangePriority();
	//�R���C�_��ނ̎擾
	EType Type();
	//�^�O�̎擾
	ETag Tag();
	//�^�O�̐ݒ�
	//Tag(�^�O)
	void Tag(ETag tag);
	void Matrix(CMatrix* m);
	CMatrix* GetIsMatrix();
protected:
	CCharacter* mpParent;//�e
	CMatrix* mpMatrix;//�e�s��
	float mRadius;	//���a
	EType mType;//�R���C�_�^�C�v
	//���_
	CVector mV[3];
	ETag mTag;
	
};

#endif
