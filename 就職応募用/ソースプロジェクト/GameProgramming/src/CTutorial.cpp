#include "CTutorial.h"

//�|�C���^��nullrtr�ɐݒ�
CTutorial* CTutorial::mpTutorial_Instance = nullptr;												//�`���[�g���A���̃C���X�^���X�ϐ��̏�����


//�f�t�H���g�R���X�g���N�^
CTutorial::CTutorial()
	:mActionTutorialflag(false)
	, mMoveTutorialflag(false)
	, mAvoidDanceTutorialflag(false)
	, mCameraAngleTutorialflag(false)
	, mCameraActionTutorialflag(false)
	, mTutorial_Out_flag(false)
	, mMoveTutorial_Accumulation_Max(MOVE_ACCEUMULATION_MAX)
	, mCameraActionTutorial_Accumulation_Max(CAMERA_ACCEUMULATION_MAX)
	, mTutorialEndflag(false)
	, mAvoidDance_Acceumulation(NULL)
	, mCameraActionTutorial_Accumulation(false)
	, mCameraAngle_Acceumulation(false)
	, mMoveTutorial_Accumulation_Pos(NULL)
{
	mpTutorial_Instance = this;
	//�^�X�N�}�l�[�W���ւ̒ǉ�
	CTaskManager::Get()->Remove(this);//�폜����
	CTaskManager::Get()->Add(this);//�ǉ�����
}
//�X�V����
void CTutorial::Update()
{
	//�ړ��ʌ��o�p�ݒ�
	//�ړ��ʂ�~�ς�
	mMoveTutorial_Accumulation += CXPlayer::GetInstance()->GetInMoveDir();
	//�ړ��ʂ�ۑ�����
	mMoveTutorial_Accumulation_Pos = fabsf(mMoveTutorial_Accumulation.Length());


	//�ړ����@�\��
	//�ړ��ʂ�����𒴂��Ă��Ȃ���΁A�ړ��`���[�g���A����`�悵�Â���
	if (mMoveTutorial_Accumulation_Pos <= mMoveTutorial_Accumulation_Max) {
		if (mMoveTutorialflag == false) {
			mTutorial_Out_flag = false;
		}
	}
	//�����Ă���΁A�ړ��`���[�g���A��������
	else if (mMoveTutorial_Accumulation_Pos > mMoveTutorial_Accumulation_Max) {
		mMoveTutorialflag = true;
		mTutorial_Out_flag = true;
	}

	//�J��������\��
	//�J��������ʌ��o
	if (mMoveTutorialflag == true) {
		mCameraActionTutorial_Accumulation += CCamera::Instance()->GetInAngleX();
		//�J��������ʂ�����𒴂��Ă��Ȃ���΁A�J��������`���[�g���A����`�悵�Â���
		if (mCameraActionTutorial_Accumulation <= mCameraActionTutorial_Accumulation_Max) {
			mTutorial_Out_flag = false;
		}
		//�����Ă���΁A�J��������`���[�g���A��������
		else if (mCameraActionTutorial_Accumulation > mCameraActionTutorial_Accumulation_Max) {
			mCameraActionTutorialflag = true;
			mTutorial_Out_flag = true;
		}
	}

	//�J�����A���O���\��
	if (mCameraActionTutorialflag == true) {
		mTutorial_Out_flag = false;
		//�A���O���ύX������͎�
		//�ύX����邽�тɕύX�ʂ����Z����
		//����𒴂��Ȃ��ԁA�J�����A���O���`���[�g���A����`��
		if (CKey::Once(VK_F1)|| CKey::Once(VK_F2))
		{
			mCameraAngle_Acceumulation += CAMERA_ANGLE_ACCEUMULATION;
		}
		//����𒴂�����
		//�J�����A���O���`���[�g���A��������
		if (mCameraAngle_Acceumulation > CAMERA_ANGLE_ACCEUMULATION_MAX)
		{
			mCameraAngleTutorialflag = true;
		}
	}
	//��𑀍�̕\��
	if (mCameraAngleTutorialflag == true) {
		mTutorial_Out_flag = false;
		//��𑀍���͎�
		//���ʂ�~�ς���
		//���ʂ�����𒴂��Ȃ�����A����`���[�g���A����`�悵������B
		if (CKey::Once(VK_W) || CKey::Once(VK_A)|| CKey::Once(VK_S) || CKey::Once(VK_D))
		{
			mAvoidDance_Acceumulation += AVOIDDANCE_ACCEUMULATION;
		}
		//�~�ς��ꂽ���ʂ�����𒴂�����A��𑀍�`���[�g���A��������
		if (mAvoidDance_Acceumulation > AVOIDDANCE_ACCEUMULATION_MAX)
		{
			mAvoidDanceTutorialflag = true;
		}
	}
	//�U������̕\��
	if (mAvoidDanceTutorialflag == true) {
		//�G�l�~�[���X�g�ɓo�^���ꂽ�G���S�Ď��S��Ԃł͂Ȃ��Ƃ�
		//�U���A�N�V�����`���[�g���A����`�悵�Â���
		if (!CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
			mActionTutorialflag = false;
		}
		//�G�l�~�[���X�g�ɓo�^���ꂽ�G���S�Ď��S��Ԃ������Ƃ�
		//�U���A�N�V�����`���[�g���A��������
		if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
			mActionTutorialflag = true;
		}
	}

}
//�`�揈��
void CTutorial::Render(){

	//2D�̕`��J�n
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		CRes::GetInstance()->GetinTutorialEndImage().DrawImage(TUTORIAL_FIRST_WID, TUTORIAL_END_WID, TUTORIAL_FIRST_HEI, TUTORIAL_END_HEI, TUTORIAL_FIRST_X, TUTORIAL_END_X, TUTORIAL_END_Y, TUTORIAL_FIRST_Y);
	}
	//�G�l�~�[���X�g�ɓo�^���ꂽ�G���S�Ď��S��Ԃł͂Ȃ��Ƃ�
	//�`�悷��
	if (!CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		//�`���[�g���A���O��t���O��true�ɂȂ�����
		//�ړ�����`���[�g���A��������
		if (mMoveTutorialflag == false) {
			CRes::GetInstance()->GetinMoveTutorialImage().DrawImage(MOVE_FIRST_WID, MOVE_END_WID, MOVE_FIRST_HEI, MOVE_END_HEI, MOVE_FIRST_X, MOVE_END_X, MOVE_END_Y, MOVE_FIRST_Y);
		}
		//�ړ�����`���[�g���A������������
		//�J��������`���[�g���A����\��
		if (mMoveTutorialflag == true) {
			if (mCameraActionTutorialflag == false) {
				CRes::GetInstance()->GetinCameraActionImage().DrawImage(CAMERA_FIRST_WID, CAMERA_END_WID, CAMERA_FIRST_HEI, CAMERA_END_HEI, CAMERA_FIRST_X, CAMERA_END_X, CAMERA_END_Y, CAMERA_FIRST_Y);
			}
		}
		//�J��������`���[�g���A������������
		//�J�����A���O���`���[�g���A����\��
		if (mCameraActionTutorialflag == true) {
			//�J�����A���O���`���[�g���A��������
			if (mCameraAngleTutorialflag == false) {
				CRes::GetInstance()->GetinCameraAngleImage().DrawImage(CAMERA_FIRST_WID, CAMERA_END_WID, CAMERA_FIRST_HEI, CAMERA_END_HEI, CAMERA_FIRST_X, CAMERA_END_X, CAMERA_END_Y, CAMERA_FIRST_Y);
			}
		}
		//�J�����A���O���`���[�g���A������������
		//����`���[�g���A����\��
		if (mCameraAngleTutorialflag == true) {
			if (mAvoidDanceTutorialflag == false) {
				//����`���[�g���A��������
				CRes::GetInstance()->GetinAvoidDanceTutorialImage().DrawImage(AVOIDDANCE_FIRST_WID, AVOIDDANCE_END_WID, AVOIDDANCE_FIRST_HEI, AVOIDDANCE_END_HEI, AVOIDDANCE_FIRST_X, AVOIDDANCE_END_X, AVOIDDANCE_END_Y, AVOIDDANCE_FIRST_Y);
			}
		}
		//����`���[�g���A����������
		//�U���A�N�V�����`���[�g���A����\��
		if (mAvoidDanceTutorialflag == true) {
			if (mActionTutorialflag == false) {
				CRes::GetInstance()->GetinActionTutorialImage().DrawImage(ACTION_FIRST_WID, ACTION_END_WID, ACTION_FIRST_HEI, ACTION_END_HEI, ACTION_FIRST_X, ACTION_END_X, ACTION_END_Y, ACTION_FIRST_Y);
			}
		}
	}
	//2D�̕`��I��
	CUtil::End2D(); {
	}
}
//�`���[�g���A���\�����A�ꕔUI�������p�̃t���O
bool CTutorial::GetIsTutorialFlag()
{
	return mTutorial_Out_flag;
}
