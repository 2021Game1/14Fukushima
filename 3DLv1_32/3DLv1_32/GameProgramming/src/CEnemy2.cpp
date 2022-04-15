#include"CEnemy2.h"

#define OBJ "res\\f16.obj" //���f���̃t�@�C��
#define MTL "res\\f16.mtl" //���f���̃}�e���A���t�@�C��

CModel CEnemy2::sModel;//���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy2::CEnemy2()
:mCollider(this, &mMatrix,CVector(0.0f,0.0f,0.0f),0.4f)
{
	//���f�����������͓ǂݍ���
	if (sModel.Triangles().size() == 0)
	{
		sModel.Load(OBJ, MTL);
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &sModel;
}
//�R���X�g���N�^
//CEnemy(�ʒu,��],�g�k)
CEnemy2::CEnemy2(const CVector& position,const CVector& rotation,const CVector& scale)
:CEnemy2()	//�f�t�H���g�R���X�g���N�^�����s����
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
//�X�V����
void CEnemy2::Update()
{

}
//�Փˏ���
//Collision(�R���C�_1,�R���C�_2)
void CEnemy2::Collision(CCollider* m, CCollider* o)
{
	//����̃R���C�_�^�C�v�̔���
	switch (o->Type())
	{
	case CCollider::ESPHERE: { //���R���C�_�̎�
			//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			//�Փ˂��Ă��鎞�͖����ɂ���
			//�폜mEnabled = false;
		}
		break;
	}

	case CCollider::ETRIANGLE: { //�O�p�R���C�_�̎�
		CVector adjust; //�����l
		//�O�p�R���C�_�Ƌ��R���C�_�̏Փ˔���
		if (CCollider::CollisionTriangleSphere(o, m, &adjust))
		{
			//�Փ˂��Ȃ��ʒu�܂Ŗ߂�
			mPosition = mPosition + adjust;
		}
		break;
	}

	}
}
void CEnemy2::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}