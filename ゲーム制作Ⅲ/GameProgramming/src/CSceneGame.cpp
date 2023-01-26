#include "CSceneGame.h"
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
	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.2f };	//�e�̐F
	float lightPos[] = { 50.0f, 160.0f, 50.0f };		//�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //�V���h�E�}�b�v������

}

void CSceneGame::Update() {
	
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{
			CRes::GetInstance()->GetinSoundBgmGameOver().Stop();
			mScene = ETITLE;
		}
	}
	if (CXEnemy::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		
		if (CKey::Once(VK_RETURN))
		{
			CRes::GetInstance()->GetinSoundBgmGameClear().Stop();
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
	CUtil::Start2D(0, 800, 0, 600);
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameOverImage().DrawImage(0, 800, 0, 600, 0, 800, 600, 0);
	}
	if (CXEnemy::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameClearImage().DrawImage(0, 800, 0, 600, 0, 800, 600, 0);
	}
	//2D�̕`��I��
	CUtil::End2D();
}
void WholeRender() {
	//�^�X�N�`��
	CTaskManager::Get()->Render();
}
CScene::EScene CSceneGame::GetNextScene()
{
	return mScene;
}


