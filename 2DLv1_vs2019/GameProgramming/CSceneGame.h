#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
// �e�N�X�`���N���X�̃C���N���[�h
#include "CTexture.h"
#include "CSceneScreen.h"
#include "CBossEnemy.h"
#include "CSceneTitle.h"
/*
�Q�[���̃V�[��
*/
//CScene�N���X���p������
class CSceneGame : public CScene {
public:
	//37
	//CTexture Texture; //�}�b�v�̉摜
	//CPlayer Player;
	//CMap Map[48];
	//int MapSize;
	//CBullet Bullet[10];
	//int FireCount = 10;
	//CEnemy Enemy[10];
	//37
	

	//�����������̃I�[�o�[���C�h
	void Init();
	
	//�X�V�����̃I�[�o�[���C�h
	void Update();

	static int GameTime;

	

	static int Remain;

	//�c�莞�ԁi30�b�j
	static int Time;
	//�X�R�A
	static int ScoreCount;
	//�Q�[���N���A
	static int CLEAR;
	//�Q�[���I�[�o�[
	static int OVER;
	//�{�X�̃t���O�Ǘ�
	static int Bossflug;
	//�G�l�~�[�̃J�E���^
	static int EnemyCount;
	//�{�X�̃J�E���^
	static int BossCount;
	//�����𕶎���ɕϊ�����
	static char buf[10];//9�����܂�OK

	EScene GetNextScene();
	//�f�X�g���N�^�̐錾
	~CSceneGame();

};

#endif
