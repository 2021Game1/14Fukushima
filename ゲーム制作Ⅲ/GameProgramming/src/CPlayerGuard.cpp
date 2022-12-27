#include"CPlayerGuard.h"

CPlayerGuard* CPlayerGuard::mpPlayerGuard_Instance = nullptr;												//プレイヤのインスタンス変数の初期化

void CPlayerGuard::Init(CModel* model)
{
	CCharacter::Model(model);
}
void CPlayerGuard::Update()
{
	CVector mGuardPosition = CXPlayer::GetInstance()->Position() + CVector(0.0f, 1.0f, 0.0f);
	mPosition = mGuardPosition;
	//拡縮,回転の設定
	mScale.Set(0.3f, 0.3f, 0.3f);										//スケール設定
	mRotation.Set(0.0f, 180.0f, 0.0f);								//回転を設定
	//行列の更新
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

//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CPlayerGuard* CPlayerGuard::GetInstance()
{
	return mpPlayerGuard_Instance;
}