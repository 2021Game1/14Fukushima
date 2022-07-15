#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CText.h"
#include "CXPlayer.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
	CText mFont;
	//確認用インスタンス
	CModelX gModelX;
	//プレイヤークラスのインスタンス
	CXPlayer mPlayer;
	//キー入力で回転
	CMatrix gMatrix;
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
};

#endif