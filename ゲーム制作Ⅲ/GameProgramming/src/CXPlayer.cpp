#include"CXPlayer.h"
#include"CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CCamera.h"
#include"CRes.h"

//�v���C���̃p�����[�^�}�N��
#define PLAYER_SPEED_DEFAULT 0.5f																//�X�s�[�h(�ʏ펞)
#define PLAYER_GRAVITY 0.9f																		//�d��
#define PLAYER_THRUST 0.01																		//����
#define PLAYER_RECEPTION 120																	//���͂̎�t����
#define PLAYER_INRECEPTION 30																	//���͂̓����蔻��̎�t����
#define PLAYER_HP_MAX 100;																		//HP�̍ő�l
#define PLAYER_INITIALIZATION 0																	//������
//�v���C����HP�t���[��,HP�Q�[�W���W,��,����
#define PLAYER_GAUGE_FRAME_TEX_WID 480	//�Q�[�W�g�̉摜�̕�
#define PLAYER_GAUGE_FRAME_TEX_HEI 80	//�Q�[�W�g�̉摜�̍���
#define PLAYER_GAUGE_FRAME_LEFT 0	//�Q�[�W�g�����W
#define PLAYER_GAUGE_FRAME_RIGHT 400 //�Q�[�W�g�E���W
#define PLAYER_GAUGE_FRAME_TOP PLAYER_GAUGE_FRAME_TEX_HEI //�Q�[�W�g����W
#define PLAYER_GAUGE_FRAME_BOTTOM (PLAYER_GAUGE_FRAME_TOP-PLAYER_GAUGE_FRAME_TEX_HEI) //�Q�[�W�g�����W
#define PLAYER_GAUGE_LEFT -80	//�Q�[�W�`�掞�̍����W
#define PLAYER_GAUGE_WID_MAX 480	//�Q�[�W�̕��̍ő�l
#define GAUGE_HEIGHT 20 //�Q�[�W�`�掞�̍���
#define PLAYER_GAUGE_HP_TOP 30 //HP�Q�[�W�`�掞�̏���W
#define PLAYER_GAUGE_HP_BOTTOM (PLAYER_GAUGE_HP_TOP-GAUGE_HEIGHT) //HP�Q�[�W�`�掞�̉����W


CXPlayer* CXPlayer::mpPlayer_Instance = nullptr;												//�v���C���̃C���X�^���X�ϐ��̏�����




CXPlayer::CXPlayer()
//�v���C���̕ϐ��̏�����
	:mPlayer_ColSphereBody(this, nullptr, CVector(0.0f, 80.0f, 0.0f), CVector(0.0f, -80.0f, 0.0f), 0.7)
	, mPlayer_ColSphereShield(this, nullptr, CVector(0.0f, 0.0f, -5.0f), CVector(0.0f, 0.0f, 0.0f), 0.5f)
	, mPlayer_ColSphereSword(this, nullptr, CVector(-13.0f, 0.0f, 90.0f), CVector(0.0f, 0.0f, 10.0f), 0.3f)
	, mPlayer_Speed(PLAYER_SPEED_DEFAULT)
	, mPlayer_Hp(100)
	, mPlayer_ComboCount(0)
	, mPlayer_Turnspeed(0.0f)
	, mPlayer_IsHit(false)
	, mPlayer_AttackFlag_1(false)
	, mPlayer_AttackFlag_2(false)
	, mPlayer_AttackFlag_3(false)
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
	mPlayer_ColSphereBody.Tag(CCollider::EBODY);					//��
	mPlayer_ColSphereShield.Tag(CCollider::ESHIERD);				//��
	mPlayer_ColSphereSword.Tag(CCollider::ESWORD);					//��
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mPlayer_ColSphereBody.Matrix(&mpCombinedMatrix[14]);
	mPlayer_ColSphereShield.Matrix(&mpCombinedMatrix[41]);
	mPlayer_ColSphereSword.Matrix(&mpCombinedMatrix[71]);
	//�v���C���̈ʒu,�g�k,��]�̐ݒ�
	mPosition.Set(0.0f, 0.0f, 0.0);									//�ʒu��ݒ�
	mScale.Set(2.0f,2.0f,2.0f);										//�X�P�[���ݒ�
	mRotation.Set(0.0f, 180.0f, 0.0f);								//��]��ݒ�
}

