#include "CXEnemyManager.h"
#include "CEnemyData.h"

CXEnemyManager* CXEnemyManager::mInstance = nullptr;


CXEnemyManager::CXEnemyManager()
	: mEnemyDeathNum(0)
	, mEnemyList(0)
{

}

CXEnemyManager::~CXEnemyManager()
{
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		delete mEnemyList[i];
	}
}

void CXEnemyManager::Generate()
{
	mInstance = new CXEnemyManager;
}

void CXEnemyManager::Release()
{
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}
}


CXEnemyManager* CXEnemyManager::GetInstance()
{
	return mInstance;
}

//�G�̐�������
//�����Ő������A��ނ�ݒ肷��
void CXEnemyManager::EnemyGenerate(int num, CXEnemy::EEnemyType type){
	//3D���f���t�@�C���̓ǂݍ���
	gEnemy_Model_Mutant.Load(ENEMY_MODEL_FILE);
	//�G�l�~�[�̃A�j���[�V�����̒ǉ�
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP1);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_BACKSTEP);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);

	for (int i = 0; i < num; i++) {
		//��������G�̎�ނ𔻕�
		switch (type) {
		case CXEnemy::EEnemyType::ETYPE_TUTORIAL:	//�`���[�g���A�����̓G�̋���
		{
			CXEnemy* tmp = new CXEnemy;
			//�G�̏����ݒ�
			tmp->SetIsType(CXEnemy::EEnemyType::ETYPE_TUTORIAL);
			tmp->EnemyTable();
			tmp->GetPos();
			tmp->GetScale();
			tmp->GetRotation();
			tmp->Init(&gEnemy_Model_Mutant);
			tmp->Update();
			tmp->TaskCollision();
			mEnemyList.push_back(tmp);	//���X�g�ɒǉ�
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_1:	//�Q�[���{�Ԏ��̓G�̋���(����)
		{
			CXEnemy* tmp = new CXEnemy;
			//�G�̏����ݒ�
			tmp->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_1);
			tmp->EnemyTable();
			tmp->SetIsPriority();
			tmp->GetPos();
			tmp->GetScale();
			tmp->GetRotation();
			tmp->Init(&gEnemy_Model_Mutant);
			tmp->Update();
			tmp->TaskCollision();
			mEnemyList.push_back(tmp);	//���X�g�ɒǉ�
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_2:	//�Q�[���{�Ԏ��̓G�̋���(�ア)
		{
			CXEnemy* tmp = new CXEnemy;
			//�G�̏����ݒ�
			tmp->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_2);
			tmp->EnemyTable();
			tmp->GetPos();
			tmp->GetScale();
			tmp->GetRotation();
			tmp->Init(&gEnemy_Model_Mutant);
			tmp->Update();
			tmp->TaskCollision();
			mEnemyList.push_back(tmp);	//���X�g�ɒǉ�
		}
		break;

		}
	}
}

void CXEnemyManager::Update()
{
	//���Z�b�g
	mEnemyDeathNum = 0;

	for (size_t i = 0; i < mEnemyList.size(); i++) {
		//���S��Ԃ�������
		if (CXEnemy::GetInstance()->GetIsDeath()) {
			mEnemyDeathNum++; //���S��Ԃ̓G�̃J�E���g���Z
			continue; //�ǂݔ�΂�
		}
	}
}

void CXEnemyManager::Render()
{
}

//�G���S�Ď��S��Ԃ̂Ƃ�true��Ԃ�
bool CXEnemyManager::GetIsEnemyAllDeath()
{
	if (mEnemyList.size() == mEnemyDeathNum)return true;
	else return false;
}
