#include "CXPlayerManager.h"
#include "CPlayerData.h"
#include "CXEnemy.h"

CXPlayerManager* CXPlayerManager::mInstance = nullptr;


CXPlayerManager::CXPlayerManager()
	: mPlayerList(0)
{

}

CXPlayerManager::~CXPlayerManager()
{
	for (size_t i = 0; i < mPlayerList.size(); i++) {
		delete mPlayerList[i];
	}
}

void CXPlayerManager::Generate()
{
	mInstance = new CXPlayerManager;
}

void CXPlayerManager::Release()
{
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}


CXPlayerManager* CXPlayerManager::GetInstance()
{
	return mInstance;
}

//�G�̐�������
//�����Ő������A��ނ�ݒ肷��
void CXPlayerManager::PlayerGenerate() {
	//3D���f���t�@�C���̓ǂݍ���
	gPlayer_Model_Knight.Load(PLAYER_MODEL_FILE);
	//�v���C���̃A�j���[�V�����̒ǉ�
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_AVOIDANCE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_DEATH);

	CXPlayer* tmp = new CXPlayer;
	//�G�̏����ݒ�
	tmp->PlayerTable();
	tmp->GetPos();
	tmp->GetScale();
	tmp->GetRotation();
	tmp->Init(&gPlayer_Model_Knight);
	tmp->Update();
	tmp->TaskCollision();
	mPlayerList.push_back(tmp);	//���X�g�ɒǉ�

}

void CXPlayerManager::Update()
{
}

void CXPlayerManager::Render()
{
}