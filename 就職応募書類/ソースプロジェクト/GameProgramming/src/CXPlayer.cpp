#include"CXPlayer.h"
#include"CXEnemyManager.h"
#include"CRes.h"


CXPlayer* CXPlayer::mpPlayer_Instance = nullptr;												//�v���C���̃C���X�^���X�ϐ��̏�����

//�e�[�u���̃f�[�^��ϐ��ɕۑ�
void CXPlayer::PlayerTable() {
	OX::Table table(PLAYER_DATATABLE);

	Player_Priority = table["Player_Priority"]["Value"].iVal;
	Player_Hp = table["Player_Hp"]["Value"].iVal;
	Player_Hp_Max = table["Player_Hp_Max"]["Value"].iVal;
	Player_Attack_Point = table["Player_Attack_Point"]["Value"].iVal;
	Player_Defense_Point = table["Player_Defense_Point"]["Value"].iVal;
	Player_Stan_Point = table["Player_Stan_Point"]["Value"].iVal;
	Player_StanAccumulation = table["Player_StanAccumulation"]["Value"].iVal;
	Player_StanAccumulation_Max = table["Player_StanAccumulation_Max"]["Value"].iVal;
	Player_Damage_Magnification = table["Player_Damage_Magnification"]["Value"].fVal;
	Player_GameOver_Hp = table["Player_GameOver_Hp"]["Value"].iVal;
	Player_Speed_Default = table["Player_Speed_Default"]["Value"].fVal;
	Player_Speed_Avoid = table["Player_Speed_Avoid"]["Value"].fVal;
	Player_Avoid_Time = table["Player_Avoid_Time"]["Value"].fVal;
	Player_Gravity = table["Player_Gravity"]["Value"].fVal;
	Player_Thrust = table["Player_Thrust"]["Value"].fVal;
	Player_Se = table["Player_Se"]["Value"].fVal;
	Player_Damage_Se = table["Player_Damage_Se"]["Value"].fVal;
	Player_Push_Reception = table["Player_Push_Reception"]["Value"].fVal;
	Player_Attack_InReception = table["Player_Attack_InReception"]["Value"].fVal;
	Player_Attack_OutReception = table["Player_Attack_OutReception"]["Value"].fVal;
	Player_Attack_Dis = table["Player_Attack_Dis"]["Value"].fVal;
	Player_Position_X = table["Player_Position_X"]["Value"].fVal;
	Player_Position_Y = table["Player_Position_Y"]["Value"].fVal;
	Player_Position_Z = table["Player_Position_Z"]["Value"].fVal;
	Player_Scale_X = table["Player_Scale_X"]["Value"].fVal;
	Player_Scale_Y = table["Player_Scale_Y"]["Value"].fVal;
	Player_Scale_Z = table["Player_Scale_Z"]["Value"].fVal;
	Player_Rotation_X = table["Player_Rotation_X"]["Value"].fVal;
	Player_Rotation_Y = table["Player_Rotation_Y"]["Value"].fVal;
	Player_Rotation_Z = table["Player_Rotation_Z"]["Value"].fVal;
	Player_Idle_Animation_Frame = table["Player_Idle_Animation_Frame"]["Value"].fVal;
	Player_Move_Animation_Frame = table["Player_Move_Animation_Frame"]["Value"].fVal;
	Player_Avoidance_Animation_Frame = table["Player_Avoidance_Animation_Frame"]["Value"].fVal;
	Player_Attack1_Animation_Frame = table["Player_Attack1_Animation_Frame"]["Value"].fVal;
	Player_Attack1_Idle_Animation_Frame = table["Player_Attack1_Idle_Animation_Frame"]["Value"].fVal;
	Player_Attack2_Animation_Frame = table["Player_Attack2_Animation_Frame"]["Value"].fVal;
	Player_Attack2_Idle_Animation_Frame = table["Player_Attack2_Idle_Animation_Frame"]["Value"].fVal;
	Player_KnockBack_Animation_Frame = table["Player_KnockBack_Animation_Frame"]["Value"].fVal;
	Player_Death_Animation_Frame = table["Player_Death_Animation_Frame"]["Value"].fVal;
	Player_Animation_No_Move = table["Player_Animation_No_Move"]["Value"].iVal;
	Player_Animation_No_Attack1 = table["Player_Animation_No_Attack1"]["Value"].iVal;
	Player_Animation_No_Attack1_Idle = table["Player_Animation_No_Attack1_Idle"]["Value"].iVal;
	Player_Animation_No_Attack2 = table["Player_Animation_No_Attack2"]["Value"].iVal;
	Player_Animation_No_Attack2_Idle = table["Player_Animation_No_Attack2_Idle"]["Value"].iVal;
	Player_Animation_No_AvoidDance = table["Player_Animation_No_AvoidDance"]["Value"].iVal;
	Player_Animation_No_Idle = table["Player_Animation_No_Idle"]["Value"].iVal;
	Player_Animation_No_Knockback = table["Player_Animation_No_Knockback"]["Value"].iVal;
	Player_Animation_No_Death = table["Player_Animation_No_Death"]["Value"].iVal;
	Player_Gauge_Hp_Shake_X = table["Player_Gauge_Hp_Shake_X"]["Value"].iVal;
	Player_Gauge_Hp_Shake_Y = table["Player_Gauge_Hp_Shake_Y"]["Value"].iVal;
	Player_Gauge_Hp_Shake_Range_X = table["Player_Gauge_Hp_Shake_Range_X"]["Value"].iVal;
	Player_Gauge_Hp_Shake_Range_Y = table["Player_Gauge_Hp_Shake_Range_Y"]["Value"].iVal;
	Player_Gauge_Hp_Rate = table["Player_Gauge_Hp_Rate"]["Value"].fVal;
	Player_Trun_Set = table["Player_Trun_Set"]["Value"].fVal;
	Player_Trun_Speeds_Set = table["Player_Trun_Speeds_Set"]["Value"].fVal;
	Player_Trun_Check_Speeds_Set = table["Player_Trun_Check_Speeds_Set"]["Value"].fVal;
	Player_Trun_Check_Set = table["Player_Trun_Check_Set"]["Value"].fVal;

	//�D��x��1�ɕύX����
	mPriority = Player_Priority;
	//�e�[�u���擾�f�[�^����
	mPlayer_Gauge_Hp_Shake_X = Player_Gauge_Hp_Shake_X;
	mPlayer_Gauge_Hp_Shake_Y = Player_Gauge_Hp_Shake_Y;
	mPlayer_Gauge_Hp_Shake_Range_X = Player_Gauge_Hp_Shake_Range_X;
	mPlayer_Gauge_Hp_Shake_Range_Y = Player_Gauge_Hp_Shake_Range_Y;
	mPlayer_FollowGaugeWid = Player_Gauge_Wid;
	mPlayer_Speed = Player_Speed_Default;
	mAttack_Point = Player_Attack_Point;
	mDefense_Point = Player_Defense_Point;
	mStan_Point = Player_Stan_Point;
	mStanAccumulation = Player_StanAccumulation;
	mPlayer_Hp = Player_Hp;
	mPlayer_Hp_Max = Player_Hp_Max;
	mPlayer_Gauge_Hp_Rate = Player_Gauge_Hp_Rate;
	mPlayer_Attack_Dis = Player_Attack_Dis;
}
//�f�t�H���g�R���X�g���N�^
CXPlayer::CXPlayer()
//�v���C���̕ϐ��̏�����
	: mPlayer_ColCapsuleBody(this, nullptr, CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_TOP_Y, PLAYER_COLCAPSULE_BODY_Z), CVector(PLAYER_COLCAPSULE_BODY_X, PLAYER_COLCAPSULE_BODY_BOTTOM_Y, PLAYER_COLCAPSULE_BODY_Z), PLAYER_COLCAPSULE_BODY_SIZE)
	,mPlayer_ColSphereHead(this,nullptr,CVector(0.0f,16.0f,0.0f),PLAYER_COLSPHER_HEAD_SIZE)
	, mPlayer_ColSphereBody(this, nullptr, CVector(), PLAYER_COLSPHERE_BODY_SIZE)
	, mPlayer_ColSphereLowerBody(this, nullptr, CVector(PLAYER_COLSPHERE_LOWERBODY_X, PLAYER_COLSPHERE_LOWERBODY_Y, PLAYER_COLSPHERE_LOWERBODY_Z), PLAYER_COLSPHERE_LOWERBODY_SIZE)
	, mPlayer_ColSphereSword(this, nullptr, CVector(PLAYER_COLSPHERE_SWORD_X, PLAYER_COLSPHERE_SWORD_Y, PLAYER_COLSPHERE_SWORD_Z), PLAYER_COLSPHERE_SWORD_SIZE)
	, mPlayer_ComboCount(PLAYER_INT_INITIALIZATION)
	, mPlayer_Turnspeed(PLAYER_FLOAT_INITIALIZATION)
	, mPlayer_InvincibleFlag(false)
	, mPlayer_IsHit(false)
	, mPlayer_AttackFlag_1(false)
	, mPlayer_SeFlag(false)
	, mPlayer_AttackFlag_Once(false)
	, mPlayer_Flag(false)
	, mPlayer_Avoid(false)
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
	mPlayer_ColSphereLowerBody.Tag(CCollider::EBODY);				//�����g
	mPlayer_ColSphereHead.Tag(CCollider::EHEAD);					//��
	mPlayer_ColSphereSword.Tag(CCollider::ESWORD);					//��
	//�v���C���̃e�[�u�����Ăяo��
	PlayerTable();
	//�^�X�N�}�l�[�W���ւ̒ǉ�
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}

