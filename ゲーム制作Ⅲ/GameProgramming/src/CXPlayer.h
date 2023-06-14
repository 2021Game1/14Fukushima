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
#include"CXEnemy.h"
#include "CModelX.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>

//�v���C��UI
#define PLAYER_UI_HP_FRAME "res\\Ui\\Player_HP_Frame.png"

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
		EDEATH,		//���S
		EKNOCKBACK,	//�m�b�N�o�b�N
	};
	//�X�V����
	void Update();
	//���f���̐ݒ�A�����ݒ�
	void Init(CModelX* model);
	//���W�A��]�l�A�X�P�[���̎擾
	void GetPos();								//���W�̎擾
	void GetScale();							//�X�P�[���̎擾
	void GetRotation();							//���f���̉�]�l�擾
	//2D�`��
	void Render2D();
	//�^�X�N�R���W����
	void TaskCollision();
	//�f�t�H���g�R���X�g���N�^
	CXPlayer();
	//�v���C����HP�擾�֐�
	int GetHp();	
	//�v���C���̃C���X�^���X�擾�֐�
	static CXPlayer* GetInstance();		//static�ŏ��������
	//�v���C���̃��f���擾
	//�v���C���̃A�j���[�V�����t���[���擾�֐�
	bool GetIsAnimationFrame();
	//�v���C���̃q�b�g����擾�֐�
	bool GetIsHit();					//�q�b�g��Ԃ̔���
	//�v���C���̗^����_���[�W�擾�p
	int GetIsAttackPoint();
	//�v���C���̗^����X�^���_���[�W�擾�p
	int GetIsStanPoint();
	//�v���C���̏�Ԏ擾�֐�
	CXPlayer::EPlayerState GetState();	//�v���C���̏�Ԃ��擾����
	//�v���C���̌��R���C�_�̍��W�擾
	CVector GetSwordColPos();			//���̃R���C�_�̍��W���擾����
	//�v���C���̈ړ��ʎ擾
	CVector GetInMoveDir();
	//�e�[�u���擾�֐�
	void PlayerTable();
