//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
//�L�[���̓N���X�̃C���N���[�h
#include"CKey.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//��]���x
#define VELOCITY CVector(0.0f,0.0f,0.1f)//�ړ����x

//�X�V����
void CPlayer::Update() {
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
	//�ϊ��s��̍X�V
	CTransform::Update();
}