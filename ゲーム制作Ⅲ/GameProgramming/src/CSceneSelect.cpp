#include "CSceneSelect.h"

CSceneSelect::CSceneSelect()
	: mSelect(CSceneSelect::ESelect::EBACKGROUND)
	, mNextScene(CScene::EScene::ESCENESELECT)
	, mSceneChange()
	, mIsButtonPush(false)
	, mMouseX(NULL)
	, mMouseY(NULL)
{

}

//�f�X�g���N�^
CSceneSelect::~CSceneSelect()
{
	CTaskManager::Get()->Delete();
}

void CSceneSelect::Init()
{
	//�V�[���̐ݒ�
	mScene = CScene::EScene::ESCENESELECT;
	//�^�C�g���I����ʉ摜�̒ǉ�
	gTitle_Select_Image.Load2D(SCENE_SELECT_IMAGE);
	//�^�C�g����ʑI����ʕ`�掞�̃e�L�X�g
	gTitle_Select_Text_Image.Load2D(SCENE_SELECT_TEXT);
	//�Q�[���J�n�I�����e�L�X�g
	gTitle_Select_GameStart_Text_Image.Load2D(SCENE_SELECT_GAMESTART_TEXT);
	//�`���[�g���A���J�n�I�����e�L�X�g
	gTitle_Select_Tutorial_Text_Image.Load2D(SCENE_SELECT_TUTORIAL_TEXT);
	//�^�C�g���o�b�N�I�����e�L�X�g
	gTitle_Select_Back_to_Title_Text_Image.Load2D(SCENE_SELECT_TITLEBACK_TEXT);
	//�Q�[���I���I�����e�L�X�g
	gTitle_Select_Quit_Game_Text_Image.Load2D(SCENE_SELECT_QUITGAME_TEXT);
	//�Q�[���X�^�[�g�摜�̒ǉ�
	gTitle_Select_GameStart_Image.Load2D(SCENE_SELECT_GAMESTART_IMAGE);
	//�`���[�g���A���X�^�[�g�摜�̒ǉ�
	gTitle_Select_TutorialStart_Image.Load2D(SCENE_SELECT_TUTORIALSTART_IMAGE);
	//�^�C�g���o�b�N�摜�̒ǉ�
	gTitle_Select_Back_to_Title_Image.Load2D(SCENE_SELECT_TITLEBACK_IMAGE);
	//�Q�[���I���̒ǉ�
	gTitle_Select_Quit_Game_Image.Load2D(SCENE_SELECT_QUITGAME_IMAGE);
	//�`���[�g���A���X�^�[�g�摜�̒ǉ�
	//�{�^�����������Ƃ��ɕ`�悳���t�F�C�h�A�E�g�A�C���p�w�i
	gTitle_Select_Fade_Image.Load2D(SCENE_SELECT_FADE_IMAGE);
}

