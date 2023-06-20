#include "CXPlayerManager.h"
#include "CPlayerData.h"
#include "CXEnemy.h"

//�v���C���}�l�[�W���N���X�̃|�C���^��nullptr�ɐݒ�
CXPlayerManager* CXPlayerManager::mInstance = nullptr;

//�f�t�H���g�R���X�g���N�^
CXPlayerManager::CXPlayerManager()
	: mPlayerList(0)
{

}

//�f�X�g���N�^
//�v���C�����폜����
CXPlayerManager::~CXPlayerManager()
{
	for (size_t i = 0; i < mPlayerList.size(); i++) {
		delete mPlayerList[i];
	}
}

//�v���C���}�l�[�W���𐶐�����
void CXPlayerManager::Generate()
{
	mInstance = new CXPlayerManager;
}

//�v���C���}�l�[�W�����폜����
void CXPlayerManager::Release()
{
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}

//�O���N���X����v���C���}�l�[�W���̃C���X�^���X���擾�p
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

	//�v���C���̐���
	CXPlayer* tmp = new CXPlayer;
	//�G�̏����ݒ�
	//�v���C���̃e�[�u�����Ăяo��
	//HP�Ȃǂ̃X�e�[�^�X���Ăяo�����
	tmp->PlayerTable();
	//�|�W�V������ݒ肷��
	tmp->GetPos();
	//�v���C���̃��f���̑傫����ݒ肷��
	tmp->GetScale();
	//�v���C���̃��f���̉�]��ݒ肷��
	tmp->GetRotation();
	//�v���C���̃��f����ݒ肷��
	tmp->Init(&gPlayer_Model_Knight);
	//�X�V�������Ăяo��
	tmp->Update();
	//�����蔻��^�X�N��ݒ肷��
	tmp->TaskCollision();
	mPlayerList.push_back(tmp);	//���X�g�ɒǉ�

}