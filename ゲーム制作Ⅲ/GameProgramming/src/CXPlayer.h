#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CColliderCapsule.h"
#include "CVector.h"
#include"CInput.h"
/*
CXPlayer
*/
#define SPEED_DEFAULT 0.5f		//�X�s�[�h(�ʏ펞)

class CXPlayer : public CXCharacter{
public:
	//�v���C���̏��
	enum EPlayerState
	{
		EIDLE = 0,	//�ҋ@
		EMOVE,		//�ړ�
		EGUARD,		//�K�[�h
		EATTACK_1,	//�U��1
		EATTACK_2,	//�U��2
		EATTACK_3,	//�U��3
		EDEATH,		//���S
		EKNOCKBACK,	//�m�b�N�o�b�N
	};
	void Update();
	void Init(CModelX* model);
	CXPlayer();


	void Collision(CCollider* m, CCollider* o);
	static CXPlayer* GetInstance();//static�ŏ��������
	bool GetIsHit();//�q�b�g��Ԃ̔���
	CXPlayer::EPlayerState GetState();	//�v���C���[�̏�Ԃ��擾����

private:
	//�R���C�_�̐錾
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��
	CCollider mColSphereSword3;	//��
	CCollider mColSphereSword4;	//��
	CCollider mColSphereShield;	//��
	CColliderCapsule mColSphereBody;	//�g��
	EPlayerState mState;	//�v���C���[�̏�Ԕ��f�p
	float mSpeed;			//�X�s�[�h
	float mTurnspeed;		//�^�[���̑��x

	CVector mMove;			//�����Ƒ��x���������킹���x�N�g���A�v���C���[�̈ړ���
	CVector mMoveDir;		//�ړ���������A���f���̉�]�ɂ��g�p���Ă���A���t���[�����Z�b�g�����
	CVector mMoveDirKeep;	//�ړ����̕�����ۑ�����
	CVector mKnockBackDir;	//�m�b�N�o�b�N���������ێ�����
	CVector mAttackDir;		//�U�����̕�����ێ�����

	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;		//���_,�����_,�����
	CVector mSideVec;		//�J�����̉��x�N�g��
	CVector mFrontVec;		//�J�����̐��ʃx�N�g��
	int mHp;				//�̗�
	

	bool mAttackFlag_1;		//�U��1��Ԃ̎�true��Ԃ�
	bool mAttackFlag_2;		//�U��2��Ԃ̎�true��Ԃ�
	bool mAttackFlag_3;		//�U��3��Ԃ̎�true��Ԃ�
	bool mIsHit;			//�U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	bool mAttackFlag_Once;	//�U�������u�Ԃ���true��Ԃ��A�G�̉�𔻒�Ɏg�p

	int mPlayerComboCount; //�R���{���[�g���ʗp�ϐ�
	int mPlayerFlag;
	static CXPlayer* mpPlayerInstance;//�ʂ̃N���X�ŕϐ����Ăяo���ꍇ,static�Ń|�C���^�����


	void Idle();		//�ҋ@����
	void MoveCamera();	//�J��������ɂ����ړ�����
	void Move();		//�ړ�����
	void Attack_1();	//�U��1����
	void Attack_2();	//�U��2����
	void Attack_3();	//�U��3����
	void Guard();		//�������
	void Death();		//���S����
	void KnockBack();	//�m�b�N�o�b�N����

};
#endif 

