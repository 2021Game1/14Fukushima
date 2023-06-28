#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include <time.h>
#include "CScene.h"
#include "CRes.h"
#include "CTutorial.h"
#include "CCamera.h"
#include "CXEnemyManager.h"
#include "CXPlayerManager.h"
#include "CMap.h"
#include "CSceneTutorial.h"

//�e�̐ݒ�
#define SHADOWCOLOR_0 0.4f
#define SHADOWCOLOR_1 0.4f
#define SHADOWCOLOR_2 0.4f
#define SHADOWCOLOR_3 0.2f

//�����̈ʒu
#define LIGHTPOS_X 50.0f
#define LIGHTPOS_Y 160.0f
#define LIGHTPOS_Z 50.0f

//2D�`��̕`��͈�
#define START2D_FIRST_WID 0
#define START2D_END_WID 800
#define START2D_FIRST_HEI 0
#define START2D_END_HEI 600

//GAMECLEAR�摜�`����W
#define GAMECLEAR_FIRST_WID 0
#define GAMECLEAR_END_WID 800
#define GAMECLEAR_FIRST_HEI 0
#define GAMECLEAR_END_HEI 600
#define GAMECLEAR_FIRST_X 0
#define GAMECLEAR_END_X 800
#define GAMECLEAR_FIRST_Y 0
#define GAMECLEAR_END_Y 600

//GAMEOVER�摜�`����W
#define GAMEOVER_FIRST_WID 0
#define GAMEOVER_END_WID 800
#define GAMEOVER_FIRST_HEI 0
#define GAMEOVER_END_HEI 600
#define GAMEOVER_FIRST_X 0
#define GAMEOVER_END_X 800
#define GAMEOVER_FIRST_Y 0
#define GAMEOVER_END_Y 600

//�G������
#define ENEMY_GENERATE_A 1
#define ENEMY_GENERATE_B 1

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
private:
	//�f�X�g���N�^
	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�`�揈���̃I�[�o�[���C�h
	void Render();
	//�V�[���ψڊ֐�
	EScene GetNextScene();

	//���\�[�X�N���X�̃C���X�^���X
	CRes mRes;
	//�V���h�E�}�b�v�̃C���X�^���X
	CShadowMap mShadowMap;
};
#endif