void CXPlayer::Update() {
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

	case EGUARD:													//������
		Guard();													//����������Ă�
		break;

	case EDEATH:													//���S���
		Death();													//���S�������Ă�
		break;

	case EKNOCKBACK:												//�m�b�N�o�b�N���
		KnockBack();												//�m�b�N�o�b�N�������Ă�
		break;
	}
	//���W�ړ�
	mPosition += mPlayer_Move;										//�v���C���̈ʒu�Ƀv���C���̈ړ��ʂ𑫂�
	//����������
	mPlayer_Move = mPlayer_Move * PLAYER_THRUST;							//�v���C���̈ړ��ʂɐ��͂��|����
	//�d�͂��v���C���Ɋ|����
	mPosition.Y(mPosition.Y() * PLAYER_GRAVITY);							//�v���C����Y���ɏd�͂��|����

	//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
	//�[���x�N�g���v�Z
	CVector ChackVec;												//�`�F�b�N�p�x�N�g��
	ChackVec = mPlayer_MoveDirKeep.Normalize();						//�ۑ����ꂽ�ړ����̕����x�N�g������
	ChackVec = mPlayer_MoveDir.Normalize();							//�ړ����̕����x�N�g������
	Check tCheck = CUtil::GetCheck2D(ChackVec.X(), ChackVec.Z(), 0, 0, mRotation.Y() * (M_PI / 180.0f));

	//��]���x�@degree�ɒ���
	mPlayer_Turnspeed = (180.0f / M_PI) * 0.3f;

	//�}�ȐU��Ԃ��}��
	if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

	//�ړ������փL��������������
	if (tCheck.cross > 0.0f) {
		mRotation = mRotation + CVector(0.0f,tCheck.turn * mPlayer_Turnspeed,0.0f);
	}
	if (tCheck.cross < 0.0f) {
		mRotation = mRotation - CVector(0.0f, tCheck.turn * mPlayer_Turnspeed, 0.0f);
	}

	//���Z�b�g
	mPlayer_MoveDir = CVector(0.0f, 0.0f, 0.0f);

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
	mPlayer_ComboCount = 0;
	ChangeAnimation(6, true, 20);
	//���N���b�N�ōU��
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//WASD�L�[�������ƈړ��ֈڍs
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		mPlayer_State = EMOVE;
	}
	else if (CKey::Once(VK_SPACE)) {
		mPlayer_State = EGUARD;
	}
}

//�ړ�����
void CXPlayer::Move()
{
	//���N���b�N�ōU��1�ֈڍs
	if (CKey::Once(VK_LBUTTON)) {
		mPlayer_State = EATTACK_1;
	}
	//�X�y�[�X�ŃK�[�h�ֈڍs
	else if (CKey::Once(VK_SPACE)) {
		mPlayer_State = EGUARD;
	}
	//WASD�L�[�������ƈړ�
	else if (CKey::Push('W') || CKey::Push('A') || CKey::Push('S') || CKey::Push('D')) {
		MoveCamera();												//�J��������ɂ����ړ��������Ă�
		ChangeAnimation(0, true, 20);
	}
	//�ҋ@��Ԃֈڍs
	else {
		mPlayer_State = EIDLE;
	}
}


