#include"CXPlayer.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CCamera.h"
#include"CRes.h"

CXPlayer* CXPlayer::mpPlayer_Instance = nullptr;												//�v���C���̃C���X�^���X�ϐ��̏�����

CXPlayer::CXPlayer()
//�v���C���̕ϐ��̏�����
	: mPlayer_ColCapsuleBody(this, nullptr, CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_Y, PLAYER_COLCAPSULE_BODY_Z), CVector(PLAYER_COLCAPSULE_BODY_X, -PLAYER_COLCAPSULE_BODY_Y, PLAYER_COLCAPSULE_BODY_Z), PLAYER_COLCAPSULE_BODY_SIZE)
	, mPlayer_ColSphereBody(this, nullptr, CVector(), PLAYER_COLSPHERE_BODY_SIZE)
	, mPlayer_ColSphereShield(this, nullptr, CVector(PLAYER_COLSPHERE_SHIELD_X, PLAYER_COLSPHERE_SHIELD_Y, PLAYER_COLSPHERE_SHIELD_Z), PLAYER_COLSPHERE_SHIELD_SIZE)
	, mPlayer_ColSphereSword(this, nullptr, CVector(PLAYER_COLSPHERE_SWORD_HEAD_X, PLAYER_COLSPHERE_SWORD_HEAD_Y, PLAYER_COLSPHERE_SWORD_HEAD_Z), PLAYER_COLSPHERE_SWORD_SIZE)
	, mPlayer_Speed(PLAYER_SPEED_DEFAULT)
	, mPlayer_Hp(PLAYER_HP)
	, mPlayer_ComboCount(PLAYER_INT_INITIALIZATION)
	, mPlayer_Turnspeed(PLAYER_FLOAT_INITIALIZATION)
	, mPlayer_InvincibleFlag(false)
	, mPlayer_IsHit(false)
	, mPlayer_AttackFlag_1(false)
	, mPlayer_AttackFlag_2(false)
	, mPlayer_AttackFlag_3(false)
	, mPlayer_SeFlag(false)
	, mPlayer_AttackFlag_Once(false)
	, mPlayer_Flag(false)
	, mPlayer_FollowGaugeWid(PLAYER_GAUGE_WID_MAX)

{
	//�v���C���̃C���X�^���X��ݒ�
	mpPlayer_Instance = this;										//�v���C���̃C���X�^���X�����g�ɐݒ肷��
	//�^�O�̕R�Â�
	mTag = EPLAYER;													//�^�O���v���C���ɐݒ�
	//������Ԃ�ݒ�
	mPlayer_State = EIDLE;											//�v���C���̏�����Ԃ�ҋ@��Ԃɐݒ肷��
	//�R���C�_�̃^�O��ݒ�
	mPlayer_ColCapsuleBody.Tag(CCollider::EBODY);					//��
	mPlayer_ColSphereBody.Tag(CCollider::EBODY);					//��
	mPlayer_ColSphereShield.Tag(CCollider::ESHIERD);				//��
	mPlayer_ColSphereSword.Tag(CCollider::ESWORD);					//��
	//�D��x��1�ɕύX����
	mPriority = PLAYER_PRIORITY;
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mPlayer_ColCapsuleBody.Matrix(&mpCombinedMatrix[14]);
	mPlayer_ColSphereBody.Matrix(&mpCombinedMatrix[16]);
	mPlayer_ColSphereShield.Matrix(&mpCombinedMatrix[41]);
	mPlayer_ColSphereSword.Matrix(&mpCombinedMatrix[71]);
	//�v���C���̈ʒu,�g�k,��]�̐ݒ�
	mPosition.Set(0.0f, 0.0f, 20.0);									//�ʒu��ݒ�
	mScale.Set(2.0f,2.0f,2.0f);										//�X�P�[���ݒ�
	mRotation.Set(0.0f, 180.0f, 0.0f);								//��]��ݒ�
}

