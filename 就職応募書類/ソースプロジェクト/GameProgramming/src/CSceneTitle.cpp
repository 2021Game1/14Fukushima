#include "CSceneTitle.h"

//デフォルトコンストラクタ
CSceneTitle::CSceneTitle()
	: mNextScene(CScene::EScene::ETITLE)
	, mSelect(CSceneTitle::ESelect::EBACKGROUND)
	, mIsButtonPush(false)
	, mSceneChange()
	, mTutorialflag(false)
	, mTitleflag(false)
	, mMouseX(NULL)
	, mMouseY(NULL)
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{
	CTaskManager::Get()->Delete();
}

//Init処理
//一度しか動かさない処理
void CSceneTitle::Init() {
	//シーンの設定
	mScene = CScene::EScene::ETITLE;
	//タイトル画像の追加
	gTitle_Image.Load2D(TITLE_IMAGE);
	//タイトル選択画面画像の追加
	gTitle_Select_Image.Load2D(TITLE_SELECT_IMAGE);
	//タイトル場面選択画面描画時のテキスト
	gTitle_Select_Text_Image.Load2D(TITLE_SELECT_TEXT);
	//ゲーム開始選択時テキスト
	gTitle_Select_GameStart_Text_Image.Load2D(TITLE_SELECT_GAMESTART_TEXT);
	//チュートリアル開始選択時テキスト
	gTitle_Select_Tutorial_Text_Image.Load2D(TITLE_SELECT_TUTORIAL_TEXT);
	//ゲームスタート画像の追加
	gTitle_Select_GameStart_Image.Load2D(TITLE_SELECT_GAMESTART_IMAGE);
	//チュートリアルスタート画像の追加
	gTitle_Select_TutorialStart_Image.Load2D(TITLE_SELECT_TUTORIALSTART_IMAGE);
	//ボタンを押したときに描画されるフェイドアウト、イン用背景
	gTitle_Select_Fade_Image.Load2D(TITLE_SELECT_FADE_IMAGE);
	//タイトルBGMの読み込み
	Title_Bgm.Load(BGM_TITLE);
	//タイトルBGMの再生
	Title_Bgm.Play(BGM_TITLE_VOLUME);
}

//更新処理のオーバーライド
void CSceneTitle::Update() {
	if (mTitleflag == false) {
		if (CKey::Once(VK_RETURN)) {
			mTitleflag = true;
		}
	}

	if (mTitleflag == true)
	{
		//ボタンを押していないとき
		if (mIsButtonPush == false) {
			//マウスの座標を取得
			CInput::GetMousePosWin(&mMouseX, &mMouseY);
			mMouseY = TITLE_SELECT_END_Y - mMouseY;
		}

		//ゲームスタートボタン上にマウスポインタがあるとき
		if ((mMouseX >= STARTBUTTON_LEFT && mMouseX <= STARTBUTTON_RIGHT) &&
			(mMouseY >= STARTBUTTON_DOWN && mMouseY <= STARTBUTTON_UP)) {
			//選択している場所をゲームスタートに設定
			mSelect = EGAMESTART;
		}
		//チュートリアルボタン上にマウスポインタがあるとき
		else if ((mMouseX >= TUTORIALBUTTON_LEFT && mMouseX <= TUTORIALBUTTON_RIGHT) &&
			(mMouseY >= TUTORIALBUTTON_DOWN && mMouseY <= TUTORIALBUTTON_UP)) {
			//選択している場所をチュートリアルに設定
			mSelect = CSceneTitle::ETUTORIAL;
		}
		//上記以外は背景
		else {
			//選択している場所を背景に設定
			mSelect = EBACKGROUND;
		}

		//左クリックしたとき
		if (CKey::Once(VK_LBUTTON)) {
			//選択している場所を判断する
			switch (mSelect) {
			case EGAMESTART: //ゲームスタート
				//ボタンを押していないとき
				if (mIsButtonPush == false) {
					mIsButtonPush = true;	//ボタンを押したら実行
					//次のシーンはゲーム
					mNextScene = CScene::EScene::EGAME;
					//シーン切り替え実行
					mSceneChange = true;
					//タイトルBGM停止
					Title_Bgm.Stop();
				}
				break;

			case CSceneTitle::ETUTORIAL: //チュートリアルスタート
					//ボタンを押していないとき
				if (mIsButtonPush == false) {
					mIsButtonPush = true;	//ボタンを押したら実行
					//次のシーンはチュートリアル
					mNextScene = CScene::EScene::ETUTORIAL;
					//シーン切り替え実行
					mSceneChange = true;
					//タイトルBGM停止
					Title_Bgm.Stop();
				}
				break;

			default:
				break;
			}
		}
	}

	if (mSceneChange) {
		mScene = mNextScene;
	}
}

