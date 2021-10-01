#include "CSceneGame.h"
//OpenGL
#include"glut.h"
//2.1
#include"CVector.h"
//3.2
#include"CTriangle.h"


void CSceneGame::Init() {

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

	//視点の設定
	//gluLookAt(視点X、視点Y、視点Z、中心X、中心Y、中心Z,上向X、上向Y、上向Z)
	gluLookAt(1.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

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
	//法線と頂点の設定②
	t1.Vertex(CVector(0.0f,0.5f,1.0f), CVector(0.0f, 0.0f,2.0f), CVector(0.0f,-0.5f,1.0f));
	t1.Normal(CVector(2.0f, 0.0f, 0.0f));
	//三角形の描画②
	t1.Render();

	//課題3 三角形クラス③のインスタンス作成
	CTriangle t2;
	//法線と頂点の設定③
	t2.Vertex(CVector(0.5f,1.0f,0.0f), CVector(0.0f,2.0f,0.0f), CVector(-0.5f,1.0,0.0f));
	t2.Normal(CVector(2.0f,0.0f,0.0f));
	//三角形の描画③
	t2.Render();
	
}

