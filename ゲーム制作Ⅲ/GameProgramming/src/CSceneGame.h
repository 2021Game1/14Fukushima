#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include <time.h>
#include "CScene.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CText.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CMap.h"
#include "CColliderMesh.h"


/*
ゲームのシーン
*/
class CSceneGame : public CScene {
	CText mFont;
	//確認用インスタンス
	CModelX gModelX;
	CModel gMap;
	CModel gCollision;
	//プレイヤークラスのインスタンス
	CXPlayer mPlayer;
	//キー入力で回転
	CMatrix gMatrix;
	//敵のインスタンス
	CXEnemy mEnemy;
	//敵モデル
	CModelX gKnight;
	//マップモデル
	CMap mMap;
	//マップ移動用の行列
	CMatrix mBackGroundMatrix;
	clock_t mStartTime, mEndTime;//計測開始時刻、計測終了時刻
	bool mCountStart; //クリア時間計測開始用
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;
	//staticでポインタを作る
	static CSceneGame* mpSceneGameInstance;
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//staticで処理を作る
	static CSceneGame* GetInstance();

};

#endif