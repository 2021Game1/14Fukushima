#ifndef CDRIVERSATOU_H
#define CDRIVERSATOU_H
#include "CScene.h"
#include"CPlayer.h"
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

extern CTexture Texture;



class CDriverSatou{

public :
	int mRight, mLeft,mBottom,mTop; 
	int buf;
	int mScene;
	

	void Init()
	{

		//画面範囲右の設定
		mRight = mLeft + WINDOW_WIDTH;
		//画面下の設定
		//mBottom = CPlayer::spInstance->y - HEIGHT / 2;
		mBottom = -590;
		//画面範囲上の設定
		mTop = mBottom + WINDOW_HEIGHT;

		/*画面の投影変更開始*/
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();//行列（設定）を初期化
		//2Dの投影範囲の設定
		gluOrtho2D(mLeft, mRight, mBottom, mTop);
		for (int i = 0; i < VectorRect.size(); i++) {
			//描画処理
			VectorRect[i]->Render();
		}
		glLoadIdentity();//行列（設定）を初期化
	//2Dの投影範囲を設定
		gluOrtho2D(-960, 960, -590, 590);

		 
		//enum EScene {
		//	EGAME,	//ゲーム
		//	ETITLE, //タイトル
		//};


		//char buf[10];
		//CText::DrawString(buf, 300, 250, 16, 16);
		//if (BOSS::m_Hp == 0) {

		//	CText::DrawString("GAME CLEAR", 0 + 0 * 7, 0, 16, 16);

		//	if (CKey::Once(VK_RETURN)) {

		//		//次のシーンはゲーム
		//		 mScene =  ETITLE;



		//		//if (CEnemy1::m_Hp == 0) {
		//		//	CText::DrawString("Next Game", 0 + 0 * 7, 0, 16, 16);

		//		//	if (CKey::Once(VK_RETURN)) {

		//		//		//次のシーンはゲーム
		//		//		->mScene = ->EGAME;

		//		//	}
		//	}
		//		else {
		//			CText::DrawString(buf, 150 + 32 * 7, -250, 16, 16);
		//			if (CPlayer::mHp == 0) {

		//				CText::DrawString("GAME OVER", 0 + 0 * 7, 0, 16, 16);

		//				if (CKey::Once(VK_RETURN)) {
		//					//次のシーンはゲーム
		//					mScene = ETITLE;

		//				}
		//			}
		//		}
		//}
	}








	void Update() {
		//画面範囲左の設定
		if (3300 > mLeft) {

			mLeft++;

		}
	}
};















#endif //終了

