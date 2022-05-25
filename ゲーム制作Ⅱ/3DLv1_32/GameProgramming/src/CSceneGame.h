#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModel.h"
//プレイヤークラスのインクルード
#include"CPlayer.h"
//ベクトルクラスのインクルード
#include"CVector.h"
//ミサイルクラス
#include"CMissile.h"
//三角形クラスのインクルード
#include"CTriangle.h"
//タスクマネージャクラスのインクルード
#include"CTaskManager.h"
//敵のクラスのインクルード
#include"CEnemy.h"
//敵2のクラスのインクルード
#include"CEnemy2.h"
//コリジョンマネージャクラスのインクルード
#include"CCollisionManager.h"
//ビルボードクラスのインクルード
#include"CBillBoard.h"
//カメラクラスのインクルード
#include"CCamera.h"
//三角コライダクラスのインクルード
#include"CColliderTriangle.h"
//キークラスのインクルード
#include"CKey.h"
//マトリックスクラスのインクルード
#include"CMatrix.h"
//トランスフォームクラスのインクルード
#include"CTransform.h"
//キャラクタクラスのインクルード
#include"CCharacter.h"
//三角コライダの生成クラスのインクルード
#include"CColliderMesh.h"


/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//モデルクラスのインスタンス作成
	CModel mModel; //プレイヤーモデル
	CModel mBackGround; //背景モデル
	CModel mModelC5; //敵モデル
	CModel mMap;     //マップ
	//プレイヤーの変数
	CPlayer mPlayer;
	//カメラの視点の変数
	CVector mEye;
	//マトリックスの変数
	CMatrix matrix;
	//背景移動用の行列
	CMatrix mBackGroundMatrix;
	//モデルからコライダを生成
	CColliderMash mColliderMesh;

};

#endif
