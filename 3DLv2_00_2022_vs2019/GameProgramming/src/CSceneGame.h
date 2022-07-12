#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CText.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
	CText mFont;
	//�m�F�p�C���X�^���X
	CModelX gModelX;
	//�L�����N�^�̃C���X�^���X
	CXCharacter mCaracter;
	//�L�[���͂ŉ�]
	CMatrix gMatrix;
	int i = 0;
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
};

#endif