//���f���̐ݒ�
void CXPlayer::Init(CModelX* model)
{
	//�v���C��SE
	Se_Player_AttackSp1.Load(SE_PLAYER_ATTACK1);
	Se_Player_AttackSp2.Load(SE_PLAYER_ATTACK2);
	Se_Player_Walk.Load(SE_PLAYER_WALK);
	Se_Player_Death.Load(SE_PLAYER_DEATH);
	//�GSE
	Se_Enemy_AttackSp.Load(SE_ENEMY_ATTACK);
	//�v���C����UI�̒ǉ�
	gPlayer_Ui_Hp_Frame.Load2D(PLAYER_UI_HP_FRAME);

	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mPlayer_ColSphereLowerBody.Matrix(&mpCombinedMatrix[2]);
	mPlayer_ColCapsuleBody.Matrix(&mpCombinedMatrix[3]);
	mPlayer_ColSphereBody.Matrix(&mpCombinedMatrix[15]);
	mPlayer_ColSphereHead.Matrix(&mpCombinedMatrix[16]);
	mPlayer_ColSphereSword.Matrix(&mpCombinedMatrix[71]);
	//�v���C���̈ʒu,�g�k,��]�̐ݒ�
	mPosition.Set(Player_Position_X, Player_Position_Y, Player_Position_Z);								//�ʒu��ݒ�
	mScale.Set(Player_Scale_X, Player_Scale_Y, Player_Scale_Z);										//�X�P�[���ݒ�
	mRotation.Set(Player_Rotation_X, Player_Rotation_Y, Player_Rotation_Z);								//��]��ݒ�
}
//�X�V����
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
	if (mPlayer_Hp <= Player_GameOver_Hp) {
		mPlayer_State = EDEATH;										//���S��Ԃֈڍs
		mPlayer_Hp = Player_GameOver_Hp;
	}
	if (mPlayer_EnemyDis >= mPlayer_Attack_Dis) {
		mPlayer_AttackDir = mPlayer_Point; //�U�����̌��������߂�
	}
	//�J�����A���O���̕ύX
	if (CKey::Push(VK_F1)) {
		Camera.CameraAngleChange();
	}
	//�J�����A���O���̕ύX
	else if(CKey::Push(VK_F2)) {
		Camera.CameraAngleDefault();
	}
	//�J�����̐ݒ�
	Camera.SetTarget(mPosition);									//�J�������v���C���̈ʒu�ɐݒ�
	//�L�����N�^�̍X�V����
	CXCharacter::Update();
}
//�ҋ@��Ԃ̏���
void CXPlayer::Idle() 
{
	mPlayer_AttackFlag_1 = false;					//�v���C���̍U��1�t���O��false�ɂ���
	mPlayer_Flag = false;							//�_���[�W�t���O�̉���
	//���N���b�N�ōU��
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//�����Ԃֈڍs
	if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	//WASD�L�[�������ƈړ��ֈڍs
	else if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
		mPlayer_State = EMOVE;
		Se_Player_Walk.Repeat(Player_Se);
	}
	//�������͂���Ȃ������̂őҋ@�����𓮂���
	else{
		mPlayer_ComboCount = PLAYER_INT_INITIALIZATION;
		ChangeAnimation(Player_Animation_No_Idle, true, Player_Idle_Animation_Frame);
	}
}

