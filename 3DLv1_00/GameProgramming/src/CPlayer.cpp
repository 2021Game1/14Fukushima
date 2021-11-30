//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include"CKey.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//��]���x
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//��]���x
#define VELOCITY CVector(0.0f,0.0f,0.1f)//�ړ����x
#

//�X�V����
void CPlayer::Update() {
	//�X�y�[�X�L�[����͂Œe�𔭎�
	//�X�y�[�X�L�[����͂Œe�𔭎�
	if (CKey::Push(VK_SPACE)){
		CBullet* bullet = new CBullet();
		bullet->Set(0.1f, 1.5f);
		bullet->Position(CVector(0.0f, 0.0f, 10.0f) * mMatrix);
		bullet->Rotation(mRotation);
		bullet->Update();
		TaskManager.Add(bullet);
		
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
	//�ϊ��s��̍X�V
	CTransform::Update();
}