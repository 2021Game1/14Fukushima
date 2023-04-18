#ifndef CXENEMY_H
#define CXENEMY_H

#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCamera.h"
#include"CEnemyData.h"
#include"CUtil.h"
#include"CXPlayer.h"
#include "CTable.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>



class CXEnemy : public CXCharacter{
public:
	//�G�̊�{�I�֐�
	void Init(CModelX* model);					//�G�̐ݒ�
	void Update();								//�G�̍X�V
	CXEnemy();									//�G�̃f�t�H���g�R���X�g���N�^
	void Collision(CCollider* m, CCollider* o);	//�G�̓����蔻��
	void Render2D();
	void TaskCollision();
	//�G�̏��
	enum EEnemyState
	{
		EIDLE = 0,								//�ҋ@
		EAUTOMOVE,								//�ړ�
		EDASH,									//�_�b�V��
		EBACKSTEP,								//���
		EATTACK_1,								//�U��1
		EATTACK_2,								//�U��2
		EATTACK_3,								//�U��3
		EKNOCKBACK,								//�m�b�N�o�b�N
		EDEATH,									//���S
	};
	bool GetIsAnimationFrame();
	bool GetHp();								//�G��HP�擾�֐�
	bool GetIsHit();							//�q�b�g��Ԃ̔���
	void SetIsHit(bool hitflag);				//�U���̓����蔻��t���O��ݒ�
	CXEnemy::EEnemyState GetState();			//�v���C���[�̏�Ԃ��擾����
	//���̃N���X�ŎQ�Ɨp�̊֐�
	static CXEnemy* GetInstance();
protected:
	//�R���C�_�̐錾
	CCollider mEnemy_ColSphereRightarm;	//�E�r
	CCollider mEnemy_ColSphereLeftarm;	//���r
	CCollider mEnemy_ColSphereBody;				//���̐g��
	CColliderCapsule mEnemy_ColCapsuleBody;		//�J�v�Z���̐g��
	//�G�̃p�����[�^
	float mEnemy_Speed;							//�G�̃X�s�[�h
	float mEnemy_Turnspeed;						//�G�̃^�[�����x
	float mEnemy_PlayerDis;						//�G���v���C���̍��W�Q�Ɨp
	float mEnemy_FollowGaugeWid;				//��_���[�W����ǂ�����Q�[�W�̕�
	int mEnemy_val;								//�����_���p�̕ϐ�
	int mHp;
	//�G�̍U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	static CXEnemy* mpEnemy_Instance;