//�ړ�����
void CXPlayer::Move()
{
	mPlayer_AttackFlag_1 = false;					//�v���C���̍U��1�t���O��false�ɂ���
	//���N���b�N�ōU��1�ֈڍs
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	} 
	//�����Ԃֈڍs
	if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		MoveCamera();
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	//WASD�L�[�������ƈړ��ֈڍs
	else if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
		ChangeAnimation(Player_Animation_No_Move, true, Player_Move_Animation_Frame);
		MoveCamera();												//�J��������ɂ����ړ��������Ă�
		Se_Player_Walk.Repeat(Player_Se);
	}
	//�ҋ@��Ԃֈڍs
	else {
		mPlayer_State = EIDLE;
	}
	//���s��Ԃł͖����̂ŕ��sSE���~����
	if (mPlayer_State != EMOVE) {
		Se_Player_Walk.Stop();
	}
}
//������
void CXPlayer::Avoidance()
{
	//�������x�����ʂ�
	if (mPlayer_Avoid == false) {
		ChangeAnimation(Player_Animation_No_AvoidDance, false, Player_Avoidance_Animation_Frame);
		mPlayer_Avoid = true;							//���
		mPlayer_Speed_Avoid = Player_Speed_Avoid;
		mPlayer_Avoid_Time = Player_Avoid_Time;
		MoveCamera();
	}
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false)
	{
		mPlayer_AttackFlag_1 = false;					//�v���C���̍U��1�t���O��false�ɂ���
		mPlayer_Flag = false;							//�_���[�W�t���O�̉���
		{
			//������Ԃ��J�E���g�_�E��
			mPlayer_Avoid_Time--;
			//�������0�ɂȂ�����
			if (mPlayer_Avoid_Time == 0) {
				mPlayer_Avoid = false;	//����I��
			}
			//������̈ړ��l����
			mPlayer_Move = mPlayer_MoveDirKeep * mPlayer_Speed_Avoid;

			//�����Ԃ��I�������Ƃ�
			if (mPlayer_Avoid == false) {
				//����I����WASD�L�[��������Ă���ƈړ�
				if (CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
					mPlayer_State = EMOVE;
				}
				//�ҋ@��Ԃֈڍs
				else {
					mPlayer_State = EIDLE;
				}
			}
		}
	}
}


