#include"CXEnemy.h"
#include"CEnemyData.h"
#include"CRes.h"


CXEnemy* CXEnemy::mpEnemy_Instance = nullptr;





//�R���C�_������
CXEnemy::CXEnemy()
	:mEnemy_Type(CXEnemy::EEnemyType::ETYPE_TUTORIAL)
	, mEnemy_ColCapsuleBody(this, nullptr, CVector(ENEMY_COLCAPSULE_BODY_X, ENEMY_COLCAPSULE_BODY_TOP_Y, ENEMY_COLCAPSULE_BODY_Z), CVector(ENEMY_COLCAPSULE_BODY_X, ENEMY_COLCAPSULE_BODY_BOTTOM_Y, ENEMY_COLCAPSULE_BODY_Z), ENEMY_COLCAPSULE_BODY_SIZE)
	, mEnemy_ColSphereBody(this, nullptr, CVector(ENEMY_COLSPHERE_BODY_X, ENEMY_COLSPHERE_BODY_Y, ENEMY_COLSPHERE_BODY_Z), ENEMY_COLSPHERE_BODY_SIZE)
	, mEnemy_ColSphereRightarm(this, nullptr, CVector(), ENEMY_COLSPHERE_RIGHTARM_SIZE)
	, mEnemy_ColSphereLeftarm(this, nullptr, CVector(), ENEMY_COLSPHERE_LEFTARM_SIZE)
	, mHp(NULL)
	, mDamage(NULL)
	, mAttack_Point(NULL)
	, mDefense_Point(NULL)
	, mStan_Damage(NULL)
	, mStan_Point(NULL)
	, mStanAccumulation(NULL)
	, mEnemy_Speed(ENEMY_SPEED)
	, mEnemy_Turnspeed(ENEMY_TURNSPEED)
	, mEnemy_PlayerDis(ENEMY_FLOAT_INITIALIZATION)
	, mEnemy_FollowGaugeWid(ENEMY_FLOAT_INITIALIZATION)
	, mEnemy_val(ENEMY_INT_INITIALIZATION)
	, mEnemy_IsHit(false)
	, mEnemy_Flag(false)
	, Enemy_Priority(NULL)
	, Enemy_Hp(NULL)
	, Enemy_Hp_Max(NULL)
	, Enemy_Attack_Point(NULL)
	, Enemy_Defense_Point(NULL)
	, Enemy_Stan_Point(NULL)
	, Enemy_Damage_Magnification(NULL)
	, Enemy_Death_Hp(NULL)
	, Enemy_Gravity(NULL)
	, Enemy_StanAccumulation(NULL)
	, Enemy_StanAccumulation_Max(NULL)
	, Enemy_Speed_WalkPattern(NULL)
	, Enemy_Speed_DashPattern(NULL)
	, Enemy_Speed_BackPattern(NULL)
	, Enemy_Walk_Dis(NULL)
	, Enemy_Dash_Dis(NULL)
	, Enemy_Walk_Dis_Max(NULL)
	, Enemy_Dash_Dis_Max(NULL)
	, Enemy_Attack_Dis(NULL)
	, Enemy_Attack_Reception(NULL)
	, Enemy_Attack_Outreception(NULL)
	, Enemy_Action_Rand(NULL)
	, Enemy_Attack_Walk_Rand(NULL)
	, Enemy_Attack_Dash_Rand(NULL)
	, Enemy_AttackSp1_Set(NULL)
	, Enemy_AttackSp2_Set(NULL)
	, Enemy_Idle_Animation_Frame(NULL)
	, Enemy_Move_Animation_Frame(NULL)
	, Enemy_Dash_Animation_Frame(NULL)
	, Enemy_BackStep_Animation_Frame(NULL)
	, Enemy_Attack1_Animation_Frame(NULL)
	, Enemy_Attack2_Animation_Frame(NULL)
	, Enemy_Knockback_Animation_Frame(NULL)
	, Enemy_Death_Animation_Frame(NULL)
	, Enemy_Animation_No_Attack_1(NULL)
	, Enemy_Animation_No_Attack_2(NULL)
	, Enemy_Animation_No_Walk(NULL)
	, Enemy_Animation_No_Dash(NULL)
	, Enemy_Animation_No_BackStep(NULL)
	, Enemy_Animation_No_Idle(NULL)
	, Enemy_Animation_No_Knockback(NULL)
	, Enemy_Animation_No_Death(NULL)
	, Enemy_Position_X(NULL)
	, Enemy_Position_Y(NULL)
	, Enemy_Position_Z(NULL)
	, Enemy_Scale_X(NULL)
	, Enemy_Scale_Y(NULL)
	, Enemy_Scale_Z(NULL)
	, Enemy_Rotation_X(NULL)
	, Enemy_Rotation_Y(NULL)
	, Enemy_Rotation_Z(NULL)
{
	//�e�[�u���̌Ăяo��
	EnemyTable();

	//������Ԃ�ݒ�
	mEnemy_State = CXEnemy::EEnemyState::EIDLE;	//�ҋ@���

	//�|�C���^�̐ݒ�
	mpEnemy_Instance = this;

	//�G��UI�̒ǉ�
	gEnemy_Ui_Hp_BackBar.Load2D(ENEMY_UI_HP_BACKBAR);

	//3D���f���t�@�C���̓ǂݍ���
	gEnemy_Model_Mutant.Load(ENEMY_MODEL_FILE);

	//�G�l�~�[�̃A�j���[�V�����̒ǉ�
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP1);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_BACKSTEP);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);

	//���f���̐ݒ�
	Init(&gEnemy_Model_Mutant);

	//�R���C�_�̃^�O��ݒ�
	mEnemy_ColCapsuleBody.Tag(CCollider::ETag::EBODY);	//��
	mEnemy_ColSphereBody.Tag(CCollider::ETag::EBODY);		//��
	mEnemy_ColSphereRightarm.Tag(CCollider::ETag::ERIGHTARM);	//�E��
	mEnemy_ColSphereLeftarm.Tag(CCollider::ETag::ELEFTARM);	//����


	//�^�X�N����
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mEnemy_ColCapsuleBody.Matrix(&mpCombinedMatrix[2]);
	mEnemy_ColSphereBody.Matrix(&mpCombinedMatrix[2]);
	mEnemy_ColSphereRightarm.Matrix(&mpCombinedMatrix[68]);
	mEnemy_ColSphereLeftarm.Matrix(&mpCombinedMatrix[41]);
}
void CXEnemy::Update() {
	//��Ԃ𔻕�
	switch (mEnemy_State)
	{
	case CXEnemy::EEnemyState::EIDLE:	//�ҋ@���
		Idle();	//�ҋ@�������Ă�
		break;

	case CXEnemy::EEnemyState::EATTACK_1:	//�U��1��Ԃ̎�
		Attack_1();	//�U��1�̏������Ă�
		break;

	case CXEnemy::EEnemyState::EATTACK_2:	//�U��2��Ԃ̎�
		Attack_2();	//�U��2�̏������Ă�
		break;

	case CXEnemy::EEnemyState::EMOVE:	//�ړ����
		Move();	//�ړ���Ԃ̏������Ă�
		break;

	case CXEnemy::EEnemyState::EDASH: //������
		Dash(); //����������Ă�
		break;
	case CXEnemy::EEnemyState::EBACKSTEP://��ޏ��
		BackStep();//��ޏ������Ă�
		break;
	case CXEnemy::EEnemyState::EDEATH: //���S���
		Death(); //���S�������Ă�
		break;

	case CXEnemy::EEnemyState::EKNOCKBACK: //�m�b�N�o�b�N���
		KnockBack(); //�m�b�N�o�b�N�������Ă�
		break;
	}

	MovingCalculation();
	if (mEnemy_PlayerDis >= Enemy_Attack_Dis) {
		mEnemy_AttackDir = mEnemy_Player_Point; //�U�����̌��������߂�
	}
	//�̗͂�0�ɂȂ�Ǝ��S
	if (mHp <= Enemy_Death_Hp)
	{
		mEnemy_State = CXEnemy::EEnemyState::EDEATH;	//���S��Ԃֈڍs
		mHp = Enemy_Death_Hp;
	}
	//�v���C���[�̍U�����肪�����ɂȂ�ƓG�̖��G�������������
	if (CXPlayer::GetInstance()->GetIsHit() == false) {
		mEnemy_Flag = false;
	}

	CXCharacter::Update();
}

