#ifndef CRES_H
#define CRES_H


#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"
#include "CCollisionManager.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CText.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CMap.h"
#include "CColliderMesh.h"

#define MODEL_MAP "res\\map\\map.obj","res\\map\\map.mtl"
#define MODEL_SKY "res\\sky\\sky.obj","res\\sky\\sky.mtl"
#define COLLISION_MAP "res\\map\\collision.obj","res\\map\\collision.mtl"

class CRes {
	CText mFont;
	//確認用インスタンス
	CModelX gModelX;
	CModel gMap;
	CModel gSky;
	CModel gCollision;
	//プレイヤークラスのインスタンス
	CXPlayer mPlayer;
	//キー入力で回転
	CMatrix gMatrix;
	//敵のインスタンス
	CXEnemy mEnemy;
	//敵モデル
	CModelX gMutant;
	//マップモデル
	CMap mMap;
	//マップ移動用の行列
	CMatrix mBackGroundMatrix;
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;
public:

	void Init() {
		mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
		//3Dモデルファイルの読み込み
		gModelX.Load(PLAYER_MODEL_FILE);
		//プレイヤのアニメーションの追加
		gModelX.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP3);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_GUARD);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_GUARDIDLE);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_IDLE);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_DEATH);
		//カメラ初期化
		Camera.Init();

		//マップモデルファイルの入力
		gMap.Load(MODEL_MAP);
		//スカイモデルファイルの入力
		gSky.Load(MODEL_SKY);
		//マップのコライダファイルの入力
		gCollision.Load(COLLISION_MAP);
		//3Dモデルファイルの読み込み
		gMutant.Load(ENEMY_MODEL_FILE);
		//エネミーのアニメーションの追加
		gMutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP1);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP2);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP4);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);
		//キャラクタにモデルを設定
		mPlayer.Init(&gModelX);
		//敵の初期設定
		mEnemy.Init(&gMutant);
		mFont.LoadTexture("font\\FontG.png", 1, 4096 / 64);
		mMap.Model(&gMap);
		
		//親インスタンスと親行列はなし
		mColliderMesh.Set(nullptr, &mBackGroundMatrix, &gCollision);
	}

	void Update() {
		//キャラクタクラスの更新
		mPlayer.Update();


		Camera.Update();
		Camera.Render();
		

		//行列設定
		glMultMatrixf(gMatrix.M());

		//頂点にアニメーション適用する
		gModelX.AnimeteVertex();
		//モデル描画
		mPlayer.Render();
		//マップモデルの描画
		mMap.Render();
		gSky.Render();
		//コライダの描画
		CCollisionManager::Get()->Render();
		//衝突処理
		CCollisionManager::Get()->Collision();
		//敵の更新
		mEnemy.Update();
		//敵描画
		mEnemy.Render();



		//2D描画開始
		CUtil::Start2D(0, 800, 0, 600);

		mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

		//2Dの描画終了
		CUtil::End2D();
	}
};
#endif

