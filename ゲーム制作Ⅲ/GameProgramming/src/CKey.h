#ifndef CKEY_H
#define CKEY_H

//GetKeyState関数のヘッダファイル
#include <Windows.h>
/*
CKeyクラス
キーボード入力を取得する
*/

#define KEY_NOWTIME 0.0f
#define KEY_OLDTIME 0.03f
#define KEY_NEXTBUTTONDOWNTIME 0.5f

class CKey {
public:
	
	/*
	Pushはstatic(スタティック)メソッド
	keyの値のキーが押されていればtrueを、
	押されていなければfalseを戻す
	*/
	static bool Push(char key);
	static bool Once(char key);
	static bool Double(char key);

private:
	static bool Flg[256];
	static int	Process;
	static float Key_NowTime;         //最初に移動ボタンが押されてからの経過時間
	static float Key_OldTime;         //以前の経過時間
	static float Key_NextButtonDownTime;    //　次に移動ボタンが押されるまでの時間
};

#endif
