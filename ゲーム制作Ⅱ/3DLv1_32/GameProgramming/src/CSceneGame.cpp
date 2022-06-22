//シーンゲームクラスのインクルード
#include "CSceneGame.h"
//OpenGL
#include"glut.h"

//モデルデータの指定
#define MODEL_OBJ "res\\car.obj","res\\car.mtl"
#define MODEL_MAP "res\\city.obj","res\\city.mtl"
#define MODEL_COLISION "res\\colision.obj","res\\colision.mtl"
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"


void CSceneGame::Init() {

	mMapMatrix.Translate(0.0f, 0.0f, 0.1f);
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
	//敵のモデルの読み込み
	mModelC5.Load("res\\C5.obj","res\\C5.mtl");
	//マトリックスの描画変数
	matrix.Print();
	//プレイヤーのモデルポインタ
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.5f, 0.5f, 0.5f));
	mPlayer.Position(CVector(92.0f, 0.0f, 76.0f)* mMapMatrix);
	mPlayer.Rotation(CVector(0.0f, -180.0f,0.0f));
	//敵機2のインスタンス作成
	new CEnemy2(CVector(-5.0f, 0.0f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
	new CEnemy2(CVector(5.0f, 0.0f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
	//ビルボードの生成
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	//背景モデルから三角コライダを生成
	//親インスタンスと親行列はなし
	mColliderMesh.Set(nullptr, &mMapMatrix, &mColision);
	//親インスタンスと親行列はなし
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &mBackGround);
}

void CSceneGame::Update() {
	//タスクマネージャの更新
	CTaskManager::Get()->Update();
	//コリジョンマネージャの衝突処理
	CTaskManager::Get()->TaskCollision();


	//カメラのパラメータを作成する
	CVector e, c, u;//視点,注視点,上方向
	//視点を求める
	e = mPlayer.Position() + CVector(0.0f,1.0f,-4.0f) * mPlayer.MatirixRotate();
	//注視点を求める
	c = mPlayer.Position();
	//上方向を求める
	u = CVector(0.0f,3.0f,0.0f) * mPlayer.MatirixRotate();
	//カメラの設定
	//gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	//カメラクラスの設定
	Camera.Set(e, c, u);
	Camera.Render();





	


	//マップモデルの描画
	mMap.Render();
	//背景モデルの描画
	mBackGround.Render();
	////コリジョンマネージャのコライダ描画
	//CCollisionManager::Get()->Render();
	//タスクリストの削除
	CTaskManager::Get()->Delete();
	//タスクマネージャの描画	
	CTaskManager::Get()->Render();


}



