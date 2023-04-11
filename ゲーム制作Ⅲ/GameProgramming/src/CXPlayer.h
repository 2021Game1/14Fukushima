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
#include"CSound.h"
#include"CTable.h"
#include"CPlayerData.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>



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
	CVector mPlayer_KnockBackDir;		//�v���C���̃m�b�N�o�b�N���������ێ�����
	CVector mPlayer_AttackDir;			//�v���C���̍U�����̕�����ێ�����
	float mPlayer_Speed;				//�v���C���̃X�s�[�h
	float mPlayer_Turnspeed;			//�v���C���̃^�[���̑��x
	float mPlayer_EnemyDis;				//�v���C�����G�̍��W�Q�Ɨp
	float mPlayer_Gauge_Hp_Rate;
	float mPlayer_Attack_Dis;





	//�J�����̃p�����[�^���쐬����
	CVector mPlayer_SideVec;			//�v���C���̉��x�N�g��
	CVector mPlayer_FrontVec;			//�v���C���̃J�����̐��ʃx�N�g��
	int mPlayer_Hp;						//�v���C���̗̑�
	int mPlayer_Hp_Max;
	int mPlayer_Damage_EnemySp1;
	int mPlayer_Damage_EnemySp2;
	int mPlayer_Damage_EnemySp3;

	int	mPlayer_Gauge_Hp_Shake_X;
	int	mPlayer_Gauge_Hp_Shake_Y;
	int	mPlayer_Gauge_Hp_Shake_Range_X;
	int	mPlayer_Gauge_Hp_Shake_Range_Y;

	//�v���C���̍U���t���O�ϐ�
	bool mPlayer_AttackFlag_1;			//�v���C���̍U��1��Ԃ̎�true��Ԃ�
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
	//�v���C���̏Փ˔���֐�
	void Collision(CCollider* m, CCollider* o);	//�Փˏ���
private:
	void PlayerTable();

	int Player_Priority;
	int Player_Hp;
	int	Player_Hp_Max;
	int Player_GameOver_Hp;
	float Player_Speed_Default;
	float Player_Gravity;
	float Player_Thrust;
	float Player_Se;
	float Player_Damage_Se;
	float Player_Push_Reception;
	float Player_Attack_InReception;
	float Player_Attack_OutReception;
	float Player_Attack_Dis;
	int Player_Damage_EnemySp1;
	int Player_Damage_EnemySp2;
	int Player_Damage_EnemySp3;
	float Player_Position_X;
	float Player_Position_Y;
	float Player_Position_Z;
	float Player_Scale_X;
	float Player_Scale_Y;
	float Player_Scale_Z;
	float Player_Rotation_X;
	float Player_Rotation_Y;
	float Player_Rotation_Z;
	float Player_Idle_Animation_Frame;
	float Player_Move_Animation_Frame;
	float Player_Avoidance_Animation_Frame;
	float Player_Attack1_Animation_Frame;
	float Player_Attack2_Animation_Frame;
	float Player_Attack3_Animation_Frame;
	float Player_KnockBack_Animation_Frame;
	float Player_Death_Animation_Frame;
	int Player_Animation_No_Move;
	int Player_Animation_No_Attack1;
	int Player_Animation_No_Attack2;
	int Player_Animation_No_Attack3;
	int Player_Animation_No_AvoidDance;
	int Player_Animation_No_Idle;
	int Player_Animation_No_Knockback;
	int Player_Animation_No_Death;
	float Player_Gauge_Frame_Tex_Wid;
	float Player_Gauge_Frame_Tex_First_Wid;
	float Player_Gauge_Frame_Tex_Hei;
	float Player_Gauge_Frame_Tex_First_Hei;
	float Player_Gauge_Frame_Left;
	float Player_Gauge_Frame_Right;
	float Player_Gauge_Frame_Top;
	float Player_Gauge_Frame_Bottom;
	float Player_Gauge_Wid;
	float Player_Gauge_Wid_First;
	float Player_Gauge_Height;
	float Player_Gauge_Height_first;
	float Player_Gauge_Hp_Top;
	float Player_Gauge_Hp_Bottom;
	int Player_Gauge_Hp_Shake_X;
	int Player_Gauge_Hp_Shake_Y;
	int Player_Gauge_Hp_Shake_Range_X;
	int Player_Gauge_Hp_Shake_Range_Y;
	float Player_Gauge_Hp_Rate;
	float Player_Trun_Set;
	float Player_Trun_Speeds_Set;
	float Player_Trun_Check_Speeds_Set;
	float Player_Trun_Check_Set;

	//�v���C��SE
	CSound Se_Player_AttackSp1;
	CSound Se_Player_AttackSp2;
	CSound Se_Player_AttackSp3;
	CSound Se_Player_Walk;
	CSound Se_Player_Death;
	//�GSE
	CSound Se_Enemy_AttackSp;
};
#endif 

