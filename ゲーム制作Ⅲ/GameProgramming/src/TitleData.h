#ifndef TITLEDATA_H
#define TITLEDATA_H

#include"CTexture.h"
#include "CSound.h"
#include "CTaskManager.h"
#include "CKey.h"
#include "CUtil.h"

//�^�C�g���摜
#define TITLE_IMAGE "res\\Image\\Title_Image.png"
//�I�����
#define TITLE_SELECT_IMAGE "res\\Image\\Title_Select.png"
//�Q�[���X�^�[�g�{�^��
#define TITLE_SELECT_GAMESTART_IMAGE "res\\Image\\Game_Start.png"
//�`���[�g���A���X�^�[�g�{�^��
#define TITLE_SELECT_TUTORIALSTART_IMAGE "res\\Image\\Tutorial_Start.png"
//�^�C�g���Z���N�g�e�L�X�g
#define TITLE_SELECT_TEXT "res\\Image\\Title_Text.png"
//�Q�[���J�n�I�����e�L�X�g
#define TITLE_SELECT_GAMESTART_TEXT "res\\Image\\Title_Select_Game_Text.png"
//�`���[�g���A���J�n�I�����e�L�X�g
#define TITLE_SELECT_TUTORIAL_TEXT "res\\Image\\Title_Select_Tutorial_Text.png"
//�{�^�����������Ƃ��ɕ`�悳���t�F�C�h�A�E�g�A�C���p�w�i
#define TITLE_SELECT_FADE_IMAGE "res\\Image\\Fade.png"


//2D�`��̕`��͈�
#define START2D_FIRST_WID 0
#define START2D_END_WID 800
#define START2D_FIRST_HEI 0
#define START2D_END_HEI 600

//�^�C�g���摜�`����W
#define TITLE_FIRST_WID 0
#define TITLE_END_WID 800
#define TITLE_FIRST_HEI 0
#define TITLE_END_HEI 600
#define TITLE_FIRST_X 0
#define TITLE_END_X 800
#define TITLE_FIRST_Y 0
#define TITLE_END_Y 600

//�^�C�g���I���摜�`����W
#define TITLE_SELECT_FIRST_WID 0
#define TITLE_SELECT_END_WID 800
#define TITLE_SELECT_FIRST_HEI 0
#define TITLE_SELECT_END_HEI 600
#define TITLE_SELECT_FIRST_X 0
#define TITLE_SELECT_END_X 800
#define TITLE_SELECT_FIRST_Y 0
#define TITLE_SELECT_END_Y 600

//�^�C�g���I���e�L�X�g�摜�`����W
#define TITLE_SELECT_TEXT_FIRST_WID 0
#define TITLE_SELECT_TEXT_END_WID 800
#define TITLE_SELECT_TEXT_FIRST_HEI 0
#define TITLE_SELECT_TEXT_END_HEI 600
#define TITLE_SELECT_TEXT_FIRST_X 0
#define TITLE_SELECT_TEXT_END_X 800
#define TITLE_SELECT_TEXT_FIRST_Y 0
#define TITLE_SELECT_TEXT_END_Y 600

//�Q�[���X�^�[�g�I�����e�L�X�g�摜�`����W
#define TITLE_SELECT_GAMESTART_TEXT_FIRST_WID 0
#define TITLE_SELECT_GAMESTART_TEXT_END_WID 800
#define TITLE_SELECT_GAMESTART_TEXT_FIRST_HEI 0
#define TITLE_SELECT_GAMESTART_TEXT_END_HEI 600
#define TITLE_SELECT_GAMESTART_TEXT_FIRST_X 0
#define TITLE_SELECT_GAMESTART_TEXT_END_X 800
#define TITLE_SELECT_GAMESTART_TEXT_FIRST_Y 0
#define TITLE_SELECT_GAMESTART_TEXT_END_Y 600

//�`���[�g���A���I�����e�L�X�g�摜�`����W
#define TITLE_SELECT_TUTORIAL_TEXT_FIRST_WID 0
#define TITLE_SELECT_TUTORIAL_TEXT_END_WID 800
#define TITLE_SELECT_TUTORIAL_TEXT_FIRST_HEI 0
#define TITLE_SELECT_TUTORIAL_TEXT_END_HEI 600
#define TITLE_SELECT_TUTORIAL_TEXT_FIRST_X 0
#define TITLE_SELECT_TUTORIAL_TEXT_END_X 800
#define TITLE_SELECT_TUTORIAL_TEXT_FIRST_Y 0
#define TITLE_SELECT_TUTORIAL_TEXT_END_Y 600

//�X�^�[�g�{�^�����W
#define STARTBUTTON_LEFT 270	//�X�^�[�g�{�^�������W
#define STARTBUTTON_RIGHT 530	//�X�^�[�g�{�^���E���W
#define STARTBUTTON_DOWN 240	//�X�^�[�g�{�^�������W
#define STARTBUTTON_UP 300		//�X�^�[�g�{�^������W
#define STARTBUTTON_FIRST_X 0	//�X�^�[�g�{�^���ŏ���X���W
#define STARTBUTTON_END_X 245	//�X�^�[�g�{�^���I����X���W
#define STARTBUTTON_FIRST_Y 0	//�X�^�[�g�{�^���ŏ���Y���W
#define STARTBUTTON_END_Y 81	//�X�^�[�g�{�^���I����Y���W

//�`���[�g���A���{�^�����W
#define TUTORIALBUTTON_LEFT 270		//�`���[�g���A���{�^�������W
#define TUTORIALBUTTON_RIGHT 530	//�`���[�g���A���{�^���E���W
#define TUTORIALBUTTON_DOWN 140		//�`���[�g���A���{�^�������W
#define TUTORIALBUTTON_UP 200		//�`���[�g���A���{�^������W
#define TUTORIALBUTTON_FIRST_X 0	//�`���[�g���A���{�^���ŏ���X���W
#define TUTORIALBUTTON_END_X 245	//�`���[�g���A���{�^���I����X���W
#define TUTORIALBUTTON_FIRST_Y 0	//�`���[�g���A���{�^���ŏ���Y���W
#define TUTORIALBUTTON_END_Y 81	//�`���[�g���A���{�^���I����Y���W

//�^�C�g��BGM
#define BGM_TITLE "res\\Bgm\\Bgm_Title.wav"
//�^�C�g��BGM����
#define BGM_TITLE_VOLUME 0.2



#endif 