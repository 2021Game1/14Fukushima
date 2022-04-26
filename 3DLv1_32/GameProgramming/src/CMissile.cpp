#include "CMissile.h"

#define OBJ "res\\missile.obj" //���f���̃t�@�C��
#define MTL "res\\missile.mtl" //���f���̃}�e���A���t�@�C��

CModel CMissile::cpModel;//���f���f�[�^�쐬



CMissile::CMissile()
:mLife(90),mCollider1(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.2f)
	, mCollider2(this, &mMatrix, CVector(0.0f, 0.0f, 1.5f), 0.2f)
	, mCollider3(this, &mMatrix, CVector(0.0f, 0.0f, -2.0f), 0.2f)
{
	//���f�����������͓ǂݍ���
	if (cpModel.Triangles().size() == 0) {
		cpModel.Load(OBJ, MTL);
		//���f���̃|�C���^�ݒ�
		mpModel = &cpModel;
	}
}

//�R���X�g���N�^
//CEnemy(�ʒu,��],�g�k)
CMissile::CMissile(const CVector& position, const CVector& rotation, const CVector& scale)
: CMissile()	//�f�t�H���g�R���X�g���N�^�����s����
{
	//�ʒu,��],�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	//�D��x��1�ɕύX����
	mPriority = 2;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}



//�X�V����
void CMissile::Update() {
	////�������Ԃ̔���
	//if (mLife-- > 0)
	//{
	//	CTransform::Update();
	//	//�ʒu�X�V
	//	mPosition = CVector(0.0f, -0.1f, 0.9f) * mMatrix;
	//}
	//else {
	//	//�����ɂ���
	//	mEnabled = false;
	//}
	CTransform::Update();
}


//�Փˏ���
//Collision(�R���C�_1,�R���C�_2)
void CMissile::Collision(CCollider* m, CCollider* o) {
	//�R���C�_��m��o���Փ˂��Ă��邩�𔻒�
	if (CCollider::Collision(m, o)) {
		//�Փ˂��Ă��鎞�͖����ɂ���
		mEnabled = false;
	}
}

//�Փˏ���
void CMissile::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mCollider1.ChangePriority();
	mCollider2.ChangePriority();
	mCollider3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider1, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mCollider3, COLLISIONRANGE);

}