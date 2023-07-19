#ifndef CXENEMY_H
#define CXENEMY_H


#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCamera.h"
#include"CUtil.h"
#include"CXPlayer.h"
#include "CTable.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include<time.h>

/*
CXEnemy�N���X
�G�̃N���X
*/

class CXEnemy : public CXCharacter {
public:
	//���̃N���X�ŎQ�Ɨp�̊֐�
	static CXEnemy* GetInstance();
	//�G�̏��
	enum class EEnemyState
	{
		EIDLE = 0,								//�ҋ@
		EMOVE,									//�ړ�
		EDASH,									//�_�b�V��
		EBACKSTEP,								//���
		EATTACK_1,								//�U��1
		EATTACK_2,								//�U��2
		EKNOCKBACK,								//�m�b�N�o�b�N
		EDEATH,									//���S
	};
	
	//�G�̋����̎��
	enum class EEnemyType {
		ETYPE_TUTORIAL,							//�`���[�g���A�����̓G�̋���
		ETYPE_GAME_1,							//�Q�[���{�Ԏ��̓G�̋���(����)
		ETYPE_GAME_2,							//�Q�[���{�Ԏ��̓G�̋���(�ア)
	};
	//�Đ����̃A�j���[�V�����t���[�������擾����
	bool GetIsAnimationFrame();					
	//�q�b�g��Ԃ̔���
	bool GetIsHit();
	//���S��Ԃ̎���true��Ԃ�
	bool GetIsDeath();	
	//���݂�HP���擾����
	int GetHp();
	//���݂̓G�̃^�C�v���擾
	CXEnemy::EEnemyType GetIsType();
	//�^�C�v�̐ݒ�
	void SetIsType(EEnemyType type);
	//�U���̓����蔻��t���O��ݒ�
	void SetIsHit(bool hitflag);
	//�v���C���ɗ^����_���[�W�擾�p
	int GetIsAttackPoint();	
	//�v���C���ɗ^����X�^���_���[�W�擾�p
	int GetIsStanPoint();
	//�v���C���̏�Ԃ��擾����
	CXEnemy::EEnemyState GetState();					
	//�G���f���ݒ�
	void Init(CModelX* model);					//�G�̃��f���ݒ�
	//�X�V����
	void Update();								//�G�̍X�V
	//�e�[�u���ǂݍ��݊֐�
	void EnemyTable();							//�G�l�~�[�e�[�u��
	//�����蔻��̊i�[
	void TaskCollision();						//�^�X�N�ɓ����蔻����i�[����
	//�f�t�H���g�R���X�g���N�^
	CXEnemy();									//�G�̃f�t�H���g�R���X�g���N�^
protected:

	//�����蔻��ݒ�
	void Collision(CCollider* m, CCollider* o);	//�G�̓����蔻��
	//2D�̕`�揈��
	void Render2D();							//2D�̕`�揈��
	//�G�̍s�����\�b�h�֐�
	void Idle();								//�ҋ@����
	void Move();								//�ړ�����
	void Dash();								//�_�b�V������
	void BackStep();							//��ޏ���
	void Attack_1();							//�U��1����
	void Attack_2();							//�U��2����
	void KnockBack();							//�m�b�N�o�b�N����
	void Death();								//���S����
	//�ړ��̌v�Z����
	void MovingCalculation();


private:
	EEnemyState mEnemy_State;					//�G�̏�Ԕ��f�p