//�U��1����
void CXPlayer::Attack_1()
{
	mPlayer_Flag = false;							//�_���[�W�t���O�̉���
	//�������Ăяo���ꂽ��1�x�����������Ȃ�
	if (mPlayer_AttackFlag_1 == false) {
		mPlayer_AttackFlag_1 = true;															//�v���C���̍U��1�̃t���O��true�ɂ���
		mPlayer_AttackFlag_Once = true;															//�v���C���̍U���t���O��true�ɐݒ�
		ChangeAnimation(Player_Animation_No_Attack1, false, Player_Attack1_Animation_Frame);	//�v���C���̍U��1���[�V����
		Se_Player_AttackSp1.Play(Player_Se);
	}
	//�A�j���[�V�������I�����Ă��邩�A�U��2�̃A�j���[�V�����������ꍇ�A���s����
	if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack2) {
		mPlayer_AttackFlag_Once = true;															//�v���C���̍U���t���O��true�ɐݒ�
		ChangeAnimation(Player_Animation_No_Attack1, false, Player_Attack1_Animation_Frame);	//�v���C���̍U��1���[�V����
		Se_Player_AttackSp1.Play(Player_Se);													//�v���C���̍U��SE���Đ�
	}
		//�G�̋������v���C���̍U���͈͂ɓ������玩���I�ɓG�ɍU�����Ǐ]����
		if (mPlayer_EnemyDis <= mPlayer_Attack_Dis) {
			mPlayer_MoveDirKeep = mPlayer_MoveDir;							  //MoveDir�ۑ�
			mPlayer_MoveDir = CXEnemyManager::GetInstance()->GetTargetEnemy();//�G�̃��X�g�ɓ����Ă���G�̈ʒu����
		}

		//�q�b�g���蔭��
		if (IsAnimationFinished() == false)
		{

			//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
			if (mAnimationFrame <= Player_Attack_InReception)
			{
				mPlayer_IsHit = false; //�q�b�g����I��
			}
			//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
			else {
				mPlayer_IsHit = true;
			}
			//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
			if (mAnimationFrame > Player_Attack_OutReception)
			{
				mPlayer_IsHit = false; //�q�b�g����I��
			}

		}

		
			//���N���b�N���ꂽ�ꍇ
			if (CKey::Once(VK_LBUTTON)) {
				//�A�j���[�V�������U��1�ł��A���͐������ԓ��ŃN���b�N�����Ύ��s����
				if (mAnimationIndex == Player_Animation_No_Attack1) {
					if (mAnimationFrame < Player_Push_Reception) {
						//�U��2���[�V�����ֈڍs
						mPlayer_State = EATTACK_2;							
					}
				}
			}
			//�ړ���Ԃֈڍs
			if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
			}
			else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
			}
			else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
			}
			else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
				mPlayer_State = EAVOIDANCE;
				mPlayer_IsHit = false;
			}
		//�A�j���[�V�����I����
		//�U��1����ҋ@���[�V�����̊Ԃ̃A�j���[�V������`�悷��
		if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack1) {
			ChangeAnimation(Player_Animation_No_Attack1_Idle, false, Player_Attack1_Idle_Animation_Frame);
		}
		//�U��1����ҋ@���[�V�����̊Ԃ̃A�j���[�V������`�悪�I����
		//�ҋ@��Ԃֈڍs
		if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack1_Idle) {
				mPlayer_IsHit = false;								//�q�b�g����I��
				mPlayer_State = EIDLE;								//�ҋ@��Ԃֈڍs
				mPlayer_AttackFlag_1 = false;						//�v���C���̍U��1�t���O��false�ɂ���
		}
}

