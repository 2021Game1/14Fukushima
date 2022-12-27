#include"CPlayerGuard.h"

CPlayerGuard* CPlayerGuard::mpPlayerGuard_Instance = nullptr;												//�v���C���̃C���X�^���X�ϐ��̏�����

void CPlayerGuard::Init(CModel* model)
{
	CCharacter::Model(model);
}
void CPlayerGuard::Update()
{
	CVector mGuardPosition = CXPlayer::GetInstance()->Position() + CVector(0.0f, 1.0f, 0.0f);
	mPosition = mGuardPosition;
	//�g�k,��]�̐ݒ�
	mScale.Set(0.3f, 0.3f, 0.3f);										//�X�P�[���ݒ�
	mRotation.Set(0.0f, 180.0f, 0.0f);								//��]��ݒ�
	//�s��̍X�V
	CTransform::Update();
}

void CPlayerGuard::Render()
{
	if (!CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EGUARD)
	{
		mEnabled = false;
		return;
	}
	else if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EGUARD)
	{
		CCharacter::Render();
		mEnabled = true;
		return;
	}
}

//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CPlayerGuard* CPlayerGuard::GetInstance()
{
	return mpPlayerGuard_Instance;
}