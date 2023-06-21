#include "CSceneGame.h"
//OpenGL
#include "glut.h"

//�f�X�g���N�^
CSceneGame::~CSceneGame()
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
	//�J�����̍폜
	CCamera::Instance()->~CCamera();
}
//Init����
//��x�����������Ȃ�����
void CSceneGame::Init() {
	//�V�[���̐ݒ�
	//�V�[���ɃQ�[���V�[����ݒ肷��
	mScene = CScene::EScene::EGAME;
	//�}�b�v�𐶐�
	CMap::GetInstance()->Generate();
	//�}�b�v�w�i�𐶐�
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
	CXEnemyManager::GetInstance()->EnemyGenerate(ENEMY_GENERATE_A, CXEnemy::EEnemyType::ETYPE_GAME_1);
	//�e�̐ݒ�
	float shadowColor[] = { SHADOWCOLOR_0, SHADOWCOLOR_1, SHADOWCOLOR_2, SHADOWCOLOR_3 };	//�e�̐F
	float lightPos[] = { LIGHTPOS_X, LIGHTPOS_Y, LIGHTPOS_Z };		//�����̈ʒu
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //�V���h�E�}�b�v������
}
//�X�V����
void CSceneGame::Update() {
	//�v���C��HP��0�ɂȂ�������s
	if (CXPlayer::GetInstance()->GetHp() == NULL) {
		//�Q�[��BGM���~�߂�
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		//Enter�L�[����������A�^�C�g���V�[���ɐ؂�ւ���
		if (CKey::Once(VK_RETURN))
		{

			mScene = CScene::EScene::ETITLE;
		}
	}
	//�G�l�~�[�}�l�[�W���Ɋi�[����Ă���G���S�Ď��S���Ă�Ȃ���s
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		//�Q�[��BGM���~�߂�
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		//Enter�L�[����������A�^�C�g���V�[���ɐ؂�ւ���
		if (CKey::Once(VK_RETURN))
		{
			mScene = CScene::EScene::ETITLE;
		}
	}

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
void CSceneGame::Render() {
	//�^�X�N�}�l�[�W���̕`����Ăяo��
	CTaskManager::Get()->Draw();
	//�e�̕`����擾
	mShadowMap.Render();
	//�^�X�N�}�l�[�W����2D�`����Ăяo��
	CTaskManager::Get()->Render2D();

	//�f�o�b�O�o�[�W�����̂ݗL��
#ifdef _DEBUG
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
#endif
	//2D�̕`��J�n
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	//�v���C����HP��0����������s
	if (CXPlayer::GetInstance()->GetHp() == NULL) {
		//�Q�[���I�[�o�[�摜��`��
		CRes::GetInstance()->GetinGameOverImage().DrawImage(GAMEOVER_FIRST_WID, GAMEOVER_END_WID, GAMEOVER_FIRST_HEI, GAMEOVER_END_HEI, GAMEOVER_FIRST_X, GAMEOVER_END_X, GAMEOVER_END_Y, GAMEOVER_FIRST_Y);
	}
	//�G�̃}�l�[�W���N���X�Ɋi�[����Ă���G���S�Ď��S��Ԃł���Ύ��s
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		//�Q�[���N���A�摜��`��
		CRes::GetInstance()->GetinGameClearImage().DrawImage(GAMECLEAR_FIRST_WID, GAMECLEAR_END_WID, GAMECLEAR_FIRST_HEI, GAMECLEAR_END_HEI, GAMECLEAR_FIRST_X, GAMECLEAR_END_X, GAMECLEAR_END_Y, GAMECLEAR_FIRST_Y);
	}
	//2D�̕`��I��
	CUtil::End2D(); {
	}
}
//���̃V�[�����擾
CScene::EScene CSceneGame::GetNextScene()
{
	//���݂̃V�[����Ԃ�
	return mScene;
}





