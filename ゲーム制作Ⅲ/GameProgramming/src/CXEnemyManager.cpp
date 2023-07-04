#include "CXEnemyManager.h"

//�|�C���^�̏�����
CXEnemyManager* CXEnemyManager::mInstance = nullptr;

//������
CXEnemyManager::CXEnemyManager()
	: mEnemyDeathNum(NULL)
	, mEnemyList(NULL)
	, mPlayerPos(PLAYER_ATTACK_POS)
	, mEnemyPos_Tutorial(NULL)
	, mEnemyPos_Game1(NULL)
	, mEnemyPos_Game2(NULL)
	, mTargetEnemy(NULL,NULL,NULL)
	, mTarget_Tutorial(NULL,NULL,NULL)
	, mTarget_Game1(NULL,NULL,NULL)
	, mTarget_Game2(NULL,NULL,NULL)
	, tmp1(NULL)
	, tmp2(NULL)
	, tmp3(NULL)
{
	mInstance = this;
	//�^�X�N�}�l�[�W���ւ̒ǉ�
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}

//�I����
CXEnemyManager::~CXEnemyManager()
{
	for (size_t i = NULL; i < mEnemyList.size(); i++) {
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
void CXEnemyManager::EnemyGenerate(int num, CXEnemy::EEnemyType type)
{
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

void CXEnemyManager::Update()
{
	//���Z�b�g
	mEnemyDeathNum = NULL;
	//������
	mTargetEnemy = CVector(NULL, NULL, NULL);

	//���X�g�Ɋi�[����Ă���G�����S��Ԃ��A�ǂ����𔻕ʂ���
	for (size_t i = NULL; i < mEnemyList.size(); i++) {
		//���S��Ԃ�������
		if (CXEnemy::GetInstance()->GetIsDeath()) {
			mEnemyDeathNum++; //���S��Ԃ̓G�̃J�E���g���Z
			continue; //�ǂݔ�΂�
		}

		//�G����������Ă��Ȃ���΃X���[
		if (!tmp1 == NULL) {
			//�G�����S���Ă��Ȃ����Ɏ��s
			if (!tmp1->GetIsDeath()) {
				//�^�[�Q�b�g�ݒ�
				//�G�̃��ʒu�����v���C���Ƃ̋����ƎQ��
				mTarget_Tutorial = tmp1->Position() - CXPlayer::GetInstance()->Position();
				//�G�̈ʒu�����x�N�g���ɕϊ����A�i�[
				mEnemyPos_Tutorial = mTarget_Tutorial.Length();
				//�G�̈ʒu��񂪃v���C���̍U���������߂��ꍇ�A���s����
				if (mPlayerPos > mEnemyPos_Tutorial) {
					//�^�[�Q�b�g�Ɋi�[����
					mTargetEnemy = mTarget_Tutorial.Normalize();
				}
				else {

				}
			}
		}
		//��������Ă��Ȃ���΃X���[
		if (!tmp2 == NULL) {
			//�G�����S���Ă��Ȃ����Ɏ��s
			if (!tmp2->GetIsDeath()) {
				//�^�[�Q�b�g�ݒ�
				//�G�̃��ʒu�����v���C���Ƃ̋����ƎQ��
				mTarget_Game1 = tmp2->Position() - CXPlayer::GetInstance()->Position();
				//�G�̈ʒu�����x�N�g���ɕϊ����A�i�[
				mEnemyPos_Game1 = mTarget_Game1.Length();
				//�G�̈ʒu��񂪃v���C���̍U���������߂��ꍇ�A���s����
				if (mPlayerPos > mEnemyPos_Game1) {
					//�^�[�Q�b�g�Ɋi�[����
					mTargetEnemy = mTarget_Game1.Normalize();
				}
				else {

				}
			}


		}
		//��������Ă��Ȃ���΃X���[
		if (!tmp3 == NULL) {
			//�G�����S���Ă��Ȃ����Ɏ��s
			if (!tmp3->GetIsDeath()) {
				//�^�[�Q�b�g�ݒ�
				//�G�̃��ʒu�����v���C���Ƃ̋����ƎQ��
				mTarget_Game2 = tmp3->Position() - CXPlayer::GetInstance()->Position();
				//�G�̈ʒu�����x�N�g���ɕϊ����A�i�[
				mEnemyPos_Game2 = mTarget_Game2.Length();
				//�G�̈ʒu��񂪃v���C���̍U���������߂��ꍇ�A���s����
				if (mPlayerPos > mEnemyPos_Game2) {
					//�^�[�Q�b�g�Ɋi�[����
					mTargetEnemy = mTarget_Game2.Normalize();
				}
				else {

				}
			}
		}
	}
}

//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)
void CXEnemyManager::Init()
{
}

//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)
void CXEnemyManager::Render()
{
}


//�G���S�Ď��S��Ԃ̂Ƃ�true��Ԃ�
bool CXEnemyManager::GetIsEnemyAllDeath()
{
	//��������Ă���G�����S��Ԃ̓G�̐��ƈ�v������true
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