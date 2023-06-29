#include "CXEnemyManager.h"


CXEnemyManager* CXEnemyManager::mInstance = nullptr;

//������
CXEnemyManager::CXEnemyManager()
	: mEnemyDeathNum(NULL)
	, mEnemyList(NULL)
	, mPlayerPos(PLAYER_ATTACK_POS)
	, mEnemyPos(NULL)
	, tmp1(NULL)
	, tmp2(NULL)
	, tmp3(NULL)
{

}

//�I����
CXEnemyManager::~CXEnemyManager()
{
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		delete mEnemyList[i];
	}
}
//�G�̃}�l�[�W�����Ő���
void CXEnemyManager::Generate()
{
	mInstance = new CXEnemyManager;
}
//�G�̃}�l�[�W�����폜����
void CXEnemyManager::Release()
{
	if (mInstance) {
		mInstance = nullptr;
		delete mInstance;
	}
}

//�O���N���X����G�}�l�[�W���C���X�^���X�̎擾�p
CXEnemyManager* CXEnemyManager::GetInstance()
{
	return mInstance;
}



//�G�̐�������
//�����Ő������A��ނ�ݒ肷��
void CXEnemyManager::EnemyGenerate(int num, CXEnemy::EEnemyType type){
	//�w�肵���������ɉ����āA���������s����
	for (int i = NULL; i < num; i++) {
		//��������G�̎�ނ𔻕�
		switch (type) {
		case CXEnemy::EEnemyType::ETYPE_TUTORIAL:	//�`���[�g���A�����̓G�̋���
		{
			//�G�𐶐�
			tmp1 = new CXEnemy;
			//�G�̏����ݒ�
			tmp1->SetIsType(CXEnemy::EEnemyType::ETYPE_TUTORIAL);
			//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
			tmp1->EnemyTable();
			//�X�V������ݒ�
			tmp1->Update();
			//���X�g�ɒǉ�
			mEnemyList.push_back(tmp1);
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_1:	//�Q�[���{�Ԏ��̓G�̋���(����)
		{
			//�G�𐶐�
			tmp2 = new CXEnemy;
			//�G�̏����ݒ�
			tmp2->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_1);
			//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
			tmp2->EnemyTable();
			//�X�V������ݒ�
			tmp2->Update();
			//���X�g�ɒǉ�
			mEnemyList.push_back(tmp2);
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_2:	//�Q�[���{�Ԏ��̓G�̋���(����)
		{
			//�G�𐶐�
			tmp3 = new CXEnemy;
			//�G�̏����ݒ�
			tmp3->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_2);
			//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
			tmp3->EnemyTable();
			//�X�V������ݒ�
			tmp3->Update();
			//���X�g�ɒǉ�
			mEnemyList.push_back(tmp3);
		}
		break;

		}
	}
}
//������
void CXEnemyManager::Init()
{

}

void CXEnemyManager::Update()
{
	
	//���Z�b�g
	mEnemyDeathNum = NULL;
	//���X�g�Ɋi�[����Ă���G�����S��Ԃ��A�ǂ����𔻕ʂ���
	for (size_t i = NULL; i < mEnemyList.size(); i++) {
		//���S��Ԃ�������
		if (CXEnemy::GetInstance()->GetIsDeath()) {
			mEnemyDeathNum++; //���S��Ԃ̓G�̃J�E���g���Z
			continue; //�ǂݔ�΂�
		}
		//�^�[�Q�b�g�ݒ�
		//�G�̃��X�g�Ɋi�[����Ă���ʒu�����v���C���Ƃ̋����ƎQ��
		mTarget = mEnemyList[i]->GetInstance()->Position() - CXPlayer::GetInstance()->Position();
		//�G�̈ʒu�����x�N�g���ɕϊ����A�i�[
		mEnemyPos = mTarget.Length();
		//�G�̈ʒu��񂪃v���C���̍U���������߂��ꍇ�A���s����
		if (mPlayerPos > mEnemyPos) {
			//�^�[�Q�b�g�Ɋi�[����
			mTargetEnemy = mTarget.Normalize();
		}
	}
}


//�G���S�Ď��S��Ԃ̂Ƃ�true��Ԃ�
bool CXEnemyManager::GetIsEnemyAllDeath()
{
	//���X�g�ɓo�^����Ă���G�����S��Ԃ̓G�̐��ƈ�v������true
	if (mEnemyList.size() == mEnemyDeathNum)return true;
	//��v���Ȃ����false
	else return false;
}
//�^�[�Q�b�g����ׂ��G���擾����
CVector CXEnemyManager::GetTargetEnemy()
{
	//�i�[�����G�̈ʒu����Ԃ�
	return mTargetEnemy;
}