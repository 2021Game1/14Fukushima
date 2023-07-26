#include"CStone.h"



//�|�C���^��nullptr�ɐݒ肷��
CStone* CStone::mpStone_Instance = nullptr;												//�C���X�^���X�ϐ��̏�����

//�|�C���^���O���N���X����Q�Ƃł���悤�ɐݒ�
CStone* CStone::GetInstance()
{
	//�|�C���^��Ԃ�
	return mpStone_Instance;
}

//�R���C�_������
CStone::CStone()
	:mStone_Type(CStone::EStoneType::ETYPE_STONE_POS_1)
	,Stone_Position_X(NULL)
	, Stone_Position_Y(NULL)
	, Stone_Position_Z(NULL)
	, Stone_Scale_X(NULL)
	, Stone_Scale_Y(NULL)
	, Stone_Scale_Z(NULL)
	, Stone_Rotation_X(NULL)
	, Stone_Rotation_Y(NULL)
	, Stone_Rotation_Z(NULL)
{
	//�f�[�^�x�[�X�̌Ăяo��
	StoneTable();

	//�}�b�v�̃|�C���^��this�ɂ���
	mpStone_Instance = this;

	//�}�b�v���f���t�@�C���̓���
	gStone_Model.Load(STONE_MODEL_OBJ);
	//�}�b�v�̃R���C�_�t�@�C���̓���
	gStone_Model_Collision.Load(STONE_COLLISION_OBJ);

	//���f���ݒ�
	Model(&gStone_Model);
	//�o���ʒu�̐ݒ�
	Position(CVector(Stone_Position_X, Stone_Position_Y, Stone_Position_Z));
	//���f���̃X�P�[���ݒ�
	Scale(CVector(Stone_Scale_X, Stone_Scale_Y, Stone_Scale_Z));
	//���f���̉�]�ݒ�
	Rotation(CVector(Stone_Rotation_X, Stone_Rotation_Y, Stone_Rotation_Z));
	//�ړ��s��
	CTransform::Update();

	//�΂̈ړ��s��
	mBackGroundMatrix.Translate(Stone_Position_X, Stone_Position_Y, Stone_Position_Z);
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(this, &mBackGroundMatrix, &gStone_Model_Collision);
	//�^�X�N�}�l�[�W���ւ̒ǉ�����
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}

void CStone::Model(CModel* model)
{
	//���f���ݒ�
	CCharacter::Model(model);
}
void CStone::StoneTable()
{
	//��������G�̎�ނ𔻕�
	switch (mStone_Type) {
	case CStone::EStoneType::ETYPE_STONE_POS_1:
	{
		OX::Table table(STONE_DATATABLE);
		Stone_Position_X = table["Stone_Position_X"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�X���W
		Stone_Position_Y = table["Stone_Position_Y"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�Y���W
		Stone_Position_Z = table["Stone_Position_Z"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�Z���W
		Stone_Scale_X = table["Stone_Scale_X"]["Value"].fVal;//��Q���̃��f���X�P�[����X���W
		Stone_Scale_Y = table["Stone_Scale_Y"]["Value"].fVal;//��Q���̃��f���X�P�[����Y���W
		Stone_Scale_Z = table["Stone_Scale_Z"]["Value"].fVal;//��Q���̃��f���X�P�[����Z���W
		Stone_Rotation_X = table["Stone_Rotation_X"]["Value"].fVal;//��Q���̃��f���̉�]X���W
		Stone_Rotation_Y = table["Stone_Rotation_Y"]["Value"].fVal;//��Q���̃��f���̉�]Y���W
		Stone_Rotation_Z = table["Stone_Rotation_Z"]["Value"].fVal;//��Q���̃��f���̉�]Z���W
		//�D��x��ݒ�
		mPriority = STONE_PRIORITY;
		//�^�O�̐ݒ�
		mTag = CCharacter::ETag::ESTONE;
	}
	break;

	case CStone::EStoneType::ETYPE_STONE_POS_2:
	{
		OX::Table table(STONE_DATATABLE);
		Stone_Position_X = table["Stone_Position_X"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�X���W
		Stone_Position_Y = table["Stone_Position_Y"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�Y���W
		Stone_Position_Z = table["Stone_Position_Z"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�Z���W
		Stone_Scale_X = table["Stone_Scale_X"]["Value"].fVal;//��Q���̃��f���X�P�[����X���W
		Stone_Scale_Y = table["Stone_Scale_Y"]["Value"].fVal;//��Q���̃��f���X�P�[����Y���W
		Stone_Scale_Z = table["Stone_Scale_Z"]["Value"].fVal;//��Q���̃��f���X�P�[����Z���W
		Stone_Rotation_X = table["Stone_Rotation_X"]["Value"].fVal;//��Q���̃��f���̉�]X���W
		Stone_Rotation_Y = table["Stone_Rotation_Y"]["Value"].fVal;//��Q���̃��f���̉�]Y���W
		Stone_Rotation_Z = table["Stone_Rotation_Z"]["Value"].fVal;//��Q���̃��f���̉�]Z���W
		//�D��x��ݒ�
		mPriority = STONE_PRIORITY;
		//�^�O�̐ݒ�
		mTag = CCharacter::ETag::ESTONE;
	}
	break;

	case CStone::EStoneType::ETYPE_STONE_POS_3:
	{
		OX::Table table(STONE_DATATABLE);
		Stone_Position_X = table["Stone_Position_X"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�X���W
		Stone_Position_Y = table["Stone_Position_Y"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�Y���W
		Stone_Position_Z = table["Stone_Position_Z"]["Value"].fVal;//��Q���̃|�W�V�����ݒ�Z���W
		Stone_Scale_X = table["Stone_Scale_X"]["Value"].fVal;//��Q���̃��f���X�P�[����X���W
		Stone_Scale_Y = table["Stone_Scale_Y"]["Value"].fVal;//��Q���̃��f���X�P�[����Y���W
		Stone_Scale_Z = table["Stone_Scale_Z"]["Value"].fVal;//��Q���̃��f���X�P�[����Z���W
		Stone_Rotation_X = table["Stone_Rotation_X"]["Value"].fVal;//��Q���̃��f���̉�]X���W
		Stone_Rotation_Y = table["Stone_Rotation_Y"]["Value"].fVal;//��Q���̃��f���̉�]Y���W
		Stone_Rotation_Z = table["Stone_Rotation_Z"]["Value"].fVal;//��Q���̃��f���̉�]Z���W
		//�D��x��ݒ�
		mPriority = STONE_PRIORITY;
		//�^�O�̐ݒ�
		mTag = CCharacter::ETag::ESTONE;
	}
	break;
	}
}

//�Փˏ���
void CStone::Collision(CCollider* m, CCollider* o) {
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
void CStone::SetIsType(EStoneType type) {
	mStone_Type = type;
}

//�ʒu��ݒ肷��
void CStone::GetPos()
{
	
}
//�G�̃X�P�[�����擾
void CStone::GetScale()
{

}
//�G�̉�]�l���擾����
void CStone::GetRotation()
{

}


