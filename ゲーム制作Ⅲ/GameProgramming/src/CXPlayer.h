#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CColliderCapsule.h"
#include "CVector.h"
#include"CInput.h"
#include"CTexture.h"
#include"CEffect.h"

/*
CXPlayer
*/
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
	void Render2D();
	void TaskCollision();
	CXPlayer();


	void Collision(CCollider* m, CCollider* o);
	static CXPlayer* GetInstance();//static�ŏ��������
	bool GetIsAnimationFrame();
	bool GetIsHit();//�q�b�g��Ԃ̔���
	CXPlayer::EPlayerState GetState();	//�v���C���̏�Ԃ��擾����
	CVector GetSwordColPos();	//���̃R���C�_�̍��W���擾����
private:
	//�R���C�_�̐錾
	CColliderCapsule mPlayer_ColCapsuleSword;	//��
	CColliderCapsule mPlayer_ColCapsuleShield;	//��
	CColliderCapsule mPlayer_ColCapsuleBody;	//�g��
	EPlayerState mPlayer_State;			//�v���C���̏�Ԕ��f�p
	float mPlayer_Speed;				//�v���C���̃X�s�[�h
	float mPlayer_Turnspeed;			//�v���C���̃^�[���̑��x
	float mPlayer_FollowGaugeWid;	//��_���[�W����ǂ�����Q�[�W�̕�

	CVector mPlayer_Move;			//�v���C���̕����Ƒ��x���������킹���x�N�g���A�v���C���̈ړ���
	CVector mPlayer_MoveDir;		//�v���C���̈ړ���������A���f���̉�]�ɂ��g�p���Ă���A���t���[�����Z�b�g�����
	CVector mPlayer_MoveDirKeep;	//�v���C���̈ړ����̕�����ۑ�����
	CVector mPlayer_KnockBackDir;	//�v���C���̃m�b�N�o�b�N���������ێ�����
	CVector mPlayer_AttackDir;		//�v���C���̍U�����̕�����ێ�����

	//�J�����̃p�����[�^���쐬����
	CVector mPlayer_SideVec;		//�v���C���̉��x�N�g��
	CVector mPlayer_FrontVec;		//�v���C���̃J�����̐��ʃx�N�g��
	int mPlayer_Hp;				//�v���C���̗̑�


	

	bool mPlayer_AttackFlag_1;		//�v���C���̍U��1��Ԃ̎�true��Ԃ�
	bool mPlayer_AttackFlag_2;		//�v���C���̍U��2��Ԃ̎�true��Ԃ�
	bool mPlayer_AttackFlag_3;		//�v���C���̍U��3��Ԃ̎�true��Ԃ�
	bool mPlayer_IsHit;			//�v���C���̍U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	bool mPlayer_AttackFlag_Once;	//�v���C���̍U�������u�Ԃ���true��Ԃ��A�G�̉�𔻒�Ɏg�p

	int mPlayer_ComboCount; //�v���C���̃R���{���[�g���ʗp�ϐ�
	int mPlayer_Flag;	   //�v���C���̃t���O
	static CXPlayer* mpPlayer_Instance;//�ʂ̃N���X�Ńv���C���̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����


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