//描画処理
void CSceneTitle::Render() {
	//2Dの描画開始
	CUtil::Start2D(START2D_FIRST_WID, START2D_END_WID, START2D_FIRST_HEI, START2D_END_HEI);
	if (mTitleflag == false)
	{
		//タイトル画面描画
		gTitle_Image.Draw(TITLE_FIRST_WID, TITLE_END_WID, TITLE_FIRST_HEI, TITLE_END_HEI, TITLE_FIRST_X, TITLE_END_X, TITLE_END_Y, TITLE_FIRST_Y);
	}
	//タイトル画像描画後
	if (mTitleflag == true)
	{
			//タイトル選択画面描画
			gTitle_Select_Image.Draw(TITLE_SELECT_FIRST_WID, TITLE_SELECT_END_WID, TITLE_SELECT_FIRST_HEI, TITLE_SELECT_END_HEI, TITLE_SELECT_FIRST_X, TITLE_SELECT_END_X, TITLE_SELECT_END_Y, TITLE_SELECT_FIRST_Y);
			//ゲームスタートスタート画像描画
			gTitle_Select_GameStart_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
			//チュートリアルスタート画像描画
			gTitle_Select_TutorialStart_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
			//背景を選択していたら描画
			if (mSelect == EBACKGROUND)
			{
				//タイトル選択画面テキスト
				gTitle_Select_Text_Image.Draw(TITLE_SELECT_TEXT_FIRST_WID, TITLE_SELECT_TEXT_END_WID, TITLE_SELECT_TEXT_FIRST_HEI, TITLE_SELECT_TEXT_END_HEI, TITLE_SELECT_TEXT_FIRST_X, TITLE_SELECT_TEXT_END_X, TITLE_SELECT_TEXT_END_Y, TITLE_SELECT_TEXT_FIRST_Y);
			}
			//ゲームスタートを選択していたら描画
			if (mSelect == EGAMESTART){
				//ゲーム開始選択時テキスト
				gTitle_Select_GameStart_Text_Image.Draw(TITLE_SELECT_GAMESTART_TEXT_FIRST_WID, TITLE_SELECT_GAMESTART_TEXT_END_WID, TITLE_SELECT_GAMESTART_TEXT_FIRST_HEI, TITLE_SELECT_GAMESTART_TEXT_END_HEI, TITLE_SELECT_GAMESTART_TEXT_FIRST_X, TITLE_SELECT_GAMESTART_TEXT_END_X, TITLE_SELECT_GAMESTART_TEXT_END_Y, TITLE_SELECT_GAMESTART_TEXT_FIRST_Y);
				//ボタンを押したときに描画されるフェイドアウト、イン用背景
				gTitle_Select_Fade_Image.Draw(STARTBUTTON_LEFT, STARTBUTTON_RIGHT, STARTBUTTON_DOWN, STARTBUTTON_UP, STARTBUTTON_FIRST_X, STARTBUTTON_END_X, STARTBUTTON_END_Y, STARTBUTTON_FIRST_Y);
			}
			//チュートリアルを選択していたら描画
			if (mSelect == ETUTORIAL) {
				//チュートリアル開始選択時テキスト
				gTitle_Select_Tutorial_Text_Image.Draw(TITLE_SELECT_TUTORIAL_TEXT_FIRST_WID, TITLE_SELECT_TUTORIAL_TEXT_END_WID, TITLE_SELECT_TUTORIAL_TEXT_FIRST_HEI, TITLE_SELECT_TUTORIAL_TEXT_END_HEI, TITLE_SELECT_TUTORIAL_TEXT_FIRST_X, TITLE_SELECT_TUTORIAL_TEXT_END_X, TITLE_SELECT_TUTORIAL_TEXT_END_Y, TITLE_SELECT_TUTORIAL_TEXT_FIRST_Y);
				//ボタンを押したときに描画されるフェイドアウト、イン用背景
				gTitle_Select_Fade_Image.Draw(TUTORIALBUTTON_LEFT, TUTORIALBUTTON_RIGHT, TUTORIALBUTTON_DOWN, TUTORIALBUTTON_UP, TUTORIALBUTTON_FIRST_X, TUTORIALBUTTON_END_X, TUTORIALBUTTON_END_Y, TUTORIALBUTTON_FIRST_Y);
			}
			
	}
	//2Dの描画終了
	CUtil::End2D();
}

//次のシーンに移行
CScene::EScene CSceneTitle::GetNextScene() {
	//現在のシーンを返す
	return mScene;
}