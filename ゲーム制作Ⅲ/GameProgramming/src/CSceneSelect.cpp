#include "CSceneSelect.h"

CSceneSelect::CSceneSelect()
	: mSelect(CSceneSelect::ESelect::EBACKGROUND)
	, mNextScene(CScene::EScene::ESCENESELECT)
	, mSceneChange()
	, mIsButtonPush(false)
	, mMouseX(NULL)
	, mMouseY(NULL)
{

}

//デストラクタ
CSceneSelect::~CSceneSelect()
{
	CTaskManager::Get()->Delete();
}

void CSceneSelect::Init()
{
	//シーンの設定
	mScene = CScene::EScene::ESCENESELECT;
	//タイトル選択画面画像の追加
	gTitle_Select_Image.Load2D(SCENE_SELECT_IMAGE);
	//タイトル場面選択画面描画時のテキスト
	gTitle_Select_Text_Image.Load2D(SCENE_SELECT_TEXT);
	//ゲーム開始選択時テキスト
	gTitle_Select_GameStart_Text_Image.Load2D(SCENE_SELECT_GAMESTART_TEXT);
	//チュートリアル開始選択時テキスト
	gTitle_Select_Tutorial_Text_Image.Load2D(SCENE_SELECT_TUTORIAL_TEXT);
	//タイトルバック選択時テキスト
	gTitle_Select_Back_to_Title_Text_Image.Load2D(SCENE_SELECT_TITLEBACK_TEXT);
	//ゲーム終了選択時テキスト
	gTitle_Select_Quit_Game_Text_Image.Load2D(SCENE_SELECT_QUITGAME_TEXT);
	//ゲームスタート画像の追加
	gTitle_Select_GameStart_Image.Load2D(SCENE_SELECT_GAMESTART_IMAGE);
	//チュートリアルスタート画像の追加
	gTitle_Select_TutorialStart_Image.Load2D(SCENE_SELECT_TUTORIALSTART_IMAGE);
	//タイトルバック画像の追加
	gTitle_Select_Back_to_Title_Image.Load2D(SCENE_SELECT_TITLEBACK_IMAGE);
	//ゲーム終了の追加
	gTitle_Select_Quit_Game_Image.Load2D(SCENE_SELECT_QUITGAME_IMAGE);
	//チュートリアルスタート画像の追加
	//ボタンを押したときに描画されるフェイドアウト、イン用背景
	gTitle_Select_Fade_Image.Load2D(SCENE_SELECT_FADE_IMAGE);
}

