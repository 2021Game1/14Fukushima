#ifndef CTUTORIAL_H
#define CTUTORIAL_H

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

//�ړ��̃`���[�g���A���摜�`����W
#define MOVE_FIRST_WID 0
#define MOVE_END_WID 800
#define MOVE_FIRST_HEI 0
#define MOVE_END_HEI 600
#define MOVE_FIRST_X 0
#define MOVE_END_X 800
#define MOVE_FIRST_Y 0
#define MOVE_END_Y 600

//�J�����̃`���[�g���A���摜�`����W
#define CAMERA_FIRST_WID 0
#define CAMERA_END_WID 800
#define CAMERA_FIRST_HEI 0
#define CAMERA_END_HEI 600
#define CAMERA_FIRST_X 0
#define CAMERA_END_X 800
#define CAMERA_FIRST_Y 0
#define CAMERA_END_Y 600

//�U���A�N�V�����̃`���[�g���A���摜�`����W
#define ACTION_FIRST_WID 0
#define ACTION_END_WID 800
#define ACTION_FIRST_HEI 0
#define ACTION_END_HEI 600
#define ACTION_FIRST_X 0
#define ACTION_END_X 800
#define ACTION_FIRST_Y 0
#define ACTION_END_Y 600

//����A�N�V�����̃`���[�g���A���摜�`����W
#define AVOIDDANCE_FIRST_WID 0
#define AVOIDDANCE_END_WID 800
#define AVOIDDANCE_FIRST_HEI 0
#define AVOIDDANCE_END_HEI 600
#define AVOIDDANCE_FIRST_X 0
#define AVOIDDANCE_END_X 800
#define AVOIDDANCE_FIRST_Y 0
#define AVOIDDANCE_END_Y 600
//�J�����A���O��



//�A�N�V�����̃`���[�g���A���摜�\������ۂ̃v���C���ƓG�̋�����ݒ�
#define ACTION_TUTORIAL_ENEMY_PLAYER_VECTOR 2.4f

class CTutorial{
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
	//�J�����̃`���[�g���A���摜�̃t���O
	bool mCameraTutorialflag;
	//�`���[�g���A���摜�̃t���O
	bool mTutorial_Out_flag;
	//�`���[�g���A���N���X�̃|�C���^
	static CTutorial* mpTutorial_Instance;	//�ʂ̃N���X�Ń`���[�g���A���̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
};





#endif 



