#include "CTutorial.h"

CTutorial* CTutorial::mpTutorial_Instance = nullptr;												//チュートリアルのインスタンス変数の初期化



CTutorial::CTutorial()
	:mActionTutorialflag(false)
	, mMoveTutorialflag(false)
	, mAvoidDanceTutorialflag(false)
	, mCameraAngleTutorialflag(false)
	, mCameraActionTutorialflag(false)
	, mTutorial_Out_flag(false)
	, mTutorialflag(false)
	, mMoveTutorial_Accumulation_Max(15)
	, mCameraActionTutorial_Accumulation_Max(180)
{

}
void CTutorial::Update()
{
	mMoveTutorial_Accumulation += CXPlayer::GetInstance()->GetInMoveDir();
	mMoveTutorial_Accumulation_Pos = fabsf(mMoveTutorial_Accumulation.Length());

	if (mMoveTutorial_Accumulation_Pos <= mMoveTutorial_Accumulation_Max) {
		if (mMoveTutorialflag == false) {
			mTutorial_Out_flag = false;
		}
	}
	else if (mMoveTutorial_Accumulation_Pos > mMoveTutorial_Accumulation_Max) {
		mMoveTutorialflag = true;
		mTutorial_Out_flag = true;
	}

	if (mMoveTutorialflag == true) {
		mCameraActionTutorial_Accumulation += CCamera::Instance()->GetInAngleX();
		if (mCameraActionTutorial_Accumulation <= mCameraActionTutorial_Accumulation_Max) {
			mTutorial_Out_flag = false;
		}
		else if (mCameraActionTutorial_Accumulation > mCameraActionTutorial_Accumulation_Max) {
			mCameraActionTutorialflag = true;
			mTutorial_Out_flag = true;
		}
	}

	if (mCameraActionTutorialflag == true) {
		mTutorial_Out_flag = false;
		if (mActionTutorialflag == false) {
			mActionTutorialflag = true;
		}
	}
	if (mActionTutorialflag == true) {
		mTutorial_Out_flag = false;
		if (mAvoidDanceTutorialflag == false) {
			mAvoidDanceTutorialflag = true;
		}
	}
}

void CTutorial::Render(){

	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {

	}
	if (mTutorialflag == false) {
		CRes::GetInstance()->GetinTutorialImage().DrawImage(TUTORIAL_FIRST_WID, TUTORIAL_END_WID, TUTORIAL_FIRST_HEI, TUTORIAL_END_HEI, TUTORIAL_FIRST_X, TUTORIAL_END_X, TUTORIAL_END_Y, TUTORIAL_FIRST_Y);
		if (CKey::Push(VK_RETURN)) {
			mTutorialflag = true;
		}
	}
	if (mTutorialflag == true) {
		if (mMoveTutorialflag == false) {
			CRes::GetInstance()->GetinMoveTutorialImage().DrawImage(MOVE_FIRST_WID, MOVE_END_WID, MOVE_FIRST_HEI, MOVE_END_HEI, MOVE_FIRST_X, MOVE_END_X, MOVE_END_Y, MOVE_FIRST_Y);
		}
	}

	if (mMoveTutorialflag == true) {
		if (mCameraActionTutorialflag == false) {
			CRes::GetInstance()->GetinCameraActionImage().DrawImage(CAMERA_FIRST_WID, CAMERA_END_WID, CAMERA_FIRST_HEI, CAMERA_END_HEI, CAMERA_FIRST_X, CAMERA_END_X, CAMERA_END_Y, CAMERA_FIRST_Y);
		}
	}
	if (mCameraActionTutorialflag == true) {
		if (mCameraAngleTutorialflag == false) {
			CRes::GetInstance()->GetinCameraAngleImage().DrawImage(CAMERA_FIRST_WID, CAMERA_END_WID, CAMERA_FIRST_HEI, CAMERA_END_HEI, CAMERA_FIRST_X, CAMERA_END_X, CAMERA_END_Y, CAMERA_FIRST_Y);
		}
	}
	if (mCameraAngleTutorialflag == true) {
		if (mAvoidDanceTutorialflag == false) {
			CRes::GetInstance()->GetinAvoidDanceTutorialImage().DrawImage(AVOIDDANCE_FIRST_WID, AVOIDDANCE_END_WID, AVOIDDANCE_FIRST_HEI, AVOIDDANCE_END_HEI, AVOIDDANCE_FIRST_X, AVOIDDANCE_END_X, AVOIDDANCE_END_Y, AVOIDDANCE_FIRST_Y);
		}
	}

	if (mAvoidDanceTutorialflag == true) {
		if (mActionTutorialflag == false) {
			CRes::GetInstance()->GetinActionTutorialImage().DrawImage(ACTION_FIRST_WID, ACTION_END_WID, ACTION_FIRST_HEI, ACTION_END_HEI, ACTION_FIRST_X, ACTION_END_X, ACTION_END_Y, ACTION_FIRST_Y);
			if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
				mActionTutorialflag = true;
			}
		}
	}
	//2Dの描画終了
	CUtil::End2D(); {
	}
}
bool CTutorial::GetIsTutorialFlag()
{
	return mTutorial_Out_flag;
}