void CXEnemy::EnemyTable()
{

	//��������G�̎�ނ𔻕�
	switch (CXEnemy::mEnemy_Type) {
	case CXEnemy::EEnemyType::ETYPE_TUTORIAL:	//�`���[�g���A�����̓G�̋���
	{
		OX::Table table(ENEMY_DATATABLE_TUTORIAL);
		Enemy_Priority = table["Enemy_Priority"]["Value"].iVal;
		Enemy_Hp = table["Enemy_Hp"]["Value"].iVal;
		Enemy_Hp_Max = table["Enemy_Hp_Max"]["Value"].iVal;
		Enemy_Attack_Point = table["Enemy_Attack_Point"]["Value"].iVal;
		Enemy_Defense_Point = table["Enemy_Defense_Point"]["Value"].iVal;
		Enemy_Stan_Point = table["Enemy_Stan_Point"]["Value"].iVal;
		Enemy_Damage_Magnification = table["Enemy_Damage_Magnification"]["Value"].fVal;
		Enemy_Death_Hp = table["Enemy_Death_Hp"]["Value"].iVal;
		Enemy_Gravity = table["Enemy_Gravity"]["Value"].fVal;
		Enemy_StanAccumulation = table["Enemy_StanAccumulation"]["Value"].iVal;
		Enemy_StanAccumulation_Max = table["Enemy_StanAccumulation_Max"]["Value"].iVal;
		Enemy_Speed_WalkPattern = table["Enemy_Speed_WalkPattern"]["Value"].fVal;
		Enemy_Speed_DashPattern = table["Enemy_Speed_DashPattern"]["Value"].fVal;
		Enemy_Speed_BackPattern = table["Enemy_Speed_BackPattern"]["Value"].fVal;
		Enemy_Walk_Dis = table["Enemy_Walk_Dis"]["Value"].fVal;
		Enemy_Dash_Dis = table["Enemy_Dash_Dis"]["Value"].fVal;
		Enemy_Walk_Dis_Max = table["Enemy_Walk_Dis_Max"]["Value"].fVal;
		Enemy_Dash_Dis_Max = table["Enemy_Dash_Dis_Max"]["Value"].fVal;
		Enemy_Attack_Dis = table["Enemy_Attack_Dis"]["Value"].fVal;
		Enemy_Attack_Reception = table["Enemy_Attack_Reception"]["Value"].fVal;
		Enemy_Attack_Outreception = table["Enemy_Attack_Outreception"]["Value"].fVal;
		Enemy_Action_Rand = table["Enemy_Action_Rand"]["Value"].iVal;
		Enemy_Attack_Walk_Rand = table["Enemy_Attack_Walk_Rand"]["Value"].iVal;
		Enemy_Attack_Dash_Rand = table["Enemy_Attack_Dash_Rand"]["Value"].iVal;
		Enemy_AttackSp1_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_AttackSp2_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_Idle_Animation_Frame = table["Enemy_Idle_Animation_Frame"]["Value"].fVal;
		Enemy_Move_Animation_Frame = table["Enemy_Move_Animation_Frame"]["Value"].fVal;
		Enemy_Dash_Animation_Frame = table["Enemy_Dash_Animation_Frame"]["Value"].fVal;
		Enemy_BackStep_Animation_Frame = table["Enemy_BackStep_Animation_Frame"]["Value"].fVal;
		Enemy_Attack1_Animation_Frame = table["Enemy_Attack1_Animation_Frame"]["Value"].fVal;
		Enemy_Attack2_Animation_Frame = table["Enemy_Attack2_Animation_Frame"]["Value"].fVal;
		Enemy_Knockback_Animation_Frame = table["Enemy_Knockback_Animation_Frame"]["Value"].fVal;
		Enemy_Death_Animation_Frame = table["Enemy_Death_Animation_Frame"]["Value"].fVal;
		Enemy_Animation_No_Attack_1 = table["Enemy_Animation_No_Attack_1"]["Value"].iVal;
		Enemy_Animation_No_Attack_2 = table["Enemy_Animation_No_Attack_2"]["Value"].iVal;
		Enemy_Animation_No_Walk = table["Enemy_Animation_No_Walk"]["Value"].iVal;
		Enemy_Animation_No_Dash = table["Enemy_Animation_No_Dash"]["Value"].iVal;
		Enemy_Animation_No_BackStep = table["Enemy_Animaton_No_BackStep"]["Value"].iVal;
		Enemy_Animation_No_Idle = table["Enemy_Animation_No_Idle"]["Value"].iVal;
		Enemy_Animation_No_Knockback = table["Enemy_Animation_No_Knockback"]["Value"].iVal;
		Enemy_Animation_No_Death = table["Enemy_Animation_No_Death"]["Value"].iVal;
		Enemy_Position_X = table["Enemy_Tutorial_Position_X"]["Value"].fVal;
		Enemy_Position_Y = table["Enemy_Tutoria_Position_Y"]["Value"].fVal;
		Enemy_Position_Z = table["Enemy_Tutoria_Position_Z"]["Value"].fVal;
		Enemy_Scale_X = table["Enemy_Scale_X"]["Value"].fVal;
		Enemy_Scale_Y = table["Enemy_Scale_Y"]["Value"].fVal;
		Enemy_Scale_Z = table["Enemy_Scale_Z"]["Value"].fVal;
		Enemy_Rotation_X = table["Enemy_Rotation_X"]["Value"].fVal;
		Enemy_Rotation_Y = table["Enemy_Rotation_Y"]["Value"].fVal;
		Enemy_Rotation_Z = table["Enemy_Rotation_Z"]["Value"].fVal;
		//�^�O�̐ݒ�
		mTag = CCharacter::ETag::EENEMY;
		//�D��x��1�ɕύX����
		mPriority = Enemy_Priority;
		mHp = Enemy_Hp;
		mAttack_Point = Enemy_Attack_Point;
		mDefense_Point = Enemy_Defense_Point;
		mStan_Point = Enemy_Stan_Point;
		mStanAccumulation = Enemy_StanAccumulation;
		mPosition.Set(Enemy_Position_X, Enemy_Position_Y, Enemy_Position_Z);
		mScale.Set(Enemy_Scale_X, Enemy_Scale_Y, Enemy_Scale_Z);
		mRotation.Set(Enemy_Rotation_X, Enemy_Rotation_Y, Enemy_Rotation_Z);
	}
	break;

	case CXEnemy::EEnemyType::ETYPE_GAME_1:	//�Q�[���{�Ԃ̓G�̋���
	{
		OX::Table table(ENEMY_DATATABLE_MAINGAME1);
		Enemy_Priority = table["Enemy_Priority"]["Value"].iVal;
		Enemy_Hp = table["Enemy_Hp"]["Value"].iVal;
		Enemy_Hp_Max = table["Enemy_Hp_Max"]["Value"].iVal;
		Enemy_Attack_Point = table["Enemy_Attack_Point"]["Value"].iVal;
		Enemy_Defense_Point = table["Enemy_Defense_Point"]["Value"].iVal;
		Enemy_Stan_Point = table["Enemy_Stan_Point"]["Value"].iVal;
		Enemy_Damage_Magnification = table["Enemy_Damage_Magnification"]["Value"].fVal;
		Enemy_Death_Hp = table["Enemy_Death_Hp"]["Value"].iVal;
		Enemy_Gravity = table["Enemy_Gravity"]["Value"].fVal;
		Enemy_StanAccumulation = table["Enemy_StanAccumulation"]["Value"].iVal;
		Enemy_StanAccumulation_Max = table["Enemy_StanAccumulation_Max"]["Value"].iVal;
		Enemy_Speed_WalkPattern = table["Enemy_Speed_WalkPattern"]["Value"].fVal;
		Enemy_Speed_DashPattern = table["Enemy_Speed_DashPattern"]["Value"].fVal;
		Enemy_Speed_BackPattern = table["Enemy_Speed_BackPattern"]["Value"].fVal;
		Enemy_Walk_Dis = table["Enemy_Walk_Dis"]["Value"].fVal;
		Enemy_Dash_Dis = table["Enemy_Dash_Dis"]["Value"].fVal;
		Enemy_Walk_Dis_Max = table["Enemy_Walk_Dis_Max"]["Value"].fVal;
		Enemy_Dash_Dis_Max = table["Enemy_Dash_Dis_Max"]["Value"].fVal;
		Enemy_Attack_Dis = table["Enemy_Attack_Dis"]["Value"].fVal;
		Enemy_Attack_Reception = table["Enemy_Attack_Reception"]["Value"].fVal;
		Enemy_Attack_Outreception = table["Enemy_Attack_Outreception"]["Value"].fVal;
		Enemy_Action_Rand = table["Enemy_Action_Rand"]["Value"].iVal;
		Enemy_Attack_Walk_Rand = table["Enemy_Attack_Walk_Rand"]["Value"].iVal;
		Enemy_Attack_Dash_Rand = table["Enemy_Attack_Dash_Rand"]["Value"].iVal;
		Enemy_AttackSp1_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_AttackSp2_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_Idle_Animation_Frame = table["Enemy_Idle_Animation_Frame"]["Value"].fVal;
		Enemy_Move_Animation_Frame = table["Enemy_Move_Animation_Frame"]["Value"].fVal;
		Enemy_Dash_Animation_Frame = table["Enemy_Dash_Animation_Frame"]["Value"].fVal;
		Enemy_BackStep_Animation_Frame = table["Enemy_BackStep_Animation_Frame"]["Value"].fVal;
		Enemy_Attack1_Animation_Frame = table["Enemy_Attack1_Animation_Frame"]["Value"].fVal;
		Enemy_Attack2_Animation_Frame = table["Enemy_Attack2_Animation_Frame"]["Value"].fVal;
		Enemy_Knockback_Animation_Frame = table["Enemy_Knockback_Animation_Frame"]["Value"].fVal;
		Enemy_Death_Animation_Frame = table["Enemy_Death_Animation_Frame"]["Value"].fVal;
		Enemy_Animation_No_Attack_1 = table["Enemy_Animation_No_Attack_1"]["Value"].iVal;
		Enemy_Animation_No_Attack_2 = table["Enemy_Animation_No_Attack_2"]["Value"].iVal;
		Enemy_Animation_No_Walk = table["Enemy_Animation_No_Walk"]["Value"].iVal;
		Enemy_Animation_No_Dash = table["Enemy_Animation_No_Dash"]["Value"].iVal;
		Enemy_Animation_No_BackStep = table["Enemy_Animaton_No_BackStep"]["Value"].iVal;
		Enemy_Animation_No_Idle = table["Enemy_Animation_No_Idle"]["Value"].iVal;
		Enemy_Animation_No_Knockback = table["Enemy_Animation_No_Knockback"]["Value"].iVal;
		Enemy_Animation_No_Death = table["Enemy_Animation_No_Death"]["Value"].iVal;
		Enemy_Position_X = table["Enemy_MainGame1_Position_X"]["Value"].fVal;
		Enemy_Position_Y = table["Enemy_MainGame1_Position_Y"]["Value"].fVal;
		Enemy_Position_Z = table["Enemy_MainGame1_Position_Z"]["Value"].fVal;
		Enemy_Scale_X = table["Enemy_Scale_X"]["Value"].fVal;
		Enemy_Scale_Y = table["Enemy_Scale_Y"]["Value"].fVal;
		Enemy_Scale_Z = table["Enemy_Scale_Z"]["Value"].fVal;
		Enemy_Rotation_X = table["Enemy_Rotation_X"]["Value"].fVal;
		Enemy_Rotation_Y = table["Enemy_Rotation_Y"]["Value"].fVal;
		Enemy_Rotation_Z = table["Enemy_Rotation_Z"]["Value"].fVal;
		//�^�O�̐ݒ�
		mTag = CCharacter::ETag::EENEMY;
		//�D��x��1�ɕύX����
		mPriority = Enemy_Priority;
		mHp = Enemy_Hp;
		mAttack_Point = Enemy_Attack_Point;
		mDefense_Point = Enemy_Defense_Point;
		mStan_Point = Enemy_Stan_Point;
		mStanAccumulation = Enemy_StanAccumulation;
		mPosition.Set(Enemy_Position_X, Enemy_Position_Y, Enemy_Position_Z);
		mScale.Set(Enemy_Scale_X, Enemy_Scale_Y, Enemy_Scale_Z);
		mRotation.Set(Enemy_Rotation_X, Enemy_Rotation_Y, Enemy_Rotation_Z);
	}
	break;

	case CXEnemy::EEnemyType::ETYPE_GAME_2:	//�Q�[���{�Ԏ��̓G�̋���
	{
		OX::Table table(ENEMY_DATATABLE_MAINGAME2);
		Enemy_Priority = table["Enemy_Priority"]["Value"].iVal;
		Enemy_Hp = table["Enemy_Hp"]["Value"].iVal;
		Enemy_Hp_Max = table["Enemy_Hp_Max"]["Value"].iVal;
		Enemy_Attack_Point = table["Enemy_Attack_Point"]["Value"].iVal;
		Enemy_Defense_Point = table["Enemy_Defense_Point"]["Value"].iVal;
		Enemy_Stan_Point = table["Enemy_Stan_Point"]["Value"].iVal;
		Enemy_Damage_Magnification = table["Enemy_Damage_Magnification"]["Value"].fVal;
		Enemy_Death_Hp = table["Enemy_Death_Hp"]["Value"].iVal;
		Enemy_Gravity = table["Enemy_Gravity"]["Value"].fVal;
		Enemy_StanAccumulation = table["Enemy_StanAccumulation"]["Value"].iVal;
		Enemy_StanAccumulation_Max = table["Enemy_StanAccumulation_Max"]["Value"].iVal;
		Enemy_Speed_WalkPattern = table["Enemy_Speed_WalkPattern"]["Value"].fVal;
		Enemy_Speed_DashPattern = table["Enemy_Speed_DashPattern"]["Value"].fVal;
		Enemy_Speed_BackPattern = table["Enemy_Speed_BackPattern"]["Value"].fVal;
		Enemy_Walk_Dis = table["Enemy_Walk_Dis"]["Value"].fVal;
		Enemy_Dash_Dis = table["Enemy_Dash_Dis"]["Value"].fVal;
		Enemy_Walk_Dis_Max = table["Enemy_Walk_Dis_Max"]["Value"].fVal;
		Enemy_Dash_Dis_Max = table["Enemy_Dash_Dis_Max"]["Value"].fVal;
		Enemy_Attack_Dis = table["Enemy_Attack_Dis"]["Value"].fVal;
		Enemy_Attack_Reception = table["Enemy_Attack_Reception"]["Value"].fVal;
		Enemy_Attack_Outreception = table["Enemy_Attack_Outreception"]["Value"].fVal;
		Enemy_Action_Rand = table["Enemy_Action_Rand"]["Value"].iVal;
		Enemy_Attack_Walk_Rand = table["Enemy_Attack_Walk_Rand"]["Value"].iVal;
		Enemy_Attack_Dash_Rand = table["Enemy_Attack_Dash_Rand"]["Value"].iVal;
		Enemy_AttackSp1_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_AttackSp2_Set = table["Enemy_AttackSp1_Set"]["Value"].iVal;
		Enemy_Idle_Animation_Frame = table["Enemy_Idle_Animation_Frame"]["Value"].fVal;
		Enemy_Move_Animation_Frame = table["Enemy_Move_Animation_Frame"]["Value"].fVal;
		Enemy_Dash_Animation_Frame = table["Enemy_Dash_Animation_Frame"]["Value"].fVal;
		Enemy_BackStep_Animation_Frame = table["Enemy_BackStep_Animation_Frame"]["Value"].fVal;
		Enemy_Attack1_Animation_Frame = table["Enemy_Attack1_Animation_Frame"]["Value"].fVal;
		Enemy_Attack2_Animation_Frame = table["Enemy_Attack2_Animation_Frame"]["Value"].fVal;
		Enemy_Knockback_Animation_Frame = table["Enemy_Knockback_Animation_Frame"]["Value"].fVal;
		Enemy_Death_Animation_Frame = table["Enemy_Death_Animation_Frame"]["Value"].fVal;
		Enemy_Animation_No_Attack_1 = table["Enemy_Animation_No_Attack_1"]["Value"].iVal;
		Enemy_Animation_No_Attack_2 = table["Enemy_Animation_No_Attack_2"]["Value"].iVal;
		Enemy_Animation_No_Walk = table["Enemy_Animation_No_Walk"]["Value"].iVal;
		Enemy_Animation_No_Dash = table["Enemy_Animation_No_Dash"]["Value"].iVal;
		Enemy_Animation_No_BackStep = table["Enemy_Animaton_No_BackStep"]["Value"].iVal;
		Enemy_Animation_No_Idle = table["Enemy_Animation_No_Idle"]["Value"].iVal;
		Enemy_Animation_No_Knockback = table["Enemy_Animation_No_Knockback"]["Value"].iVal;
		Enemy_Animation_No_Death = table["Enemy_Animation_No_Death"]["Value"].iVal;
		Enemy_Position_X = table["Enemy_MainGame2_Position_X"]["Value"].fVal;
		Enemy_Position_Y = table["Enemy_MainGame2_Position_Y"]["Value"].fVal;
		Enemy_Position_Z = table["Enemy_MainGame2_Position_Z"]["Value"].fVal;
		Enemy_Scale_X = table["Enemy_Scale_X"]["Value"].fVal;
		Enemy_Scale_Y = table["Enemy_Scale_Y"]["Value"].fVal;
		Enemy_Scale_Z = table["Enemy_Scale_Z"]["Value"].fVal;
		Enemy_Rotation_X = table["Enemy_Rotation_X"]["Value"].fVal;
		Enemy_Rotation_Y = table["Enemy_Rotation_Y"]["Value"].fVal;
		Enemy_Rotation_Z = table["Enemy_Rotation_Z"]["Value"].fVal;
		//�^�O�̐ݒ�
		mTag = CCharacter::ETag::EENEMY;
		//�D��x��1�ɕύX����
		mPriority = Enemy_Priority;
		mHp = Enemy_Hp;
		mAttack_Point = Enemy_Attack_Point;
		mDefense_Point = Enemy_Defense_Point;
		mStan_Point = Enemy_Stan_Point;
		mStanAccumulation = Enemy_StanAccumulation;
		mPosition.Set(Enemy_Position_X, Enemy_Position_Y, Enemy_Position_Z);
		mScale.Set(Enemy_Scale_X, Enemy_Scale_Y, Enemy_Scale_Z);
		mRotation.Set(Enemy_Rotation_X, Enemy_Rotation_Y, Enemy_Rotation_Z);
	}
	break;

	}
}

