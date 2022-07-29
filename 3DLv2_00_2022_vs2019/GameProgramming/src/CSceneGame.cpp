#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"



void CSceneGame::Init() {
	//3Dモデルファイルの読み込み
	gModelX.Load(MODEL_FILE);
	//キャラクタにモデルを設定
	mPlayer.Init(&gModelX);
	//敵の初期設定
	mEnemy.Init(&gModelX);
	//敵の配置
	mEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

void CSceneGame::Update() {
	//キャラクタクラスの更新
	mPlayer.Update();
	//敵の更新
	mEnemy.Update();
	
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 2.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);
	
	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();

	//X軸+回転
	if (CKey::Push('K')) {
		gMatrix = gMatrix * CMatrix().RotateX(1);
	}
	//Y軸+回転
	if (CKey::Push('L')){
		gMatrix = gMatrix * CMatrix().RotateY(1);
	}
	//X軸-回転
	if (CKey::Push('I')) {
		gMatrix = gMatrix * CMatrix().RotateX(-1);
	}
	//Y軸-回転
	if (CKey::Push('J')) {
		gMatrix = gMatrix * CMatrix().RotateY(-1);
	}
	//行列設定
	glMultMatrixf(gMatrix.M());
	
	//頂点にアニメーション適用する
	gModelX.AnimeteVertex();
	//モデル描画
	mPlayer.Render();
	//敵描画
	mEnemy.Render();


	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();

}

