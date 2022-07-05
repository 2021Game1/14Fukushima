//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include"CKey.h"
//�^�C��
#include<time.h>

//�^�X�N�}�l�[�W���N���X�̃C���N���[�h
#include"CTaskManager.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//��]���x
#define VELOCITY CVector(0.0f,0.0f,1.0f)//�ړ����x
#define MAX_VELOCITY 0.6f//�ō����x
#define _VELOCITY  0.0f//������



CPlayer* CPlayer::spInstance = nullptr;





//�f�t�H���g�R���X�g���N�^
CPlayer::CPlayer()
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f),
	mHp(10), mVelocity(_VELOCITY),mAcceleration(0.001f)
	
{
	//�e�N�X�`���t�@�C���̓ǂݍ���(1�s64��)
	mText.LoadTexture("FontGreen.tga", 1, 64);
	//�C���X�^���X�̐ݒ�
	spInstance = this;
	mTag = EPLAYER;
}

//�X�V����
void CPlayer::Update() 
{
	if (CKey::Push(VK_SPACE)) {
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
	}
	


		//W�L�[���͂őO�i
	if (CKey::Push('W')) {
		//Z�������̒l����]�����ړ�������
		if (mVelocity < 0.6f)
		{
			mVelocity += mAcceleration;
		}
		mPosition = mPosition + (VELOCITY * mVelocity) * mMatrixRotate;
	}
	else if (!CKey::Push('S')){
		if (mVelocity > 0.001f) {
			mVelocity -= mAcceleration;
			mPosition = mPosition + (VELOCITY * mVelocity) * mMatrixRotate;
		}
		mVelocity -= mAcceleration;
	}
	//A�L�[���͂ŉ�]
	if (CKey::Push('A') && mVelocity > _VELOCITY) {
		//Y���̉�]�l�𑝉�
		mRotation = mRotation  + ROTATION_YV;

	}
	//D�L�[���͂ŉ�]
	if (CKey::Push('D') && mVelocity > _VELOCITY) {
		//Y���̉�]�l������
		mRotation = mRotation - ROTATION_YV;
	}

	//S�L�[���͂Ō��
	if (CKey::Push('S')) {
		if (mVelocity > -0.1f) {
			mVelocity -= mAcceleration;
		}
		//Z�������̒l����]�����ړ�������
		mPosition = mPosition + (VELOCITY * mVelocity) * mMatrixRotate;
	
		//A�L�[���͂ŉ�]
		if (CKey::Push('A') && mVelocity <= _VELOCITY) {
			//Y���̉�]�l�𑝉�
			mRotation = mRotation + ROTATION_YV;

		}
		//D�L�[���͂ŉ�]
		if (CKey::Push('D') && mVelocity <= _VELOCITY) {
			//Y���̉�]�l������
			mRotation = mRotation - ROTATION_YV;
		}
	}
	else if (!CKey::Push('W')) {
		if (mVelocity < -0.001f) {
			mVelocity += mAcceleration;
			mPosition = mPosition + (VELOCITY * mVelocity) * mMatrixRotate;
		}
		mVelocity += mAcceleration;
	}


	//I�L�[�Ńu���[�L
	if (CKey::Push('I')) {
		if (mVelocity > 0.0f)
		{
			mVelocity -= mAcceleration + mAcceleration;
			mPosition = mPosition - (VELOCITY * mAcceleration) * mMatrixRotate;
		}
	}


	CTransform::Update();
}


//�Փˏ���
void CPlayer::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ESPHERE: {//���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			CCollider::CollisionTriangleSphere(o, m, &adjust);
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition + adjust;
			//�s��̍X�V
			CTransform::Update();
			
		}
		break;
	}
	}

}

//�Փˏ���
void CPlayer::TaskCollision() 
{
	//�R���C�_�̗D��x�ύX
	mCollider.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mCollider,COLLISIONRANGE);
}
void CPlayer::Render()
{
	//�e�̕`�揈��
	CCharacter::Render();

	//2D�̕`��J�n
	CUtil::Start2D(-400, 400, -300, 300);
	//�`��F�̐ݒ�(�ΐF�̔�����)
	glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
	//������ҏW�G���A�̍쐬
	char buf[64];
		//Y���W�̕\��
		//������̐ݒ�
		sprintf(buf, "PX:%7.2f", mPosition.X());
		//������̕`��
		mText.DrawString(buf, 150, 30, 8, 16);

		//Y���W�̕\��
		//������̐ݒ�
		sprintf(buf, "PZ:%7.2f", mPosition.Z());
		//������̕`��
		mText.DrawString(buf, 150, 0, 8, 16);

	

	//2D�̕`��I��
	CUtil::End2D();
}
CPlayer* CPlayer::Get() {
	return spInstance;
}