void CXEnemy::TaskCollision()
{
	//�R���C�_�̗D��x�ύX
	mEnemy_ColCapsuleBody.ChangePriority();
	mEnemy_ColSphereBody.ChangePriority();
	mEnemy_ColSphereRightarm.ChangePriority();
	mEnemy_ColSphereLeftarm.ChangePriority();
	//�Փˏ��������s
	CCollisionManager::Get()->Collision(&mEnemy_ColCapsuleBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereRightarm, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mEnemy_ColSphereLeftarm, COLLISIONRANGE);
}


void CXEnemy::Render2D()
{
	//2D�`��J�n
	CUtil::Start2D(WINDOW_FIRST_WIDTH, WINDOW_WIDTH, WINDOW_FIRST_HEIGHT, WINDOW_HEIGHT);
	CVector tpos;
	CVector ret;
	tpos = mPosition + CVector(ret.X(), mPosition.Y() + ENEMY_GAUGE_HP_Y, ret.Z());
	Camera.WorldToScreen(&ret, tpos);
	float HpRate = (float)mHp / (float)Enemy_Hp_Max; //�̗͍ő�l�ɑ΂���A���݂̗̑͂̊���
	float HpGaugeWid = ENEMY_GAUGE_WID_MAX * HpRate; //�̗̓Q�[�W�̕�
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕����傫����
	if (mEnemy_FollowGaugeWid > HpGaugeWid) {
		//���`��ԂŔ�_���[�W����ǂ�����Q�[�W�̕���ݒ肷��
		mEnemy_FollowGaugeWid = Camera.mHpLerp(mEnemy_FollowGaugeWid, HpGaugeWid, ENEMY_GAUGE_HP_RATE);
	}
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕���菬�����Ƃ�
	else if (mEnemy_FollowGaugeWid < HpGaugeWid) {
		//��_���[�W����ǂ�����Q�[�W�̕��ɑ̗̓Q�[�W�̕���ݒ肷��
		mEnemy_FollowGaugeWid = HpGaugeWid;
	}
	//��ʊO�̎��ɕ\�����Ȃ�
	if (ret.X() > WINDOW_FIRST_WIDTH && ret.X() < WINDOW_WIDTH) {
		if (mHp > Enemy_Death_Hp) {
			if (!CXPlayer::GetInstance()->GetHp() == NULL) {
				gEnemy_Ui_Hp_BackBar.Draw(ret.X() - ENEMY_GAUGE_WID_MAX, ret.X() + ENEMY_GAUGE_WID_MAX, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 0, 30);
				//��_���[�W����ǂ�����Q�[�W��\��
				CRes::GetInstance()->GetInUiHpRedGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + mEnemy_FollowGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
				//�̗̓Q�[�W
				CRes::GetInstance()->GetInUiHpGreenGauge().Draw(ret.X() - ENEMY_GAUGE_WID_MAX, (ret.X() - ENEMY_GAUGE_WID_MAX) + HpGaugeWid * 2.0f, ret.Y() + ENEMY_GAUGE_HP_BOTTOM, ret.Y() + ENEMY_GAUGE_HP_TOP, 0, 480, 10, 30);
			}
		}
	}
	//2D�̕`��I��
	CUtil::End2D();
}

