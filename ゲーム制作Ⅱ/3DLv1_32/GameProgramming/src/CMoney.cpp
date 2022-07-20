#include "CMoney.h"
#include <time.h>


#define OBJ "res\\goldbar.obj" //���f���̃t�@�C��
#define MTL "res\\goldbar.mtl" //���f���̃}�e���A���t�@�C��


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

	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
}







//�R���X�g���N�^
//CMoney(�ʒu,��],�g�k)
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
				mMoney = mMoney + 1;
			}
			break;
		}
	}
	
}

void CMoney::Update() {
		if (mRepop % 100 == 50) {
			//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
			srand((unsigned)time(NULL));
			vel = (rand() % 100) + 1;
			for (int i = 0; i < 1; i++) {
				if (vel >= 0 && vel <= 7) {
					new CMoney(CVector(75.0f, -0.5f, 76.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 8 && vel <= 15) {
					new CMoney(CVector(71.0f, -0.5f, 153.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 16 && vel <= 23) {
					new CMoney(CVector(0.0f, -0.5f, 159.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 24 && vel <= 31) {
					new CMoney(CVector(-61.5f, -0.5f, 158.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 32 && vel <= 39) {
					new CMoney(CVector(-60.0f, -0.5f, 105.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 40 && vel <= 47) {
					new CMoney(CVector(-16.0f, -0.5f, 0.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 48 && vel <= 55) {
					new CMoney(CVector(25.0f, -0.5f, 49.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 56 && vel <= 63) {
					new CMoney(CVector(73.5f, -0.5f, -35.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 64 && vel <= 71) {
					new CMoney(CVector(-63.0f, -0.5f, -30.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 78 && vel <= 85) {
					new CMoney(CVector(-100.0f, -0.5f, 35.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 86 && vel <= 93) {
					new CMoney(CVector(20.0f, -0.5f, 58.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
			for (int i = 0; i < 1; i++) {
				if (vel >= 94 && vel <= 101) {
					new CMoney(CVector(50.0f, -0.5f, 50.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
				}
			}
		}
		mRepop = mRepop + 1;

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


