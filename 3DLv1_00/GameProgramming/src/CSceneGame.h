#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModel.h"
//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//���f���N���X�̃C���X�^���X�쐬
	CModel mModel;
	CModel mBackGround; //�w�i���f��
	//�v���C���[�̕ϐ�
	CPlayer mPlayer;
};

#endif