void CXPlayer::Update() {
	//���R���C�_�̍��W���Q��
	CVector tpos = mPlayer_ColSphereSword.GetIsMatrix()->GetPos();
	//��Ԃ𔻕�
	switch (mPlayer_State) {
	case EIDLE:														//�ҋ@���
		Idle();														//�ҋ@�������Ă�
		break;

	case EATTACK_1:													//�U��1��Ԃ̎�
		Attack_1();													//�U��1�̏������Ă�
		break;

	case EATTACK_2:													//�U��2��Ԃ̎�
		Attack_2();													//�U��2�̏������Ă�
		break;

	case EATTACK_3:													//�U��3��Ԃ̎�
		Attack_3();													//�U��3�̏������Ă�
		break;

	case EMOVE:														//�ړ����
		Move();														//�ړ���Ԃ̏������Ă�
		break;

	case EAVOIDANCE:												//������
		Avoidance();												//����������Ă�
		break;

	case EDEATH:													//���S���
		Death();													//���S�������Ă�
		break;

	case EKNOCKBACK:												//�m�b�N�o�b�N���
		KnockBack();												//�m�b�N�o�b�N�������Ă�
		break;
	}
	MovingCalculation();
	//�̗͂�0�ɂȂ�Ǝ��S
	if (mPlayer_Hp <= 0) {
		mPlayer_State = EDEATH;										//���S��Ԃֈڍs
		mPlayer_Hp = 0;
	}
	//�J�����̐ݒ�
	Camera.SetTarget(mPosition);									//�J�������v���C���̈ʒu�ɐݒ�
	//�L�����N�^�̍X�V����
	CXCharacter::Update();
}

void CXPlayer::Idle() 
{
	mPlayer_ComboCount = PLAYER_INT_INITIALIZATION;
	ChangeAnimation(PLAYER_ANIMATION_No_IDLE, true, 20);
	//���N���b�N�ōU��
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//WASD�L�[�������ƈړ��ֈڍs
	if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mPlayer_State = EMOVE;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
}

