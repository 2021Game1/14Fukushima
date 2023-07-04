#ifndef CTUTORIAL_H
#define CTUTORIAL_H

#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CXEnemyManager.h"
#include "CRes.h"
/*
�`���[�g���A���`��N���X
*/

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

/*
�`���[�g���A���`��N���X
*/

//2D�`��̕`��͈�
#define START2D_FIRST_WID 0
#define START2D_END_WID 800
#define START2D_FIRST_HEI 0
#define START2D_END_HEI 600

//Tutorial�摜�`����W
#define TUTORIAL_FIRST_WID 0
#define TUTORIAL_END_WID 800
#define TUTORIAL_FIRST_HEI 0
#define TUTORIAL_END_HEI 600
#define TUTORIAL_FIRST_X 0
#define TUTORIAL_END_X 800
#define TUTORIAL_FIRST_Y 0
#define TUTORIAL_END_Y 600

//�ړ��̃`���[�g���A���摜�`����W
#define MOVE_FIRST_WID 0
#define MOVE_END_WID 800
#define MOVE_FIRST_HEI -150
#define MOVE_END_HEI 500
#define MOVE_FIRST_X -100
#define MOVE_END_X 900
#define MOVE_FIRST_Y -125
#define MOVE_END_Y 675

//�J�����̃`���[�g���A���摜�`����W
#define CAMERA_FIRST_WID 0
#define CAMERA_END_WID 800
#define CAMERA_FIRST_HEI -150
#define CAMERA_END_HEI 500
#define CAMERA_FIRST_X -25
#define CAMERA_END_X 825
#define CAMERA_FIRST_Y -125
#define CAMERA_END_Y 675

//�U���A�N�V�����̃`���[�g���A���摜�`����W
#define ACTION_FIRST_WID 0
#define ACTION_END_WID 800
#define ACTION_FIRST_HEI -150
#define ACTION_END_HEI 500
#define ACTION_FIRST_X -150
#define ACTION_END_X 950
#define ACTION_FIRST_Y -200
#define ACTION_END_Y 600

//����A�N�V�����̃`���[�g���A���摜�`����W
#define AVOIDDANCE_FIRST_WID 0
#define AVOIDDANCE_END_WID 800
#define AVOIDDANCE_FIRST_HEI -150
#define AVOIDDANCE_END_HEI 500
#define AVOIDDANCE_FIRST_X -25
#define AVOIDDANCE_END_X 825
#define AVOIDDANCE_FIRST_Y -125
#define AVOIDDANCE_END_Y 600

//�J�����A���O���̑���ݐϒl�ݒ�
#define CAMERA_ANGLE_ACCEUMULATION 1
//�J�����A���O���̑���ݐϒl�ݒ�
#define CAMERA_ANGLE_ACCEUMULATION_MAX 4

//��𑀍�ݐϒl�ݒ�
#define AVOIDDANCE_ACCEUMULATION 1
//��𑀍�ݐϒl�ݒ�
#define AVOIDDANCE_ACCEUMULATION_MAX 6

//�A�N�V�����̃`���[�g���A���摜�\������ۂ̃v���C���ƓG�̋�����ݒ�
#define ACTION_TUTORIAL_ENEMY_PLAYER_VECTOR 2.4f

//�ړ�����ʏ���̐ݒ�
#define MOVE_ACCEUMULATION_MAX 15

//�J��������ʏ���ݒ�
#define CAMERA_ACCEUMULATION_MAX 180

class CTutorial : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^
	CTutorial();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�`���[�g���A���̃t���O�擾
	bool GetIsTutorialFlag();
private:
	//�A�N�V�����̃`���[�g���A���摜�̃t���O
	bool mActionTutorialflag;
	//�ړ��̃`���[�g���A���摜�̃t���O
	bool mMoveTutorialflag;
	//����̃`���[�g���A���摜�̃t���O
	bool mAvoidDanceTutorialflag;
	//�J�����̃A���O���`���[�g���A���摜�̃t���O
	bool mCameraAngleTutorialflag;
	//�v���C���̎��_����`���[�g���A���摜�̃t���O
	bool mCameraActionTutorialflag;
	//�`���[�g���A���I���̉摜�t���O
	bool mTutorialEndflag;
	//�`���[�g���A���̏I���t���O
	bool mTutorial_Out_flag;
	//�`���[�g���A���N���X�̃|�C���^
	static CTutorial* mpTutorial_Instance;	//�ʂ̃N���X�Ń`���[�g���A���̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
	//���s�`���[�g���A���̃v���C���̗ݐψړ��ϐ�
	CVector mMoveTutorial_Accumulation;
	//���s�`���[�g���A���̃v���C���̗ݐϕϐ�
	float mMoveTutorial_Accumulation_Pos;
	//���s�ݐψړ��l�̍ő�l
	float mMoveTutorial_Accumulation_Max;
	//�J��������`���[�g���A���̗ݐϕϐ�
	float mCameraActionTutorial_Accumulation;
	//�J��������ݐϒl�̍ő�l
	float mCameraActionTutorial_Accumulation_Max;
	//�J�����A���O������ݐϐݒ�
	int mCameraAngle_Acceumulation;
	//��𑀍�~�ϐݒ�
	int mAvoidDance_Acceumulation;
};
#endif 



