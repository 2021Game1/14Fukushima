#include"CXPlayer.h"
#include "CRes.h"

CXPlayer* CXPlayer::mpPlayer_Instance = nullptr;												//�v���C���̃C���X�^���X�ϐ��̏�����

CXPlayer::CXPlayer()
//�v���C���̕ϐ��̏�����
	: mPlayer_ColCapsuleBody(this, nullptr, CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_TOP_Y, PLAYER_COLCAPSULE_BODY_Z), CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_BOTTOM_Y, PLAYER_COLCAPSULE_BODY_Z), PLAYER_COLCAPSULE_BODY_SIZE)
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
	mPlayer_ColCapsuleBody.Matrix(&mpCombinedMatrix[3]);
	mPlayer_ColSphereBody.Matrix(&mpCombinedMatrix[16]);
	mPlayer_ColSphereShield.Matrix(&mpCombinedMatrix[41]);
	mPlayer_ColSphereSword.Matrix(&mpCombinedMatrix[71]);
	//�v���C���̈ʒu,�g�k,��]�̐ݒ�
	mPosition.Set(0.0f, 0.0f, 20.0);								//�ʒu��ݒ�
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
	if (mPlayer_Hp <= PLAYER_GAMEOVER_HP) {
		mPlayer_State = EDEATH;										//���S��Ԃֈڍs
		mPlayer_Hp = PLAYER_GAMEOVER_HP;
	}
	if (mPlayer_EnemyDis >= PLAYER_ATTACK_DIS) {
		mPlayer_AttackDir = mPlayer_Point; //�U�����̌��������߂�
	}
	//�J�����̐ݒ�
	Camera.SetTarget(mPosition);									//�J�������v���C���̈ʒu�ɐݒ�
	//�L�����N�^�̍X�V����
	CXCharacter::Update();
}

void CXPlayer::Idle() 
{
	//���N���b�N�ōU��
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//WASD�L�[�������ƈړ��ֈڍs
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mPlayer_State = EMOVE;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else{
		mPlayer_ComboCount = PLAYER_INT_INITIALIZATION;
		ChangeAnimation(PLAYER_ANIMATION_No_IDLE, true, PLAYER_IDLE_ANIMATION_FRAME);
	}

}

