#include "CKey.h"

bool CKey::Push(char key) {
	/*
	GetKeyState関数は引数のキーが押されている状態だと
	先頭ビットが1の16ビットの値を返します。
	押されていないと先頭ビットは0です。
	0x8000は1000000000000000の16ビットの値
	（16ビットの2進数）です。
	&は論理積演算(AND)です。
	*/
	return (GetAsyncKeyState(key) & 0x8000) == 0x8000;
}

/*初期化*/
bool CKey::Flg[256];
int CKey::Process = false;
float CKey::Key_NowTime = KEY_NOWTIME; //最初に移動ボタンが押されてからの経過時間
float CKey::Key_OldTime = KEY_OLDTIME;         //以前の経過時間
float CKey::Key_NextButtonDownTime = KEY_NEXTBUTTONDOWNTIME;    //　次に移動ボタンが押されるまでの時間


bool CKey::Once(char key) {
	//キーが押されているか
	if ((GetAsyncKeyState(key) & 0x8000)) {
		//!演算子：否定
		//押し中か判定
		if (!Flg[key]) {
			//押し中にする
			Flg[key] = true;
			//初めて押されたのでtrue返す
			return true;
		}
	}
	else {
		//押されていないのでfalseにする
		Flg[key] = false;
	}
	//押されていないか、押し中
	return false;
}

bool CKey::Double(char key) {
	if (!Process) {
		//キーが押されているか
		if ((GetAsyncKeyState(key) & 0x8000)) {
			//!演算子：否定
			//押し中か判定
			if (!Flg[key]) {
				//押し中にする
				Flg[key] = true;
				Key_NowTime = (Key_NowTime + Key_OldTime);
				if (Key_NowTime <= Key_NextButtonDownTime) {
					Process = true;
					return true;
				}
			}
		}
	}
	else {
		//押されていないのでfalseにする
		Flg[key] = false;
		Process = false;
	}
	//押し中か判定
	if (Flg[key]) {
		Key_NowTime = (Key_NowTime + Key_OldTime);
		if (Key_NowTime > Key_NextButtonDownTime) {
			return false;
		}
	}
}