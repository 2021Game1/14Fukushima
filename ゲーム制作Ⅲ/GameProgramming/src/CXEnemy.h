#ifndef CXENEMY_H
#define CXENEMY_H

#include"CXCharacter.h"
#include"CColliderCapsule.h"
#include"CCamera.h"




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
		EATTACK_1,								//�U��1
		EATTACK_2,								//�U��2
		EATTACK_3,								//�U��3
		EKNOCKBACK,								//�m�b�N�o�b�N
		//EREPELLED,								//�͂����ꂽ���̃m�b�N�o�b�N
		EDEATH,									//���S
	};
	//���̃N���X�ŎQ�Ɨp�̊֐�
	static CXEnemy* GetInstance();				//static�ŏ��������
	bool GetIsAnimationFrame();
	bool GetHp();								//�G��HP�擾�֐�
	bool GetIsHit();							//�q�b�g��Ԃ̔���
	void SetIsHit(bool hitflag);	//�U���̓����蔻��t���O��ݒ�
	bool mIsDeath();							//���S��Ԃ̎���true��Ԃ�
	CXEnemy::EEnemyState GetState();			//�v���C���[�̏�Ԃ��擾����
protected:
	//�R���C�_�̐錾
	CCollider mEnemy_ColSphereRightarm;	//�E�r
	CCollider mEnemy_ColSphereLeftarm;	//���r
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
	EEnemyState mEnemy_State;					//�G�̏�Ԕ��f�p
	bool mEnemy_Flag;							//�G�̃t���O
	bool mEnemy_IsHit;							//�G�̍U������true��Ԃ��@�G�ɍU����������or�U���I������false��Ԃ�
	static CXEnemy* mpEnemy_Instance;			//�ʂ̃N���X�œG�̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
	//�G�̍s�����\�b�h�֐�
	void Idle();								//�ҋ@����
	void Move();								//�ړ�����
	void Dash();								//�ǐՏ���
	void Attack_1();							//�U��1����
	void Attack_2();							//�U��2����
	void Attack_3();							//�U��3����
	void KnockBack();							//�m�b�N�o�b�N����
	//void Repelled();							//�͂����ꂽ���̏���
	void Death();								//���S����
	//�ړ��̌v�Z����
	void MovingCalculation();


};
#endif

