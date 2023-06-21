#include "CSceneTitle.h"
#include <stdio.h>

//�f�t�H���g�R���X�g���N�^
CSceneTitle::CSceneTitle()
	: mNextScene(CScene::EScene::ETITLE)
	, mSelect(CSceneTitle::ESelect::EBACKGROUND)
	, mIsButtonPush(false)
	, mSceneChange()
	, mTutorialflag(false)
	, mTitleflag(false)
	, mMouseX(NULL)
	, mMouseY(NULL)
{

}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{
	CTaskManager::Get()->Delete();
}

//Init����
//��x�����������Ȃ�����
void CSceneTitle::Init() {
	//�V�[���̐ݒ�
	mScene = CScene::EScene::ETITLE;
	//�^�C�g���摜�̒ǉ�
	gTitle_Image.Load2D(TITLE_IMAGE);
	//�^�C�g���I����ʉ摜�̒ǉ�
	gTitle_Select_Image.Load2D(TITLE_SELECT_IMAGE);
	//�Q�[���X�^�[�g�摜�̒ǉ�
	gTitle_Select_GameStart_Image.Load2D(TITLE_SELECT_GAMESTART_IMAGE);
	//�`���[�g���A���X�^�[�g�摜�̒ǉ�
	gTitle_Select_TutorialStart_Image.Load2D(TITLE_SELECT_TUTORIALSTART_IMAGE);
	//�^�C�g��BGM�̓ǂݍ���
	Title_Bgm.Load(BGM_TITLE);
	//�^�C�g��BGM�̍Đ�
	Title_Bgm.Play(BGM_TITLE_VOLUME);
}

//�X�V�����̃I�[�o�[���C�h
void CSceneTitle::Update() {
	if (mTitleflag == false) {
		if (CKey::Once(VK_RETURN)) {
			mTitleflag = true;
		}
	}
	//�{�^���������Ă��Ȃ��Ƃ�
	if (mIsButtonPush == false) {
		//�}�E�X�̍��W���擾
		CInput::GetMousePosWin(&mMouseX, &mMouseY);
		mMouseY = TITLE_SELECT_END_Y - mMouseY;
	}


	//�Q�[���X�^�[�g�{�^����Ƀ}�E�X�|�C���^������Ƃ�
	if ((mMouseX >= STARTBUTTON_LEFT && mMouseX <= STARTBUTTON_RIGHT) &&
		(mMouseY >= STARTBUTTON_DOWN && mMouseY <= STARTBUTTON_UP)) {
		//�I�����Ă���ꏊ���Q�[���X�^�[�g�ɐݒ�
		mSelect = EGAMESTART;
	}
	//���R�[�h�{�^����Ƀ}�E�X�|�C���^������Ƃ�
	else if ((mMouseX >= TUTORIALBUTTON_LEFT && mMouseX <= TUTORIALBUTTON_RIGHT) &&
		(mMouseY >= TUTORIALBUTTON_DOWN && mMouseY <= TUTORIALBUTTON_UP)) {
		//�I�����Ă���ꏊ�����R�[�h�ɐݒ�
		mSelect = CSceneTitle::ETUTORIAL;
	}
	//��L�ȊO�͔w�i
	else {
		//�I�����Ă���ꏊ��w�i�ɐݒ�
		mSelect = EBACKGROUND;
	}

	//���N���b�N�����Ƃ�
	if (CKey::Once(VK_LBUTTON)) {
		//�I�����Ă���ꏊ�𔻒f����
		switch (mSelect) {
		case EGAMESTART: //�Q�[���X�^�[�g
				//�{�^���������Ă��Ȃ��Ƃ�
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//�{�^��������������s
				//���̃V�[���̓Q�[��
				mNextScene = CScene::EScene::EGAME;
				mSceneChange = true;
				Title_Bgm.Stop();
			}
			break;

		case CSceneTitle::ETUTORIAL: //�`���[�g���A���X�^�[�g
				//�{�^���������Ă��Ȃ��Ƃ�
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//�{�^��������������s
				//���̃V�[���̓`���[�g���A��
				mNextScene = CScene::EScene::ETUTORIAL;
				mSceneChange = true;
				Title_Bgm.Stop();
			}
			break;

		default:
			break;
		}
	}

	if (mSceneChange) {
		mScene = mNextScene;
	}
}

//�`�揈��
void CSceneTitle::Render() {
	//2D�̕`��J�n
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	if (mTitleflag == false)
	{
		gTitle_Image.Draw(TITLE_FIRST_WID, TITLE_END_WID, TITLE_FIRST_HEI, TITLE_END_HEI, TITLE_FIRST_X, TITLE_END_X, TITLE_END_Y, TITLE_FIRST_Y);
	}
	//�^�C�g���摜�`���
	if (mTitleflag == true)
	{//�^�C�g���I����ʕ`��
		gTitle_Select_Image.Draw(TITLE_SELECT_FIRST_WID, TITLE_SELECT_END_WID, TITLE_SELECT_FIRST_HEI, TITLE_SELECT_END_HEI, TITLE_SELECT_FIRST_X, TITLE_SELECT_END_X, TITLE_SELECT_END_Y, TITLE_SELECT_FIRST_Y);
		//�Q�[���X�^�[�g�X�^�[�g�摜�`��
		gTitle_Select_GameStart_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		//�`���[�g���A���X�^�[�g�摜�`��
		gTitle_Select_TutorialStart_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);	
	}
	//2D�̕`��I��
	CUtil::End2D();
}

//���̃V�[���Ɉڍs
CScene::EScene CSceneTitle::GetNextScene() {
	//���݂̃V�[����Ԃ�
	return mScene;
}