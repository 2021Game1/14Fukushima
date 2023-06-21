#ifndef CRES_H
#define CRES_H

#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"
#include "CText.h"
#include "CEffect.h"
#include "CShadowMap.h"
#include "CSound.h"

//�V���h�E�}�b�s���O�p�}�N��
#define TEXWIDTH  8192	//�e�N�X�`����
#define TEXHEIGHT  6144	//�e�N�X�`������

/*�摜, UI*/
//�Q�[���N���A�摜
#define GAMECLEAR_IMAGE "res\\Image\\GameClear.png"
//�Q�[���I�[�o�[�摜
#define GAMEOVER_IMAGE "res\\Image\\GameOver_Image.png"
//�`���[�g���A���摜
//�`���[�g���A���I���摜
#define TUTORIAL_END_IMAGE "res\\Image\\Tutorial_End.png"
//�A�N�V�����`���[�g���A���摜
#define ACTION_TUTORIAL_IMAGE "res\\Image\\Action_Tutorial.png"
//�ړ��`���[�g���A���摜
#define MOVE_TUTORIAL_IMAGE "res\\Image\\Move_Tutorial.png"
//����A�N�V�����`���[�g���A���摜
#define AVOIDANCE_TUTORIAL_IMAGE "res\\Image\\AvoidDance_Tutorial.png"
//�J�����A���O���ύX�`���[�g���A���摜
#define CAMERA_ANGLE_TUTORIAL_IMAGE "res\\Image\\Camera_Angle_Tutorial.png"
//�v���C�����_�̑���`���[�g���A���摜
#define CAMERA_ACTION_TUTORIAL_IMAGE "res\\Image\\Camera_Action_Tutorial.png"
//HP�Q�[�W
#define CHARACTER_UI_HP_GREENGAUGE "res\\Ui\\HP_Gauge.png"
#define CHARACTER_UI_HP_REDGAUGE "res\\Ui\\HP_RedGauge.png"

/*BGM�ESE*/

//BGM
#define BGM_GAME "res\\Bgm\\Bgm_Game.wav"


class CRes {
public:
	//�X�V����
	void Update();
	void Init();
	/*�摜�̎擾�p�֐�*/
	//�Q�[���N���A�摜���擾����
	CTexture& GetinGameClearImage();
	//�Q�[���I�[�o�[�摜���擾����
	CTexture& GetinGameOverImage();
	//�`���[�g���A���I���̉摜
	CTexture& GetinTutorialEndImage();
	//�A�N�V�����̃`���[�g���A���摜���擾����
	CTexture& GetinActionTutorialImage();
	//�ړ��̃`���[�g���A���摜���擾����
	CTexture& GetinMoveTutorialImage();
	//����A�N�V�����̃`���[�g���A���摜���擾����
	CTexture& GetinAvoidDanceTutorialImage();
	//�J�����A���O���̃`���[�g���A���摜���擾����
	CTexture& GetinCameraAngleImage();
	//�v���C�����_����̃`���[�g���A���摜���擾����
	CTexture& GetinCameraActionImage();
	//UI�t�H���g�̎擾
	CText& GetInUiFont();
	//HP�Q�[�W���擾����
	CTexture& GetInUiHpGreenGauge();
	CTexture& GetInUiHpRedGauge();
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

	//�L�[���͂ŉ�]
	CMatrix gMatrix;

	/*�摜�ϐ�*/
	//�Q�[���N���A�摜
	CTexture gGameClear_Image;
	//�Q�[���I�[�o�[�摜
	CTexture gGameOver_Image;
	//�`���[�g���A���̏I���摜
	CTexture gTutorial_End_Image;
	//�A�N�V�����`���[�g���A���摜
	CTexture gAction_Tutorial_Image;
	//�ړ��`���[�g���A���摜
	CTexture gMove_Tutorial_Image;
	//����A�N�V�����`���[�g���A���摜
	CTexture gAvoidDance_Tutorial_Image;
	//�J�����A���O���̃`���[�g���A���摜
	CTexture gCamera_Angle_Image;
	//�v���C�����_�̑���`���[�g���A���摜
	CTexture gCamera_Action_Image;
	//�L�����N�^��UI�C���X�^���X
	CTexture gCharacter_Ui_Hp_GreenGauge;
	CTexture gCharacter_Ui_Hp_RedGauge;
	static CRes* mpRes_Instance;//�ʂ̃N���X�Ń��\�[�X�̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
};
#endif

