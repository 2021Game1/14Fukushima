#include "CTutorial.h"

//ポインタをnullrtrに設定
CTutorial* CTutorial::mpTutorial_Instance = nullptr;												//チュートリアルのインスタンス変数の初期化


//デフォルトコンストラクタ
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
	//タスクマネージャへの追加
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}
//更新処理
void CTutorial::Update()
{
	//移動量検出用設定
	//移動量を蓄積し
	mMoveTutorial_Accumulation += CXPlayer::GetInstance()->GetInMoveDir();
	//移動量を保存する
	mMoveTutorial_Accumulation_Pos = fabsf(mMoveTutorial_Accumulation.Length());


	//移動方法表示
	//移動量が上限を超えていなければ、移動チュートリアルを描画しつづける
	if (mMoveTutorial_Accumulation_Pos <= mMoveTutorial_Accumulation_Max) {
		if (mMoveTutorialflag == false) {
			mTutorial_Out_flag = false;
		}
	}
	//超えていれば、移動チュートリアルを消す
	else if (mMoveTutorial_Accumulation_Pos > mMoveTutorial_Accumulation_Max) {
		mMoveTutorialflag = true;
		mTutorial_Out_flag = true;
	}

	//カメラ操作表示
	//カメラ操作量検出
	if (mMoveTutorialflag == true) {
		mCameraActionTutorial_Accumulation += CCamera::Instance()->GetInAngleX();
		//カメラ操作量が上限を超えていなければ、カメラ操作チュートリアルを描画しつづける
		if (mCameraActionTutorial_Accumulation <= mCameraActionTutorial_Accumulation_Max) {
			mTutorial_Out_flag = false;
		}
		//超えていれば、カメラ操作チュートリアルを消す
		else if (mCameraActionTutorial_Accumulation > mCameraActionTutorial_Accumulation_Max) {
			mCameraActionTutorialflag = true;
			mTutorial_Out_flag = true;
		}
	}

	//カメラアングル表示
	if (mCameraActionTutorialflag == true) {
		mTutorial_Out_flag = false;
		//アングル変更操作入力時
		//変更されるたびに変更量を加算する
		//上限を超えない間、カメラアングルチュートリアルを描画
		if (CKey::Once(VK_F1)|| CKey::Once(VK_F2))
		{
			mCameraAngle_Acceumulation += CAMERA_ANGLE_ACCEUMULATION;
		}
		//上限を超えたら
		//カメラアングルチュートリアルを消す
		if (mCameraAngle_Acceumulation > CAMERA_ANGLE_ACCEUMULATION_MAX)
		{
			mCameraAngleTutorialflag = true;
		}
	}
	//回避操作の表示
	if (mCameraAngleTutorialflag == true) {
		mTutorial_Out_flag = false;
		//回避操作入力時
		//回避量を蓄積する
		//回避量が上限を超えない限り、回避チュートリアルを描画し続ける。
		if (CKey::Once(VK_W) || CKey::Once(VK_A)|| CKey::Once(VK_S) || CKey::Once(VK_D))
		{
			mAvoidDance_Acceumulation += AVOIDDANCE_ACCEUMULATION;
		}
		//蓄積された回避量が上限を超えたら、回避操作チュートリアルを消す
		if (mAvoidDance_Acceumulation > AVOIDDANCE_ACCEUMULATION_MAX)
		{
			mAvoidDanceTutorialflag = true;
		}
	}
	//攻撃操作の表示
	if (mAvoidDanceTutorialflag == true) {
		//エネミーリストに登録された敵が全て死亡状態ではないとき
		//攻撃アクションチュートリアルを描画しつづける
		if (!CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
			mActionTutorialflag = false;
		}
		//エネミーリストに登録された敵が全て死亡状態だったとき
		//攻撃アクションチュートリアルを消す
		if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
			mActionTutorialflag = true;
		}
	}

}
//描画処理
void CTutorial::Render(){

	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	if (CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		CRes::GetInstance()->GetinTutorialEndImage().DrawImage(TUTORIAL_FIRST_WID, TUTORIAL_END_WID, TUTORIAL_FIRST_HEI, TUTORIAL_END_HEI, TUTORIAL_FIRST_X, TUTORIAL_END_X, TUTORIAL_END_Y, TUTORIAL_FIRST_Y);
	}
	//エネミーリストに登録された敵が全て死亡状態ではないとき
	//描画する
	if (!CXEnemyManager::GetInstance()->GetIsEnemyAllDeath()) {
		//チュートリアル前提フラグがtrueになったら
		//移動操作チュートリアルを消す
		if (mMoveTutorialflag == false) {
			CRes::GetInstance()->GetinMoveTutorialImage().DrawImage(MOVE_FIRST_WID, MOVE_END_WID, MOVE_FIRST_HEI, MOVE_END_HEI, MOVE_FIRST_X, MOVE_END_X, MOVE_END_Y, MOVE_FIRST_Y);
		}
		//移動操作チュートリアルを消した後
		//カメラ操作チュートリアルを表示
		if (mMoveTutorialflag == true) {
			if (mCameraActionTutorialflag == false) {
				CRes::GetInstance()->GetinCameraActionImage().DrawImage(CAMERA_FIRST_WID, CAMERA_END_WID, CAMERA_FIRST_HEI, CAMERA_END_HEI, CAMERA_FIRST_X, CAMERA_END_X, CAMERA_END_Y, CAMERA_FIRST_Y);
			}
		}
		//カメラ操作チュートリアルを消した後
		//カメラアングルチュートリアルを表示
		if (mCameraActionTutorialflag == true) {
			//カメラアングルチュートリアルを消す
			if (mCameraAngleTutorialflag == false) {
				CRes::GetInstance()->GetinCameraAngleImage().DrawImage(CAMERA_FIRST_WID, CAMERA_END_WID, CAMERA_FIRST_HEI, CAMERA_END_HEI, CAMERA_FIRST_X, CAMERA_END_X, CAMERA_END_Y, CAMERA_FIRST_Y);
			}
		}
		//カメラアングルチュートリアルを消した後
		//回避チュートリアルを表示
		if (mCameraAngleTutorialflag == true) {
			if (mAvoidDanceTutorialflag == false) {
				//回避チュートリアルを消す
				CRes::GetInstance()->GetinAvoidDanceTutorialImage().DrawImage(AVOIDDANCE_FIRST_WID, AVOIDDANCE_END_WID, AVOIDDANCE_FIRST_HEI, AVOIDDANCE_END_HEI, AVOIDDANCE_FIRST_X, AVOIDDANCE_END_X, AVOIDDANCE_END_Y, AVOIDDANCE_FIRST_Y);
			}
		}
		//回避チュートリアル消した後
		//攻撃アクションチュートリアルを表示
		if (mAvoidDanceTutorialflag == true) {
			if (mActionTutorialflag == false) {
				CRes::GetInstance()->GetinActionTutorialImage().DrawImage(ACTION_FIRST_WID, ACTION_END_WID, ACTION_FIRST_HEI, ACTION_END_HEI, ACTION_FIRST_X, ACTION_END_X, ACTION_END_Y, ACTION_FIRST_Y);
			}
		}
	}
	//2Dの描画終了
	CUtil::End2D(); {
	}
}
//チュートリアル表示時、一部UIを消す用のフラグ
bool CTutorial::GetIsTutorialFlag()
{
	return mTutorial_Out_flag;
}
