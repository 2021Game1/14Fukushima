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

//�V���h�E�}�b�s���O�p�}�N��
#define TEXWIDTH  8192	//�e�N�X�`����
#define TEXHEIGHT  6144	//�e�N�X�`������


/*�v���C���̃A�j���[�V�������f��*/

#define PLAYER_MODEL_FILE "res\\Player\\Paladin\\paladin.x"
#define PLAYER_ANIMATION_ATTACKSP1 "res\\Player\\Paladin\\Attack1.x"
#define PLAYER_ANIMATION_ATTACKSP1_IDLE "res\\Player\\Paladin\\Attack1_Idle.x"
#define PLAYER_ANIMATION_ATTACKSP2 "res\\Player\\Paladin\\Attack2.x"
#define PLAYER_ANIMATION_ATTACKSP2_IDLE "res\\Player\\Paladin\\Attack2_Idle.x"
#define PLAYER_ANIMATION_AVOIDANCE "res\\Player\\Paladin\\Avoidance.x" 
#define PLAYER_ANIMATION_IDLE "res\\Player\\Paladin\\Idle.x"
#define PLAYER_ANIMATION_KNOCKBACK "res\\Player\\Paladin\\KnockBack.x"
#define PLAYER_ANIMATION_DEATH "res\\Player\\Paladin\\Death.x"

/*�G�l�~�[�̃A�j���[�V�������f��*/

#define ENEMY_MODEL_FILE "res\\Enemy\\Mutant\\mutant.x"
#define ENEMY_ANIMATION_ATTACKSP1 "res\\Enemy\\Mutant\\Attack1.x"
#define ENEMY_ANIMATION_WALK "res\\Enemy\\Mutant\\Walk.x"
#define ENEMY_ANIMATION_DASH "res\\Enemy\\Mutant\\Dash.x"
#define ENEMY_ANIMATION_BACKSTEP "res\\Enemy\\Mutant\\BackStep.x"
#define ENEMY_ANIMATION_IDLE "res\\Enemy\\Mutant\\Idle.x"
#define ENEMY_ANIMATION_KNOCKBACK "res\\Enemy\\Mutant\\KnockBack.x"
#define ENEMY_ANIMATION_DEATH "res\\Enemy\\Mutant\\Death.x"

/*�}�b�v�̃��f��*/

#define MAP_MODEL_MAP "res\\Map\\map.obj","res\\Map\\map.mtl"
#define MAP_MODEL_SKY "res\\Sky\\sky.obj","res\\Sky\\sky.mtl"
#define MAP_COLLISION_MAP "res\\Map\\collision.obj","res\\Map\\collision.mtl"

/*�摜, UI*/
//�Q�[���N���A�摜
#define GAMECLEAR_IMAGE "res\\Image\\GameClear.png"
//�Q�[���I�[�o�[�摜
#define GAMEOVER_IMAGE "res\\Image\\GameOver_Image.png"
//�`���[�g���A���摜
//�A�N�V�����`���[�g���A���摜
#define ACTION_TUTORIAL_IMAGE "res\\Image\\Action_Tutorial.png"
//�ړ��`���[�g���A���摜
#define MOVE_TUTORIAL_IMAGE "res\\Image\\Move_Tutorial.png"
//����A�N�V�����`���[�g���A���摜
#define AVOIDANCE_TUTORIAL_IMAGE "res\\Image\\AvoidDance_Tutorial.png"
//�J��������`���[�g���A���摜
#define CAMERA_ACTION_TUTORIAL_IMAGE "res\\Image\\Camera_Angle_Tutorial.png"
//HP�Q�[�W
#define CHARACTER_UI_HP_GREENGAUGE "res\\Ui\\HP_Gauge.png"
#define CHARACTER_UI_HP_REDGAUGE "res\\Ui\\HP_RedGauge.png"
//�v���C��UI
#define PLAYER_UI_HP_FRAME "res\\Ui\\Player_HP_Frame.png"

/*BGM�ESE*/

//BGM
#define BGM_GAME "res\\Bgm\\Bgm_Game.wav"


class CRes {
public:
	//�X�V����
	void Update();
	void Init();
	//�Q�[���N���A�摜���擾����
	CTexture& GetinGameClearImage();
	//�Q�[���I�[�o�[�摜���擾����
	CTexture& GetinGameOverImage();
	//�A�N�V�����̃`���[�g���A���摜���擾����
	CTexture& GetinActionTutorialImage();
	//�ړ��̃`���[�g���A���摜���擾����
	CTexture& GetinMoveTutorialImage();
	//����A�N�V�����̃`���[�g���A���摜���擾����
	CTexture& GetinAvoidDanceTutorialImage();
	//�J��������̃`���[�g���A���摜���擾����
	CTexture& GetinCameraTutorialImage();
	//UI�t�H���g�̎擾
	CText& GetInUiFont();
	//HP�Q�[�W���擾����
	CTexture& GetInUiHpGreenGauge();
	CTexture& GetInUiHpRedGauge();
	CTexture& GetInPlayerUiHpFrame();
	CTexture& GetInEnemyUiHpBackBar();
	//�Q�[��BGM�̎擾
	CSound& GetinSoundBgmGame();
	//�C���X�^���X�̎擾
	static CRes* GetInstance();//static�ŏ��������

private:
	//�t�H���g
	CText mFont;
	//CSound�N���X�̃C���X�^���X�쐬
	//BGM
	CSound Game_Bgm;

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
	//�Q�[���N���A�摜
	CTexture gGameClear_Image;
	//�Q�[���I�[�o�[�摜
	CTexture gGameOver_Image;
	//�A�N�V�����`���[�g���A���摜
	CTexture gAction_Tutorial_Image;
	//�ړ��`���[�g���A���摜
	CTexture gMove_Tutorial_Image;
	//����A�N�V�����`���[�g���A���摜
	CTexture gAvoidDance_Tutorial_Image;
	//�J��������̃`���[�g���A���摜
	CTexture gCamera_Tutorial_Image;
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

