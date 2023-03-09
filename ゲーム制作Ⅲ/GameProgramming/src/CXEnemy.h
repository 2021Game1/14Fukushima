#ifndef CXENEMY_H
#define CXENEMY_H

#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCamera.h"
#include"CEnemyData.h"



class CXEnemy : public CXCharacter{
public:
	//�G�̊�{�I�֐�
	void Init(CModelX* model);					//�G�̐ݒ�
	void Update();								//�G�̍X�V
	CXEnemy();									//�G�̃f�t�H���g�R���X�g���N�^
	void Collision(CCollider* m, CCollider* o);	//�G�̓����蔻��
	void Render2D();
	void Load(int argc, char* argv[]);
	void TaskCollision();
	//�G�̏��
	enum EEnemyState
	{
		EIDLE = 0,								//�ҋ@
		EAUTOMOVE,								//�ړ�
		EDASH,									//�_�b�V��
		EATTACK_1,								//�U��1
		EATTACK_2,								//�U��2
		EATTACK_3,								//�U��3
		EKNOCKBACK,								//�m�b�N�o�b�N
		//EREPELLED,								//�͂����ꂽ���̃m�b�N�o�b�N
		EDEATH,									//���S
	};
	bool GetIsAnimationFrame();
	bool GetHp();								//�G��HP�擾�֐�
	bool GetIsHit();							//�q�b�g��Ԃ̔���
	void SetIsHit(bool hitflag);				//�U���̓����蔻��t���O��ݒ�
	CXEnemy::EEnemyState GetState();			//�v���C���[�̏�Ԃ��擾����
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
	int mEnemy_Hp;								//�G�̗̑�
	int mEnemy_val;								//�����_���p�̕ϐ�

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
	void Dash();								//�ǐՏ���
	void Attack_1();							//�U��1����
	void Attack_2();							//�U��2����
	void Attack_3();							//�U��3����
	void KnockBack();							//�m�b�N�o�b�N����
	void Death();								//���S����
	//�ړ��̌v�Z����
	void MovingCalculation();

	int Enemy_Type;//�G���
	int Enemy_Priority;//�`��D��x
	float Enemy_Speed_WalkPattern;//�ړ��X�s�[�h�p�^�[��
	float Enemy_Speed_DashPattern;//���s�X�s�[�h�p�^�[��
	float Enemy_Walk_Dis; //���s�J�n�̋���
	float Enemy_Dash_Dis; //���s�J�n�̋���
	float Enemy_Walk_Dis_Max; //���s�I���̋���
	float Enemy_Dash_Dis_Max; //���s�I���̋���
	float Enemy_Attack_Dis;//�U���\�ȋ���
	float Enemy_Attack_Reception;//�����蔻��̊J�n
	float Enemy_Attack_Outreception;//�����蔻��̏I��
	int Enemy_Attack_Walk_Rand;
	int Enemy_Attack_Dash_Rand;
	int Enemy_Damage_PlayerSp1;
	int Enemy_Damage_PlayerSp2;
	int Enemy_Damage_PlayerSp3;
	float Position_X;//�ʒu��X���W
	float Position_Y;//�ʒu��Y���W
	float Position_Z;//�ʒu��Z���W
	float Scale_X;   //�X�P�[����X���W
	float Scale_Y;   //�X�P�[����Y���W
	float Scale_Z;   //�X�P�[����Z���W
	float Rotation_X;//���f���̉�]X���W
	float Rotation_Y;//���f���̉�]Y���W
	float Rotation_Z;//���f���̉�]Z���W
	int Hp;          //HP
	int Hp_Max;      //HP�ő�l
	int Death_Hp;    //���S����
};
#endif

