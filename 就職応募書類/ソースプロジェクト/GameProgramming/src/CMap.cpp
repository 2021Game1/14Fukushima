#include"CMap.h"




CMap* CMap::mpMap_Instance = nullptr;												//�C���X�^���X�ϐ��̏�����
CSkyMap* CSkyMap::mpSkyMap_Instance = nullptr;												//�C���X�^���X�ϐ��̏�����

CMap* CMap::GetInstance()
{
	return mpMap_Instance;
}

//�R���C�_������
CMap::CMap()
{
	mpMap_Instance = this;
	mTag = EMAP;
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
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//�ǉ�����
}
void CMap::Init() {

}

void CMap::Generate()
{
	mpMap_Instance = new CMap;
}
void CMap::Release()
{
	if (mpMap_Instance) {
		delete mpMap_Instance;
		mpMap_Instance = nullptr;
	}
}
void CMap::Collision(CCollider* m, CCollider* o) {
	switch (m->Type())
	{
	case CCollider::ESPHERE: {
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)) {
			//�s��̍X�V
			CTransform::Update();
		}
	}
	case CCollider::ECAPSUL: {
		CVector adjust;//�����p�x�N�g��
		if (CCollider::CollisionCapsule(m, o, &adjust))
		{
			//�s��̍X�V
			CTransform::Update();
		}
	}

	}
}

CSkyMap::CSkyMap()
{
	mTag = EMAP;
	mpSkyMap_Instance = this;
	//�X�J�C���f���t�@�C���̓���
	gSky_Map_Model.Load(MAP_MODEL_SKY);
	Model(&gSky_Map_Model);
	//�D��x��ݒ�
	mPriority = MAP_PRIORITY;
	CTaskManager::Get()->Remove(this);//
	CTaskManager::Get()->Add(this);//�ǉ�����
}
void CSkyMap::Init()
{

}

void CSkyMap::Collision(CCollider* m, CCollider* o)
{
	switch (m->Type())
	{
	case CCollider::ESPHERE: {
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)) {

		}
	}
	}
}

void CSkyMap::Generate()
{
	mpSkyMap_Instance = new CSkyMap;
}

void CSkyMap::Release()
{
	if (mpSkyMap_Instance) {
		delete mpSkyMap_Instance;
		mpSkyMap_Instance = nullptr;
	}
}

CSkyMap* CSkyMap::GetInstance()
{
	return mpSkyMap_Instance;
}
