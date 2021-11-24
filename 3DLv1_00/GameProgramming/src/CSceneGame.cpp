#include "CSceneGame.h"
//OpenGL
#include"glut.h"
//2.1
#include"CVector.h"
//3.2
#include"CTriangle.h"
//4.2
#include"CKey.h"
//課題11
#include"CMatrix.h"
//16.2
#include"CTransform.h"
//16.2
#include"CCharacter.h"
//17.1
#include"CPlayer.h"
//モデルデータの指定
#define MODEL_OBJ "res\\f14.obj","res\\f14.mtl"
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"
//カメラの視点の変数
CVector mEye;

//課題11
CMatrix matrix;

//17.1
CPlayer mPlayer;

void CSceneGame::Init() {
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//モデルファイルの入力
	mModel.Load(MODEL_OBJ);
	mBackGround.Load(MODEL_BACKGROUND);
	//課題11
	matrix.Print();
	
	//プレイヤーのモデルポインタ
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f));
	mPlayer.Position(CVector(0.0f, 0.0f, -3.0f));
	mPlayer.Rotation(CVector(0.0f, 180.0f,0.0f));
}

void CSceneGame::Update() {

	//頂点１，頂点２，頂点３，法線データの作成
	CVector v0, v1, v2, n;
	//法線を上向きで設定する
	n.Set(0.0f, 1.0f, 0.0f);
	//頂点１の座標を設定する
	v0.Set(0.0f, 0.0f, 0.5f);
	//頂点２の座標を設定する
	v1.Set(1.0f, 0.0f, 0.0f);
	//頂点３の座標を設定する
	v2.Set(0.0f, 0.0f, -0.5f);

	////視点の移動
	////Jキー:X軸マイナス方向へ移動
	//if (CKey::Push('J'))
	//{a
	//	mEye = mEye - CVector(0.1f, 0.0f, 0.0f);
	//}
	////Lキー:X軸プラス方向へ移動
	//if (CKey::Push('L'))
	//{
	//	mEye = mEye + CVector(0.1f, 0.0f, 0.0f);
	//}
	////Iキー:Y軸マイナス方向へ移動
	//if (CKey::Push('I'))
	//{
	//	mEye = mEye - CVector(0.0f, 0.0f, 0.1f);
	//}
	////Kキー:Y軸プラス方向へ移動
	//if (CKey::Push('K'))
	//{
	//	mEye = mEye + CVector(0.0f, 0.0f, 0.1f);
	//}
	////課題4 Mキー:Y軸マイナス方向へ移動
	//if (CKey::Push('M'))
	//{
	//	mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	//}
	////課題4 Oキー:Y軸プラス方向へ移動
	//if (CKey::Push('O'))
	//{
	//	mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	//}
	//視点の設定
	//gluLookAt(視点X、視点Y、視点Z、中心X、中心Y、中心Z,上向X、上向Y、上向Z)
	/*gluLookAt(mEye.X(), mEye.Y(), mEye.Z(), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);*/
	
	

	mPlayer.Update();
	//カメラのパラメータを作成する
	CVector e, c, u;//視点,注視点,上方向
	//視点を求める
	e = mPlayer.Position() + CVector(0.0f,1.0f,-3.0f) * mPlayer.MatirixRotate();
	//注視点を求める
	c = mPlayer.Position();
	//上方向を求める
	u = CVector(0.0f,1.0f,0.0f) * mPlayer.MatirixRotate();
	//カメラの設定
	gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	mPlayer.Render();
	
	
	mBackGround.Render(CMatrix());//背景モデルの描画

	//CTransform trans; //変数行列インスタンスの作成
	//trans.Position(CVector(0.5f, 1.8f, 0.5f)); //位置の設定
	//trans.Rotation(CVector(-10.0f, -20.0f, -30.0f)); //回転の設定
	//trans.Scale(CVector(0.1f, 0.1f, 0.1f)); //拡大縮小の設定
	//trans.Update(); //行列の更新
	//mModel.Render(trans.Matrix()); //戦闘機モデルの描画


	//CTransform mPlayer;
	//mPlayer.Position(CVector(0.5f, 1.8f, 0.5f)); //位置の設定
	//mPlayer.Rotation(CVector(-10.0f, -20.0f, -30.0f)); //回転の設定
	//mPlayer.Scale(CVector(0.1f, 0.1f, 0.1f)); //拡大縮小の設定
	//mPlayer.Update(); //行列の更新
	//mModel.Render(mPlayer.Matrix()); //戦闘機モデルの描画

	
}
	/*
	//描画開始
	glBegin(GL_TRIANGLES);


	//法線（面の向き）の設定
	glNormal3f(n.X(), n.Y(), n.Z());
	//頂点座標の設定
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());

	//法線と頂点の設定
	n.Set(0.0f, 0.0f, 1.0f);
	v0.Set(0.5f, 0.0f, 0.0f);
	v1.Set(0.0f, 1.0f, 0.0f);
	v2.Set(-0.5f, 0.0f, 0.0f);

	//三角形２の描画
	glNormal3f(n.X(), n.Y(), n.Z());
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());

	//課題２　法線と頂点の設定
	n.Set(1.0f, 0.0f, 0.0f);
	v0.Set(0.0f, 0.5f, 0.0f);
	v1.Set(0.0f, 0.0f, 1.0f);
	v2.Set(0.0f,-0.5f,0.0f);

	//課題２ 三角形３の描画
	glNormal3f(n.X(), n.Y(), n.Z());
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());

	//描画終了
	glEnd();

	//三角形クラスのインスタンス作成①
	CTriangle t0;
	//法線と頂点の設定①
	t0.Vertex(CVector(1.0f, 0.0f, 0.5f), CVector(2.0f, 0.0f, 0.0f), CVector(1.0f, 0.0f, -0.5f));
	t0.Normal(CVector(0.0f, 1.0f, 0.0f));
	//三角形の描画①
	t0.Render();

	//課題3　三角形クラス②のインスタンス作成
	CTriangle t1;
	//課題3 法線と頂点の設定②
	t1.Vertex(CVector(0.0f,0.5f,1.0f), CVector(0.0f, 0.0f,2.0f), CVector(0.0f,-0.5f,1.0f));
	t1.Normal(CVector(1.0f, 0.0f, 0.0f));
	//課題3 三角形の描画②
	t1.Render();

	//課題3 三角形クラス③のインスタンス作成
	CTriangle t2;
	//課題3 法線と頂点の設定③
	t2.Vertex(CVector(0.5f,1.0f,0.0f), CVector(0.0f,2.0f,0.0f), CVector(-0.5f,1.0,0.0f));
	t2.Normal(CVector(0.0f,0.0f,1.0f));
	//課題3 三角形の描画③
	t2.Render();
	*/


