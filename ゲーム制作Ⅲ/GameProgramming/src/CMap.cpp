#include"CMap.h"



//�|�C���^��nullptr�ɐݒ肷��
CMap* CMap::mpMap_Instance = nullptr;												//�C���X�^���X�ϐ��̏�����
CSkyMap* CSkyMap::mpSkyMap_Instance = nullptr;												//�C���X�^���X�ϐ��̏�����

//�|�C���^���O���N���X����Q�Ƃł���悤�ɐݒ�
CMap* CMap::GetInstance()
{
	//�|�C���^��Ԃ�
	return mpMap_Instance;
}

//�R���C�_������
CMap::CMap()
{
	//�}�b�v�̃|�C���^��this�ɂ���
	mpMap_Instance = this;
	mTag = CCharacter::ETag::EMAP;
	//�}�b�v���f���t�@�C���̓���
	gMap_Model.Load(MAP_MODEL_MAP);
	Model(&gMap_Model);
	//�}�b�v�̃R���C�_�t�@�C���̓���
	gMap_Model_Collision.Load(MAP_COLLISION_MAP);
	//�}�b�v�̈ړ��s��
	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(this, &mBackGroundMatrix, &gMap_Model_Collision);

	//�D��x��ݒ�
	mPriority = MAP_PRIORITY;
	//�^�X�N�}�l�[�W���ւ̒ǉ�����
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}
//��������
void CMap::Generate()
{
	mpMap_Instance = new CMap;
}
//�폜����
void CMap::Release()
{
	//�|�C���^���폜
	if (mpMap_Instance) {
		delete mpMap_Instance;
		mpMap_Instance = nullptr;
	}
}
//�Փˏ���
void CMap::Collision(CCollider* m, CCollider* o) {
	switch (m->Type())
	{
	//����̃R���C�_�����̏ꍇ
	case CCollider::EType::ESPHERE: {
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)) {
			//�s��̍X�V
			CTransform::Update();
		}
	}
	//����̃R���C�_���J�v�Z���̏ꍇ
	case CCollider::EType::ECAPSUL: {
		CVector adjust;//�����p�x�N�g��
		if (CCollider::CollisionCapsule(m, o, &adjust))
		{
			//�s��̍X�V
			CTransform::Update();
		}
	}

	}
}
//�f�t�H���g�R���X�g���N�^
CSkyMap::CSkyMap()
{
	mTag = CCharacter::ETag::EMAP;
	mpSkyMap_Instance = this;
	//�X�J�C���f���t�@�C���̓���
	gSky_Map_Model.Load(MAP_MODEL_SKY);
	Model(&gSky_Map_Model);
	//�D��x��ݒ�
	mPriority = MAP_PRIORITY;
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//�ǉ�����
}
//�Փˏ���
void CSkyMap::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::EType::ESPHERE: {
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)) {

		}
	}
	}
}
//��������
//�w�i�}�b�v�̃��f���𐶐�����
void CSkyMap::Generate()
{
	mpSkyMap_Instance = new CSkyMap;
}
//�폜����
//�|�C���^���폜���Anull�ɐݒ肷��
void CSkyMap::Release()
{
	if (mpSkyMap_Instance) {
		delete mpSkyMap_Instance;
		mpSkyMap_Instance = nullptr;
	}
}
//�|�C���^���O���N���X����Q�Ƃł���悤�ɐݒ�
CSkyMap* CSkyMap::GetInstance()
{
	//�|�C���^��Ԃ�
	return mpSkyMap_Instance;
}