//�U��2����
void CXPlayer::Attack_2()
{
	//�A�j���[�V�������I�����Ă��邩�A�v���C���̍U��1���A�j���[�V�������ꂽ��
	//�U��2�̍s�����������s����
	if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack1) {
		mPlayer_AttackFlag_Once = true;																//�v���C���̍U���t���O��true�ɐݒ�
		ChangeAnimation(Player_Animation_No_Attack2, false, Player_Attack2_Animation_Frame);		//�v���C���̍U��2���[�V����
		Se_Player_AttackSp2.Play(Player_Se);														//�U��2��SE���Đ�����		
	}

	//�G�̋������v���C���̍U���͈͂ɓ������玩���I�ɓG�ɍU�����Ǐ]����
	if (mPlayer_EnemyDis <= mPlayer_Attack_Dis) {
		mPlayer_MoveDirKeep = mPlayer_MoveDir;							  //MoveDir�ۑ�
		mPlayer_MoveDir = CXEnemyManager::GetInstance()->GetTargetEnemy();//�G�̃��X�g�ɓ����Ă���G�̈ʒu����
	}


	//�q�b�g���蔭��
	//�A�j���[�V�������I�����Ă��Ȃ����A���̃A�j���[�V�������U��2�ł���΁A���������s����
	if (IsAnimationFinished() == false && mAnimationIndex == Player_Animation_No_Attack2) {

		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame <= Player_Attack_InReception)
		{
			mPlayer_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else {
			mPlayer_IsHit = true; //�q�b�g����𔭐�������
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > Player_Attack_OutReception)
		{
			mPlayer_IsHit = false; //�q�b�g����I��
		}
	}

	//���N���b�N���ꂽ�ꍇ
	//�U��2�̃A�j���[�V�������A�A���͐������ԓ��ŃN���b�N�����Ύ��s����
	if (CKey::Once(VK_LBUTTON)) {
		if (mAnimationIndex == Player_Animation_No_Attack2) {
			if (mAnimationFrame < Player_Push_Reception) {
				//�U��1���[�V�����ֈڍs
				mPlayer_State = EATTACK_1;						
			}
		}
	}
	//�ړ���Ԃֈڍs
	if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {
		mPlayer_State = EAVOIDANCE;
		mPlayer_IsHit = false;
	}
	//�A�j���[�V�����I����
	//�U��2�Ƒҋ@��Ԃ̊Ԃ̃A�j���[�V������`�悷��
	if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack2) {
		ChangeAnimation(Player_Animation_No_Attack2_Idle, false, Player_Attack2_Idle_Animation_Frame);
	}	
	//�U��2�Ƒҋ@��Ԃ̊Ԃ̃A�j���[�V������`�悪�I����
	//�ҋ@��Ԃֈڍs
	if (IsAnimationFinished() && mAnimationIndex == Player_Animation_No_Attack2_Idle) {
			mPlayer_IsHit = false;								//�q�b�g����I��
			mPlayer_State = EIDLE;								//�ҋ@��Ԃֈڍs
	}
}

//�m�b�N�o�b�N����
void CXPlayer::KnockBack()
{
	//�m�b�N�o�b�N�̃A�j���[�V����
	ChangeAnimation(Player_Animation_No_Knockback, false, Player_KnockBack_Animation_Frame);	//�m�b�N�o�b�N�A�j���[�V����
	mPlayer_AttackFlag_1 = false;																//�v���C���̍U��1�t���O��false�ɂ���
	//�A�j���[�V�������`�掞
	//�v���C���̍U��������~����
	if (IsAnimationFinished() == true)
	{
		mPlayer_IsHit = false;			//�v���C���̍U������t���O��false	
	}
	//�A�j���[�V�����̕`�悪�I�������ꍇ
	//�����蔻��̃t���O��true�ɂ��A�����蔻����~
	if (mPlayer_Flag == false)
	{
		mPlayer_Flag = true;			//�����蔻����~����
	}

		//���N���b�N�ōU��1�ֈڍs
		if (CKey::Once(VK_LBUTTON)) {
			mPlayer_State = EATTACK_1;		//�U��1��Ԃֈڍs
			mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		}
		else if (CKey::Push(VK_W) && CKey::Once(VK_SHIFT)) {
			mPlayer_State = EAVOIDANCE;		//�����Ԃֈڍs
			mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		}
		else if (CKey::Push(VK_A) && CKey::Once(VK_SHIFT)) {
			mPlayer_State = EAVOIDANCE;		//�����Ԃֈڍs
			mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		}
		else if (CKey::Push(VK_S) && CKey::Once(VK_SHIFT)) {
			mPlayer_State = EAVOIDANCE;		//�����Ԃֈڍs
			mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		}
		else if (CKey::Push(VK_D) && CKey::Once(VK_SHIFT)) {

			mPlayer_State = EAVOIDANCE;		//�����Ԃֈڍs
			mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
		}

	//�A�j���[�V�����I����
	if (IsAnimationFinished()){
		mPlayer_State = EIDLE;			//�ҋ@��Ԃֈڍs
		mPlayer_Flag = false;			//�t���O��false�ɂ���
		mPlayer_InvincibleFlag = false; //���G��Ԃ��I������
	}
}

