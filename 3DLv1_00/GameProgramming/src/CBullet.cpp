#include"CBullet.h"
#define VELOCITYBULLET CVector(0.0f,0.0f,0.2f)//移動速度


//幅と奥行きの設定
//Set(幅,奥行)
void CBullet::Set(float w, float d) {
	//スケール設定
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//三角形の頂点設定
	mT.Vertex(CVector(0.5f, 0.0f, 0.0f), CVector(0.0f, 0.0f, -1.0f), CVector(-0.5, 0.0f, 0.0f));
	//三角形の法線設定
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//更新処理
void CBullet::Update() {
	CTransform::Update();
	//位置更新
	mPosition = mPosition + VELOCITYBULLET * mMatrixRotate;
}

//描画
void CBullet::Render() {
	//DIFFUSE黄色設定
	float c[] = { 1.0f,1.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//三角形描画
	

}