//�U��1����
void CXPlayer::Attack_1()
{
	//�������Ăяo���ꂽ��1�x�����������Ȃ�
	if (mPlayer_AttackFlag_1 == false) {							
		mPlayer_AttackFlag_1 = true;								//�v���C���̍U��1�̃t���O��true�ɂ���
		mPlayer_AttackFlag_Once = true;								//�v���C���̍U���t���O��true�ɐݒ�
		ChangeAnimation(5, false, 1);								//�ҋ@���[�V����
	}
	//�A�j���[�V�����C���f�b�N�X���T�̎�
	if (mAnimationIndex == 5)
	{
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(1, false, 30);							//�v���C���̍U��1���[�V����
		}
	}
	//�A�j���[�V�����C���f�b�N�X���R�̎�
	else if (mAnimationIndex == 3) {
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
				mPlayer_IsHit = true;									//�v���C���[�̃q�b�g�����true�ɂ���
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(1, false, 30);							//�v���C���̍U��1���[�V����
		}
	}
	//�A�j���[�V�����C���f�b�N�X���P�̎�
	else if (mAnimationIndex == 1)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) 
		{
			if (mAnimationFrame > PLAYER_INRECEPTION) {
				mPlayer_IsHit = true;									//�q�b�g����L��
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
			//�X�y�[�X�L�[�������ꂽ�ꍇ
			else if(CKey::Once(VK_SPACE)) {
				mPlayer_State = EGUARD;								//�K�[�h���[�V�����ֈڍs
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
	if (mAnimationIndex == 1)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
				mPlayer_IsHit = true;									//�q�b�g����L��
		}
		//�A�j���[�V�����I����
		else if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(2, false, 60);							//�v���C���̍U��2���[�V����
		}
	}
	//�A�j���[�V�����C���f�b�N�X��2�̎�
	else if (mAnimationIndex == 2)
	{
		//�A�j���[�V�����̃t���[������t���Ԃ�菬������
		if (mAnimationFrame < PLAYER_RECEPTION) {
			//���N���b�N���ꂽ�ꍇ
			if (CKey::Once(VK_LBUTTON)) {
				mPlayer_State = EATTACK_3;							//�U��3���[�V�����ֈڍs
			}
			//�X�y�[�X�L�[�������ꂽ�ꍇ
			else if (CKey::Once(VK_SPACE)) {
				mPlayer_State = EGUARD;								//�K�[�h���[�V�����ֈڍs
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
	if (mAnimationIndex == 2)
	{
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
				mPlayer_IsHit = true;
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false;									//�q�b�g����I��
			ChangeAnimation(3, false, 80);
		}
	}
	else if (mAnimationIndex == 3)
	{
		if (mAnimationFrame < PLAYER_RECEPTION) {
			//���N���b�N���ꂽ�ꍇ
			if (CKey::Once(VK_LBUTTON)) {
				mPlayer_State = EATTACK_1;							//�U��1���[�V�����ֈڍs
			}
			//�X�y�[�X�L�[�������ꂽ�ꍇ
			else if(CKey::Once(VK_SPACE)) {
				mPlayer_State = EGUARD;								//�K�[�h���[�V�����ֈڍs
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
	ChangeAnimation(7, false, 30);	//�̂�����A�j���[�V����
		//�A�j���[�V�����I����
	if (IsAnimationFinished())
	{
		mPlayer_State = EIDLE; //�ҋ@��Ԃֈڍs
		mPlayer_Hp = mPlayer_Hp - 10;
	}
}
//�K�[�h
void CXPlayer::Guard()
{
	if (mPlayer_Flag == false) {
		ChangeAnimation(6, false, 1);//�ҋ@���[�V����
		mPlayer_Flag = true;
	}
	
	if (mAnimationIndex == 6){
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
				mPlayer_IsHit = true;
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			ChangeAnimation(4, false, 10);	//�K�[�h�ҋ@�A�j���[�V����
		}
	}
	else if (mAnimationIndex == 4) {
		//�q�b�g���蔭��
		if (IsAnimationFinished() == false) {
			if (mAnimationFrame > PLAYER_INRECEPTION) {
				mPlayer_IsHit = true;
			}
		}
		//�A�j���[�V�����I����
		if (IsAnimationFinished())
		{
			mPlayer_IsHit = false; //�q�b�g����I��
			ChangeAnimation(5, false, 30);//�K�[�h�A�j���[�V����
		}

	}
	//�A�j���[�V�����I����
	else if (IsAnimationFinished())
	{
		mPlayer_State = EIDLE;
		mPlayer_Flag = false;
	}

}

//���S����
void CXPlayer::Death()
{
	ChangeAnimation(8, false, 60);	//���S�A�j���[�V����
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
	if (CKey::Push('W')) {
		mPlayer_MoveDir += mPlayer_FrontVec;
	}
	else if (CKey::Push('S'))
	{
		mPlayer_MoveDir -= mPlayer_FrontVec;
	}

	//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
	mPlayer_MoveDir = mPlayer_MoveDir.Normalize();
	mPlayer_MoveDirKeep = mPlayer_MoveDir;	//MoveDir�ۑ�
	mPlayer_Move = mPlayer_MoveDir * mPlayer_Speed;	//�ړ��ʂ�ݒ�
}
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
		shakeX = -5 + rand() % 6;
		shakeY = -2 + rand() % 2;
	}
	//�̗̓Q�[�W
	float HpRate = (float)mPlayer_Hp / (float)PLAYER_HP_MAX;	//�̗͍ő�l�ɑ΂���A���݂̗̑͂̊���
	float HpGaugeWid = PLAYER_GAUGE_WID_MAX * HpRate;	//�̗̓Q�[�W�̕�
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕����傫����
	if (mPlayer_FollowGaugeWid > HpGaugeWid) {
		//���`��ԂŔ�_���[�W����ǂ�����Q�[�W�̕���ݒ肷��
		mPlayer_FollowGaugeWid = Camera.mLerp(mPlayer_FollowGaugeWid, HpGaugeWid, 0.05f);
	}
	//��_���[�W����ǂ�����Q�[�W�̕����̗̓Q�[�W�̕���菬�����Ƃ�
	else if (mPlayer_FollowGaugeWid < HpGaugeWid) {
		//��_���[�W����ǂ�����Q�[�W�̕��ɑ̗̓Q�[�W�̕���ݒ肷��
		mPlayer_FollowGaugeWid = HpGaugeWid;
	}
	CRes::GetInstance()->GetInUiHpRedGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + mPlayer_FollowGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, 0, 480, 0, 10);
	CRes::GetInstance()->GetInUiHpGreenGauge().Draw(PLAYER_GAUGE_LEFT + shakeX, PLAYER_GAUGE_LEFT + HpGaugeWid + shakeX, PLAYER_GAUGE_HP_BOTTOM + shakeY, PLAYER_GAUGE_HP_TOP + shakeY, 0, 480, 0, 10);
	CRes::GetInstance()->GetInPlayerUiHpFrame().Draw(PLAYER_GAUGE_FRAME_LEFT, PLAYER_GAUGE_FRAME_RIGHT, PLAYER_GAUGE_FRAME_BOTTOM, PLAYER_GAUGE_FRAME_TOP, 0, PLAYER_GAUGE_FRAME_TEX_WID, PLAYER_GAUGE_FRAME_TEX_HEI, 0);
	//2D�̕`��I��
	CUtil::End2D();
}