void CXEnemy::Idle()
{
	int random = ENEMY_INT_INITIALIZATION;
	//�v���C���[�����S��Ԃł͖����Ƃ�
	if (CXPlayer::EPlayerState::EDEATH != CXPlayer::GetInstance()->GetState())
	{
		mEnemy_Flag = false;
		//�v���C���[����苗���܂ŋ߂Â��ƒǐՏ�Ԃֈڍs
		if (mEnemy_PlayerDis <= Enemy_Walk_Dis)
		{
			mEnemy_State = CXEnemy::EEnemyState::EMOVE;
		}
		else if (mEnemy_PlayerDis <= Enemy_Dash_Dis)
		{
			mEnemy_State = CXEnemy::EEnemyState::EDASH;
		}
		else
		{
			//�A�j���[�V�����̐ݒ�
			ChangeAnimation(Enemy_Animation_No_Idle, true, Enemy_Idle_Animation_Frame);
		}
	}
	else
	{
		//�A�j���[�V�����̐ݒ�
		ChangeAnimation(Enemy_Animation_No_Idle, true, Enemy_Idle_Animation_Frame);
	}
}
void CXEnemy::Move() {
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(Enemy_Animation_No_Walk, true, Enemy_Move_Animation_Frame);
	mEnemy_Speed = Enemy_Speed_WalkPattern;
	//�ړI�n�_�܂ł̃x�N�g�������߂�
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDir�Ƀv���C���[�����̃x�N�g��������
	mEnemy_MoveDir.Y(ENEMY_FLOAT_INITIALIZATION);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//�ڕW�n�_���X�V
	int r = rand() % Enemy_Attack_Walk_Rand; //rand()�͐����̗�����Ԃ�
	//%Enemy_Attack_Walk_Rand��Enemy_Attack_Walk_Rand�Ŋ������]������߂�
	//�U���o���鋗���ɂ��Ȃ���ΖڕW�n�_�Ɉړ�
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = ENEMY_INT_INITIALIZATION;
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
	{
		if (random == ENEMY_INT_INITIALIZATION)
		{
			//�����_���ōU���̎�ނ����߂�
			random = rand() % 2;
			switch (random)
			{
			case 0:
				mEnemy_State = CXEnemy::EEnemyState::EATTACK_1; //�U��1��Ԃֈڍs
				break;
			case 1:
				mEnemy_State = CXEnemy::EEnemyState::EATTACK_2; //�U��2��Ԃֈڍs
				break;
			}
		}
	}
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mEnemy_PlayerDis >= Enemy_Walk_Dis_Max)
	{
		mEnemy_State = CXEnemy::EEnemyState::EIDLE; //�ҋ@��Ԃֈڍs
	}

}