//�ړ�����
void CXPlayer::Move()
{
	//���N���b�N�ōU��1�ֈڍs
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	} 
	else if (CKey::Push('W') && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	else if (CKey::Push('A') && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	else if (CKey::Push('S') && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	else if (CKey::Push('D') && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	//WASD�L�[�������ƈړ��ֈڍs
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		ChangeAnimation(PLAYER_ANIMATION_No_MOVE, true, 45);
		MoveCamera();												//�J��������ɂ����ړ��������Ă�
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	//�ҋ@��Ԃֈڍs
	else {
		mPlayer_State = EIDLE;
	}

	if (mPlayer_State != EMOVE) {
		CRes::GetInstance()->GetinPlayerSeWalk().Stop();
	}




}

void CXPlayer::Avoidance()
{
	ChangeAnimation(PLAYER_ANIMATION_No_AVOIDANCE, true, 50);
	//���W�ړ�
	mPosition += mPlayer_Move;												//�v���C���̈ʒu�Ƀv���C���̈ړ��ʂ𑫂�
	//����������
	mPlayer_Move = mPlayer_MoveDirKeep * PLAYER_THRUST;							//�v���C���̈ړ��ʂɐ��͂��|����

	//�q�b�g���蔭��
	if (IsAnimationFinished() == false)
	{
		MoveCamera();
	}
	//�A�j���[�V�����I����
	else if (IsAnimationFinished())
	{
		mPlayer_State = EIDLE;
	}
	if (mPlayer_State != EAVOIDANCE) {
		CRes::GetInstance()->GetinPlayerSeWalk().Stop();
	}
}


//�U��1����
void CXPlayer::Attack_1()
{
	//�������Ăяo���ꂽ��1�x�����������Ȃ�
	if (mPlayer_AttackFlag_1 == false) {							
		mPlayer_AttackFlag_1 = true;								//�v���C���̍U��1�̃t���O��true�ɂ���
		mPlayer_AttackFlag_Once = true;								//�v���C���̍U���t���O��true�ɐݒ�
		ChangeAnimation(PLAYER_ANIMATION_No_IDLE, false, 1);								//�ҋ@���[�V����
	}
	//�A�j���[�V�����C���f�b�N�X���T�̎�
	if (mAnimationIndex == PLAYER_ANIMATION_No_IDLE)
	{
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_1, false, 50);							//�v���C���̍U��1���[�V����
			CRes::GetInstance()->GetinPlayerSeAttackSp1().Play(0.1);
		}
	}
	//�A�j���[�V�����C���f�b�N�X���R�̎�
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_3) {
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false)
		{
			//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
			if (mAnimationFrame <= PLAYER_INRECEPTION)
			{
				mPlayer_IsHit = false; //�q�b�g����I��
			}
			//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
			else {
				mPlayer_IsHit = true;
			}
			//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
			if (mAnimationFrame > PLAYER_OUTRECEPTION)
			{
				mPlayer_IsHit = false; //�q�b�g����I��
			}

			if (CKey::Push('W') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('A') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('S') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('D') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_1, false, 60);							//�v���C���̍U��1���[�V����
			CRes::GetInstance()->GetinPlayerSeAttackSp1().Play(0.1);
		}
	}
	//�A�j���[�V�����C���f�b�N�X���P�̎�
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_1)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false)
		{
			if (CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EKNOCKBACK && CXEnemy::EEnemyState::EIDLE)
			{
				mPlayer_IsHit = false;
			}
			else {
				mPlayer_IsHit = true;
			}
			if (CKey::Push('W') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('A') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('S') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('D') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{	
			mPlayer_IsHit = false;								//�q�b�g����I��
		}
		//�A�j���[�V�����̃t���[������t���Ԃ�菬������
		if (mAnimationFrame < PLAYER_RECEPTION) {
			//���N���b�N���ꂽ�ꍇ
			if (CKey::Once(VK_LBUTTON)) {
				mPlayer_State = EATTACK_2;							//�U��2���[�V�����ֈڍs
			}
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
	mPlayer_State = EIDLE;											//�ҋ@��Ԃֈڍs
	mPlayer_AttackFlag_1 = false;									//�v���C���̍U��1�t���O��false�ɂ���
	}
}

//�U��2����
void CXPlayer::Attack_2()
{
	//�������Ăяo���ꂽ��1�x�����������Ȃ�
	if (mPlayer_AttackFlag_2 == false) {
		mPlayer_AttackFlag_2 = true;								//�v���C���̍U��2�̃t���O��true�ɂ���
		mPlayer_AttackFlag_Once = true;								//�v���C���̍U���t���O��true�ɐݒ�
	}
	//�A�j���[�V�����C���f�b�N�X��1�̎�
	if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_1)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) 
		{
			//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
			if (mAnimationFrame <= PLAYER_INRECEPTION)
			{
				mPlayer_IsHit = false; //�q�b�g����I��
			}
			//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
			else {
				mPlayer_IsHit = true;
			}
			//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
			if (mAnimationFrame > PLAYER_OUTRECEPTION)
			{
				mPlayer_IsHit = false; //�q�b�g����I��
			}
			if (CKey::Push('W') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('A') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('S') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('D') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
		}
		//�A�j���[�V�����I����
		else if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_2, false, 70);							//�v���C���̍U��2���[�V����
			CRes::GetInstance()->GetinPlayerSeAttackSp2().Play(0.1);
		}
	}
	//�A�j���[�V�����C���f�b�N�X��2�̎�
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_2)
	{
		//�A�j���[�V�����̃t���[������t���Ԃ�菬������
		if (mAnimationFrame < PLAYER_RECEPTION) {
			//���N���b�N���ꂽ�ꍇ
			if (CKey::Once(VK_LBUTTON)) {
				mPlayer_State = EATTACK_3;							//�U��3���[�V�����ֈڍs
			}
		}
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
	mPlayer_State = EIDLE;											//�ҋ@��Ԃֈڍs
	mPlayer_AttackFlag_2 = false;									//�v���C���̍U��2�t���O��false�ɂ���
	}
}

