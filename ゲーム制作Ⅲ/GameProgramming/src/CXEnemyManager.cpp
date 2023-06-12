#include "CXEnemyManager.h"
#include "CEnemyData.h"
#include "CXPlayer.h"

CXEnemyManager* CXEnemyManager::mInstance = nullptr;

//������
CXEnemyManager::CXEnemyManager()
	: mEnemyDeathNum(0)
	, mEnemyList(0)
	, mPlayerPos(5.3)
	, mEnemyPos(0)
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
	for (int i = 0; i < num; i++) {
		Init();
		//��������G�̎�ނ𔻕�
		switch (type) {
		case CXEnemy::EEnemyType::ETYPE_TUTORIAL:	//�`���[�g���A�����̓G�̋���
		{
			//�G�𐶐�
			CXEnemy* tmp1 = new CXEnemy;
			//�G�̏����ݒ�
			//�G�̃^�C�v��ݒ�
			tmp1->SetIsType(CXEnemy::EEnemyType::ETYPE_TUTORIAL);
			//�G�Ƀ��f����ݒ肷��
			tmp1->Init(&gEnemy_Model_Mutant);
			//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
			tmp1->EnemyTable();
			//�|�W�V�����̎擾
			tmp1->GetPos();
			//���f���̑傫�����擾
			tmp1->GetScale();
			//���f���̉�]���擾
			tmp1->GetRotation();
			//�X�V������ݒ�
			tmp1->Update();
			//�����蔻��̃^�X�N�ɒǉ�
			tmp1->TaskCollision();
			mEnemyList.push_back(tmp1);	//���X�g�ɒǉ�
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_1:	//�Q�[���{�Ԏ��̓G�̋���(����)
		{
			//�G�𐶐�
			CXEnemy* tmp2 = new CXEnemy;
			//�G�̏����ݒ�
			//�G�̃^�C�v��ݒ�
			tmp2->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_1);
			//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
			tmp2->EnemyTable();
			//�|�W�V�����̎擾
			tmp2->GetPos();
			//���f���̑傫�����擾
			tmp2->GetScale();
			//���f���̉�]���擾
			tmp2->GetRotation();
			//�G�Ƀ��f����ݒ肷��
			tmp2->Init(&gEnemy_Model_Mutant);
			//�X�V������ݒ�
			tmp2->Update();
			//�����蔻��̃^�X�N�ɒǉ�
			tmp2->TaskCollision();
			mEnemyList.push_back(tmp2);	//���X�g�ɒǉ�
		}
		break;

		case CXEnemy::EEnemyType::ETYPE_GAME_2:	//�Q�[���{�Ԏ��̓G�̋���(�ア)
		{
			//�G�𐶐�
			CXEnemy* tmp3 = new CXEnemy;
			//�G�̏����ݒ�
			//�G�̃^�C�v��ݒ�
			tmp3->SetIsType(CXEnemy::EEnemyType::ETYPE_GAME_2);
			//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
			tmp3->EnemyTable();
			//�|�W�V�����̎擾
			tmp3->GetPos();
			//���f���̑傫�����擾
			tmp3->GetScale();
			//���f���̉�]���擾
			tmp3->GetRotation();
			//�G�Ƀ��f����ݒ肷��
			tmp3->Init(&gEnemy_Model_Mutant);
			//�X�V������ݒ�
			tmp3->Update();
			//�����蔻��̃^�X�N�ɒǉ�
			tmp3->TaskCollision();
			mEnemyList.push_back(tmp3);	//���X�g�ɒǉ�
		}
		break;

		}
	}
}
//������
void CXEnemyManager::Init()
{
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
}

void CXEnemyManager::Update()
{
	//���Z�b�g
	mEnemyDeathNum = 0;
	//���X�g�Ɋi�[����Ă���G�����S��Ԃ��A�ǂ����𔻕ʂ���
	for (size_t i = 0; i < mEnemyList.size(); i++) {
		//���S��Ԃ�������
		if (CXEnemy::GetInstance()->GetIsDeath()) {
			mEnemyDeathNum++; //���S��Ԃ̓G�̃J�E���g���Z
			continue; //�ǂݔ�΂�
		}
		mTarget = mEnemyList[i]->GetInstance()->Position() - CXPlayer::GetInstance()->Position();
		mEnemyPos = mTarget.Length();
		if (mPlayerPos > mEnemyPos) {
			mTargetEnemy = mTarget.Normalize();
		}
	}
}


//�`�悵�Ȃ�
void CXEnemyManager::Render()
{
}

//�G���S�Ď��S��Ԃ̂Ƃ�true��Ԃ�
bool CXEnemyManager::GetIsEnemyAllDeath()
{
	//���X�g�ɓo�^����Ă���G�����S��Ԃ̓G�̐��ƈ�v������true
	if (mEnemyList.size() == mEnemyDeathNum)return true;
	//��v���Ȃ����false
	else return false;
}
CVector CXEnemyManager::GetTargetEnemy()
{
	return mTargetEnemy;
}