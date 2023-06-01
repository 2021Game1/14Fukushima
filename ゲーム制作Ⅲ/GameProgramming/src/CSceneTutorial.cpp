#include "CSceneTutorial.h"
//OpenGL
#include "glut.h"


CSceneTutorial::~CSceneTutorial()
{
	CXEnemyManager::GetInstance()->Release();	//�G�Ǘ����
	CTaskManager::Get()->Delete();
}

void CSceneTutorial::Init() {
	//�V�[���̐ݒ�
	mScene = ETUTORIAL;
	mRes.Init();
	CRes::GetInstance()->GetinSoundBgmGame().Repeat(0.2);
	//�G�Ǘ�����
	CXEnemyManager::GetInstance()->Generate();
	CXEnemyManager::GetInstance()->EnemyGenerate(TUTORIAL_GENERATE_A, CXEnemy::EEnemyType::ETYPE_TUTORIAL);
	//�e�̐ݒ�
	float shadowColor[] = { SHADOWCOLOR_0, SHADOWCOLOR_1, SHADOWCOLOR_2, SHADOWCOLOR_3 };	//�e�̐F
	float lightPos[] = { LIGHTPOS_X, LIGHTPOS_Y, LIGHTPOS_Z };		//�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //�V���h�E�}�b�v������
}

void CSceneTutorial::Update() {

	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{

			mScene = ETITLE;
		}
	}
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{
			mScene = EGAME;
		}
	}

	mTutorial.Update();

	//�X�V����
	CTaskManager::Get()->Update();
	//�Փˏ���
	CCollisionManager::Get()->Collision();
	CXEnemyManager::GetInstance()->Update();


	//�^�X�N���X�g�폜
	CTaskManager::Get()->Delete();
}
void CSceneTutorial::Render() {
	CTaskManager::Get()->Draw();
	mShadowMap.Render();
	if (mTutorial.GetIsTutorialFlag() == true) {
		CTaskManager::Get()->Render2D();
	}

	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
#endif
	mTutorial.Render();

}
CScene::EScene CSceneTutorial::GetNextScene()
{
	return mScene;
}
void WholeRender() {
	//�^�X�N�`��
	CTaskManager::Get()->Render();
}