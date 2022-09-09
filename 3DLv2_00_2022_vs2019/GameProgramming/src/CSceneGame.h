#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CText.h"
#include "CXPlayer.h"
#include "CXEnemy.h"


/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
	CText mFont;
	//�m�F�p�C���X�^���X
	CModelX gModelX;
	//�v���C���[�N���X�̃C���X�^���X
	CXPlayer mPlayer;
	//�L�[���͂ŉ�]
	CMatrix gMatrix;
	//�G�̃C���X�^���X
	CXEnemy mEnemy;
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif