#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "TitleData.h"

/*
�V�[���^�C�g���N���X
*/

class CSceneTitle : public CScene {
private:
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
	//�^�C�g��BGM
	CSound Title_Bgm;
public:
	//�f�t�H���g�R���X�g���N�^
	CSceneTitle();
	//�f�X�g���N�^
	~CSceneTitle();

};
#endif
