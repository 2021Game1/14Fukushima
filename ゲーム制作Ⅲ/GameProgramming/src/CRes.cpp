#include "CRes.h"

CRes* CRes::mpRes_Instance = nullptr;												//���\�[�X�̃C���X�^���X�ϐ��̏�����

void CRes::Init() {
	//�C���X�^���X�̗L����
	mpRes_Instance = this;
	//BGM�̓ǂݍ���
	Game_Bgm.Load(BGM_GAME);
	//�Q�[���N���A�摜�̒ǉ�
	gGameClear_Image.Load2D(GAMECLEAR_IMAGE);
	//�Q�[���I�[�o�[�摜�̒ǉ�
	gGameOver_Image.Load2D(GAMEOVER_IMAGE);
	//�`���[�g���A���̏I���摜�̒ǉ�
	gTutorial_End_Image.Load2D(TUTORIAL_END_IMAGE);
	//�A�N�V�����`���[�g���A���摜�̒ǉ�
	gAction_Tutorial_Image.Load2D(ACTION_TUTORIAL_IMAGE);
	//�ړ��`���[�g���A���摜�̒ǉ�
	gMove_Tutorial_Image.Load2D(MOVE_TUTORIAL_IMAGE);
	//����A�N�V�����`���[�g���A���摜�̒ǉ�
	gAvoidDance_Tutorial_Image.Load2D(AVOIDANCE_TUTORIAL_IMAGE);
	//�J�����A���O���̃`���[�g���A���摜�̒ǉ�
	gCamera_Angle_Image.Load2D(CAMERA_ANGLE_TUTORIAL_IMAGE);
	//�v���C���̎��_����`���[�g���A��
	gCamera_Action_Image.Load2D(CAMERA_ACTION_TUTORIAL_IMAGE);
	//�L�����N�^��UI�ǉ�
	gCharacter_Ui_Hp_GreenGauge.Load2D(CHARACTER_UI_HP_GREENGAUGE);
	gCharacter_Ui_Hp_RedGauge.Load2D(CHARACTER_UI_HP_REDGAUGE);
	mFont.LoadTexture("Font\\FontG.png", 1, 4096 / 64);
	//�J����������
	Camera.Init();
}
void CRes::Update() {

}
//���\�[�X�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CRes* CRes::GetInstance()
{
	return mpRes_Instance;
}
//�t�H���g�̎擾
CText& CRes::GetInUiFont()
{
	return mFont;
}
//�N���A��ʂ̎擾
CTexture& CRes::GetinGameClearImage()
{
	return gGameClear_Image;
}
//�Q�[���I�[�o�[��ʂ̎擾
CTexture& CRes::GetinGameOverImage()
{
	return gGameOver_Image;
}

//�`���[�g���A���̏I���摜�̎擾
CTexture& CRes::GetinTutorialEndImage()
{
	return gTutorial_End_Image;
}
//�A�N�V�����`���[�g���A���摜���擾����
CTexture& CRes::GetinActionTutorialImage()
{
	return gAction_Tutorial_Image;
}
//�ړ��`���[�g���A���摜���擾����
CTexture& CRes::GetinMoveTutorialImage()
{
	return gMove_Tutorial_Image;
}
//����`���[�g���A���摜���擾
CTexture& CRes::GetinAvoidDanceTutorialImage()
{
	return gAvoidDance_Tutorial_Image;
}
//�J�����A���O���`���[�g���A���摜���擾
CTexture& CRes::GetinCameraAngleImage()
{
	return gCamera_Angle_Image;
}
//�J�����A���O���`���[�g���A���摜���擾
CTexture& CRes::GetinCameraActionImage()
{
	return gCamera_Action_Image;
}
//��HP�o�[�̎擾
CTexture& CRes::GetInUiHpGreenGauge()
{
	return gCharacter_Ui_Hp_GreenGauge;
}
//��HP�o�[�̎擾
CTexture& CRes::GetInUiHpRedGauge()
{
	return gCharacter_Ui_Hp_RedGauge;
}
//�Q�[��BGM�̎擾
CSound& CRes::GetinSoundBgmGame() 
{
	return Game_Bgm;
}
