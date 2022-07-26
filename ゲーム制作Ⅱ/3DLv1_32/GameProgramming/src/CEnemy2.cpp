#include"CEnemy2.h"
//�v���C���[�N���X�̃C���N���[�h
#include "CPlayer.h"

#define OBJ "res\\Police.obj" //���f���̃t�@�C��
#define MTL "res\\Police.mtl" //���f���̃}�e���A���t�@�C��
#define HP 3	//�ϋv�l
#define VELOCITY 0.18f	   //���x
#define _VELOCITY 0.0f //������
#define ACCELERATION 0.01f    //�����x

CModel CEnemy2::sModel;//���f���f�[�^�쐬

//�f�t�H���g�R���X�g���N�^
CEnemy2::CEnemy2()
:mCollider(this, &mMatrix,CVector(0.0f,2.0f,0.0f),0.4f),mHp(HP),mVelocity(_VELOCITY),mAcceleration(ACCELERATION)
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
	//�ڕW�n�_�̐ݒ�
	mPoint = mPosition + CVector(0.0f, 0.0f, 100.0f) * mMatrixRotate;
	//�D��x��1�ɕύX����
	mPriority = 1;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
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
			//�s��̍X�V
			CTransform::Update();
		}

		break;
	}

	}
}
//�X�V����
void CEnemy2::Update()
{
	//������(X��)�̃x�N�g�������߂�
	CVector vx = CVector(1.0f, 0.0f, 0.0f) * mMatrixRotate;
	//�����(Y��)�̃x�N�g�������߂�
	CVector vy = CVector(0.0f, 1.0f, 0.0f) * mMatrixRotate;
	//�O����(Z��)�̃x�N�g�������߂�
	CVector vz = CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
	//�v���C���[�̃|�C���^��0�ȊO�̎�
	CPlayer* player = CPlayer::Get();
	if (player != nullptr)
	{
		//�v���C���[�܂ł̃x�N�g�������߂�
		CVector vp = player->Position() - mPosition;
		float dx = vp.Dot(vx); //���x�N�g���Ƃ̓��ς����߂�
		float dy = vp.Dot(vy); //��x�N�g���Ƃ̓��ς����߂�
		float dz = vp.Dot(vz); //�O�����̃x�N�g���Ƃ̓��ς����߂�
		if (0.0f < dz && dz < 30.0f)
		{
			//X���̃Y����2.0�ȉ�
			if (-2.0f < dx && dx < 2.0f)
			{
				if (-2.0f < dz && dz < 2.0f) {
					//�e�𔭎˂��܂�
					CBullet* bullet = new CBullet();
					bullet->Set(0.1f, 1.5f);
					bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
					bullet->Rotation(mRotation);
					bullet->Update();
				}
			}
		}
	}
	//�ڕW�n�_�܂ł̃x�N�g�������߂�
	CVector vp = mPoint - mPosition;
	float dx = vp.Dot(vx); //���x�N�g���Ƃ̓��ς����߂�
	float dy = vp.Dot(vy); //��x�N�g���Ƃ̓��ς����߂�
	float margin = 0.1f;
	//���E�����ւ̉�]
	if (dx > margin)
	{
		mRotation = mRotation + CVector(0.0f, 1.2f, 0.0f);//���։�]
	}
	//���E�����ւ̉�]
	else if (dx < -margin)
	{
		mRotation = mRotation + CVector(0.0f, -1.2f, 0.0f);//�E�։�]
	}
	////�㉺�����։�]
	//if (dy > margin)
	//{
	//	mRotation = mRotation + CVector(-1.0f, 0.0f, 0.0f);//���
	//}
	//else if (dy < -margin)
	//{
	//	mRotation = mRotation + CVector(1.0f, 0.0f, 0.0f);//����
	//}

	if (mVelocity < 1.7f){
		mVelocity = mVelocity + mAcceleration;
	}
	mPosition = mPosition + (CVector(0.0f,0.0f, VELOCITY) * mVelocity) * mMatrixRotate;


	
	CTransform::Update();
	//���悻3�b���ɖڕW�n�_���X�V
	int r = rand() % 180; //rand()�͐����̗�����Ԃ�
						  //%180��180�Ŋ������]������߂�
	if (r == 0)
	{
		if (player != nullptr)
		{
			mPoint = player->Position();
		}
		else
		{
			mPoint = mPoint * CMatrix().RotateY(45);
		}
	}
	//HP��0�ȉ��̎��@���j
	if (mHp <= 0)
	{
		mHp--;
		//15�t���[�����ɃG�t�F�N�g
		if (mHp % 15 == 0)
		{
			//�G�t�F�N�g����
			new CEffect(mPosition, 1.0f, 1.0f, "exp.tga", 4, 4, 2);
		}
		////���~������
		//mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		//CTransform::Update();
		//return;
	}
}
void CEnemy2::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider, COLLISIONRANGE);
}