void CSceneSelect::Update()
{

	//�{�^���������Ă��Ȃ��Ƃ�
	if (mIsButtonPush == false) {
		//�}�E�X�̍��W���擾
		CInput::GetMousePosWin(&mMouseX, &mMouseY);
		mMouseY = SCENE_SELECT_END_Y - mMouseY;
	}

		//�Q�[���X�^�[�g�{�^����Ƀ}�E�X�|�C���^������Ƃ�
	if ((mMouseX >= STARTBUTTON_LEFT && mMouseX <= STARTBUTTON_RIGHT) &&
		(mMouseY >= STARTBUTTON_DOWN && mMouseY <= STARTBUTTON_UP)) {
		//�I�����Ă���ꏊ���Q�[���X�^�[�g�ɐݒ�
		mSelect = CSceneSelect::ESelect::EGAMESTART;
	}
		//�`���[�g���A���{�^����Ƀ}�E�X�|�C���^������Ƃ�
	else if ((mMouseX >= TUTORIALBUTTON_LEFT && mMouseX <= TUTORIALBUTTON_RIGHT) &&
		(mMouseY >= TUTORIALBUTTON_DOWN && mMouseY <= TUTORIALBUTTON_UP)) {
		//�I�����Ă���ꏊ���`���[�g���A���ɐݒ�
		mSelect = CSceneSelect::ESelect::ETUTORIAL;
	}
	//�^�C�g���o�b�N�{�^����Ƀ}�E�X�|�C���^������Ƃ�
	else if ((mMouseX >= TITLEBACKBUTTON_LEFT && mMouseX <= TITLEBACKBUTTON_RIGHT) &&
		(mMouseY >= TITLEBACKBUTTON_DOWN && mMouseY <= TITLEBACKBUTTON_UP)) {
		//�I�����Ă���ꏊ���^�C�g���o�b�N�ɐݒ�
		mSelect = CSceneSelect::ESelect::EBACKTOTITLE;
	}
	//�Q�[���I���{�^����Ƀ}�E�X�|�C���^������Ƃ�
	else if ((mMouseX >= QUITGAMEBUTTON_LEFT && mMouseX <= QUITGAMEBUTTON_RIGHT) &&
		(mMouseY >= QUITGAMEBUTTON_DOWN && mMouseY <= QUITGAMEBUTTON_UP)) {
		//�I�����Ă���ꏊ���Q�[���I���ɐݒ�
		mSelect = CSceneSelect::ESelect::EQUITGAME;
	}
		//��L�ȊO�͔w�i
	else {
		//�I�����Ă���ꏊ��w�i�ɐݒ�
		mSelect = CSceneSelect::ESelect::EBACKGROUND;
	}

		//���N���b�N�����Ƃ�
	if (CKey::Once(VK_LBUTTON)) {
		//�I�����Ă���ꏊ�𔻒f����
		switch (mSelect) {
		case CSceneSelect::ESelect::EGAMESTART: //�Q�[���X�^�[�g
			//�{�^���������Ă��Ȃ��Ƃ�
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//�{�^��������������s
				//���̃V�[���̓Q�[��
				mNextScene = CScene::EScene::EGAME;
				//�V�[���؂�ւ����s
				mSceneChange = true;
			}
			break;

		case CSceneSelect::ESelect::ETUTORIAL: //�`���[�g���A���X�^�[�g
				//�{�^���������Ă��Ȃ��Ƃ�
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//�{�^��������������s
				//���̃V�[���̓`���[�g���A��
				mNextScene = CScene::EScene::ETUTORIAL;
				//�V�[���؂�ւ����s
				mSceneChange = true;
			}
			break;

		case CSceneSelect::ESelect::EBACKTOTITLE: //�^�C�g���o�b�N
			//�{�^���������Ă��Ȃ��Ƃ�
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//�{�^��������������s
				//���̃V�[���̓^�C�g��
				mNextScene = CScene::EScene::ETITLE;
				//�V�[���؂�ւ����s
				mSceneChange = true;
			}
			break;
		
		case CSceneSelect::ESelect::EQUITGAME: //�Q�[�����I��
			//�{�^���������Ă��Ȃ��Ƃ�
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//�{�^��������������s
				//�Q�[�����I������
				exit(NULL);
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
void CSceneSelect::Render() {

	//2D�̕`��J�n
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	//�^�C�g���I����ʕ`��
	gTitle_Select_Image.Draw(SCENE_SELECT_FIRST_WID, SCENE_SELECT_END_WID, SCENE_SELECT_FIRST_HEI, SCENE_SELECT_END_HEI, SCENE_SELECT_FIRST_X, SCENE_SELECT_END_X, SCENE_SELECT_END_Y, SCENE_SELECT_FIRST_Y);
	//�Q�[���X�^�[�g�X�^�[�g�摜�`��
	gTitle_Select_GameStart_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
	//�`���[�g���A���X�^�[�g�摜�`��
	gTitle_Select_TutorialStart_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
	//�^�C�g���o�b�N
	gTitle_Select_Back_to_Title_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
	//�Q�[���I���`��
	gTitle_Select_Quit_Game_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	//�w�i��I�����Ă�����`��
	if (mSelect == CSceneSelect::ESelect::EBACKGROUND)
	{
		
		//�^�C�g���I����ʃe�L�X�g
		gTitle_Select_Text_Image.Draw(SCENE_SELECT_TEXT_FIRST_WID, SCENE_SELECT_TEXT_END_WID, SCENE_SELECT_TEXT_FIRST_HEI, SCENE_SELECT_TEXT_END_HEI, SCENE_SELECT_TEXT_FIRST_X, SCENE_SELECT_TEXT_END_X, SCENE_SELECT_TEXT_END_Y, SCENE_SELECT_TEXT_FIRST_Y);
		
		//�X�^�[�g�{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		
		//�`���[�g���A���{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
		
		//�^�C�g���ɖ߂�{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
		
		//�Q�[���I���{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	}
	//�Q�[���X�^�[�g��I�����Ă�����`��
	if (mSelect == CSceneSelect::ESelect::EGAMESTART) {
		
		//�Q�[���J�n�I�����e�L�X�g
		gTitle_Select_GameStart_Text_Image.Draw(SCENE_SELECT_GAMESTART_TEXT_FIRST_WID, SCENE_SELECT_GAMESTART_TEXT_END_WID, SCENE_SELECT_GAMESTART_TEXT_FIRST_HEI, SCENE_SELECT_GAMESTART_TEXT_END_HEI, SCENE_SELECT_GAMESTART_TEXT_FIRST_X, SCENE_SELECT_GAMESTART_TEXT_END_X, SCENE_SELECT_GAMESTART_TEXT_END_Y, SCENE_SELECT_GAMESTART_TEXT_FIRST_Y);
		
		//�`���[�g���A���{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
		
		//�^�C�g���ɖ߂�{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
		
		//�Q�[���I���{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	}
	//�`���[�g���A����I�����Ă�����`��
	if (mSelect == CSceneSelect::ESelect::ETUTORIAL) {
		
		//�`���[�g���A���J�n�I�����e�L�X�g
		gTitle_Select_Tutorial_Text_Image.Draw(SCENE_SELECT_TUTORIAL_TEXT_FIRST_WID, SCENE_SELECT_TUTORIAL_TEXT_END_WID, SCENE_SELECT_TUTORIAL_TEXT_FIRST_HEI, SCENE_SELECT_TUTORIAL_TEXT_END_HEI, SCENE_SELECT_TUTORIAL_TEXT_FIRST_X, SCENE_SELECT_TUTORIAL_TEXT_END_X, SCENE_SELECT_TUTORIAL_TEXT_END_Y, SCENE_SELECT_TUTORIAL_TEXT_FIRST_Y);
		
		//�X�^�[�g�{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		
		//�^�C�g���ɖ߂�{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
		
		//�Q�[���I���{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	}
	//�^�C�g���o�b�N��I�����Ă�����`��
	if (mSelect == CSceneSelect::ESelect::EBACKTOTITLE) {
		
		//�`���[�g���A���J�n�I�����e�L�X�g
		gTitle_Select_Back_to_Title_Text_Image.Draw(SCENE_SELECT_TITLEBACK_TEXT_FIRST_WID, SCENE_SELECT_TITLEBACK_TEXT_END_WID, SCENE_SELECT_TITLEBACK_TEXT_FIRST_HEI, SCENE_SELECT_TITLEBACK_TEXT_END_HEI, SCENE_SELECT_TITLEBACK_TEXT_FIRST_X, SCENE_SELECT_TITLEBACK_TEXT_END_X, SCENE_SELECT_TITLEBACK_TEXT_END_Y, SCENE_SELECT_TITLEBACK_TEXT_FIRST_Y);
		
		//�X�^�[�g�{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		
		//�`���[�g���A���{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
		
		//�Q�[���I���{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	}
	//�Q�[���I����I�����Ă�����`��
	if (mSelect == CSceneSelect::ESelect::EQUITGAME) {
		
		//�`���[�g���A���J�n�I�����e�L�X�g
		gTitle_Select_Quit_Game_Text_Image.Draw(SCENE_SELECT_QUITGAME_TEXT_FIRST_WID, SCENE_SELECT_QUITGAME_TEXT_END_WID, SCENE_SELECT_QUITGAME_TEXT_FIRST_HEI, SCENE_SELECT_QUITGAME_TEXT_END_HEI, SCENE_SELECT_QUITGAME_TEXT_FIRST_X, SCENE_SELECT_QUITGAME_TEXT_END_X, SCENE_SELECT_QUITGAME_TEXT_END_Y, SCENE_SELECT_QUITGAME_TEXT_FIRST_Y);
		
		//�X�^�[�g�{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		
		//�`���[�g���A���{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
		
		//�^�C�g���ɖ߂�{�^���ɂ�����t�F�C�h�摜
		gTitle_Select_Fade_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
	}
	//
	//2D�̕`��I��
	CUtil::End2D();
}

//���̃V�[���Ɉڍs
CScene::EScene CSceneSelect::GetNextScene() {
	//���݂̃V�[����Ԃ�
	return mScene;
}