//�U��3����
void CXPlayer::Attack_3()
{
	//�������Ăяo���ꂽ��1�x�����������Ȃ�
	if (mPlayer_AttackFlag_3 == false) {
		mPlayer_AttackFlag_3 = true;								//�v���C���̍U��2�̃t���O��true�ɂ���								
		mPlayer_AttackFlag_Once = true;								//�v���C���̍U���t���O��true�ɐݒ�
	}
	if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_2)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) 
		{
			//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
			if (mAnimationFrame <= PLAYER_INRECEPTION)
			{
				mPlayer_IsHit = false; //�q�b�g����I��
			}
			//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
			else {
				mPlayer_IsHit = true;
			}
			//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
			if (mAnimationFrame > PLAYER_OUTRECEPTION)
			{
				mPlayer_IsHit = false; //�q�b�g����I��
			}
			if (CKey::Push('W') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('A') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('S') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
			else if (CKey::Push('D') && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
			}
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_3, false, 80);
			CRes::GetInstance()->GetinPlayerSeAttackSp3().Play(0.1);
		}
	}
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_3)
	{
		if (mAnimationFrame < PLAYER_RECEPTION) 
		{
			//���N���b�N���ꂽ�ꍇ
			if (CKey::Once(VK_LBUTTON)) 
			{
				mPlayer_State = EATTACK_1;							//�U��1���[�V�����ֈڍs
			}
		}
	}

	if (IsAnimationFinished())
	{
	mPlayer_State = EIDLE;											//�ҋ@��Ԃֈڍs
	mPlayer_AttackFlag_3 = false;									//�v���C���̍U��3�̃t���O��false�ɐݒ�
	}
}
//�m�b�N�o�b�N����
void CXPlayer::KnockBack()
{
	ChangeAnimation(PLAYER_ANIMATION_No_KNOCKBACK, false, 60);	//�̂�����A�j���[�V����

	if (IsAnimationFinished() == true)
	{
		mPlayer_IsHit = false;
	}
	if (CXEnemy::GetInstance()->GetIsHit() == true)
	{
		if (mPlayer_Flag == false)
		{
			mPlayer_Flag = true;
			if (CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EATTACK_1)
			{
				mPlayer_Hp = mPlayer_Hp - 15;
			}
			else if (CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EATTACK_2)
			{
				mPlayer_Hp = mPlayer_Hp - 10;
			}
			else if (CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EATTACK_3)
			{
				mPlayer_Hp = mPlayer_Hp - 20;
			}
		}
	}

	if (CKey::Push('W') && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	else if (CKey::Push('A') && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	else if (CKey::Push('S') && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	else if (CKey::Push('D') && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(0.1);
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		mPlayer_State = EIDLE; //�ҋ@��Ԃֈڍs
	}
}

//���S����
void CXPlayer::Death()
{
	MovingCalculation();
	ChangeAnimation(PLAYER_ANIMATION_No_DEATH, false, 60);	//���S�A�j���[�V����
}

//�J��������ɂ����ړ�����
void CXPlayer::MoveCamera()
{
	//�J�������_�ړ��@�ʏ̖��o�ړ�
	//�J�����̍��E�ƑO��̃x�N�g�����擾
	mPlayer_SideVec = Camera.GetMat().GetXVec();
	mPlayer_FrontVec = Camera.GetMat().GetZVec();
	//�����ړ��̓J�b�g����
	mPlayer_SideVec.Y(0.0f);
	mPlayer_FrontVec.Y(0.0f);
	//���K������
	mPlayer_SideVec.Normalize();
	mPlayer_FrontVec.Normalize();

	if (CKey::Push('A'))
	{
		mPlayer_MoveDir -= mPlayer_SideVec;
	}
	else if (CKey::Push('D'))
	{
		mPlayer_MoveDir += mPlayer_SideVec;
	}
	if (CKey::Push('W'))
	{
		mPlayer_MoveDir += mPlayer_FrontVec;
	}
	else if (CKey::Push('S'))
	{
		mPlayer_MoveDir -= mPlayer_FrontVec;
	}

	if (CKey::Push('D') && CKey::Once(VK_SHIFT))
	{
		mPlayer_MoveDir += mPlayer_SideVec;
	}
	else if (CKey::Push('A') && CKey::Once(VK_SHIFT))
	{
		mPlayer_MoveDir -= mPlayer_SideVec;
	}
	if (CKey::Push('S') && CKey::Once(VK_SHIFT))
	{
		mPlayer_MoveDir -= mPlayer_FrontVec;
	}
	else if (CKey::Push('W') && CKey::Once(VK_SHIFT))
	{
		mPlayer_MoveDir += mPlayer_FrontVec;
	}


	//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
	mPlayer_MoveDir = mPlayer_MoveDir;
	mPlayer_MoveDirKeep = mPlayer_MoveDir;	//MoveDir�ۑ�
	mPlayer_Move = mPlayer_MoveDir * mPlayer_Speed;	//�ړ��ʂ�ݒ�
}
//2D�`��
void CXPlayer::Render2D()
{
	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);
	//�Q�[�W��h�炷�p
	int shakeX = 0;
	int shakeY = 0;
	//�m�b�N�o�b�N��Ԃ̂Ƃ�
	if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EKNOCKBACK) {
		//�Q�[�W��h�炷�l��ݒ�
		shakeX = -5 + rand() % 12;
		shakeY = -2 + rand() % 2;
	}
	//�̗̓Q�[�W
	float HpRate = (float)mPlayer_Hp / (float)PLAYER_HP_MAX;	//�̗͍ő�l�ɑ΂���A���݂̗̑͂̊���
	float HpGaugeWid = PLAYER_GAUGE_WID_MAX * HpRate;	//�̗̓Q�[�W�̕�
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕����傫����
	if (mPlayer_FollowGaugeWid > HpGaugeWid) {
		//���`��ԂŔ�_���[�W����ǂ�����Q�[�W�̕���ݒ肷��
		mPlayer_FollowGaugeWid = Camera.mHpLerp(mPlayer_FollowGaugeWid, HpGaugeWid, 0.05f);
	}
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕���菬�����Ƃ�
	else if (mPlayer_FollowGaugeWid < HpGaugeWid) {
		//��_���[�W����ǂ�����Q�[�W�̕��ɑ̗̓Q�[�W�̕���ݒ肷��
		mPlayer_FollowGaugeWid = HpGaugeWid;
	}
	if(mPlayer_Hp >= PLAYER_INT_INITIALIZATION)
	{
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + mPlayer_FollowGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, 0, 480, 0, 10);
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + HpGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, 0, 480, 0, 10);
		CRes::GetInstance()->GetInPlayerUiHpFrame().Draw(PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_RIGHT, PLAYER_GAUGE_FRAME_BOTTOM, PLAYER_GAUGE_FRAME_TOP, 0, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_HEI, 0);
	}
	//2D�̕`��I��
	CUtil::End2D();
}