//���S����
void CXPlayer::Death()
{
	//�ړ��v�Z����
	MovingCalculation();
	//���S���SE���Đ�
	Se_Player_Death.Play(Player_Se);
	//���S��Ԃ̃A�j���[�V�������Đ�����
	ChangeAnimation(Player_Animation_No_Death, false, Player_Death_Animation_Frame);	//���S�A�j���[�V����
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

	//�ړ���Ԏ��̏ꍇ
	//�ړ��ʂ���
	if (mPlayer_State == EMOVE) {
		if (CKey::Push(VK_A)) {
			mPlayer_MoveDir -= mPlayer_SideVec;
		}
		else if (CKey::Push(VK_D)) {
			mPlayer_MoveDir += mPlayer_SideVec;
		}
		if (CKey::Push(VK_W)) {
			mPlayer_MoveDir += mPlayer_FrontVec;
		}
		else if (CKey::Push(VK_S)) {
			mPlayer_MoveDir -= mPlayer_FrontVec;
		}
		//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
		mPlayer_MoveDir = mPlayer_MoveDir.Normalize();
		mPlayer_MoveDirKeep = mPlayer_MoveDir;	//MoveDir�ۑ�
		mPlayer_Move = mPlayer_MoveDir * mPlayer_Speed;	//�ړ��ʂ�ݒ�
	}
	//�����Ԃ̏ꍇ
	//�ړ��ʂ���
	else if (mPlayer_State == EAVOIDANCE)
	{
		if (CKey::Push(VK_A)) {
			mPlayer_MoveDir -= mPlayer_SideVec;
		}
		else if (CKey::Push(VK_D)) {
			mPlayer_MoveDir += mPlayer_SideVec;
		}
		if (CKey::Push(VK_W)) {
			mPlayer_MoveDir += mPlayer_FrontVec;
		}
		else if (CKey::Push(VK_S)) {
			mPlayer_MoveDir -= mPlayer_FrontVec;
		}
		//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
		mPlayer_MoveDir = mPlayer_MoveDir.Normalize();//�ړ��ʂ̑��
		mPlayer_MoveDirKeep = mPlayer_MoveDir;	      //MoveDir�ۑ�
	}
	//�ړ���Ԃł������Ԃł��Ȃ��ꍇ
	else {
		//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
		mPlayer_MoveDir = mPlayer_MoveDir.Normalize();//�ړ��ʂ̑��
		mPlayer_MoveDirKeep = mPlayer_MoveDir;		  //MoveDir�ۑ�
	}
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
		shakeX = mPlayer_Gauge_Hp_Shake_X + rand() % mPlayer_Gauge_Hp_Shake_Range_X;
		shakeY = mPlayer_Gauge_Hp_Shake_Y + rand() % mPlayer_Gauge_Hp_Shake_Range_Y;
	}
	//�̗̓Q�[�W
	float HpRate = (float)mPlayer_Hp / (float)mPlayer_Hp_Max;	//�̗͍ő�l�ɑ΂���A���݂̗̑͂̊���
	float HpGaugeWid = PLAYER_GAUGE_WID_MAX * HpRate;	//�̗̓Q�[�W�̕�
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕����傫����
	if (mPlayer_FollowGaugeWid > HpGaugeWid) {
		//���`��ԂŔ�_���[�W����ǂ�����Q�[�W�̕���ݒ肷��
		mPlayer_FollowGaugeWid = Camera.mHpLerp(mPlayer_FollowGaugeWid, HpGaugeWid, mPlayer_Gauge_Hp_Rate);
	}
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕���菬�����Ƃ�
	else if (mPlayer_FollowGaugeWid < HpGaugeWid) {
		//��_���[�W����ǂ�����Q�[�W�̕��ɑ̗̓Q�[�W�̕���ݒ肷��
		mPlayer_FollowGaugeWid = HpGaugeWid;
	}
	//�v���C����HP���Q�[���I�[�o�[�̏���HP�Ɠ����ɂȂ��Ă��܂����ꍇ
	if(mPlayer_Hp >= Player_GameOver_Hp){
		//HP�ԃQ�[�W
		CRes::GetInstance()->GetInUiHpRedGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + mPlayer_FollowGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_FIRST_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
		//HP�΃Q�[�W
		CRes::GetInstance()->GetInUiHpGreenGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + HpGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_FIRST_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
		//�v���C����HP�t���[��
		gPlayer_Ui_Hp_Frame.Draw(PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_RIGHT, PLAYER_GAUGE_FRAME_BOTTOM, PLAYER_GAUGE_FRAME_TOP, PLAYER_GAUGE_FRAME_TEX_FIRST_WID, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_HEI, PLAYER_GAUGE_FRAME_TEX_FIRST_WID);
	}
	//2D�̕`��I��
	CUtil::End2D();
}


