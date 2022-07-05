#include "CMoney.h"


#define OBJ "res\\money.obj" //���f���̃t�@�C��
#define MTL "res\\money.mtl" //���f���̃}�e���A���t�@�C��


CModel CMoney::mModel;//���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CMoney::CMoney()
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.4f)
{
	//���f�����������͓ǂݍ���
	if (mModel.Triangles().size() == 0)
	{
		mModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;
}

//�R���X�g���N�^
//CEnemy(�ʒu,��],�g�k)
CMoney::CMoney(const CVector& position, const CVector& rotation, const CVector& scale)
	:CMoney()	//�f�t�H���g�R���X�g���N�^�����s����
{
	//�ʒu,��],�g�k��ݒ肷��
	mPosition = position;	//�ʒu�̐ݒ�
	mRotation = rotation;	//��]�̐ݒ�
	mScale = scale;			//�g�k�̐ݒ�
	CTransform::Update();	//�s��̍X�V

	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}

//�Փˏ���
//Collision(�R���C�_1,�R���C�_2)
void CMoney::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
		case CCollider::ESPHERE: { //���R���C�_�̎�
			//�R���C�_��m��o���Փ˂��Ă��邩�̔���
			if (CCollider::Collision(m, o)) {
				//�G�t�F�N�g����
				new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
				mEnabled = false;
			}
			break;
		}
	}
	
}

void CMoney::Update() {
		mRotation = mRotation + CVector(0.0f, -1.0f, 0.0f);//�E�։�]
		CTransform::Update();
}

void CMoney::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}