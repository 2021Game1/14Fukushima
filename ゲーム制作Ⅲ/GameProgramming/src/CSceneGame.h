#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include <time.h>
#include "CScene.h"
#include "CRes.h"



/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
	CRes mRes;
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//static�ŏ��������
	static CSceneGame* GetInstance();

};

#endif