void CXEnemy::Dash()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(Enemy_Animation_No_Dash, true, Enemy_Dash_Animation_Frame);
	//�ړ��X�s�[�h��ύX
	mEnemy_Speed = Enemy_Speed_DashPattern;
	//�ړI�n�_�܂ł̃x�N�g�������߂�
	mEnemy_Player_Point = mEnemy_Point - mPosition;
	//mMoveDir�ɖڕW�n�_�����̃x�N�g��������
	mEnemy_MoveDir.Y(ENEMY_FLOAT_INITIALIZATION);
	mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
	//�ڕW�n�_���X�V
	int r = rand() % Enemy_Attack_Dash_Rand; //rand()�͐����̗�����Ԃ�
	//%Enemy_Attack_Dash_Rand��Enemy_Attack_Dash_Rand�Ŋ������]������߂�
	//�U���o���鋗���ɂ��Ȃ���ΖڕW�n�_�Ɉړ�
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	int random = ENEMY_INT_INITIALIZATION;
	//�v���C���[���U���\�ȋ����ɂ���Ƃ�
	if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
	{
		if (random == ENEMY_INT_INITIALIZATION)
		{
			//�����_���ōU���̎�ނ����߂�
			random = rand() % Enemy_Action_Rand;
			switch (random)
			{
			case 0:
				mEnemy_State = CXEnemy::EEnemyState::EATTACK_1; //�U��1��Ԃֈڍs
				break;
			case 1:
				mEnemy_State = CXEnemy::EEnemyState::EATTACK_2; //�U��2��Ԃֈڍs
				break;
			}
		}
	}
	//�v���C���[���ǐՉ\�ȋ����ɂ��Ȃ��Ƃ�
	if (mEnemy_PlayerDis >= Enemy_Dash_Dis_Max)
	{
		mEnemy_State = CXEnemy::EEnemyState::EIDLE; //�ҋ@��Ԃֈڍs
	}

	CTransform::Update();

}