	EEnemyType mEnemy_Type;						//�G�̎�ޔ��f�p
	//�n��
	//�e�[�u���擾�p�ϐ�
	int Enemy_Priority;							//�`��D��x
	int Enemy_Hp;								//HP
	int Enemy_Hp_Max;							//HP�ő�l
	int Enemy_Attack_Point;						//�U����
	int Enemy_Defense_Point;					//�����
	int Enemy_Stan_Point;						//�X�^���l
	float Enemy_Damage_Magnification;			//�_���[�W�{��
	int Enemy_Death_Hp;							//���S����
	float Enemy_Gravity;						//�G�̏d��
	int Enemy_StanAccumulation;				    //�G�̃X�^���~��
	int Enemy_StanAccumulation_Max;				//�G�̃X�^���~�ύő�l
	float Enemy_Speed_WalkPattern;				//�ړ��X�s�[�h�p�^�[��
	float Enemy_Speed_DashPattern;				//�_�b�V���X�s�[�h�p�^�[��
	float Enemy_Speed_BackPattern;				//��ރX�s�[�h�p�^�[��
	float Enemy_Walk_Dis;						//���s�J�n�̋���
	float Enemy_Dash_Dis;						//���s�J�n�̋���
	float Enemy_Walk_Dis_Max;					//���s�I���̋���
	float Enemy_Dash_Dis_Max;					//���s�I���̋���
	float Enemy_Attack_Dis;						//�U���\�ȋ���
	float Enemy_Attack_Reception;				//�����蔻��̊J�n
	float Enemy_Attack_Outreception;			//�����蔻��̏I��
	int Enemy_Action_Rand;						//�A�N�V�����̐��ڐݒ�
	int Enemy_Attack_Walk_Rand;					//���s���A�����_���ɍU������
	int Enemy_Attack_Dash_Rand;					//���s���A�����_���ɍU������
	int Enemy_AttackSp1_Set;					//�U��1�̎��A�U���\���Ǐ]���鐸�x�ݒ�
	int Enemy_AttackSp2_Set;					//�U��2�̎��A�U���\���Ǐ]���鐸�x�ݒ�
	float Enemy_Idle_Animation_Frame;			//�G�̑ҋ@�A�j���[�V�����t���[��
	float Enemy_Move_Animation_Frame;			//�G�̈ړ��A�j���[�V�����t���[��
	float Enemy_Dash_Animation_Frame;			//�G�̑��s�A�j���[�V�����t���[��
	float Enemy_BackStep_Animation_Frame;		//�G�̃o�b�N�X�e�b�v�A�j���[�V�����t���[��
	float Enemy_Attack1_Animation_Frame;		//�G�̍U��1�A�j���[�V�����t���[��
	float Enemy_Attack2_Animation_Frame;		//�G�̍U��2�A�j���[�V�����t���[��
	float Enemy_Knockback_Animation_Frame;		//�G�̃m�b�N�o�b�N�A�j���[�V�����t���[��
	float Enemy_Death_Animation_Frame;			//�G�̎��S�A�j���[�V�����t���[��
	int Enemy_Animation_No_Attack_1;			//�G�̍U��1�A�j���[�V�����ԍ�
	int Enemy_Animation_No_Attack_2;			//�G�̍U��2�A�j���[�V�����ԍ�
	int Enemy_Animation_No_Walk;				//�G�̈ړ��A�j���[�V�����ԍ�
	int Enemy_Animation_No_Dash;				//�G�̑��s�A�j���[�V�����ԍ�
	int Enemy_Animation_No_BackStep;			//�G�̃o�b�N�X�e�b�v�A�j���[�V�����ԍ�
	int Enemy_Animation_No_Idle;				//�G�̑ҋ@�A�j���[�V�����ԍ�
	int Enemy_Animation_No_Knockback;			//�G�̃m�b�N�o�b�N�A�j���[�V�����ԍ�
	int Enemy_Animation_No_Death;				//�G�̎��S�A�j���[�V�����ԍ�
	float Enemy_Position_X;						//�G�̃|�W�V�����ݒ�X���W
	float Enemy_Position_Y;						//�G�̃|�W�V�����ݒ�Y���W
	float Enemy_Position_Z;						//�G�̃|�W�V�����ݒ�Z���W
	float Enemy_Scale_X;						//���f���X�P�[����X���W
	float Enemy_Scale_Y;						//���f���X�P�[����Y���W
	float Enemy_Scale_Z;						//���f���X�P�[����Z���W
	float Enemy_Rotation_X;						//���f���̉�]X���W
	float Enemy_Rotation_Y;						//���f���̉�]Y���W
	float Enemy_Rotation_Z;						//���f���̉�]Z���W
	//�I���

	//�R���C�_�̐錾
	CCollider mEnemy_ColSphereRightarm;			//�E�r
	CCollider mEnemy_ColSphereLeftarm;			//���r
	CCollider mEnemy_ColSphereBody;				//���̐g��
	CColliderCapsule mEnemy_ColCapsuleBody;		//�J�v�Z���̐g��

	//�G��UI�C���X�^���X
	CTexture gEnemy_Ui_Hp_BackBar;				//HP�̔w�i�o�[
	//�G���f��
	CModelX gEnemy_Model_Mutant;

	//�G�̃p�����[�^
	float mEnemy_Speed;							//�G�̃X�s�[�h
	float mEnemy_Turnspeed;						//�G�̃^�[�����x
	float mEnemy_PlayerDis;						//�G���v���C���̍��W�Q�Ɨp
	float mEnemy_FollowGaugeWid;				//��_���[�W����ǂ�����Q�[�W�̕�
	int mEnemy_val;								//�����_���p�̕ϐ�


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
	bool mEnemy_Flag;							//�G�̃t���O
	bool mEnemy_IsHit;							//�G�̍U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	bool mEnemy_Death_Flag;						//�G�̎��S�������t���O

	//�X�e�[�^�X
	int mHp;									//HP�ݒ�
	int mAttack_Point;							//�U����
	int mDefense_Point;							//�����
	int mStan_Point;							//�X�^���l
	int mStanAccumulation;						//�X�^���~��

	//�v���C������̍U�����f�p
	int mDamage;								//�v���C������̃_���[�W
	int mStan_Damage;							//�v���C������̃X�^���_���[�W

};
#endif