//�ړ�����
void CXPlayer::Move()
{
	//���N���b�N�ōU��1�ֈڍs
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	} 
	else if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
		CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	//WASD�L�[�������ƈړ��ֈڍs
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		ChangeAnimation(PLAYER_ANIMATION_No_MOVE, true, PLAYER_MOVE_ANIMATION_FRAME);
		MoveCamera();												//�J��������ɂ����ړ��������Ă�
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
	ChangeAnimation(PLAYER_ANIMATION_No_AVOIDANCE, false, PLAYER_AVOIDANCE_ANIMATION_FRAME);

	//�q�b�g���蔭��
	if (IsAnimationFinished() == false)
	{
		MoveCamera();
	}
	//�A�j���[�V�����I����
	else if (IsAnimationFinished())
	{
		//���N���b�N�ōU��1�ֈڍs
		if (CKey::Once(VK_LBUTTON)) {
			mPlayer_State = EATTACK_1;
		}
		else if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		//WASD�L�[�������ƈړ��ֈڍs
		else if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
			mPlayer_State = EMOVE;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else {
			mPlayer_State = EIDLE;
		}
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
		mPlayer_AttackFlag_1 = true;															//�v���C���̍U��1�̃t���O��true�ɂ���
		mPlayer_AttackFlag_Once = true;															//�v���C���̍U���t���O��true�ɐݒ�
		mPlayer_IsHit = false;																	//�q�b�g����I��
		ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_1, false, PLAYER_ATTACK1_ANIMATION_FRAME);	//�v���C���̍U��1���[�V����
		CRes::GetInstance()->GetinPlayerSeAttackSp1().Play(PLAYER_SE);
	}
	//�A�j���[�V�����C���f�b�N�X���R�̎�
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_3) {
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false)
		{
			mPlayer_MoveDirKeep = mPlayer_AttackDir;
			mPlayer_MoveDir = mPlayer_AttackDir;
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

			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_1, false, PLAYER_ATTACK1_ANIMATION_FRAME);							//�v���C���̍U��1���[�V����
			CRes::GetInstance()->GetinPlayerSeAttackSp1().Play(PLAYER_SE);
		}
	}
	//�A�j���[�V�����C���f�b�N�X���P�̎�
	else if (mAnimationIndex == PLAYER_ANIMATION_No_ATTACK_1)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false)
		{
			mPlayer_MoveDirKeep = mPlayer_AttackDir;
			mPlayer_MoveDir = mPlayer_AttackDir;
			if (CXEnemy::EEnemyState::EKNOCKBACK && CXEnemy::EEnemyState::EIDLE)
			{
				mPlayer_IsHit = false;
			}
			else {
				mPlayer_IsHit = true;
			}
			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
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
			mPlayer_MoveDirKeep = mPlayer_AttackDir;
			mPlayer_MoveDir = mPlayer_AttackDir;
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
			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
		}
		//�A�j���[�V�����I����
		else if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_2, false, PLAYER_ATTACK2_ANIMATION_FRAME);							//�v���C���̍U��2���[�V����
			CRes::GetInstance()->GetinPlayerSeAttackSp2().Play(PLAYER_SE);
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
			mPlayer_MoveDirKeep = mPlayer_AttackDir;
			mPlayer_MoveDir = mPlayer_AttackDir;
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
			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				MoveCamera();
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
				//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
			}
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(PLAYER_ANIMATION_No_ATTACK_3, false, PLAYER_ATTACK3_ANIMATION_FRAME);
			CRes::GetInstance()->GetinPlayerSeAttackSp3().Play(PLAYER_SE);
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
	ChangeAnimation(PLAYER_ANIMATION_No_KNOCKBACK, false, PLAYER_KNOCKBACK_ANIMATION_FRAME);	//�̂�����A�j���[�V����

	if (IsAnimationFinished() == true)
	{
		mPlayer_IsHit = false;
	}
		if (mPlayer_Flag == false)
		{
			mPlayer_Flag = true;
			if (CXEnemy::EEnemyState::EATTACK_1)
			{
				mPlayer_Hp = mPlayer_Hp - PLAYER_DAMAGE_ENEMYSP1;
			}
			else if (CXEnemy::EEnemyState::EATTACK_2)
			{
				mPlayer_Hp = mPlayer_Hp - PLAYER_DAMAGE_ENEMYSP2;
			}
			else if (CXEnemy::EEnemyState::EATTACK_3)
			{
				mPlayer_Hp = mPlayer_Hp - PLAYER_DAMAGE_ENEMYSP3;
			}
		}


	if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		//���N���b�N�ōU��1�ֈڍs
		if (CKey::Once(VK_LBUTTON)) {
			mPlayer_State = EATTACK_1;
		}
		else if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
			MoveCamera();
			mPlayer_State = EAVOIDANCE;
			mPlayer_IsHit = false;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		//WASD�L�[�������ƈړ��ֈڍs
		else if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
			mPlayer_State = EMOVE;
			//CRes::GetInstance()->GetinPlayerSeWalk().Repeat(PLAYER_SE);
		}
		else {
			mPlayer_State = EIDLE;
		}
		mPlayer_Flag = false;
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
	}
}

//���S����
void CXPlayer::Death()
{
	MovingCalculation();
	ChangeAnimation(PLAYER_ANIMATION_No_DEATH, false, PLAYER_DEATH_ANIMATION_FRAME);	//���S�A�j���[�V����
}

