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



//�v���C���̃A�j���[�V�������f��
#define PLAYER_MODEL_FILE "res\\paladin\\paladin.x"
#define PLAYER_ANIMATION_ATTACKSP1 "res\\paladin\\Attack1.x"
#define PLAYER_ANIMATION_ATTACKSP2 "res\\paladin\\Attack2.x"
#define PLAYER_ANIMATION_ATTACKSP3 "res\\paladin\\Attack3.x"
#define PLAYER_ANIMATION_GUARD "res\\paladin\\Guard.x"
#define PLAYER_ANIMATION_GUARDIDLE "res\\paladin\\GuardIdle.x"
#define PLAYER_ANIMATION_IDLE "res\\paladin\\Idle.x"
#define PLAYER_ANIMATION_KNOCKBACK "res\\paladin\\KnockBack.x"
#define PLAYER_ANIMATION_DEATH "res\\paladin\\Death.x"

//�G�l�~�[�̃A�j���[�V�������f��
#define ENEMY_MODEL_FILE "res\\mutant\\mutant.x"
#define ENEMY_ANIMATION_ATTACKSP1 "res\\mutant\\Attack1.x"
#define ENEMY_ANIMATION_ATTACKSP2 "res\\mutant\\Attack4.x"
#define ENEMY_ANIMATION_WALK "res\\mutant\\Walk.x"
#define ENEMY_ANIMATION_DASH "res\\mutant\\Dash.x"
#define ENEMY_ANIMATION_IDLE "res\\mutant\\Idle.x"
#define ENEMY_ANIMATION_KNOCKBACK "res\\mutant\\KnockBack.x"
#define ENEMY_ANIMATION_DEATH "res\\mutant\\Death.x"

//�}�b�v�̃��f��
#define MAP_MODEL_MAP "res\\map\\map.obj","res\\map\\map.mtl"
#define MAP_MODEL_SKY "res\\sky\\sky.obj","res\\sky\\sky.mtl"
#define MAP_COLLISION_MAP "res\\map\\collision.obj","res\\map\\collision.mtl"

//�摜,UI
#define CHARACTER_UI_HP_GREENGAUGE "res\\ui\\HP_Gauge.png"
#define CHARACTER_UI_HP_REDGAUGE "res\\ui\\HP_RedGauge.png"
#define PLAYER_UI_HP_FRAME "res\\ui\\Player_HP_Frame.png"
#define ENEMY_UI_HP_FRAME "res\\ui\\Enemy_HP_Frame.png"

#define PLAYER_EF_ATTACKSP1 "res\\effect\\Player_Attack1.png"
#define PLAYER_EF_ATTACKSP2 "res\\effect\\Player_Attack2.png"
#define PLAYER_EF_ATTACKSP3 "res\\effect\\Player_Attack3.png"
#define TEXWIDTH  8192	//�e�N�X�`����
#define TEXHEIGHT  6144	//�e�N�X�`������


class CRes {
public:
	void Update();
	void Init();
	CText& GetInUiFont();
	CTexture& GetInUiHpGreenGauge();
	CTexture& GetInUiHpRedGauge();
	CTexture& GetInPlayerUiHpFrame();
	CTexture& GetInEnemyUiHpFrame();
	static CRes* GetInstance();//static�ŏ��������
private:
	//�t�H���g
	CText mFont;
	//�v���C�����f��
	CModelX gPlayer_Model_Knight;
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
	//�L�����N�^��UI�C���X�^���X
	CTexture gCharacter_Ui_Hp_GreenGauge;
	CTexture gCharacter_Ui_Hp_RedGauge;
	//�v���C����UI�C���X�^���X
	CTexture gPlayer_Ui_Hp_Frame;
	//�G��UI�C���X�^���X
	CTexture gEnemy_Ui_Hp_Frame;
	static CRes* mpRes_Instance;//�ʂ̃N���X�Ń��\�[�X�̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����

};
#endif