void CXEnemy::BackStep()
{
	if (mEnemy_Flag == false)
	{
		ChangeAnimation(Enemy_Animation_No_BackStep, false, Enemy_BackStep_Animation_Frame);
		mEnemy_Flag = true;
	}
	if (IsAnimationFinished() == false && mAnimationIndex == Enemy_Animation_No_BackStep) {
		//�o�b�N����
		CVector BackVec = mEnemy_Player_Point.Normalize();
		//�o�b�N��
		float BackAmount = Enemy_Speed_BackPattern;
		//�o�b�N������
		mPosition -= BackVec * BackAmount;
	}
	if (IsAnimationFinished()) {
		//�v���C���[���U���\�ȋ����ɂ��Ȃ��Ƃ�
		if (mEnemy_PlayerDis >= Enemy_Attack_Dis)
		{
			mEnemy_State = CXEnemy::EEnemyState::EDASH;
		}
		else if (mEnemy_PlayerDis < Enemy_Attack_Dis)
		{
			mEnemy_State = CXEnemy::EEnemyState::EATTACK_1;
		}
	}
}

void CXEnemy::Attack_1()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(Enemy_Animation_No_Attack_1, false, Enemy_Attack1_Animation_Frame);

	//�U���o���鋗���ɋ���ΒǏ]���čU��
	int r = rand() % Enemy_AttackSp1_Set; //rand()�͐����̗�����Ԃ�
	//%Enemy_AttackSp1_Set��Enemy_AttackSp1_Set�Ŋ������]������߂�
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}
	//�q�b�g���蔭��
	if (IsAnimationFinished() == false)
	{
		//�ړI�n�_�܂ł̃x�N�g�������߂�
		mEnemy_Player_Point = mEnemy_Point - mPosition;
		mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		else if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else{
			mEnemy_IsHit = true;
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}

	}

	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //�q�b�g����I��
		int random = ENEMY_INT_INITIALIZATION;
		//�v���C���[���U���\�ȋ����ɂ���Ƃ�
		if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
		{
			if (random == ENEMY_INT_INITIALIZATION)
			{
				//�����_���ōU���̎�ނ����߂�
				random = rand() % Enemy_Action_Rand;
				switch (random)
				{
				case 0:
					mEnemy_State = CXEnemy::EEnemyState::EBACKSTEP; //�o�b�N�X�e�b�v�ֈڍs
					break;
				case 1:
					mEnemy_State = CXEnemy::EEnemyState::EATTACK_2; //�U��2��Ԃֈڍs
					break;
				}
			}
		}
		else {
			mEnemy_State = CXEnemy::EEnemyState::EDASH; //���s�ֈڍs
		}
	}
}

