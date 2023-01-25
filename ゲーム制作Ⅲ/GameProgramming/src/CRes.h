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
#include"CPlayerGuard.h"
#include "CXEnemy.h"
#include "CMap.h"
#include "CEffect.h"
#include "CColliderMesh.h"
#include "CEffect.h"
#include "CShadowMap.h"
#include "CSound.h"



/*�v���C���̃A�j���[�V�������f��*/

#define PLAYER_MODEL_FILE "res\\Player\\Paladin\\paladin.x"
#define PLAYER_ANIMATION_ATTACKSP1 "res\\Player\\Paladin\\Attack1.x"
#define PLAYER_ANIMATION_ATTACKSP2 "res\\Player\\Paladin\\Attack2.x"
#define PLAYER_ANIMATION_ATTACKSP3 "res\\Player\\Paladin\\Attack3.x"
#define PLAYER_ANIMATION_GUARD "res\\Player\\Paladin\\Guard.x"
#define PLAYER_ANIMATION_GUARDIDLE "res\\Player\\Paladin\\GuardIdle.x"
#define PLAYER_ANIMATION_IDLE "res\\Player\\Paladin\\Idle.x"
#define PLAYER_ANIMATION_KNOCKBACK "res\\Player\\Paladin\\KnockBack.x"
#define PLAYER_ANIMATION_DEATH "res\\Player\\Paladin\\Death.x"
#define PLAYER_MODEL_ACTION_GUARDSP "res\\Player\\Paladin\\Shield.obj","res\\Player\\Paladin\\Shield.mtl"

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
//�v���C����p�U���G�t�F�N�g
#define PLAYER_EF_ATTACKSP1 "res\\Effect\\Player_Attack1.png"
#define PLAYER_EF_ATTACKSP2 "res\\Effect\\Player_Attack2.png"
#define PLAYER_EF_ATTACKSP3 "res\\Effect\\Player_Attack3.png"
//�V���h�E�}�b�s���O�p
#define TEXWIDTH  8192	//�e�N�X�`����
#define TEXHEIGHT  6144	//�e�N�X�`������

/*BGM�ESE*/

//BGM
#define BGM_GAME "res\\Bgm\\Bgm_Game.wav"
#define BGM_TITLE "res\\Bgm\\Bgm_Title.wav"

//SE�E�v���C��
#define SE_PLAYER_ATTACK1 "res\\Se\\SE_Player_AttackSp1.wav"
#define SE_PLAYER_ATTACK2 "res\\Se\\SE_Player_AttackSp2.wav"
#define SE_PLAYER_ATTACK3 "res\\Se\\SE_Player_AttackSp3.wav"
#define SE_PLAYER_GUARD "res\\Se\\SE_Player_Guard.wav"
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
	CSound& GetinPlayerSeGuard();
	CSound& GetinPlayerSeWalk();
	CSound& GetinPlayerSeDeath();
	//�GSE���擾����
	CSound& GetinEnemySeAttackSp();
	CSound& GetinEnemySeDeath();
	CSound& GetinSoundBgmGame();
	//BGM�̎擾
	CSound& GetinSoundBgmTitle();
	//�C���X�^���X�̎擾
	static CRes* GetInstance();//static�ŏ��������

private:
	//�t�H���g
	CText mFont;
	//CSound�N���X�̃C���X�^���X�쐬
	CSound Game_Bgm;
	CSound Title_Bgm;
	//�v���C��SE
	CSound Se_Player_AttackSp1;
	CSound Se_Player_AttackSp2;
	CSound Se_Player_AttackSp3;
	CSound Se_Player_Guard;
	CSound Se_Player_Walk;
	CSound Se_Player_Death;
	//�GSE
	CSound Se_Enemy_AttackSp;
	CSound Se_Enemy_Death;
	//�v���C�����f��
	CModelX gPlayer_Model_Knight;
	//�v���C���̃K�[�h�A�N�V�����G�t�F�N�g
	CModel gPlayer_GuardSP_Model;
	CPlayerGuard mPlayer_GuardSP_Model;
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