private:
	//�v���C��SE
	CSound Se_Player_AttackSp1;						//�v���C�����U��1�̎�����
	CSound Se_Player_AttackSp2;						//�v���C�����U��2�̎�����
	CSound Se_Player_Walk;							//�v���C�����ړ�������
	CSound Se_Player_Death;							//�v���C�����S������
	//�GSE
	CSound Se_Enemy_AttackSp;						//�G����U�����󂯂����ɗ���
	//�v���C����UI�C���X�^���X
	CTexture gPlayer_Ui_Hp_Frame;

	//�R���C�_�̐錾
	CCollider mPlayer_ColSphereSword;				//��
	CCollider mPlayer_ColSphereBody;				//���̐g��
	CCollider mPlayer_ColSphereLowerBody;				//���̐g��
	CCollider mPlayer_ColSphereHead;				//���̓�
	CColliderCapsule mPlayer_ColCapsuleBody;		//�J�v�Z���̐g��

	//�v���C���̏�Ԑ���
	EPlayerState mPlayer_State;			//�v���C���̏�Ԕ��f�p
	bool mPlayer_InvincibleFlag;		//���G��Ԃ̎�true��Ԃ�
	bool mPlayer_Avoid;					//�����Ԃ̎�true��Ԃ�

	//�v���C����HP�Q�[�W�p�̕ϐ�
	float mPlayer_FollowGaugeWid;		//��_���[�W����ǂ�����Q�[�W�̕�
	float mPlayer_Gauge_Hp_Rate;		//�v���C����HP�Q�[�W�̗h�ꕝ�ݒ�

	//�v���C���̈ړ��p�ϐ�
	CVector mPlayer_Point;				//�v���C���ړ����̖ڕW�n�_
	CVector mPlayer_Move;				//�v���C���̕����Ƒ��x���������킹���x�N�g���A�v���C���̈ړ���
	CVector mPlayer_MoveDir;			//�v���C���̈ړ���������A���f���̉�]�ɂ��g�p���Ă���A���t���[�����Z�b�g�����
	CVector mPlayer_MoveDirKeep;		//�v���C���̈ړ����̕�����ۑ�����
	CVector mPlayer_KnockBackDir;		//�v���C���̃m�b�N�o�b�N���������ێ�����
	CVector mPlayer_AttackDir;			//�v���C���̍U�����̕�����ێ�����
	float mPlayer_Speed;				//�v���C���̃X�s�[�h(�f�t�H���g)
	float mPlayer_Speed_Avoid;			//�v���C���̃X�s�[�h(���)
	float mPlayer_Avoid_Time;			//�v���C���̉������
	float mPlayer_Turnspeed;			//�v���C���̃^�[���̑��x
	float mPlayer_EnemyDis;				//�v���C�����G�̍��W�Q�Ɨp
	float mPlayer_Attack_Dis;			//�v���C���̍U���Ώ۔��ʌ�̋����ݒ�
	CVector mPlayer_Gravity;				//�d�͂̕ۑ��p

	//�J�����̃p�����[�^���쐬����
	CVector mPlayer_SideVec;			//�v���C���̉��x�N�g��
	CVector mPlayer_FrontVec;			//�v���C���̃J�����̐��ʃx�N�g��


	int	mPlayer_Gauge_Hp_Shake_X;		//HP�Q�[�W�̗h�ꕝ�ŏ��l��X
	int	mPlayer_Gauge_Hp_Shake_Y;		//HP�Q�[�W�̗h�ꕝ�ŏ��l��Y
	int	mPlayer_Gauge_Hp_Shake_Range_X; //HP�Q�[�W�̗h�ꕝ�ŏ��l��X
	int	mPlayer_Gauge_Hp_Shake_Range_Y; //HP�Q�[�W�̗h�ꕝ�ŏ��l��Y

	//�v���C���̍U���t���O�ϐ�
	bool mPlayer_AttackFlag_1;			//�v���C���̍U��1��Ԃ̎�true��Ԃ�
	bool mPlayer_SeFlag;				//�v���C����SE�t���O
	bool mPlayer_IsHit;					//�v���C���̍U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	bool mPlayer_AttackFlag_Once;		//�v���C���̍U�������u�Ԃ���true��Ԃ��A�G�̉�𔻒�Ɏg�p
	int mPlayer_ComboCount;				//�v���C���̃R���{���[�g���ʗp�ϐ�
	int mPlayer_Flag;					//�v���C���̃t���O

	//�G�ɗ^����U��
	int mDamage;					//�G����̃_���[�W
	int mStan_Damage;				//�G����̃X�^���_���[�W
	int mStanAccumulation;			//�X�^���~��
	//�X�e�[�^�X
	int mPlayer_Hp;					//�̗�
	int mPlayer_Hp_Max;				//�̗͂̏��
	int mAttack_Point;				//�U����
	int mDefense_Point;				//�����
	int mStan_Point;				//�X�^���l

	//�v���C���̃|�C���^
	static CXPlayer* mpPlayer_Instance;	//�ʂ̃N���X�Ńv���C���̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����

	//�e�[�u���擾�p�ϐ�
	int Player_Priority;							//�`��D��x
	int Player_Hp;									//�v���C����HP
	int	Player_Hp_Max;								//�v���C����HP���
	int Player_Attack_Point;						//�v���C���̍U����
	int Player_Defense_Point;						//�v���C���̎����
	int	Player_Stan_Point;							//�G�ɗ^����X�^���l
	int Player_StanAccumulation;					//�v���C���̃X�^���~��
	int Player_StanAccumulation_Max;				//�v���C���̃X�^���~�ύő�l
	float Player_Damage_Magnification;				//�v���C���̃_���[�W�{��
	int Player_GameOver_Hp;							//�v���C���̃Q�[���I�[�o�[����(HP)
	float Player_Speed_Default;						//�v���C���̃X�s�[�h(�f�t�H���g)
	float Player_Speed_Avoid;						//�v���C���̃X�s�[�h(���)
	float Player_Avoid_Time;						//�v���C���̉������
	float Player_Gravity;							//�v���C���Ɋ|����d��
	float Player_Thrust;							//�v���C���Ɋ|���鐄��
	float Player_Se;								//SE�̉��ʐݒ�
	float Player_Damage_Se;							//�_���[�WSE�̉��ʐݒ�
	float Player_Push_Reception;					//�}�E�X���N���b�N�̔����^�C�~���O
	float Player_Attack_InReception;				//�U������n��
	float Player_Attack_OutReception;				//�U������I���
	float Player_Attack_Dis;						//�v���C���̍U���Ώ۔��ʌ�̋����ݒ�
	float Player_Position_X;						//�v���C���̈ʒuX���W
	float Player_Position_Y;						//�v���C���̈ʒuY���W
	float Player_Position_Z;						//�v���C���̈ʒuZ���W
	float Player_Scale_X;							//�v���C���̃X�P�[��X���W
	float Player_Scale_Y;							//�v���C���̃X�P�[��Y���W
	float Player_Scale_Z;							//�v���C���̃X�P�[��Z���W
	float Player_Rotation_X;						//�v���C���̃��f���̉�]�l
	float Player_Rotation_Y;						//�v���C���̃��f���̉�]�l
	float Player_Rotation_Z;						//�v���C���̃��f���̉�]�l
	float Player_Idle_Animation_Frame;				//�v���C���̑ҋ@�A�j���[�V�����t���[��
	float Player_Move_Animation_Frame;				//�v���C���̈ړ��A�j���[�V�����t���[��
	float Player_Avoidance_Animation_Frame;			//�v���C���̉���A�j���[�V�����t���[��
	float Player_Attack1_Animation_Frame;			//�v���C���̍U��1�A�j���[�V�����t���[��
	float Player_Attack1_Idle_Animation_Frame;		//�v���C���̍U��1�̌�A�Đ�����ҋ@�A�j���[�V�����t���[��
	float Player_Attack2_Animation_Frame;			//�v���C���̍U��2�A�j���[�V�����t���[��
	float Player_Attack2_Idle_Animation_Frame;		//�v���C���̍U��2�̌�A�Đ�����ҋ@�A�j���[�V�����t���[��
	float Player_KnockBack_Animation_Frame;			//�v���C���̃m�b�N�o�b�N�A�j���[�V�����t���[��
	float Player_Death_Animation_Frame;				//�v���C���̎��S�A�j���[�V�����t���[��
	int Player_Animation_No_Move;					//�v���C���̈ړ��A�j���[�V�����ԍ�
	int Player_Animation_No_Attack1;				//�v���C���̍U��1�A�j���[�V�����ԍ�
	int Player_Animation_No_Attack1_Idle;			//�U��1�Đ���̑ҋ@�A�j���[�V�����ԍ�
	int Player_Animation_No_Attack2;				//�v���C���̍U��2�A�j���[�V�����ԍ�
	int Player_Animation_No_Attack2_Idle;			//�U��2�Đ���̑ҋ@�A�j���[�V�����ԍ�
	int Player_Animation_No_AvoidDance;				//�v���C���̉���A�j���[�V�����ԍ�
	int Player_Animation_No_Idle;					//�v���C���̑ҋ@�A�j���[�V�����ԍ�
	int Player_Animation_No_Knockback;				//�v���C���̃m�b�N�o�b�N�A�j���[�V�����ԍ�
	int Player_Animation_No_Death;					//�v���C���̎��S�A�j���[�V�����ԍ�
	float Player_Gauge_Frame_Tex_Wid;				//�v���C����HP�Q�[�W�t���[���e�N�X�`���I�_�̉���
	float Player_Gauge_Frame_Tex_First_Wid;			//�v���C����HP�Q�[�W�t���[���e�N�X�`���n�_�̉���
	float Player_Gauge_Frame_Tex_Hei;				//�v���C����HP�Q�[�W�t���[���e�N�X�`���I�_�̏c��
	float Player_Gauge_Frame_Tex_First_Hei;			//�v���C����HP�Q�[�W�t���[���e�N�X�`���n�_�̏c��
	float Player_Gauge_Frame_Left;					//�v���C����HP�Q�[�W�t���[�������W�w��
	float Player_Gauge_Frame_Right;					//�v���C����HP�Q�[�W�t���[���E���W�w��
	float Player_Gauge_Frame_Top;					//�v���C����HP�Q�[�W�t���[�����_���W�w��
	float Player_Gauge_Frame_Bottom;				//�v���C����HP�Q�[�W�t���[����Ӎ��W�w��
	float Player_Gauge_Wid;							//�v���C����HP�Q�[�W�I�_�̉���
	float Player_Gauge_Wid_First;					//�v���C����HP�Q�[�W�n�_�̉���
	float Player_Gauge_Height;						//�v���C����HP�Q�[�W�I�_�̏c��
	float Player_Gauge_Height_first;				//�v���C����HP�Q�[�W�n�_�̏c��
	float Player_Gauge_Hp_Top;						//�v���C����HP�Q�[�W���_���W�w��
	float Player_Gauge_Hp_Bottom;					//�v���C����HP�Q�[�W��Ӎ��W�w��
	int Player_Gauge_Hp_Shake_X;					//�v���C����HP�Q�[�W��h�炷X���W�̏����l�l�ݒ�
	int Player_Gauge_Hp_Shake_Y;					//�v���C����HP�Q�[�W��h�炷Y���W�̏����l�ݒ�
	int Player_Gauge_Hp_Shake_Range_X;				//�v���C����HP�Q�[�W��h�炷X���W�̍ő�l
	int Player_Gauge_Hp_Shake_Range_Y;				//�v���C����HP�Q�[�W��h�炷Y���W�̍ő�l
	float Player_Gauge_Hp_Rate;						//�v���C����HP�Q�[�W�̗h�ꔻ��
	float Player_Trun_Set;							//�v���C���̉�]�ݒ�
	float Player_Trun_Speeds_Set;					//�v���C���̉�]���x�ݒ�
	float Player_Trun_Check_Speeds_Set;				//�v���C���̉�]���x�`�F�b�N�ݒ�
	float Player_Trun_Check_Set;					//�v���C���̉�]�`�F�b�N�ݒ�

	//�v���C���̍s������
	void Idle();						//�ҋ@����
	void MoveCamera();					//�J��������ɂ����ړ�����
	void Move();						//�ړ�����
	void Attack_1();					//�U��1����
	void Attack_2();					//�U��2����
	void Avoidance();					//�������
	void Death();						//���S����
	void KnockBack();					//�m�b�N�o�b�N����
	//�ړ��̌v�Z����
	void MovingCalculation();
	//�v���C���̏Փ˔���֐�
	void Collision(CCollider* m, CCollider* o);		//�Փˏ���

};
#endif 

