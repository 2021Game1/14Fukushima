#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "TitleData.h"
#include "CInput.h"

/*
�V�[���^�C�g���N���X
*/

class CSceneTitle : public CScene {
private:
	//�I�����Ă���ꏊ
	enum ESelect {
		EBACKGROUND = 0,//�w�i
		EGAMESTART,		//�Q�[���X�^�[�g
		ETUTORIAL,		//�`���[�g���A��
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
	bool CSceneTitle::mSceneChange;
	//���̃V�[���ֈڍs
	CScene::EScene CSceneTitle::mNextScene;
	//�^�C�g���摜
	CTexture gTitle_Image;
	//�^�C�g���Z���N�g�摜
	CTexture gTitle_Select_Image;
	//�Q�[���X�^�[�g�摜
	CTexture gTitle_Select_GameStart_Image;
	//�`���[�g���A���X�^�[�g�摜
	CTexture gTitle_Select_TutorialStart_Image;
	//�{�^����������true
	bool mIsButtonPush;
	//�`���[�g���A���J�n�̉摜�̃t���O
	bool mTutorialflag;
	//�`���[�g���A���I���̉摜�t���O
	bool mTitleflag;
	//�^�C�g��BGM
	CSound Title_Bgm;
	//�}�E�X�̍��W�Q�Ɨp
	int mMouseX, mMouseY;

public:
	//�f�t�H���g�R���X�g���N�^
	CSceneTitle();
	//�f�X�g���N�^
	~CSceneTitle();

};
#endif
