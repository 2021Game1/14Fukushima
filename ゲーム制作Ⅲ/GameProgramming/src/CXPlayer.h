#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CColliderCapsule.h"
#include "CVector.h"
#include"CInput.h"
#include"CTexture.h"
#include"CEffect.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"CPlayerData.h"
#include "CCamera.h"


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
		EAVOIDANCE,	//���
		EATTACK_1,	//�U��1
		EATTACK_2,	//�U��2
		EATTACK_3,	//�U��3
		EDEATH,		//���S
		EKNOCKBACK,	//�m�b�N�o�b�N
	};
	//�X�V����
	void Update();
	//���f���̐ݒ�A�����ݒ�
	void Init(CModelX* model);
	//2D�`��
	void Render2D();
	//�^�X�N�R���W����
	void TaskCollision();
	//�f�t�H���g�R���X�g���N�^
	CXPlayer();
	//�v���C����HP�擾�֐�
	bool GetHp();
	//�v���C���̏Փ˔���֐�
	void Collision(CCollider* m, CCollider* o);	//�Փˏ���
	//�v���C���̃C���X�^���X�擾�֐�
	static CXPlayer* GetInstance();		//static�ŏ��������
	//�v���C���̃A�j���[�V�����t���[���擾�֐�
	bool GetIsAnimationFrame();
	//�v���C���̃q�b�g����擾�֐�
	bool GetIsHit();					//�q�b�g��Ԃ̔���
	//�v���C���̏�Ԏ擾�֐�
	CXPlayer::EPlayerState GetState();	//�v���C���̏�Ԃ��擾����
	//�v���C���̌��R���C�_�̍��W�擾
	CVector GetSwordColPos();			//���̃R���C�_�̍��W���擾����
private:
	//�R���C�_�̐錾
	CCollider mPlayer_ColSphereSword;						//��
	CCollider mPlayer_ColSphereShield;				//��
	CCollider mPlayer_ColSphereBody;				//���̐g��
	CColliderCapsule mPlayer_ColCapsuleBody;		//�J�v�Z���̐g��
	//�v���C���̏�Ԑ���
	EPlayerState mPlayer_State;			//�v���C���̏�Ԕ��f�p
	bool mPlayer_InvincibleFlag;				//���G��Ԃ̎�true��Ԃ�


	//�v���C����HP�Q�[�W�p�̕ϐ�
	float mPlayer_FollowGaugeWid;		//��_���[�W����ǂ�����Q�[�W�̕�

	//�v���C���̈ړ��p�ϐ�
	CVector mPlayer_Point;				//�v���C���ړ����̖ڕW�n�_
	CVector mPlayer_Move;				//�v���C���̕����Ƒ��x���������킹���x�N�g���A�v���C���̈ړ���
	CVector mPlayer_MoveDir;			//�v���C���̈ړ���������A���f���̉�]�ɂ��g�p���Ă���A���t���[�����Z�b�g�����
	CVector mPlayer_MoveDirKeep;		//�v���C���̈ړ����̕�����ۑ�����
	CVector mPlayer_Player_Point;		//�G�̕����x�N�g���ۑ��p
	CVector mPlayer_KnockBackDir;		//�v���C���̃m�b�N�o�b�N���������ێ�����
	CVector mPlayer_AttackDir;			//�v���C���̍U�����̕�����ێ�����
	float mPlayer_Speed;				//�v���C���̃X�s�[�h
	float mPlayer_Turnspeed;			//�v���C���̃^�[���̑��x
	float mPlayer_EnemyDis;				//�v���C�����G�̍��W�Q�Ɨp


	//�J�����̃p�����[�^���쐬����
	CVector mPlayer_SideVec;			//�v���C���̉��x�N�g��
	CVector mPlayer_FrontVec;			//�v���C���̃J�����̐��ʃx�N�g��
	int mPlayer_Hp;						//�v���C���̗̑�

	//�v���C���̍U���t���O�ϐ�
	bool mPlayer_AttackFlag_1;			//�v���C���̍U��1��Ԃ̎�true��Ԃ�
	bool mPlayer_AttackFlag_2;			//�v���C���̍U��2��Ԃ̎�true��Ԃ�
	bool mPlayer_AttackFlag_3;			//�v���C���̍U��3��Ԃ̎�true��Ԃ�
	bool mPlayer_SeFlag;				//�v���C����SE�t���O
	bool mPlayer_IsHit;					//�v���C���̍U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	bool mPlayer_AttackFlag_Once;		//�v���C���̍U�������u�Ԃ���true��Ԃ��A�G�̉�𔻒�Ɏg�p
	int mPlayer_ComboCount;				//�v���C���̃R���{���[�g���ʗp�ϐ�
	int mPlayer_Flag;					//�v���C���̃t���O

	//�v���C���̃|�C���^
	static CXPlayer* mpPlayer_Instance;	//�ʂ̃N���X�Ńv���C���̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����

	//�v���C���̍s������
	void Idle();						//�ҋ@����
	void MoveCamera();					//�J��������ɂ����ړ�����
	void Move();						//�ړ�����
	void Attack_1();					//�U��1����
	void Attack_2();					//�U��2����
	void Attack_3();					//�U��3����
	void Avoidance();					//�������
	void Death();						//���S����
	void KnockBack();					//�m�b�N�o�b�N����
	//�ړ��̌v�Z����
	void MovingCalculation();
};
#endif 

