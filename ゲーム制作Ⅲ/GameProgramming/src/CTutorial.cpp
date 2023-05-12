#include "CTutorial.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CRes.h"

CTutorial* CTutorial::mpTutorial_Instance = nullptr;												//チュートリアルのインスタンス変数の初期化



CTutorial::CTutorial()
	:mActionTutorialflag(false)
	,mMoveTutorialflag(false)
	,mAvoidDanceTutorialflag(false)
	,mCameraTutorialflag(false)
	,mTutorial_Out_flag(false)
{

}
void CTutorial::Update() 
{
	
	if (mMoveTutorialflag == false) {
		mTutorial_Out_flag = false;
	}
	else if (mMoveTutorialflag == true) {
		if (mMoveTutorialflag == true) {
			mTutorial_Out_flag = true;
		}
	}

	if (CXEnemy::GetInstance()->GetIsEnemyPlayerDis() > CXEnemy::GetInstance()->GetIsEnemyAttackDis())
	{
		if (mMoveTutorialflag == true) {
			if (mCameraTutorialflag == false) {
				mTutorial_Out_flag = false;
			}
			if (mCameraTutorialflag == true) {
				mTutorial_Out_flag = true;
			}
		}
	}

	if (CXEnemy::GetInstance()->GetIsEnemyPlayerDis() <= CXEnemy::GetInstance()->GetIsEnemyAttackDis() + ACTION_TUTORIAL_ENEMY_PLAYER_VECTOR)
	{
		if (mCameraTutorialflag == true) {
			if (mActionTutorialflag == false) {
				mTutorial_Out_flag = false;
			}
			if (mActionTutorialflag == true) {
				mTutorial_Out_flag = true;
			}
		}
	}

	if (CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EATTACK_1)
	{
		if (mActionTutorialflag == true) {
			if (mAvoidDanceTutorialflag == false) {
				mTutorial_Out_flag = false;
			}
			if (mAvoidDanceTutorialflag == true) {
				mTutorial_Out_flag = true;
			}
		}
	}
}

void CTutorial::Render(){

	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameOverImage().DrawImage(GAMEOVER_FIRST_WID, GAMEOVER_END_WID, GAMEOVER_FIRST_HEI, GAMEOVER_END_HEI, GAMEOVER_FIRST_X, GAMEOVER_END_X, GAMEOVER_END_Y, GAMEOVER_FIRST_Y);
	}
	if (CXEnemy::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameClearImage().DrawImage(GAMECLEAR_FIRST_WID, GAMECLEAR_END_WID, GAMECLEAR_FIRST_HEI, GAMECLEAR_END_HEI, GAMECLEAR_FIRST_X, GAMECLEAR_END_X, GAMECLEAR_END_Y, GAMECLEAR_FIRST_Y);
	}
	if (mMoveTutorialflag == false) {
		CRes::GetInstance()->GetinMoveTutorialImage().DrawImage(MOVE_FIRST_WID, MOVE_END_WID, MOVE_FIRST_HEI, MOVE_END_HEI, MOVE_FIRST_X, MOVE_END_X, MOVE_END_Y, MOVE_FIRST_Y);
		if (CKey::Once(VK_LBUTTON) || CKey::Push(VK_W) || CKey::Push(VK_A) || CKey::Push(VK_S) || CKey::Push(VK_D)) {
			mMoveTutorialflag = true;
		}
	}
	if (CXEnemy::GetInstance()->GetIsEnemyPlayerDis() > CXEnemy::GetInstance()->GetIsEnemyAttackDis())
	{
		if (mMoveTutorialflag == true) {
			if (mCameraTutorialflag == false) {
				CRes::GetInstance()->GetinCameraTutorialImage().DrawImage(CAMERA_FIRST_WID, CAMERA_END_WID, CAMERA_FIRST_HEI, CAMERA_END_HEI, CAMERA_FIRST_X, CAMERA_END_X, CAMERA_END_Y, CAMERA_FIRST_Y);
				if (CKey::Push(VK_F1) || CKey::Push(VK_F2)) {
					mCameraTutorialflag = true;
				}
			}
		}
	}

	if (CXEnemy::GetInstance()->GetIsEnemyPlayerDis() <= CXEnemy::GetInstance()->GetIsEnemyAttackDis() + ACTION_TUTORIAL_ENEMY_PLAYER_VECTOR)
	{
		if (mCameraTutorialflag == true) {
			if (mActionTutorialflag == false) {
				CRes::GetInstance()->GetinActionTutorialImage().DrawImage(ACTION_FIRST_WID, ACTION_END_WID, ACTION_FIRST_HEI, ACTION_END_HEI, ACTION_FIRST_X, ACTION_END_X, ACTION_END_Y, ACTION_FIRST_Y);
				if (CKey::Push(VK_LBUTTON)) {
					mActionTutorialflag = true;
				}
			}
		}
	}
	if (CXEnemy::GetInstance()->GetState() == CXEnemy::EEnemyState::EATTACK_1)
	{
		if (mActionTutorialflag == true) {
			if (mAvoidDanceTutorialflag == false) {
				CRes::GetInstance()->GetinAvoidDanceTutorialImage().DrawImage(AVOIDDANCE_FIRST_WID, AVOIDDANCE_END_WID, AVOIDDANCE_FIRST_HEI, AVOIDDANCE_END_HEI, AVOIDDANCE_FIRST_X, AVOIDDANCE_END_X, AVOIDDANCE_END_Y, AVOIDDANCE_FIRST_Y);
				if (CKey::Once(VK_SHIFT)) {
					mAvoidDanceTutorialflag = true;
				}
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