//�v���C���̓����蔻��
void CXPlayer::Collision(CCollider* m, CCollider* o) {
	//����̐e�������̎��̓��^�[��
	if (o->Parent() == this)return;
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->CCollider::Type()) {
	case CCollider::ESPHERE: {//���R���C�_
		//����̃R���C�_�����R���C�_�̎�
		if (o->CCollider::Type() == CCollider::ESPHERE) {
			//���̏Փ˔���
			if (CCollider::Collision(m, o)) {
				//����̐e�̃^�O���v���C���[
				if (o->Parent()->Tag() == CCharacter::ETag::EENEMY)
				{
					if (m->CCollider::Tag() == CCollider::EBODY) {
						//����̃R���C�_�̃^�O���E��
						if (o->CCollider::Tag() == CCollider::ERIGHTARM)
						{
							if (((CXEnemy*)(o->Parent()))->GetState() != CXEnemy::EEnemyState::EATTACK_2) {
								//�v���C���[�����G��Ԃł͂Ȃ��Ƃ�
								if (mPlayer_InvincibleFlag == false)
								{
									//�e�̃|�C���^���G���A�U����Ԃł����
									if (((CXEnemy*)(o->Parent()))->GetIsHit() == true)
									{
										//�G�̍U��������~����
										((CXEnemy*)(o->Parent()))->SetIsHit(false);
										//�_���[�W�v�Z����
										mDamage = CXEnemy::GetInstance()->GetIsAttackPoint() * (CXEnemy::GetInstance()->GetIsAttackPoint() / mDefense_Point) + (CXEnemy::GetInstance()->GetIsAttackPoint() * Player_Damage_Magnification);
										//�v���C����HP�����Z
										mPlayer_Hp = mPlayer_Hp - mDamage;
										//�v���C���𖳓G��Ԃɂ���
										mPlayer_InvincibleFlag = true;
										mPlayer_IsHit = false;		//�q�b�g����I��
										//�v���C����e����SE���Đ�
										Se_Enemy_AttackSp.Play(Player_Damage_Se);
										//�m�b�N�o�b�N��Ԃֈڍs
										mPlayer_State = EKNOCKBACK;
										//�X�^���~�ϒl������𒴂��Ă����
										//�m�b�N�o�b�N���A�~�ς����X�^���l������������
										if (Player_StanAccumulation_Max < mStanAccumulation)
										{
											//�X�^���~�ϒl�̏�����
											mStanAccumulation = Player_StanAccumulation;
										}
										//�X�^���~�ϒl������𒴂��Ă��Ȃ����
										//�m�b�N�o�b�N�����A�v���C���̃X�^���~�ϒl�́A�G�̍U���X�^���l���Q�Ƃ��~�ς���
										else {
											//�X�^���_���[�W���Q��
											mStan_Damage = CXEnemy::GetInstance()->GetIsStanPoint() * (CXEnemy::GetInstance()->GetIsStanPoint() / mDefense_Point);
											//�X�^���_���[�W���X�^���~�ϒl�ɒ~�ς�����
											mStanAccumulation = mStanAccumulation + mStan_Damage;
										}
									}

								}
							}
						}
						//�R���C�_�̃|�C���^������ł����
						else if (o->CCollider::Tag() == CCollider::ELEFTARM)
						{
							//�|�C���^���G���A�U��1�̏�Ԃ�
							if (((CXEnemy*)(o->Parent()))->GetState() != CXEnemy::EEnemyState::EATTACK_1) {
								//�v���C���[�����G��Ԃł͂Ȃ��Ƃ�
								if (mPlayer_InvincibleFlag == false)
								{
									//�e�̃|�C���^���G���A�U����Ԃł����
									if (((CXEnemy*)(o->Parent()))->GetIsHit() == true)
									{
										//�G�̍U��������~����
										((CXEnemy*)(o->Parent()))->SetIsHit(false);
										//�_���[�W�v�Z����
										mDamage = CXEnemy::GetInstance()->GetIsAttackPoint() * (CXEnemy::GetInstance()->GetIsAttackPoint() / mDefense_Point) + (CXEnemy::GetInstance()->GetIsAttackPoint() * Player_Damage_Magnification);
										//�v���C����HP�����Z
										mPlayer_Hp = mPlayer_Hp - mDamage;
										//�v���C���𖳓G��Ԃɂ���
										mPlayer_InvincibleFlag = true;
										mPlayer_IsHit = false;		//�q�b�g����I��
										//�v���C����e����SE���Đ�
										Se_Enemy_AttackSp.Play(Player_Damage_Se);
										//�m�b�N�o�b�N��Ԃֈڍs
										mPlayer_State = EKNOCKBACK;
										//�X�^���~�ϒl������𒴂��Ă����
										//�m�b�N�o�b�N���A�~�ς����X�^���l������������
										if (Player_StanAccumulation_Max < mStanAccumulation)
										{
											//�X�^���~�ϒl�̏�����
											mStanAccumulation = Player_StanAccumulation;
										}
										//�X�^���~�ϒl������𒴂��Ă��Ȃ����
										//�m�b�N�o�b�N�����A�v���C���̃X�^���~�ϒl�́A�G�̍U���X�^���l���Q�Ƃ��~�ς���
										else {
											//�X�^���_���[�W���Q��
											mStan_Damage = CXEnemy::GetInstance()->GetIsStanPoint() * (CXEnemy::GetInstance()->GetIsStanPoint() / mDefense_Point);
											//�X�^���_���[�W���X�^���~�ϒl�ɒ~�ς�����
											mStanAccumulation = mStanAccumulation + mStan_Damage;
										}
									}

								}
							}
						}
					}
				}
			}

		}
	}
	break;

	case CCollider::ECAPSUL: {//�J�v�Z���R���C�_
		//����̃R���C�_���J�v�Z���R���C�_�̎�
		if (o->Type() == CCollider::ECAPSUL) {
			CVector adjust;//�����p�x�N�g��
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

	if (m->Type() == CCollider::ESPHERE && o->Type() == CCollider::ETRIANGLE) {
		CVector adjust;//�����p�x�N�g��
		//����̐e�̃^�O���}�b�v
		if (o->Parent()->Tag() == EMAP)
		{
			//�����̃R���C�_�̃^�O����or��
			if (m->Tag() == CCollider::EBODY) {
				if (CCollider::CollisionTriangleSphere(o, m, &adjust))
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
//�ړ��v�Z����
void CXPlayer::MovingCalculation() {
	//����������
	mPlayer_Move = mPlayer_Move * Player_Thrust;							//�v���C���̈ړ��ʂɐ��͂��|����
	//�d�͂��v���C���Ɋ|����
	mPosition.Y(mPosition.Y() * Player_Gravity);							//�v���C����Y���ɏd�͂��|����
	//���W�ړ�
	mPosition += mPlayer_Move;												//�v���C���̈ʒu�Ƀv���C���̈ړ��ʂ𑫂�

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
	//�v���C���̉�]�l���`�F�b�N
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / Player_Trun_Set));

	//��]���x�@degree�ɒ���
	mPlayer_Turnspeed = (Player_Trun_Set / M_PI) * Player_Trun_Speeds_Set;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > Player_Trun_Check_Speeds_Set) tCheck.turn = Player_Trun_Check_Speeds_Set;

	//�ړ������փL��������������
	if (tCheck.cross > Player_Trun_Check_Set) {
		mRotation = mRotation + CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}
	if (tCheck.cross < Player_Trun_Check_Set) {
		mRotation = mRotation - CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}

	//���Z�b�g
	mPlayer_MoveDir = CVector(0.0f, 0.0f, 0.0f);


}
//�^�X�N�ɓ����蔻����i�[����
void CXPlayer::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mPlayer_ColCapsuleBody.ChangePriority();
	mPlayer_ColSphereBody.ChangePriority();
	mPlayer_ColSphereLowerBody.ChangePriority();
	mPlayer_ColSphereHead.ChangePriority();
	mPlayer_ColSphereSword.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mPlayer_ColCapsuleBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereLowerBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereHead, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mPlayer_ColSphereSword, COLLISIONRANGE);
}

//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayer_Instance;
}
//�v���C����HP�̎擾
int CXPlayer::GetHp()
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
//�v���C���̍U���͂��擾����
int CXPlayer::GetIsAttackPoint()
{
	return mAttack_Point;
}
//�v���C���̃X�^���l���擾����
int CXPlayer::GetIsStanPoint()
{
	return mStan_Point;
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
//�ړ��ʎ擾
CVector CXPlayer::GetInMoveDir()
{
	return mPlayer_Move;
}
//�v���C���̏����ʒu���擾
void CXPlayer::GetPos()
{
	mPosition.Set(Player_Position_X, Player_Position_Y, Player_Position_Z);								//�ʒu��ݒ�

}
//�v���C���̃��f���̑傫�����擾
void CXPlayer::GetScale()
{
	mScale.Set(Player_Scale_X, Player_Scale_Y, Player_Scale_Z);										  //�X�P�[���ݒ�

}
//�v���C���̃��f���̏�����]�l���擾
void CXPlayer::GetRotation()
{
	mRotation.Set(Player_Rotation_X, Player_Rotation_Y, Player_Rotation_Z);								//��]��ݒ�
}