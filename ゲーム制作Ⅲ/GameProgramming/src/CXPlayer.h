#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CColliderCapsule.h"
#include "CVector.h"
#include"CInput.h"
#include"CTexture.h"
#include"CEffect.h"

//�v���C���̃p�����[�^�}�N��
#define PLAYER_SPEED_DEFAULT 0.5f																//�X�s�[�h(�ʏ펞)
#define PLAYER_GRAVITY 0.9f																		//�d��
#define PLAYER_THRUST 0.01																		//����
#define PLAYER_RECEPTION 120																	//���͂̎�t����
#define PLAYER_INRECEPTION 	21.0f																//�����蔻��̎�t����															
#define PLAYER_OUTRECEPTION 60.0f																//�����蔻��̏I������
#define PLAYER_HP_MAX 100;																		//HP�̍ő�l
#define PLAYER_INITIALIZATION 0																	//������

//�v���C����HP�t���[��,HP�Q�[�W���W,��,����
#define PLAYER_GAUGE_FRAME_TEX_WID 480															//�Q�[�W�g�̉摜�̕�
#define PLAYER_GAUGE_FRAME_TEX_HEI 80															//�Q�[�W�g�̉摜�̍���
#define PLAYER_GAUGE_FRAME_LEFT 0																//�Q�[�W�g�����W
#define PLAYER_GAUGE_FRAME_RIGHT 380															//�Q�[�W�g�E���W
#define PLAYER_GAUGE_FRAME_TOP PLAYER_GAUGE_FRAME_TEX_HEI										//�Q�[�W�g����W
#define PLAYER_GAUGE_FRAME_BOTTOM (PLAYER_GAUGE_FRAME_TOP-PLAYER_GAUGE_FRAME_TEX_HEI)			//�Q�[�W�g�����W
#define PLAYER_GAUGE_LEFT 0																		//�Q�[�W�`�掞�̍����W
#define PLAYER_GAUGE_WID_MAX 380																//�Q�[�W�̕��̍ő�l
#define GAUGE_HEIGHT 20																			//�Q�[�W�`�掞�̍���
#define PLAYER_GAUGE_HP_TOP 30																	//HP�Q�[�W�`�掞�̏���W
#define PLAYER_GAUGE_HP_BOTTOM (PLAYER_GAUGE_HP_TOP-GAUGE_HEIGHT)								//HP�Q�[�W�`�掞�̉����W

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
	//�v���C���̃G�t�F�N�g
	enum EPlayerEffect
	{
		EEFFECT_NULL = 0,				//�G�t�F�N�g�Ȃ�
		EEFFECT_PLAYER_ATTACKSP1,		//�v���C���̍U��1�G�t�F�N�g
		EEFFECT_PLAYER_ATTACKSP2,		//�v���C���̍U��2�G�t�F�N�g
		EEFFECT_PLAYER_ATTACKSP3,		//�v���C���̍U��3�G�t�F�N�g
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
	CColliderCapsule mPlayer_ColCapsuleSword;	//��
	CCollider mPlayer_ColSphereShield;	//��
	CCollider mPlayer_ColSphereBody;					//���̐g��
	CColliderCapsule mPlayer_ColCapsuleBody;	//�J�v�Z���̐g��
	//�v���C���̏�Ԑ���
	EPlayerState mPlayer_State;			//�v���C���̏�Ԕ��f�p
	bool mPlayer_InvincibleFlag;				//���G��Ԃ̎�true��Ԃ�
	//�v���C���̃G�t�F�N�g����
	EPlayerEffect mPlayer_Effect;		//�v���C���̃G�t�F�N�g���f�p

	//�v���C����HP�Q�[�W�p�̕ϐ�
	float mPlayer_FollowGaugeWid;		//��_���[�W����ǂ�����Q�[�W�̕�

	//�v���C���̈ړ��p�ϐ�
	CVector mPlayer_Move;				//�v���C���̕����Ƒ��x���������킹���x�N�g���A�v���C���̈ړ���
	CVector mPlayer_MoveDir;			//�v���C���̈ړ���������A���f���̉�]�ɂ��g�p���Ă���A���t���[�����Z�b�g�����
	CVector mPlayer_MoveDirKeep;		//�v���C���̈ړ����̕�����ۑ�����
	CVector mPlayer_KnockBackDir;		//�v���C���̃m�b�N�o�b�N���������ێ�����
	CVector mPlayer_AttackDir;			//�v���C���̍U�����̕�����ێ�����
	float mPlayer_Speed;				//�v���C���̃X�s�[�h
	float mPlayer_Turnspeed;			//�v���C���̃^�[���̑��x

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

