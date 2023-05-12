#include "CSceneGame.h"
#include "CSceneTutorial.h"
//OpenGL
#include "glut.h"


CSceneGame::~CSceneGame()
{
	CTaskManager::Get()->Delete();
}

void CSceneGame::Init() {
	//�V�[���̐ݒ�
	mScene = EGAME;
	mRes.Init();
	CRes::GetInstance()->GetinSoundBgmGame().Repeat(0.2);
	//�e�̐ݒ�
	float shadowColor[] = { SHADOWCOLOR_0, SHADOWCOLOR_1, SHADOWCOLOR_2, SHADOWCOLOR_3 };	//�e�̐F
	float lightPos[] = { LIGHTPOS_X, LIGHTPOS_Y, LIGHTPOS_Z };		//�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //�V���h�E�}�b�v������
}

void CSceneGame::Update() {
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{

			mScene = ETITLE;
		}
	}
	if (CXEnemy::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{

			mScene = ETITLE;
		}
	}

	//�X�V����
	CTaskManager::Get()->Update();
	//�Փˏ���
	CCollisionManager::Get()->Collision();



	//�^�X�N���X�g�폜
	CTaskManager::Get()->Delete();
}
void CSceneGame::Render() {
	CTaskManager::Get()->Draw();
	mShadowMap.Render();
	CTaskManager::Get()->Render2D();

	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
#endif
	//2D�̕`��J�n
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameOverImage().DrawImage(GAMEOVER_FIRST_WID, GAMEOVER_END_WID, GAMEOVER_FIRST_HEI, GAMEOVER_END_HEI, GAMEOVER_FIRST_X, GAMEOVER_END_X, GAMEOVER_END_Y, GAMEOVER_FIRST_Y);
	}
	if (CXEnemy::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameClearImage().DrawImage(GAMECLEAR_FIRST_WID, GAMECLEAR_END_WID, GAMECLEAR_FIRST_HEI, GAMECLEAR_END_HEI, GAMECLEAR_FIRST_X, GAMECLEAR_END_X, GAMECLEAR_END_Y, GAMECLEAR_FIRST_Y);
	}
	//2D�̕`��I��
	CUtil::End2D(); {
	}
}
CScene::EScene CSceneGame::GetNextScene()
{
	return mScene;
}





