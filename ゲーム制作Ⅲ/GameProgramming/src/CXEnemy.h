#ifndef CXENEMY_H
#define CEENEMY_H

#include"CXCharacter.h"
#include"CColliderCapsule.h"

class CXEnemy : public CXCharacter{
public:
	void Collision(CCollider* m, CCollider* o);
	void Init(CModelX* model);
	void Update();
	CXEnemy(const CVector& position, const CVector& rotation, const CVector& scale);
	CXEnemy();


	enum EEnemyState
	{
		EIDLE = 0,		//�ҋ@
		EAUTOMOVE,		//�ړ�
		EDASH,			//�_�b�V��
		EATTACK_1,		//�U��1
		EATTACK_2,		//�U��2
		EATTACK_3,		//�U��3
		EATTACK_4,		//�U��4
		EKNOCKBACK,		//�m�b�N�o�b�N
		EDEATH,			//���S
	};

	static CXEnemy* GetInstance();//static�ŏ��������
	bool GetIsHit();//�q�b�g��Ԃ̔���
	CXEnemy::EEnemyState GetState();	//�v���C���[�̏�Ԃ��擾����
protected:
	//�R���C�_�̐錾
	CCollider mColSphereRightarm1;	//�E�r1
	CCollider mColSphereLeftarm1;	//���r
	CCollider mColSphereRightarm2;	//�E�r2
	CCollider mColSphereLeftarm2;	//���r2
	CColliderCapsule mColSphereBody;	//�g��

	float mSpeed;			//�X�s�[�h
	float mTurnspeed;		//�^�[���̑��x
	float mPlayerDis;
	int mHp;				//�̗�
	CVector mPoint;			//�ړ����̖ڕW�n�_
	CVector mPlayerPos;	//�ǐՎ��̖ڕW�n�_

	CVector mMove;			//�����Ƒ��x���������킹���x�N�g���A�v���C���[�̈ړ���
	CVector mMoveDir;		//�ړ���������A���f���̉�]�ɂ��g�p���Ă���A���t���[�����Z�b�g�����
	CVector mMoveDirKeep;	//�ړ����̕�����ۑ�����
	EEnemyState mState;		//�G�̏�Ԕ��f�p

	bool mIsHit;			//�U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	static CXEnemy* mpEnemyInstance;//�ʂ̃N���X�ŕϐ����Ăяo���ꍇ,static�Ń|�C���^�����

	void Idle();		//�ҋ@����
	void Move();	//�ړ�����
	void Dash();		//�ǐՏ���
	void Attack_1();	//�U��1����
	void Attack_2();	//�U��2����
	void Attack_3();	//�U��3����
	void Attack_4();	//�U��4����
	void KnockBack();	//�m�b�N�o�b�N����
	void Death();		//���S����
};

#endif