void CSceneSelect::Update()
{

	//ボタンを押していないとき
	if (mIsButtonPush == false) {
		//マウスの座標を取得
		CInput::GetMousePosWin(&mMouseX, &mMouseY);
		mMouseY = SCENE_SELECT_END_Y - mMouseY;
	}

		//ゲームスタートボタン上にマウスポインタがあるとき
	if ((mMouseX >= STARTBUTTON_LEFT && mMouseX <= STARTBUTTON_RIGHT) &&
		(mMouseY >= STARTBUTTON_DOWN && mMouseY <= STARTBUTTON_UP)) {
		//選択している場所をゲームスタートに設定
		mSelect = CSceneSelect::ESelect::EGAMESTART;
	}
		//チュートリアルボタン上にマウスポインタがあるとき
	else if ((mMouseX >= TUTORIALBUTTON_LEFT && mMouseX <= TUTORIALBUTTON_RIGHT) &&
		(mMouseY >= TUTORIALBUTTON_DOWN && mMouseY <= TUTORIALBUTTON_UP)) {
		//選択している場所をチュートリアルに設定
		mSelect = CSceneSelect::ESelect::ETUTORIAL;
	}
	//タイトルバックボタン上にマウスポインタがあるとき
	else if ((mMouseX >= TITLEBACKBUTTON_LEFT && mMouseX <= TITLEBACKBUTTON_RIGHT) &&
		(mMouseY >= TITLEBACKBUTTON_DOWN && mMouseY <= TITLEBACKBUTTON_UP)) {
		//選択している場所をタイトルバックに設定
		mSelect = CSceneSelect::ESelect::EBACKTOTITLE;
	}
	//ゲーム終了ボタン上にマウスポインタがあるとき
	else if ((mMouseX >= QUITGAMEBUTTON_LEFT && mMouseX <= QUITGAMEBUTTON_RIGHT) &&
		(mMouseY >= QUITGAMEBUTTON_DOWN && mMouseY <= QUITGAMEBUTTON_UP)) {
		//選択している場所をゲーム終了に設定
		mSelect = CSceneSelect::ESelect::EQUITGAME;
	}
		//上記以外は背景
	else {
		//選択している場所を背景に設定
		mSelect = CSceneSelect::ESelect::EBACKGROUND;
	}

		//左クリックしたとき
	if (CKey::Once(VK_LBUTTON)) {
		//選択している場所を判断する
		switch (mSelect) {
		case CSceneSelect::ESelect::EGAMESTART: //ゲームスタート
			//ボタンを押していないとき
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//ボタンを押したら実行
				//次のシーンはゲーム
				mNextScene = CScene::EScene::EGAME;
				//シーン切り替え実行
				mSceneChange = true;
			}
			break;

		case CSceneSelect::ESelect::ETUTORIAL: //チュートリアルスタート
				//ボタンを押していないとき
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//ボタンを押したら実行
				//次のシーンはチュートリアル
				mNextScene = CScene::EScene::ETUTORIAL;
				//シーン切り替え実行
				mSceneChange = true;
			}
			break;

		case CSceneSelect::ESelect::EBACKTOTITLE: //タイトルバック
			//ボタンを押していないとき
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//ボタンを押したら実行
				//次のシーンはタイトル
				mNextScene = CScene::EScene::ETITLE;
				//シーン切り替え実行
				mSceneChange = true;
			}
			break;
		
		case CSceneSelect::ESelect::EQUITGAME: //ゲームを終了
			//ボタンを押していないとき
			if (mIsButtonPush == false) {
				mIsButtonPush = true;	//ボタンを押したら実行
				//ゲームを終了する
				exit(NULL);
			}
			break;

		default:
			break;
		}
	}

	if (mSceneChange) {
		mScene = mNextScene;
	}
}

