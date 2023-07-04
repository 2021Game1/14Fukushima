#ifndef CSCENESELECT_H
#define CSCENESELECT_H

#include "CScene.h"
#include "CSceneSelect_Data.h"
#include "CTaskManager.h"
#include "CTexture.h"
#include "CKey.h"
#include "CInput.h"
#include "CUtil.h"

/*
�V�[���̃Z���N�g���
CSceneSelect�N���X
*/


class CSceneSelect : public CScene {
public:
	//�f�t�H���g�R���X�g���N�^
	CSceneSelect();
	//�f�X�g���N�^
	~CSceneSelect();

private:
	//�I�����Ă���ꏊ
	enum class ESelect {
		EBACKGROUND = 0,//�w�i
		EGAMESTART,		//�Q�[���X�^�[�g
		ETUTORIAL,		//�`���[�g���A��
		EBACKTOTITLE,	//�^�C�g���o�b�N
		EQUITGAME,		//�Q�[���I��
	};
	ESelect mSelect; //�I�����Ă���ꏊ�̔��f�p
		//Init����
	//��x�����������Ȃ�����
	void Init();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//���̃V�[���̎擾
	EScene GetNextScene();
	//�V�[���ψ�
	bool CSceneSelect::mSceneChange;
	//���̃V�[���ֈڍs
	CScene::EScene CSceneSelect::mNextScene;
	//�^�C�g���Z���N�g��ʉ摜
	CTexture gTitle_Select_Image;
	//�^�C�g���Z���N�g��ʃe�L�X�g�摜
	CTexture gTitle_Select_Text_Image;
	//�Q�[���J�n�I�����e�L�X�g
	CTexture gTitle_Select_GameStart_Text_Image;
	//�`���[�g���A���J�n�I�����e�L�X�g
	CTexture gTitle_Select_Tutorial_Text_Image;
	//�^�C�g���o�b�N�I�����e�L�X�g
	CTexture gTitle_Select_Back_to_Title_Text_Image;
	//�Q�[���I���I�����e�L�X�g
	CTexture gTitle_Select_Quit_Game_Text_Image;
	//�Q�[���X�^�[�g�摜
	CTexture gTitle_Select_GameStart_Image;
	//�`���[�g���A���X�^�[�g�摜
	CTexture gTitle_Select_TutorialStart_Image;
	//�^�C�g���o�b�N�摜
	CTexture gTitle_Select_Back_to_Title_Image;
	//�Q�[���I���摜
	CTexture gTitle_Select_Quit_Game_Image;
	//�{�^�����������Ƃ��ɕ`�悳���t�F�C�h�A�E�g�A�C���p�w�i
	CTexture gTitle_Select_Fade_Image;
	//�{�^����������true
	bool mIsButtonPush;
	//�}�E�X�̍��W�Q�Ɨp
	int mMouseX, mMouseY;
};
#endif

