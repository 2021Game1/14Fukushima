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
	//�V���h�E�}�b�v�̃C���X�^���X
	CShadowMap mShadowMap;
private:
	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�`�揈���̃I�[�o�[���C�h
	void Render();
	//�V�[���ψڊ֐�
	EScene GetNextScene();
};
void WholeRender();
#endif