#ifndef CRES_H
#define CRES_H

#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"
#include "CCollisionManager.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CText.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CMap.h"
#include "CEffect.h"
#include "CColliderMesh.h"
#include "CEffect.h"
#include "CShadowMap.h"
#include "CSound.h"

//�v���C���̃Q�[���I�[�o�̗͐ݒ�
#define PLAYER_GAMEOVER_HP 0																	//�Q�[���I�[�o�ݒ�
//�v���C���̃p�����[�^�}�N��
#define PLAYER_HP_MAX 100																		//HP�̍ő�l
#define PLAYER_HP 100																			//HP�̐ݒ�
#define PLAYER_SPEED_DEFAULT 0.2f																//�X�s�[�h(�ʏ펞)
#define PLAYER_GRAVITY 0.9f																		//�d��
#define PLAYER_THRUST 0.9																		//����
#define PLAYER_SE 0.1																			//�v���C��SE�ݒ�
#define PLAYER_DAMAGE_SE 0.3																	//�v���C���_���[�WSE�ݒ�
#define PLAYER_RECEPTION 10																		//�L�[���͂̎�t����
#define PLAYER_INRECEPTION 	21.0f																//�����蔻��̎�t����															
#define PLAYER_OUTRECEPTION 60.0f																//�����蔻��̏I������
#define PLAYER_ATTACK_DIS 2.2f																	//�G�ɍU�����Ǐ]�\�ɂȂ鋗��

//�v���C���̃A�j���[�V�����̃t���[���ݒ�
#define PLAYER_IDLE_ANIMATION_FRAME 20
#define PLAYER_MOVE_ANIMATION_FRAME 45															//�ړ��̃A�j���[�V�����t���[���ݒ�
#define PLAYER_AVOIDANCE_ANIMATION_FRAME 50														//����̃A�j���[�V�����t���[���ݒ�
#define PLAYER_ATTACK1_ANIMATION_FRAME 60														//�U��1�̃A�j���[�V�����t���[���ݒ�
#define PLAYER_ATTACK2_ANIMATION_FRAME 70														//�U��2�̃A�j���[�V�����t���[���ݒ�
#define PLAYER_ATTACK3_ANIMATION_FRAME 80														//�U��3�̃A�j���[�V�����t���[���ݒ�
#define PLAYER_KNOCKBACK_ANIMATION_FRAME 60														//�m�b�N�o�b�N�̃A�j���[�V�����t���[���ݒ�
#define PLAYER_DEATH_ANIMATION_FRAME 60															//���S�̃A�j���[�V�����t���[���ݒ�

//�v���C���̃_���[�W�ݒ�
#define PLAYER_DAMAGE_ENEMYSP1 15						//�G�̍U��1�̃_���[�W	
#define PLAYER_DAMAGE_ENEMYSP2 10						//�G�̍U��2�̃_���[�W
#define PLAYER_DAMAGE_ENEMYSP3 20						//�G�̍U��3�̃_���[�W

//�v���C���̃A�j���[�V�����ԍ��̐ݒ�
#define PLAYER_ANIMATION_No_MOVE 0			//�ړ��A�j���[�V�����ԍ�
#define PLAYER_ANIMATION_No_ATTACK_1 1		//�U���A�j���[�V����1�ԍ�
#define PLAYER_ANIMATION_No_ATTACK_2 2		//�U���A�j���[�V����2�ԍ�
#define PLAYER_ANIMATION_No_ATTACK_3 3		//�U���A�j���[�V����3�ԍ�
#define PLAYER_ANIMATION_No_AVOIDANCE 4		//����A�j���[�V�����ԍ�
#define PLAYER_ANIMATION_No_IDLE 5			//�ҋ@�A�j���[�V�����ԍ�
#define PLAYER_ANIMATION_No_KNOCKBACK 6		//�m�b�N�o�b�N�A�j���[�V�����ԍ�
#define PLAYER_ANIMATION_No_DEATH 7			//���S�A�j���[�V�����ԍ�

//�G�p�����[�^�}�N��
#define ENEMY_HP_MAX 150			//HP�̍ő�l
#define ENEMY_HP 150				//HP�ݒ�
#define ENEMY_DAMAGE_BODY 15		//�_���[�W(��)
#define ENEMY_ATTACK_DIS 3.2f		//�U���\�ɂȂ鋗��
#define ENEMY_SPEED_MOVE 0.1f		//�ʏ�ړ��̃X�s�[�h
#define ENEMY_SPEED_DASH 0.15f		//���s�̈ړ����x
#define ENEMY_SPEED_STOP 0.0f		//��~
#define ENEMY_WALK_DIS 30.0f		//���s���J�n���鋗��
#define ENEMY_SEARCH_DIS 60.0f		//���s���J�n���鋗��
#define ENEMY_WALK_DIS_MAX 50.0f	//���s�\�ȍő勗��
#define ENEMY_CHASE_DIS_MAX 80.0f   //���s�\�ȍő勗��
#define ENEMY_GRAVITY 0.9f			//�d��
#define ENEMY_RECEPTION 26.0f		//�����蔻��̎�t����
#define ENEMY_OUTRECEPTION 60.0f	//�����蔻��̎�t�I��

//�V���h�E�}�b�s���O�p�}�N��
#define TEXWIDTH  8192	//�e�N�X�`����
#define TEXHEIGHT  6144	//�e�N�X�`������


/*�v���C���̃A�j���[�V�������f��*/

#define PLAYER_MODEL_FILE "res\\Player\\Paladin\\paladin.x"
#define PLAYER_ANIMATION_ATTACKSP1 "res\\Player\\Paladin\\Attack1.x"
#define PLAYER_ANIMATION_ATTACKSP2 "res\\Player\\Paladin\\Attack2.x"
#define PLAYER_ANIMATION_ATTACKSP3 "res\\Player\\Paladin\\Attack3.x"
#define PLAYER_ANIMATION_AVOIDANCE "res\\Player\\Paladin\\Avoidance.x" 
#define PLAYER_ANIMATION_IDLE "res\\Player\\Paladin\\Idle.x"
#define PLAYER_ANIMATION_KNOCKBACK "res\\Player\\Paladin\\KnockBack.x"
#define PLAYER_ANIMATION_DEATH "res\\Player\\Paladin\\Death.x"

/*�G�l�~�[�̃A�j���[�V�������f��*/

#define ENEMY_MODEL_FILE "res\\Enemy\\Mutant\\mutant.x"
#define ENEMY_ANIMATION_ATTACKSP1 "res\\Enemy\\Mutant\\Attack1.x"
#define ENEMY_ANIMATION_ATTACKSP2 "res\\Enemy\\Mutant\\Attack2.x"
#define ENEMY_ANIMATION_WALK "res\\Enemy\\Mutant\\Walk.x"
#define ENEMY_ANIMATION_DASH "res\\Enemy\\Mutant\\Dash.x"
#define ENEMY_ANIMATION_IDLE "res\\Enemy\\Mutant\\Idle.x"
#define ENEMY_ANIMATION_KNOCKBACK "res\\Enemy\\Mutant\\KnockBack.x"
#define ENEMY_ANIMATION_DEATH "res\\Enemy\\Mutant\\Death.x"

/*�}�b�v�̃��f��*/

#define MAP_MODEL_MAP "res\\Map\\map.obj","res\\Map\\map.mtl"
#define MAP_MODEL_SKY "res\\Sky\\sky.obj","res\\Sky\\sky.mtl"
#define MAP_COLLISION_MAP "res\\Map\\collision.obj","res\\Map\\collision.mtl"

/*�摜, UI*/
//�^�C�g���摜
#define TITLE_IMAGE "res\\Image\\Title_Image.png"
//�Q�[���N���A�摜
#define GAMECLEAR_IMAGE "res\\Image\\GameClear.png"
//�Q�[���I�[�o�[�摜
#define GAMEOVER_IMAGE "res\\Image\\GameOver_Image.png"
//HP�Q�[�W
#define CHARACTER_UI_HP_GREENGAUGE "res\\Ui\\HP_Gauge.png"
#define CHARACTER_UI_HP_REDGAUGE "res\\Ui\\HP_RedGauge.png"
//�v���C��UI
#define PLAYER_UI_HP_FRAME "res\\Ui\\Player_HP_Frame.png"
//�GUI
#define ENEMY_UI_HP_BACKBAR "res\\Ui\\Enemy_HP_BackBar.png"
//�G�_���[�W�G�t�F�N�g
#define ENEMY_EF_DAMAGESP1 "Effect\\Enemy_DamageSp1.png"
#define ENEMY_EF_DAMAGESP2 "Effect\\Enemy_DamageSp2.png"
#define ENEMY_EF_DAMAGESP3 "Effect\\Enemy_DamageSp3.png"

/*BGM�ESE*/

