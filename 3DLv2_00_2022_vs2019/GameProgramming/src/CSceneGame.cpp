#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CModelX.h"
#include "CKey.h"
#include "CUtil.h"

//確認用インスタンス
CModelX gModelX;

//キー入力で回転
CMatrix gMatrix;

void CSceneGame::Init() {
	//3Dモデルファイルの読み込み
	gModelX.Load(MODEL_FILE);
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

void CSceneGame::Update() {
	gModelX.AnimationSet()[0]->Time(gModelX.AnimationSet()[0]->Time() + 1.0f);
	gModelX.AnimationSet()[0]->Time((int)gModelX.AnimationSet()[0]->Time() % (int)(gModelX.AnimationSet()[0]->MaxTime() + 1));
	//最初のアニメーション重みを1.0(100%)にする
	gModelX.AnimationSet()[0]->Weught(1.0f);
	//フレームの変換行列をアニメーションで更新する
	gModelX.AnimateFrame();
	//フレームの合成行列を計算する
	gModelX.Frames()[0]->AnimateCombined(&gMatrix);
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
	gModelX.Render();

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();
}

