#ifndef CGAMETEST
#define CGAMETEST

#include "CGameTest.h"
#include "CModel.h"
//プレイヤークラスのインクルード
#include"CPlayer.h"
//ベクトルクラスのインクルード
#include"CVector.h"
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

#include"CMoney.h"

#include<time.h>
#include<stdlib.h>
#include<stdio.h>

//モデルデータの指定
#define MODEL_OBJ "res\\model.obj","res\\model.mtl"
#define MODEL_MAP "res\\city.obj","res\\city.mtl"
#define MODEL_COLISION "res\\colision.obj","res\\colision.mtl"
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"

class CGameTest {
	//モデルクラスのインスタンス作成
	CModel mModel; //プレイヤーモデル
	CModel mBackGround; //背景モデル
	CModel mModelC5; //敵モデル
	CModel mMap; //マップモデル
	CModel mColision;     //コリジョンマップ
	//確認用インスタンス
	CMoney gMoney;
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
	CColliderMash ColliderMesh;

public:
	void Init() {
		mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
		mEye = CVector(1.0f, 2.0f, 3.0f);
		//モデルファイルの入力
		mModel.Load(MODEL_OBJ);
		//マップモデルファイルの入力
		mMap.Load(MODEL_MAP);
		//背景モデル
		mBackGround.Load(MODEL_BACKGROUND);
		//マップコリジョンのモデルファイルの入力
		mColision.Load(MODEL_COLISION);
		//マトリックスの描画変数
		matrix.Print();
		//プレイヤーのモデルポインタ
		mPlayer.Model(&mModel);
		mPlayer.Scale(CVector(0.5f, 0.5f, 0.5f));
		mPlayer.Position(CVector(92.0f, -0.5f, 76.0f) * mBackGroundMatrix);
		mPlayer.Rotation(CVector(0.0f, -180.0f, 0.0f));
		//敵機2のインスタンス作成
		new CEnemy2(CVector(-5.0f, -0.5f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
		new CEnemy2(CVector(5.0f, -0.5f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
		//ビルボードの生成
		/*new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);*/
		//背景モデルから三角コライダを生成
		//親インスタンスと親行列はなし
		mColliderMesh.Set(nullptr, &mBackGroundMatrix, &mColision);
		//親インスタンスと親行列はなし
		ColliderMesh.Set(nullptr, &mBackGroundMatrix, &mBackGround);

	}

	void  Update() {


		//カメラのパラメータを作成する
		CVector e, c, u;//視点,注視点,上方向
			//視点を求める
		e = mPlayer.Position() + CVector(0.0f, 1.0f, -2.5f) * mPlayer.MatirixRotate();
		//注視点を求める
		c = mPlayer.Position();
		//上方向を求める
		u = CVector(0.0f, 3.0f, 0.0f) * mPlayer.MatirixRotate();
		//カメラの設定
		//gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
		//カメラクラスの設定
		Camera.Set(e, c, u);
		Camera.Render();
		//マップモデルの描画
		mMap.Render();
		//背景モデルの描画
		mBackGround.Render();
	}




	
};
#endif //CGAMETEST

