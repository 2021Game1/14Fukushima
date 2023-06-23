#include "CSceneTutorial.h"
//OpenGL
#include "glut.h"


//�f�X�g���N�^
CSceneTutorial::~CSceneTutorial()
{
	//�G�̊Ǘ��폜
	CXEnemyManager::GetInstance()->~CXEnemyManager();
	//�v���C�����폜
	CXPlayerManager::GetInstance()->Release();
	//�X�e�[�W�}�b�v���폜
	CMap::GetInstance()->Release();
	//��̔w�i�}�b�v���폜
	CSkyMap::GetInstance()->Release();
	//�^�X�N�}�l�[�W���̍폜
	CTaskManager::Get()->Delete();
}
//Init����
//��x�����������Ȃ�����
void CSceneTutorial::Init() {
	//�V�[���̐ݒ�
	//�`���[�g���A���ɃV�[����ݒ�
	mScene = CScene::EScene::ETUTORIAL;
	//�n��}�b�v�̐���
	CMap::GetInstance()->Generate();
	//�w�i�}�b�v�̐���
	CSkyMap::GetInstance()->Generate();
	//���\�[�X�̓ǂݍ��ݐݒ�
	mRes.Init();
	//BGM�Z�b�g(���s�[�g�j
	CRes::GetInstance()->GetinSoundBgmGame().Repeat(0.2);
	//�v���C���Ǘ�����
	CXPlayerManager::GetInstance()->Generate();
	//�G�Ǘ�����
	CXEnemyManager::GetInstance()->Generate();
	//�v���C������
	CXPlayerManager::GetInstance()->PlayerGenerate();
	//�G����
	CXEnemyManager::GetInstance()->EnemyGenerate(TUTORIAL_GENERATE_A, CXEnemy::EEnemyType::ETYPE_TUTORIAL);
	//�J����������
	Camera.Init();
	//�J�����^�[�Q�b�g
	Camera.SetTarget(CXPlayer::GetInstance()->Position());
	//�e�̐ݒ�
	float shadowColor[] = { SHADOWCOLOR_0, SHADOWCOLOR_1, SHADOWCOLOR_2, SHADOWCOLOR_3 };	//�e�̐F
	float lightPos[] = { LIGHTPOS_X, LIGHTPOS_Y, LIGHTPOS_Z };		//�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //�V���h�E�}�b�v������
}
//�X�V����
void CSceneTutorial::Update() {
	//�v���C��HP��0�ɂȂ�������s
	if (CXPlayer::GetInstance()->GetHp() == NULL) {
		//�Q�[��BGM���~�߂�
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		//Enter�L�[����������A�^�C�g���V�[���ɐ؂�ւ���
		if (CKey::Once(VK_RETURN))
		{
			//�V�[�����^�C�g���V�[���ɐݒ�
			mScene = CScene::EScene::ETITLE;
		}
	}
	//�G�l�~�[�}�l�[�W���Ɋi�[����Ă���G���S�Ď��S���Ă�Ȃ���s
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		//�Q�[��BGM���~�߂�
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		//Enter�L�[����������A�{�Ԃ̃Q�[���V�[���ɐ؂�ւ���
		if (CKey::Once(VK_RETURN))
		{
			//�V�[�����Q�[���V�[���ɐݒ�
			mScene = CScene::EScene::EGAME;
		}
	}
	//�`���[�g���A���N���X��Update���Ăяo��
	mTutorial.Update();

	//�^�X�N�}�l�[�W���Ɋi�[����Ă���S�Ă̍X�V�������Ăяo��
	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���Ɋi�[����Ă���S�Ă̏Փˏ������Ăяo��
	CCollisionManager::Get()->Collision();
	//�G�l�~�[�}�l�[�W���̍X�V�������Ăяo��
	CXEnemyManager::GetInstance()->Update();


	//�^�X�N���X�g�폜
	CTaskManager::Get()->Delete();
}
//�`�揈��
void CSceneTutorial::Render() {
	//�^�X�N�}�l�[�W���̕`����Ăяo��
	CTaskManager::Get()->Draw();
	//�e�̕`����擾
	mShadowMap.Render();
	//�`���[�g���A���̃t���O��true�̎��A�^�X�N�}�l�[�W����2D�`�悳���
	if (mTutorial.GetIsTutorialFlag() == true) {
		CTaskManager::Get()->Render2D();
	}

	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
#endif
	//�`���[�g���A���̕`��
	mTutorial.Render();

}
//���̃V�[���擾
CScene::EScene CSceneTutorial::GetNextScene()
{
	//���݂̃V�[����Ԃ�
	return mScene;
}
//�e�̕`��̂��߂ɊO������^�X�N�`��
//�e�̕`�掞�A1�x�S�ĕ`�悷����̂������e��`�悵�Ă���S�ĕ`�悷����̂�`�悵�Ȃ���
void WholeRender() {
	//�^�X�N�`��
	CTaskManager::Get()->Render();
}