void CXEnemy::Attack_2()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(Enemy_Animation_No_Attack_2, false, Enemy_Attack2_Animation_Frame);

	//�U���o���鋗���ɋ���ΒǏ]���čU��
	int r = rand() % Enemy_AttackSp2_Set; //rand()�͐����̗�����Ԃ�
	//%Enemy_AttackSp2_Set��Enemy_AttackSp2_Set�Ŋ������]������߂�
	if (mEnemy_PlayerDis > Enemy_Attack_Dis)
	{
		if (r == ENEMY_INT_INITIALIZATION)
		{
			mEnemy_Point = CXPlayer::GetInstance()->Position();
		}
	}

	//�q�b�g���蔭��
	if (IsAnimationFinished() == false)
	{
		//�ړI�n�_�܂ł̃x�N�g�������߂�
		mEnemy_Player_Point = mEnemy_Point - mPosition;
		mEnemy_MoveDir = mEnemy_Player_Point.Normalize();
		if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EAVOIDANCE)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t�O�̎��́A�����蔻���false�ɂ���
		else if (mAnimationFrame <= Enemy_Attack_Reception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}
		//�A�j���[�V�����t���[���̓����蔻�肪��t���Ԃ̂��߁A�����蔻���true�ɂ���
		else {
				mEnemy_IsHit = true;
		}
		//�A�j���[�V�����t���[���������蔻��̏I���̎��́A�����蔻���false�ɂ���
		if (mAnimationFrame > Enemy_Attack_Outreception)
		{
			mEnemy_IsHit = false; //�q�b�g����I��
		}

	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mEnemy_IsHit = false; //�q�b�g����I��
		int random = ENEMY_INT_INITIALIZATION;
		//�v���C���[���U���\�ȋ����ɂ���Ƃ�
		if (mEnemy_PlayerDis <= Enemy_Attack_Dis)
		{
			if (random == ENEMY_INT_INITIALIZATION)
			{
				//�����_���ōU���̎�ނ����߂�
				random = rand() % Enemy_Action_Rand;
				switch (random)
				{
				case 0:
					mEnemy_State = CXEnemy::EEnemyState::EATTACK_1; //�U��1��Ԃֈڍs
					break;
				case 1:
					mEnemy_State = CXEnemy::EEnemyState::EBACKSTEP; //�o�b�N�X�e�b�v�ֈڍs
					break;
				}
			}
		}
		else {
			mEnemy_State = CXEnemy::EEnemyState::EDASH; //���s�ֈڍs
		}
	}
}


void CXEnemy::KnockBack()
{
	//�A�j���[�V�����̐ݒ�
	ChangeAnimation(Enemy_Animation_No_Knockback, false, Enemy_Knockback_Animation_Frame);
	//�A�j���[�V�������Đ�����
	if (IsAnimationFinished() == false)
	{
		mEnemy_IsHit = false;
	}
	//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		//�����蔻��̃t���O�𔻒肷��悤�ɕύX
		mEnemy_Flag = false;
		mEnemy_State = CXEnemy::EEnemyState::EATTACK_2; //�U��2
	}
}

void CXEnemy::Death()
{
	//���S�A�j���[�V����
	ChangeAnimation(Enemy_Animation_No_Death, false, Enemy_Death_Animation_Frame);
	//�G�̍U�������false�ɂ���
	mEnemy_IsHit = false;
}

void CXEnemy::Collision(CCollider* m, CCollider* o) {
	//����̐e�������̎��̓��^�[��
	if (o->Parent() == this)return;

	if (m->CCollider::Type() == CCollider::EType::ECAPSUL && o->CCollider::Type() == CCollider::EType::ECAPSUL)
	{
		CVector adjust;//�����p�x�N�g��
		//�R���C�_��m��o���Փ˂��Ă��邩�̔���
		if (CCollider::CollisionCapsule(m, o, &adjust))
		{
			if (m->CCollider::Tag() == CCollider::ETag::EBODY && o->CCollider::Tag() == CCollider::ETag::EBODY)
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();
			}
		}
	}

	//�J�v�Z���ƎO�p�`�̏Փˏ���
	if (m->Type() == CCollider::EType::ECAPSUL && o->Type() == CCollider::EType::ETRIANGLE) {
		CVector adjust;//�����p�x�N�g��
		//�O�p�`�R���C�_�ƃJ�v�Z���̏Փˏ���
		if (CCollider::CollisionTriangleLine(o, m, &adjust))
		{
			mPosition.Y(NULL);
			//�ʒu�̍X�V(mPosition + adjust)
			mPosition = mPosition + adjust;
			//�s��̍X�V
			CTransform::Update();
		}

	}
	if (m->Type() == CCollider::EType::ESPHERE && o->Type() == CCollider::EType::ETRIANGLE) {
		CVector adjust;//�����p�x�N�g��
		//����̐e�̃^�O���}�b�v
		if (o->Parent()->Tag() == CCharacter::ETag::EMAP)
		{
			//�����̃R���C�_�̃^�O����or��
			if (m->Tag() == CCollider::ETag::EBODY) {
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

	//�G�����S���Ă��Ȃ��Ƃ�
	if (mEnemy_State != EEnemyState::EDEATH) {
		//���g�̃R���C�_�^�C�v�̔���
		if (m->Type() == CCollider::EType::ESPHERE) {
			//����̃R���C�_�����R���C�_�̎�
			if (o->Type() == CCollider::EType::ESPHERE) {
				//���̏Փ˔���
				if (CCollider::Collision(m, o)) {
					//����̐e�̃^�O���v���C���[
					if (o->Parent()->Tag() == CCharacter::ETag::EPLAYER)
					{
						//����̃R���C�_�̃^�O����
						if (o->Tag() == CCollider::ETag::ESWORD)
						{
							if (CXPlayer::GetInstance()->GetState() != CXPlayer::EPlayerState::EDEATH)
							{
								if (CXPlayer::GetInstance()->GetIsHit() == true) {
									//�_���[�W����
									//1�x�����������Ȃ����߂̃J�E���^
									if (mEnemy_Flag == false)
									{
										if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_1)
										{
											//�_���[�W�v�Z
											mDamage = CXPlayer::GetInstance()->GetIsAttackPoint() * (CXPlayer::GetInstance()->GetIsAttackPoint() / mDefense_Point) + (CXPlayer::GetInstance()->GetIsAttackPoint() * Enemy_Damage_Magnification);
											//�_���[�W����
											mHp = mHp - mDamage;
											//�U�������false�ɂ���
											mEnemy_IsHit = false;
											//���������Ƃ��̃G�t�F�N�g
											new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 2, 5, 2);
											new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 4, 5, 2);
											//���ݒl������𒴂�����A�Ђ��
											if (Enemy_StanAccumulation_Max <= mStanAccumulation)
											{
												//�m�b�N�o�b�N����
												mEnemy_State = CXEnemy::EEnemyState::EKNOCKBACK;
												mStanAccumulation = Enemy_StanAccumulation;
											}
											else {
												//�G�̂Ђ�ݒl�ݒ�
												mStan_Damage = CXPlayer::GetInstance()->GetIsStanPoint() * (CXPlayer::GetInstance()->GetIsStanPoint() / mDefense_Point) + (CXPlayer::GetInstance()->GetIsStanPoint() * Enemy_Damage_Magnification);
												mStanAccumulation = mStanAccumulation + mStan_Damage;
											}

										}
										else if (CXPlayer::GetInstance()->GetState() == CXPlayer::EPlayerState::EATTACK_2)
										{
											//�_���[�W�v�Z
											mDamage = CXPlayer::GetInstance()->GetIsAttackPoint() * (CXPlayer::GetInstance()->GetIsAttackPoint() / mDefense_Point) + (CXPlayer::GetInstance()->GetIsAttackPoint() * Enemy_Damage_Magnification);
											//�_���[�W����
											mHp = mHp - mDamage;
											//�U�������false�ɂ���
											mEnemy_IsHit = false;
											//���������Ƃ��̃G�t�F�N�g
											new CEffectEnemyDamageSp1(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP1, 2, 5, 2);
											new CEffectEnemyDamageSp2(CXPlayer::GetInstance()->GetSwordColPos(), 2.0f, 2.0f, ENEMY_EF_DAMAGESP2, 4, 5, 2);
											//���ݒl������𒴂�����A�Ђ��
											if (Enemy_StanAccumulation_Max <= mStanAccumulation)
											{
												//�m�b�N�o�b�N����
												mEnemy_State = CXEnemy::EEnemyState::EKNOCKBACK;
												mStanAccumulation = Enemy_StanAccumulation;
											}
											else {
												//�G�̂Ђ�ݒl�ݒ�
												mStan_Damage = CXPlayer::GetInstance()->GetIsStanPoint() * (CXPlayer::GetInstance()->GetIsStanPoint() / mDefense_Point) + (CXPlayer::GetInstance()->GetIsStanPoint() * Enemy_Damage_Magnification);
												mStanAccumulation = mStanAccumulation + mStan_Damage;
											}

										}
										//�v���C���Ƃ̏Փˏ������~����
										mEnemy_Flag = true;
									}

								}
							}
						}
					}
				}
			}

		}
	}
	//���S���Ă���Ƃ��́A�Փ˔�����X���[����
	else if (mHp <= Enemy_Death_Hp) {

	}
}


