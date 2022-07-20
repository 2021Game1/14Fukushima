//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include"CKey.h"
//�^�C��
#include<time.h>

//�^�X�N�}�l�[�W���N���X�̃C���N���[�h
#include"CTaskManager.h"

#define ROTATION_YV CVector(0.0f,1.1f,0.0f)//��]���x
#define VELOCITY CVector(0.0f,0.0f,1.0f)//�ړ����x
#define MAX_VELOCITY 0.4f//�ō����x
#define _VELOCITY  0.0f//������
#define ACCELERATION 0.001f    //�����x


CPlayer* CPlayer::spInstance = nullptr;





//�f�t�H���g�R���X�g���N�^
CPlayer::CPlayer()
	:mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f),
	mHp(10), Velocity(_VELOCITY),Acceleration(ACCELERATION)
	
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
		if (Velocity < MAX_VELOCITY)
		{
			Velocity += Acceleration;
		}
		mPosition = mPosition + (VELOCITY * Velocity) * mMatrixRotate;
	}
	else if (!CKey::Push('S')){
		if (Velocity > 0.001f) {
			Velocity -= Acceleration;
			mPosition = mPosition + (VELOCITY * Velocity) * mMatrixRotate;
		}
		Velocity -= Acceleration;
	}
	//A�L�[���͂ŉ�]
	if (CKey::Push('A') && Velocity > _VELOCITY) {
		//Y���̉�]�l�𑝉�
		mRotation = mRotation  + ROTATION_YV;

	}
	//D�L�[���͂ŉ�]
	if (CKey::Push('D') && Velocity > _VELOCITY) {
		//Y���̉�]�l������
		mRotation = mRotation - ROTATION_YV;
	}

	//S�L�[���͂Ō��
	if (CKey::Push('S')) {
		if (Velocity > -0.1f) {
			Velocity -= Acceleration;
		}
		//Z�������̒l����]�����ړ�������
		mPosition = mPosition + (VELOCITY * Velocity) * mMatrixRotate;
	
		//A�L�[���͂ŉ�]
		if (CKey::Push('A') && Velocity <= _VELOCITY) {
			//Y���̉�]�l�𑝉�
			mRotation = mRotation + ROTATION_YV;

		}
		//D�L�[���͂ŉ�]
		if (CKey::Push('D') && Velocity <= _VELOCITY) {
			//Y���̉�]�l������
			mRotation = mRotation - ROTATION_YV;
		}
	}
	else if (!CKey::Push('W')) {
		if (Velocity < -0.001f) {
			Velocity += Acceleration;
			mPosition = mPosition + (VELOCITY * Velocity) * mMatrixRotate;
		}
		Velocity += Acceleration;
	}


	//I�L�[�Ńu���[�L
	if (CKey::Push('I')) {
		if (Velocity > 0.0f)
		{
			Velocity -= Acceleration + Acceleration;
			mPosition = mPosition - (VELOCITY * Acceleration) * mMatrixRotate;
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