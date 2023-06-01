#ifndef CSCENETUTORIAL_H
#define CSCENETUTORIAL_H
#include <time.h>
#include "CScene.h"
#include "CRes.h"
#include "CTutorial.h"

//�e�̐ݒ�
#define SHADOWCOLOR_0 0.4f
#define SHADOWCOLOR_1 0.4f
#define SHADOWCOLOR_2 0.4f
#define SHADOWCOLOR_3 0.2f

//�����̈ʒu
#define LIGHTPOS_X 50.0f
#define LIGHTPOS_Y 160.0f
#define LIGHTPOS_Z 50.0f

//�`���[�g���A���X�e�[�W�ɏo������G�̐�
#define TUTORIAL_GENERATE_A 1

/*
�Q�[���̃V�[��
*/
class CSceneTutorial : public CScene {
private:
	~CSceneTutorial();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�`�揈���̃I�[�o�[���C�h
	void Render();
	//�V�[���ψڊ֐�
	EScene GetNextScene();

	//�`���[�g���A���̃C���X�^���X
	CTutorial mTutorial;
	//���\�[�X�N���X�̃C���X�^���X
	CRes mRes;
	//�V���h�E�}�b�v�̃C���X�^���X
	CShadowMap mShadowMap;
};
void WholeRender();
#endif
