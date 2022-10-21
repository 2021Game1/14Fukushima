#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CInput.h"
/*
CXPlayer
*/
#define SPEED_DEFAULT 0.15f		//�X�s�[�h(�ʏ펞)

class CXPlayer : public CXCharacter {
public:
	//�v���C���̏��
	enum EPlayerState
	{
		EIDLE = 0,	//�ҋ@
		EMOVE,		//�ړ�
		//EDASH,		//�_�b�V��
		EGUARD,		//�K�[�h
		EATTACK_1,	//�U��1
		//EATTACK_2,	//�U��2
		//EATTACK_3,	//�U��3(�U��1����h��)
		EDEATH,		//���S
		EKNOCKBACK,	//�m�b�N�o�b�N
	};
	void Update();
	void Init(CModelX* model);
	CXPlayer();
	static CXPlayer* mpPlayerInstance;//�ʂ̃N���X�ŕϐ����Ăяo���ꍇ,static�Ń|�C���^�����
	static CXPlayer* GetInstance();//static�ŏ��������

	void Collision(CCollider* m, CCollider* o);

	void Idle();		//�ҋ@����
	void MoveCamera();	//�J��������ɂ����ړ�����
	void Move();		//�ړ�����
	//void Dash();		//�_�b�V������
	void Attack_1();	//�U��1����
	//void Attack_2();	//�U��2����
	//void Attack_3();	//�U��3����
	void Guard();		//�������
	void Death();		//���S����
	void KnockBack();	//�m�b�N�o�b�N����

private:
	//�R���C�_�̐錾
	CCollider mColSphereHead;//��
	CCollider mColSphereSword;//��
	CCollider mColSphereBody; //�g��
	EPlayerState mState;	//�v���C���[�̏�Ԕ��f�p
	float mSpeed;	//�X�s�[�h

	CVector mMove;			//�����Ƒ��x���������킹���x�N�g���A�v���C���[�̈ړ���
	CVector mMoveDir;		//�ړ���������A���f���̉�]�ɂ��g�p���Ă���A���t���[�����Z�b�g�����
	CVector mMoveDirKeep;	//�ړ����̕�����ۑ�����
	CVector mKnockBackDir;	//�m�b�N�o�b�N���������ێ�����
	CVector mAttackDir;		//�U�����̕�����ێ�����

	CVector mSideVec;		//�J�����̉��x�N�g��
	CVector mFrontVec;		//�J�����̐��ʃx�N�g��
	float mTurnspeed;		//�^�[���̑��x


};
#endif 