void CXEnemy::MovingCalculation() {
	//�v���C���[�����̃x�N�g�������߂�
	mEnemy_PlayerPos = CXPlayer::GetInstance()->Position() - mPosition;
	//�v���C���[�܂ł̋��������߂�
	mEnemy_PlayerDis = mEnemy_PlayerPos.Length();
	//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
	//�[���x�N�g���v�Z
	CVector ChackVec; //�`�F�b�N�p�x�N�g��
	ChackVec = mEnemy_MoveDirKeep.Normalize(); //�ۑ����ꂽ�ړ����̕����x�N�g������
	ChackVec = mEnemy_MoveDir.Normalize(); //�ړ����̕����x�N�g������
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / ENEMY_TURN_SET));

	//��]���x�@degree�ɒ���
	mEnemy_Turnspeed = (ENEMY_TURN_SET / M_PI) * ENEMY_TURN_SPEEDS_SET;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > ENEMY_TRUN_CHECK_SPEEDS_SET) tCheck.turn = ENEMY_TRUN_CHECK_SPEEDS_SET;

	//�ړ������ɃL��������������
	if (tCheck.cross > ENEMY_TRUN_CHECK_SET)
	{
		mRotation.Y(mRotation.Y() + tCheck.turn * mEnemy_Turnspeed);
	}
	//�ړ������ɃL��������������
	if (tCheck.cross < ENEMY_TRUN_CHECK_SET)
	{
		mRotation.Y(mRotation.Y() - tCheck.turn * mEnemy_Turnspeed);
	}
	//�ړ�����
	mPosition += mEnemy_MoveDir * mEnemy_Speed;
	//�L�����ɏd�͂��|����
	mPosition.Y(mPosition.Y() * Enemy_Gravity);

	//�ړ��������Z�b�g
	mEnemy_MoveDir = CVector(0.0f, 0.0f, 0.0f);
	//�ړ��X�s�[�h���Z�b�g
	mEnemy_Speed = ENEMY_SPEED;
}
//�C���X�^���X�̎擾
CXEnemy* CXEnemy::GetInstance()
{
	//�C���X�^���X�̐ݒ�
	return mpEnemy_Instance;
}
//HP�̎擾
int CXEnemy::GetHp() {
	//HP�̎擾
	return mHp;
}
//�G�̃^�C�v���擾
CXEnemy::EEnemyType CXEnemy::GetIsType()
{
	return mEnemy_Type;
}
//�A�j���[�V�����t���[���̎擾
bool CXEnemy::GetIsAnimationFrame() {
	return mAnimationFrame;
}
//�U���̓����蔻����擾����
bool CXEnemy::GetIsHit()
{
	return mEnemy_IsHit; //�U���̓����蔻���Ԃ�
}
//���S��Ԃ̂Ƃ�true��Ԃ�
bool CXEnemy::GetIsDeath()
{
	return (mEnemy_State == CXEnemy::EEnemyState::EDEATH);
}
//�U���̓����蔻��t���O��ݒ�
void CXEnemy::SetIsHit(bool hitflag)
{
	mEnemy_IsHit = hitflag;
}
//�U���͂��擾����
int CXEnemy::GetIsAttackPoint()
{
	return mAttack_Point;
}
//�X�^���l���擾����
int CXEnemy::GetIsStanPoint()
{
	return mStan_Point;
}
//�G�̏�Ԃ��擾����
CXEnemy::EEnemyState CXEnemy::GetState()
{
	return mEnemy_State;
}
void CXEnemy::SetIsType(EEnemyType type) {
	mEnemy_Type = type;
}
//�ʒu��ݒ肷��
void CXEnemy::GetPos()
{
	mPosition.Set(Enemy_Position_X, Enemy_Position_Y, Enemy_Position_Z);
}
//�G�̃X�P�[�����擾
void CXEnemy::GetScale()
{
	mScale.Set(Enemy_Scale_X, Enemy_Scale_Y, Enemy_Scale_Z);
}
//�G�̉�]�l���擾����
void CXEnemy::GetRotation()
{
	mRotation.Set(Enemy_Rotation_X, Enemy_Rotation_Y, Enemy_Rotation_Z);
}
	

