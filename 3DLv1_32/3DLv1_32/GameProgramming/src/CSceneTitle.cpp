//#include"CSceneTitle.h"
//
//void CSceneTitle::Render()
//{
//	//親の描画処理
//	CCharacter::Render();
//
//	//2Dの描画開始
//	CUtil::Start2D(-400, 400, -300, 300);
//	//描画色の設定(緑色の半透明)
//	glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
//	//文字列編集エリアの作成
//	char buf[64];
//
//	//Y座標の表示
//	//文字列の設定
//	sprintf(buf, "PY:%7.2f", mPosition.Y());
//	//文字列の描画
//	mText.DrawString(buf, 100, 30, 8, 16);
//
//	//X軸回転値の表示
//	//文字列の設定
//	sprintf(buf, "RX:%7.2f", mRotation.X());
//	//文字列の描画
//	mText.DrawString(buf, 100, 0, 8, 16);
//
//	//Y軸回転値の表示
//	//文字列の設定
//	sprintf(buf, "RY:%7.2f", mRotation.Y());
//	//文字列の描画
//	mText.DrawString(buf, 100, -100, 8, 16);
//
//	//2Dの描画終了
//	CUtil::End2D();
//}