//描画処理
void CSceneSelect::Render() {

	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	//タイトル選択画面描画
	gTitle_Select_Image.Draw(SCENE_SELECT_FIRST_WID, SCENE_SELECT_END_WID, SCENE_SELECT_FIRST_HEI, SCENE_SELECT_END_HEI, SCENE_SELECT_FIRST_X, SCENE_SELECT_END_X, SCENE_SELECT_END_Y, SCENE_SELECT_FIRST_Y);
	//ゲームスタートスタート画像描画
	gTitle_Select_GameStart_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
	//チュートリアルスタート画像描画
	gTitle_Select_TutorialStart_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
	//タイトルバック
	gTitle_Select_Back_to_Title_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
	//ゲーム終了描画
	gTitle_Select_Quit_Game_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	//背景を選択していたら描画
	if (mSelect == CSceneSelect::ESelect::EBACKGROUND)
	{
		
		//タイトル選択画面テキスト
		gTitle_Select_Text_Image.Draw(SCENE_SELECT_TEXT_FIRST_WID, SCENE_SELECT_TEXT_END_WID, SCENE_SELECT_TEXT_FIRST_HEI, SCENE_SELECT_TEXT_END_HEI, SCENE_SELECT_TEXT_FIRST_X, SCENE_SELECT_TEXT_END_X, SCENE_SELECT_TEXT_END_Y, SCENE_SELECT_TEXT_FIRST_Y);
		
		//スタートボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		
		//チュートリアルボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
		
		//タイトルに戻るボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
		
		//ゲーム終了ボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	}
	//ゲームスタートを選択していたら描画
	if (mSelect == CSceneSelect::ESelect::EGAMESTART) {
		
		//ゲーム開始選択時テキスト
		gTitle_Select_GameStart_Text_Image.Draw(SCENE_SELECT_GAMESTART_TEXT_FIRST_WID, SCENE_SELECT_GAMESTART_TEXT_END_WID, SCENE_SELECT_GAMESTART_TEXT_FIRST_HEI, SCENE_SELECT_GAMESTART_TEXT_END_HEI, SCENE_SELECT_GAMESTART_TEXT_FIRST_X, SCENE_SELECT_GAMESTART_TEXT_END_X, SCENE_SELECT_GAMESTART_TEXT_END_Y, SCENE_SELECT_GAMESTART_TEXT_FIRST_Y);
		
		//チュートリアルボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
		
		//タイトルに戻るボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
		
		//ゲーム終了ボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	}
	//チュートリアルを選択していたら描画
	if (mSelect == CSceneSelect::ESelect::ETUTORIAL) {
		
		//チュートリアル開始選択時テキスト
		gTitle_Select_Tutorial_Text_Image.Draw(SCENE_SELECT_TUTORIAL_TEXT_FIRST_WID, SCENE_SELECT_TUTORIAL_TEXT_END_WID, SCENE_SELECT_TUTORIAL_TEXT_FIRST_HEI, SCENE_SELECT_TUTORIAL_TEXT_END_HEI, SCENE_SELECT_TUTORIAL_TEXT_FIRST_X, SCENE_SELECT_TUTORIAL_TEXT_END_X, SCENE_SELECT_TUTORIAL_TEXT_END_Y, SCENE_SELECT_TUTORIAL_TEXT_FIRST_Y);
		
		//スタートボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		
		//タイトルに戻るボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
		
		//ゲーム終了ボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	}
	//タイトルバックを選択していたら描画
	if (mSelect == CSceneSelect::ESelect::EBACKTOTITLE) {
		
		//チュートリアル開始選択時テキスト
		gTitle_Select_Back_to_Title_Text_Image.Draw(SCENE_SELECT_TITLEBACK_TEXT_FIRST_WID, SCENE_SELECT_TITLEBACK_TEXT_END_WID, SCENE_SELECT_TITLEBACK_TEXT_FIRST_HEI, SCENE_SELECT_TITLEBACK_TEXT_END_HEI, SCENE_SELECT_TITLEBACK_TEXT_FIRST_X, SCENE_SELECT_TITLEBACK_TEXT_END_X, SCENE_SELECT_TITLEBACK_TEXT_END_Y, SCENE_SELECT_TITLEBACK_TEXT_FIRST_Y);
		
		//スタートボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		
		//チュートリアルボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
		
		//ゲーム終了ボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(QUITGAMEBUTTON_LEFT, QUITGAMEBUTTON_RIGHT, QUITGAMEBUTTON_DOWN, QUITGAMEBUTTON_UP, QUITGAMEBUTTON_FIRST_X, QUITGAMEBUTTON_END_X, QUITGAMEBUTTON_END_Y, QUITGAMEBUTTON_FIRST_Y);
	}
	//ゲーム終了を選択していたら描画
	if (mSelect == CSceneSelect::ESelect::EQUITGAME) {
		
		//チュートリアル開始選択時テキスト
		gTitle_Select_Quit_Game_Text_Image.Draw(SCENE_SELECT_QUITGAME_TEXT_FIRST_WID, SCENE_SELECT_QUITGAME_TEXT_END_WID, SCENE_SELECT_QUITGAME_TEXT_FIRST_HEI, SCENE_SELECT_QUITGAME_TEXT_END_HEI, SCENE_SELECT_QUITGAME_TEXT_FIRST_X, SCENE_SELECT_QUITGAME_TEXT_END_X, SCENE_SELECT_QUITGAME_TEXT_END_Y, SCENE_SELECT_QUITGAME_TEXT_FIRST_Y);
		
		//スタートボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
		
		//チュートリアルボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
		
		//タイトルに戻るボタンにかけるフェイド画像
		gTitle_Select_Fade_Image.Draw(TITLEBACKBUTTON_LEFT, TITLEBACKBUTTON_RIGHT, TITLEBACKBUTTON_DOWN, TITLEBACKBUTTON_UP, TITLEBACKBUTTON_FIRST_X, TITLEBACKBUTTON_END_X, TITLEBACKBUTTON_END_Y, TITLEBACKBUTTON_FIRST_Y);
	}
	//
	//2Dの描画終了
	CUtil::End2D();
}

//次のシーンに移行
CScene::EScene CSceneSelect::GetNextScene() {
	//現在のシーンを返す
	return mScene;
}