void CXPlayer::Collision(CCollider* m, CCollider* o) {
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
						   
	case CCollider::ECAPSUL:{//�J�v�Z���R���C�_
		//����̃R���C�_���J�v�Z���R���C�_�̎�
		if (o->Type() == CCollider::ECAPSUL) {
			CVector adjust;//�����p�x�N�g��
			if (!mPlayer_Hp <= 0) {
				if (CCollider::CollisionCapsule(m, o, &adjust))
				{
					//����̃R���C�_�̃^�O����
					if (o->Tag() == CCollider::EARM) {
							if (CXEnemy::GetInstance()->GetIsHit() == true)
							{
								if (CXEnemy::GetInstance()->GetIsAnimationFrame() >= mAnimationFrame)
								{
									mPlayer_State = EKNOCKBACK;
								}
							}
					}
					else {
						//�ʒu�̍X�V(mPosition + adjust)
						mPosition = mPosition + adjust;
						//�s��̍X�V
						CTransform::Update();
					}
				}
			}
		}
		else if (o->Type() == CCollider::ETRIANGLE) {
			CVector adjust;//�����p�x�N�g��
			if (CCollider::CollisionTriangleLine(o, m, &adjust))
			{
				//�ʒu�̍X�V(mPosition + adjust)
				mPosition = mPosition + adjust;
				//�s��̍X�V
				CTransform::Update();
			}
			
		}
		break;
	}
	}		
}

//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CXPlayer* CXPlayer::GetInstance()
{
	return mpPlayer_Instance;
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