//�J��������ɂ����ړ�����
void CXPlayer::MoveCamera()
{
	//�J�������_�ړ��@�ʏ̖��o�ړ�
	//�J�����̍��E�ƑO��̃x�N�g�����擾
	mPlayer_SideVec = Camera.GetMat().GetXVec();
	mPlayer_FrontVec = Camera.GetMat().GetZVec();
	//�����ړ��̓J�b�g����
	mPlayer_SideVec.Y(PLAYER_FLOAT_INITIALIZATION);
	mPlayer_FrontVec.Y(PLAYER_FLOAT_INITIALIZATION);
	//���K������
	mPlayer_SideVec.Normalize();
	mPlayer_FrontVec.Normalize();

	if (CKey::Push(VK_A))
	{
		mPlayer_MoveDir -= mPlayer_SideVec;
	}
	else if (CKey::Push(VK_D))
	{
		mPlayer_MoveDir += mPlayer_SideVec;
	}
	if (CKey::Push(VK_W))
	{
		mPlayer_MoveDir += mPlayer_FrontVec;
	}
	else if (CKey::Push(VK_S))
	{
		mPlayer_MoveDir -= mPlayer_FrontVec;
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
	CUtil::Start2D(WINDOW_FIRST_WIDTH, WINDOW_WIDTH, WINDOW_FIRST_HEIGHT, WINDOW_HEIGHT);
	//�Q�[�W��h�炷�p
	int shakeX = PLAYER_INT_INITIALIZATION;
	int shakeY = PLAYER_INT_INITIALIZATION;
	//�m�b�N�o�b�N��Ԃ̂Ƃ�
	if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EKNOCKBACK) {
		//�Q�[�W��h�炷�l��ݒ�
		shakeX = PLAYER_GAUGE_HP_SHAKE_X + rand() % PLAYER_GAUGE_HP_SHAKE_RANGE_X;
		shakeY = PLAYER_GAUGE_HP_SHAKE_Y + rand() % PLAYER_GAUGE_HP_SHAKE_RANGE_Y;
	}
	//�̗̓Q�[�W
	float HpRate = (float)mPlayer_Hp / (float)PLAYER_HP_MAX;	//�̗͍ő�l�ɑ΂���A���݂̗̑͂̊���
	float HpGaugeWid = PLAYER_GAUGE_WID_MAX * HpRate;	//�̗̓Q�[�W�̕�
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕����傫����
	if (mPlayer_FollowGaugeWid > HpGaugeWid) {
		//���`��ԂŔ�_���[�W����ǂ�����Q�[�W�̕���ݒ肷��
		mPlayer_FollowGaugeWid = Camera.mHpLerp(mPlayer_FollowGaugeWid, HpGaugeWid, PLAYER_GAUGE_HP_RATE);
	}
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕���菬�����Ƃ�
	else if (mPlayer_FollowGaugeWid < HpGaugeWid) {
		//��_���[�W����ǂ�����Q�[�W�̕��ɑ̗̓Q�[�W�̕���ݒ肷��
		mPlayer_FollowGaugeWid = HpGaugeWid;
	}
	if(mPlayer_Hp >= PLAYER_GAMEOVER_HP)
	{
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + mPlayer_FollowGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_FIRST_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + HpGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_FIRST_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
		CRes::GetInstance()->GetInPlayerUiHpFrame().Draw(PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_RIGHT, PLAYER_GAUGE_FRAME_BOTTOM, PLAYER_GAUGE_FRAME_TOP, PLAYER_GAUGE_FRAME_TEX_FIRST_WID, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
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
							if (CXEnemy::EEnemyState::EATTACK_1 || CXEnemy::EEnemyState::EATTACK_3)
							{
								if (((CXEnemy*)(o->Parent()))->GetIsHit() == true)
								{
									((CXEnemy*)(o->Parent()))->SetIsHit(false);
									mPlayer_InvincibleFlag = true;
									mPlayer_State = EKNOCKBACK;
									CRes::GetInstance()->GetinEnemySeAttackSp().Play(PLAYER_DAMAGE_SE);
								}
							}
						}
					}
					else if (o->Tag() == CCollider::ELEFTARM)
					{
						//�v���C���[�����G��Ԃł͂Ȃ��Ƃ�
						if (mPlayer_InvincibleFlag == false)
						{
							if (CXEnemy::EEnemyState::EATTACK_2)
							{
								if (((CXEnemy*)(o->Parent()))->GetIsHit() == true)
								{
									((CXEnemy*)(o->Parent()))->SetIsHit(false);
									mPlayer_InvincibleFlag = true;
									mPlayer_State = EKNOCKBACK;
									CRes::GetInstance()->GetinEnemySeAttackSp().Play(PLAYER_DAMAGE_SE);
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
			if (!mPlayer_Hp <= PLAYER_GAMEOVER_HP) {
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
	//�v���C���[�܂ł̋��������߂�
	mPlayer_EnemyDis = mPlayer_Point.Length();
	//���W�ړ�
	mPosition += mPlayer_Move;												//�v���C���̈ʒu�Ƀv���C���̈ړ��ʂ𑫂�
	//����������
	mPlayer_Move = mPlayer_Move * PLAYER_THRUST;							//�v���C���̈ړ��ʂɐ��͂��|����
	//�d�͂��v���C���Ɋ|����
	mPosition.Y(mPosition.Y() * PLAYER_GRAVITY);							//�v���C����Y���ɏd�͂��|����

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
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / PLAYER_TURN_SET));

	//��]���x�@degree�ɒ���
	mPlayer_Turnspeed = (PLAYER_TURN_SET / M_PI) * PLAYER_TURN_SPEEDS_SET;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > PLAYER_TRUN_CHECK_SPEEDS_SET) tCheck.turn = PLAYER_TRUN_CHECK_SPEEDS_SET;

	//�ړ������փL��������������
	if (tCheck.cross > PLAYER_TRUN_CHECK_SET) {
		mRotation = mRotation + CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}
	if (tCheck.cross < PLAYER_TRUN_CHECK_SET){
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
