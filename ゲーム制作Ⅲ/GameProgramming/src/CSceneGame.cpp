#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"
#include "CCollisionManager.h"


#define MODEL_MAP "res\\map\\map.obj","res\\map\\map.mtl"
#define COLLISION_MAP "res\\map\\Collision.obj","res\\map\\Collision.mtl"



CSceneGame* CSceneGame::mpSceneGameInstance;
//プレイヤーのポインタを返すことで、座標などが参照できるようになる
CSceneGame* CSceneGame::GetInstance()
{
	return mpSceneGameInstance;
}
void CSceneGame::Init() {
	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
	//3Dモデルファイルの読み込み
	gModelX.Load(MODEL_FILE);
	//マップモデルファイルの入力
	gMap.Load(MODEL_MAP);
	//マップのコライダファイルの入力
	gCollision.Load(COLLISION_MAP);
	//3Dモデルファイルの読み込み
	gKnight.Load("res\\knight\\knight_low.X");
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:移動
	gKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:待機
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:ダミー
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:ダミー
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:ダミー
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:ダミー
	gKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	gKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:ダミー
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:ダミー
	gKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:ダウン
	//キャラクタにモデルを設定
	mPlayer.Init(&gModelX);
	//敵の初期設定
	mEnemy.Init(&gKnight);
	//敵の配置
	mEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	mEnemy.ChangeAnimation(2, true, 200);
	mFont.LoadTexture("font\\FontG.png", 1, 4096 / 64);
	mMap.Model(&gMap);
	//親インスタンスと親行列はなし
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &gCollision);
}

void CSceneGame::Update() {
	Camera.Update();
	//キャラクタクラスの更新
	mPlayer.Update();
	//敵の更新
	mEnemy.Update();
	//カメラのパラメータを作成する
	CVector e, c, u;//視点,注視点,上方向
		//視点を求める
	e = mPlayer.Position() + CVector(0.0f, 1.2f, -3.0f) * mPlayer.MatrixRotate();
	//注視点を求める
	c = mPlayer.Position();
	//上方向を求める
	u = CVector(0.0f, 4.0f, 0.0f) * mPlayer.MatrixRotate();
	//カメラクラスの設定
	Camera.Set(e, c, u);
	

	Camera.Render();


	//行列設定
	glMultMatrixf(gMatrix.M());
	
	//頂点にアニメーション適用する
	gModelX.AnimeteVertex();
	//モデル描画
	mPlayer.Render();
		//マップモデルの描画
	mMap.Render();
	//コライダの描画
	CCollisionManager::Get()->Render();
	//衝突処理
	CCollisionManager::Get()->Collision();
	//敵描画
	mEnemy.Render();



	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();


}