//BGM
#define BGM_GAME "res\\Bgm\\Bgm_Game.wav"
#define BGM_TITLE "res\\Bgm\\Bgm_Title.wav"

//SE�E�v���C��
#define SE_PLAYER_ATTACK1 "res\\Se\\SE_Player_AttackSp1.wav"
#define SE_PLAYER_ATTACK2 "res\\Se\\SE_Player_AttackSp2.wav"
#define SE_PLAYER_ATTACK3 "res\\Se\\SE_Player_AttackSp3.wav"
#define SE_PLAYER_WALK "res\\Se\\SE_Player_Walk.wav"
#define SE_PLAYER_DEATH "res\\Se\\SE_Player_Death.wav"

//SE�E�G
#define SE_ENEMY_ATTACK "res\\Se\\SE_Enemy_AttackSp.wav" 
#define SE_EMEMY_DEATH "res\\Se\\SE_Enemy_Death.wav"

class CRes {
public:
	//�X�V����
	void Update();
	void Init();
	//�^�C�g���摜���擾����
	CTexture& GetInTitleImage();
	//�Q�[���N���A�摜���擾����
	CTexture& GetinGameClearImage();
	//�Q�[���I�[�o�[�摜���擾����
	CTexture& GetinGameOverImage();
	//UI�t�H���g�̎擾
	CText& GetInUiFont();
	//HP�Q�[�W���擾����
	CTexture& GetInUiHpGreenGauge();
	CTexture& GetInUiHpRedGauge();
	CTexture& GetInPlayerUiHpFrame();
	CTexture& GetInEnemyUiHpBackBar();
	//�v���C��SE���擾����
	CSound& GetinPlayerSeAttackSp1();
	CSound& GetinPlayerSeAttackSp2();
	CSound& GetinPlayerSeAttackSp3();
	CSound& GetinPlayerSeWalk();
	CSound& GetinPlayerSeDeath();
	//�GSE���擾����
	CSound& GetinEnemySeAttackSp();
	CSound& GetinEnemySeDeath();
	//�Q�[��BGM�̎擾
	CSound& GetinSoundBgmGame();
	//�^�C�g��BGM�̎擾
	CSound& GetinSoundBgmTitle();
	//�C���X�^���X�̎擾
	static CRes* GetInstance();//static�ŏ��������

private:
	//�t�H���g
	CText mFont;
	//CSound�N���X�̃C���X�^���X�쐬
	//BGM
	CSound Game_Bgm;
	CSound Title_Bgm;
	//�v���C��SE
	CSound Se_Player_AttackSp1;
	CSound Se_Player_AttackSp2;
	CSound Se_Player_AttackSp3;
	CSound Se_Player_Walk;
	CSound Se_Player_Death;
	//�GSE
	CSound Se_Enemy_AttackSp;
	CSound Se_Enemy_Death;
	//�v���C�����f��
	CModelX gPlayer_Model_Knight;
	//�v���C���̃K�[�h�A�N�V�����G�t�F�N�g
	CModel gPlayer_GuardSP_Model;
	//�G���f��
	CModelX gEnemy_Model_Mutant;
	//�}�b�v���f��
	CModel gMap_Model;
	//�}�b�v�̔w�i���f��
	CModel gMap_Model_Sky;
	//�}�b�v�̓����蔻�胂�f��
	CModel gMap_Model_Collision;
	//�v���C���N���X�̃C���X�^���X
	CXPlayer mPlayer;
	//�G�N���X�̃C���X�^���X
	CXEnemy mEnemy;
	//�}�b�v�N���X�̃C���X�^���X
	CMap mMap;
	CMap mMap_Sky;
	//�L�[���͂ŉ�]
	CMatrix gMatrix;
	//�}�b�v�ړ��p�̍s��
	CMatrix mBackGroundMatrix;
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;
	//�^�C�g���摜
	CTexture gTitle_Image;
	//�Q�[���N���A�摜
	CTexture gGameClear_Image;
	//�Q�[���I�[�o�[�摜
	CTexture gGameOver_Image;
	//�L�����N�^��UI�C���X�^���X
	CTexture gCharacter_Ui_Hp_GreenGauge;
	CTexture gCharacter_Ui_Hp_RedGauge;
	//�v���C����UI�C���X�^���X
	CTexture gPlayer_Ui_Hp_Frame;
	//�G��UI�C���X�^���X
	CTexture gEnemy_Ui_Hp_BackBar;
	static CRes* mpRes_Instance;//�ʂ̃N���X�Ń��\�[�X�̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
};
#endif