void CXPlayer::Collision(CCollider* m, CCollider* o) {
	//����̐e�������̎��̓��^�[��
	if (o->Parent() == this)return;
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->Type()) {
	case CCollider::ESPHERE: {//���R���C�_
		//����̃R���C�_�����R���C�_�̎�
		if (o->Type() == CCollider::ESPHERE) {
			//���̏Փ˔���
			if (CCollider::Collision(m, o)) {
				//����̐e�̃^�O���v���C���[
				if (o->Parent()->Tag() == EENEMY)
				{
					//����̃R���C�_�̃^�O���E��
					if (o->Tag() == CCollider::ERIGHTARM)
					{
						//�v���C���[�����G��Ԃł͂Ȃ��Ƃ�
						if (mPlayer_InvincibleFlag == false)
						{
							if (CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EATTACK_1 || CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EATTACK_3)
							{
								if (CXEnemy::GetInstance()->GetIsHit() == true)
								{
									CXEnemy::GetInstance()->SetIsHit(false);
									mPlayer_InvincibleFlag = true;
									mPlayer_State = EKNOCKBACK;
									CRes::GetInstance()->GetinEnemySeAttackSp().Play(0.3);
								}
							}
						}
					}
					else if (o->Tag() == CCollider::ELEFTARM)
					{
						//�v���C���[�����G��Ԃł͂Ȃ��Ƃ�
						if (mPlayer_InvincibleFlag == false)
						{
							if (CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EATTACK_2)
							{
								if (CXEnemy::GetInstance()->GetIsHit() == true)
								{
									CXEnemy::GetInstance()->SetIsHit(false);
									mPlayer_InvincibleFlag = true;
									mPlayer_State = EKNOCKBACK;
									CRes::GetInstance()->GetinEnemySeAttackSp().Play(0.3);
								}
							}
						}
					}
				}
			}
		}
		break;
	}

	case CCollider::ECAPSUL: {//�J�v�Z���R���C�_
		//����̃R���C�_���J�v�Z���R���C�_�̎�
		if (o->Type() == CCollider::ECAPSUL) {
			CVector adjust;//�����p�x�N�g��
			if (!mPlayer_Hp <= 0) {
				if (CCollider::CollisionCapsule(m, o, &adjust))
				{
					//�ʒu�̍X�V(mPosition + adjust)
					mPosition = mPosition + adjust;
					//�s��̍X�V
					CTransform::Update();
				}
			}
		}
	}
	}

	if (m->Type() == CCollider::ECAPSUL && o->Type() == CCollider::ETRIANGLE) {
		CVector adjust;//�����p�x�N�g��
		if (CCollider::CollisionTriangleLine(o, m, &adjust))
		{
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition + adjust;
			//�s��̍X�V
			CTransform::Update();
		}

	}
}
void CXPlayer::MovingCalculation() {
	//���W�ړ�
	mPosition += mPlayer_Move;												//�v���C���̈ʒu�Ƀv���C���̈ړ��ʂ𑫂�
	//����������
	mPlayer_Move = mPlayer_Move * PLAYER_THRUST;							//�v���C���̈ړ��ʂɐ��͂��|����
	//�d�͂��v���C���Ɋ|����
	mPosition.Y(mPosition.Y() - PLAYER_GRAVITY);							//�v���C����Y���ɏd�͂��|����

	//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
	//�[���x�N�g���v�Z
	CVector ChackVec; //�`�F�b�N�p�x�N�g��
	//�����Ԃ̂Ƃ�
	if (mPlayer_State == EAVOIDANCE) {
		ChackVec = mPlayer_MoveDirKeep.Normalize(); //�ۑ����ꂽ�ړ����̕����x�N�g������
	}
	else {
		ChackVec = mPlayer_MoveDir.Normalize(); //�ړ����̕����x�N�g������
	}
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / 180.0f));

	//��]���x�@degree�ɒ���
	mPlayer_Turnspeed = (180.0f / M_PI) * 0.3f;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//�ړ������փL��������������
	if (tCheck.cross > 0.0f) {
		mRotation = mRotation + CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}
	if (tCheck.cross < 0.0f) {
		mRotation = mRotation - CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}
	//���Z�b�g
	mPlayer_MoveDir = CVector(0.0f, 0.0f, 0.0f);
}
void CXPlayer::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mPlayer_ColCapsuleBody.ChangePriority();
	mPlayer_ColSphereBody.ChangePriority();
	mPlayer_ColSphereShield.ChangePriority();
	mPlayer_ColSphereSword.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mPlayer_ColCapsuleBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereShield, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereSword, COLLISIONRANGE);
}

//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayer_Instance;
}
//�v���C����HP�̎擾
bool CXPlayer::GetHp()
{
	return mPlayer_Hp;
}
//�A�j���[�V�����t���[���̎擾
bool CXPlayer::GetIsAnimationFrame() {
	return mAnimationFrame;
}
//�U���̓����蔻����擾����
bool CXPlayer::GetIsHit()
{
	return mPlayer_IsHit; //�U���̓����蔻���Ԃ�
}

//�v���C���[�̏�Ԃ��擾����
CXPlayer::EPlayerState CXPlayer::GetState()
{
	return mPlayer_State;
}
//���̃R���C�_�̍��W���擾����
CVector CXPlayer::GetSwordColPos()
{
	return mPlayer_ColSphereSword.GetIsMatrix()->GetPos();	//���̃R���C�_�̍��W��Ԃ�
}
