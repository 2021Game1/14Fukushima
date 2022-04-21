//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include"CKey.h"
//�^�X�N�}�l�[�W���N���X�̃C���N���[�h
#include"CTaskManager.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//��]���x
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//��]���x
#define VELOCITY CVector(0.0f,0.0f,0.1f)//�ړ����x


CPlayer* CPlayer::spInstance = nullptr;

//�f�t�H���g�R���X�g���N�^
CPlayer::CPlayer()
	:mLine(this, &mMatrix, CVector(0.0f, 0.0f, -14.0f), CVector(0.0f, 0.0f, 17.0f)),
	mLine2(this, &mMatrix, CVector(0.0f, 5.0f, -8.0f), CVector(0.0f, -3.0f, -8.0f)),
	mLine3(this, &mMatrix, CVector(9.0f, 0.0f, -8.0f), CVector(-9.0f, 0.0f, -8.0f)),
	mCollider(this, &mMatrix, CVector(0.0f, 0.0f, 0.0f), 0.5f),
	mHp(10)
{
	//�e�N�X�`���t�@�C���̓ǂݍ���(1�s64��)
	mText.LoadTexture("FontWhite.tga", 1, 64);

	//�C���X�^���X�̐ݒ�
	spInstance = this;
	mTag = EPLAYER;
}

//�X�V����
void CPlayer::Update() 
{

	//�X�y�[�X�L�[����͂Œe�𔭎�
	//�X�y�[�X�L�[����͂Œe�𔭎�
	if (CKey::Push(VK_SPACE)) {
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
	//TaskManager.Add(bullet);
	}
	//D�L�[���͂ŉ�]
	if (CKey::Push('D')) {
		//Y���̉�]�l������
		mRotation = mRotation - ROTATION_YV;
	}
	//A�L�[���͂ŉ�]
	if (CKey::Push('A')) {
		//Y���̉�]�l�𑝉�
		mRotation = mRotation + ROTATION_YV;
	}
	//I�L�[���͂őO�i
	if (CKey::Push('I')){
		//Z�������̒l����]�����ړ�������
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	//S�L�[���͂ŏ����
	if (CKey::Push('S'))
	{
		//X���̉�]�l�����Z
		mRotation = mRotation - ROTATION_XV;
	}
	//W�L�[���͂ŉ�����
	if (CKey::Push('W'))
	{
		//X���̉�]�l�����Z
		mRotation = mRotation + ROTATION_XV;
	}
	CTransform::Update();
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
		//���~������
		mPosition = mPosition - CVector(0.0f, 0.03f, 0.0f);
		CTransform::Update();
		return;
	}
}


//�Փˏ���
void CPlayer::Collision(CCollider* m, CCollider* o) {
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ELINE: {//�����R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			//�O�p�`�Ɛ����̏Փ˔���
			CCollider::CollisionTriangleLine(o, m, &adjust);
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition + adjust;
			//�s��̍X�V
			CTransform::Update();
		}
		break;
	}
	}
	switch (o->Type()) {
	case CCollider::ESPHERE: { //���R���C�_�̎�
				//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::Collision(m, o)) {
			//�G�t�F�N�g����
			new CEffect(o->Parent()->Position(), 1.0f, 1.0f, "exp.tga", 4, 4, 2);
			if (mHp >= 0)
			{
				mHp--;
			}
		}
		break;
	}
	}
	
}

//�Փˏ���
void CPlayer::TaskCollision() 
{
	//�R���C�_�̗D��x�ύX
	mLine.ChangePriority();
	mLine2.ChangePriority();
	mLine3.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mLine,COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine2, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mLine3, COLLISIONRANGE);
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
	sprintf(buf, "PY:%7.2f", mPosition.Y());
	//������̕`��
	mText.DrawString(buf, 100, 30, 8, 16);

	//X����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RX:%7.2f", mRotation.X());
	//������̕`��
	mText.DrawString(buf, 100, 0, 8, 16);

	//Y����]�l�̕\��
	//������̐ݒ�
	sprintf(buf, "RY:%7.2f", mRotation.Y());
	//������̕`��
	mText.DrawString(buf, 100, -100, 8, 16);

	//2D�̕`��I��
	CUtil::End2D();
}
CPlayer* CPlayer::Get() {
	return spInstance;
}