	//�G�̈ړ�
	CVector mEnemy_Point;						//�G�ړ����̖ڕW�n�_
	CVector mEnemy_PlayerPos;					//�G�ǐՎ��̖ڕW�n�_
	CVector mEnemy_Move;						//�G�̕����Ƒ��x���������킹���x�N�g���A�v���C���[�̈ړ���
	CVector mEnemy_MoveDir;						//�G�̈ړ���������A���f���̉�]�ɂ��g�p���Ă���A���t���[�����Z�b�g�����
	CVector mEnemy_MoveDirKeep;					//�G�̈ړ����̕�����ۑ�����
	CVector mEnemy_Player_Point;				//�v���C���̕����x�N�g���ۑ��p
	CVector mEnemy_AttackDir;					//�G�̍U�����̕�����ێ�����
	EEnemyState mEnemy_State;					//�G�̏�Ԕ��f�p
	bool mEnemy_Flag;							//�G�̃t���O
	bool mEnemy_IsHit;							//�G�̍U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	//�G�̍s�����\�b�h�֐�
	void Idle();								//�ҋ@����
	void Move();								//�ړ�����
	void Dash();								//�_�b�V������
	void BackStep();							//��ޏ���
	void Attack_1();							//�U��1����
	void Attack_2();							//�U��2����
	void Attack_3();							//�U��3����
	void KnockBack();							//�m�b�N�o�b�N����
	void Death();								//���S����
	//�ړ��̌v�Z����
	void MovingCalculation();

private:
	void EnemyTable();
	int mEnemy_Priority;						//�`��D��x
	float mEnemy_Speed_WalkPattern;				//�ړ��X�s�[�h�p�^�[��
	float mEnemy_Speed_DashPattern;				//�_�b�V���X�s�[�h�p�^�[��
	float mEnemy_Walk_Dis;						//���s�J�n�̋���
	float mEnemy_Dash_Dis;						//���s�J�n�̋���
	float mEnemy_Walk_Dis_Max;					//���s�I���̋���
	float mEnemy_Dash_Dis_Max;					//���s�I���̋���
	float mEnemy_Attack_Dis;					//�U���\�ȋ���
	float mEnemy_Attack_Reception;				//�����蔻��̊J�n
	float mEnemy_Attack_Outreception;			//�����蔻��̏I��
	int mEnemy_Attack_Walk_Rand;				//���s���A�����_���ɍU������
	int mEnemy_Attack_Dash_Rand;				//���s���A�����_���ɍU������
	int mEnemy_Damage_PlayerSp1;				//�v���C���̍U��1�̃_���[�W
	int mEnemy_Damage_PlayerSp2;				//�v���C���̍U��2�̃_���[�W
	float mEnemy_Idle_Animation_Frame;			//�G�̑ҋ@�A�j���[�V�����t���[��
	float mEnemy_Move_Animation_Frame;			//�G�̈ړ��A�j���[�V�����t���[��
	float mEnemy_Dash_Animation_Frame;			//�G�̑��s�A�j���[�V�����t���[��
	float mEnemy_BackStep_Animation_Frame;		//�G�̃o�b�N�X�e�b�v�A�j���[�V�����t���[��
	float mEnemy_Attack1_Animation_Frame;		//�G�̍U��1�A�j���[�V�����t���[��
	float mEnemy_Attack2_Animation_Frame;		//�G�̍U��2�A�j���[�V�����t���[��
	float mEnemy_Attack3_Animation_Frame;		//�G�̍U��3�A�j���[�V�����t���[��
	float mEnemy_Knockback_Animation_Frame;		//�G�̃m�b�N�o�b�N�A�j���[�V�����t���[��
	float mEnemy_Death_Animation_Frame;			//�G�̎��S�A�j���[�V�����t���[��
	int mEnemy_Animation_No_Attack_1;			//�G�̍U��1�A�j���[�V�����ԍ�
	int mEnemy_Animation_No_Attack_2;			//�G�̍U��2�A�j���[�V�����ԍ�
	int mEnemy_Animation_No_Attack_3;			//�G�̍U��3�A�j���[�V�����ԍ�
	int mEnemy_Animation_No_Walk;				//�G�̈ړ��A�j���[�V�����ԍ�
	int mEnemy_Animation_No_Dash;				//�G�̑��s�A�j���[�V�����ԍ�
	int mEnemy_Animation_No_BackStep;			//�G�̃o�b�N�X�e�b�v�A�j���[�V�����ԍ�
	int mEnemy_Animation_No_Idle;				//�G�̑ҋ@�A�j���[�V�����ԍ�
	int mEnemy_Animation_No_Knockback;			//�G�̃m�b�N�o�b�N�A�j���[�V�����ԍ�
	int mEnemy_Animation_No_Death;				//�G�̎��S�A�j���[�V�����ԍ�
	float mEnemy_Position_X;					//�����ʒu��X���W
	float mEnemy_Position_Y;					//�����ʒu��Y���W
	float mEnemy_Position_Z;					//�����ʒu��Z���W
	float mEnemy_Scale_X;						//���f���X�P�[����X���W
	float mEnemy_Scale_Y;						//���f���X�P�[����Y���W
	float mEnemy_Scale_Z;						//���f���X�P�[����Z���W
	float mEnemy_Rotation_X;					//���f���̉�]X���W
	float mEnemy_Rotation_Y;					//���f���̉�]Y���W
	float mEnemy_Rotation_Z;					//���f���̉�]Z���W
	int mEnemy_Probability_Low_Set1;			//�G�̍s��1�ݒ胉���_���ϐ��Œ�l�ݒ�
	int mEnemy_Probability_Max_Set1;			//�G�̍s��1�ݒ胉���_���ϐ��ō��l�ݒ�
	int mEnemy_Probability_Low_Set2;			//�G�̍s��2�ݒ胉���_���ϐ��Œ�l�ݒ�
	int mEnemy_Probability_Max_Set2;			//�G�̍s��2�ݒ胉���_���ϐ��ō��l�ݒ�
	float mEnemy_Gravity;						//�G�̏d��
	int mEnemy_Hp;								//HP
	int mEnemy_Hp_Max;							//HP�ő�l
	int mEnemy_Hp_State;						//HP��Ԑ��ڐݒ�
	int mEnemy_Death_Hp;						//���S����
};
#endif

