#include "CStoneManager.h"

//�|�C���^�̏�����
CStoneManager* CStoneManager::mInstance = nullptr;

//������
CStoneManager::CStoneManager()
	: mStoneList(NULL)
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
CStoneManager::~CStoneManager()
{
	for (size_t i = NULL; i < mStoneList.size(); i++) {
		delete mStoneList[i];
	}
}

//�G�̃}�l�[�W�����Ő���
void CStoneManager::Generate()
{
	mInstance = new CStoneManager;
}

//�G�̃}�l�[�W�����폜����
void CStoneManager::Release()
{
	if (mInstance) {
		mInstance = nullptr;
		delete mInstance;
	}
}

//�O���N���X����G�}�l�[�W���C���X�^���X�̎擾�p
CStoneManager* CStoneManager::GetInstance()
{
	return mInstance;
}



//�G�̐�������
//�����Ő������A��ނ�ݒ肷��
void CStoneManager::StoneGenerate(CStone::EStoneType type)
{

	//���f���ݒ�
	//��������G�̎�ނ𔻕�
	switch (type) {
	case CStone::EStoneType::ETYPE_STONE_POS_1:	//�v���C���̏����ʒu���猩�ē��ɔz�u
	{
		//�G�𐶐�
		tmp1 = new CStone;
		//�G�̏����ݒ�
		tmp1->SetIsType(CStone::EStoneType::ETYPE_STONE_POS_1);
		//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
		tmp1->StoneTable();
		//���X�g�ɒǉ�
		mStoneList.push_back(tmp1);
	}
	break;

	case CStone::EStoneType::ETYPE_STONE_POS_2:	//�v���C���̏����ʒu���猩�Đ��ɔz�u
	{
		//�G�𐶐�
		tmp2 = new CStone;
		//�G�̏����ݒ�
		tmp2->SetIsType(CStone::EStoneType::ETYPE_STONE_POS_2);
		//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
		tmp2->StoneTable();
		//���X�g�ɒǉ�
		mStoneList.push_back(tmp2);
	}
	break;

	case CStone::EStoneType::ETYPE_STONE_POS_3:	//�v���C���̏����ʒu���猩�Ėk�ɔz�u
	{
		//�G�𐶐�
		tmp3 = new CStone;
		//�G�̏����ݒ�
		tmp3->SetIsType(CStone::EStoneType::ETYPE_STONE_POS_3);
		//�e�[�u����HP�Ȃǂ̃p�����[�^�̐ݒ�
		tmp3->StoneTable();
		//���X�g�ɒǉ�
		mStoneList.push_back(tmp3);
	}
	break;

	}
}
//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)
void CStoneManager::Update()
{
}

//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)
void CStoneManager::Init()
{
}

//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)
void CStoneManager::Render()
{
}


