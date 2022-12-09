#include "CRes.h"

CRes* CRes::mpRes_Instance = nullptr;												//リソースのインスタンス変数の初期化

void CRes::Init() {
	mpRes_Instance = this;
	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
	//3Dモデルファイルの読み込み
	gPlayer_Model_Knight.Load(PLAYER_MODEL_FILE);
	//プレイヤのアニメーションの追加
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP3);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_GUARD);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_GUARDIDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_DEATH);
	//キャラクタのUI追加
	gCharacter_Ui_Hp_GreenGauge.Load2D(CHARACTER_UI_HP_GREENGAUGE);
	gCharacter_Ui_Hp_RedGauge.Load2D(CHARACTER_UI_HP_REDGAUGE);
	//プレイヤのUIの追加
	gPlayer_Ui_Hp_Frame.Load2D(PLAYER_UI_HP_FRAME);
	//敵のUIの追加
	gEnemy_Ui_Hp_Frame.Load2D(ENEMY_UI_HP_FRAME);
	//カメラ初期化
	Camera.Init();
	//マップモデルファイルの入力
	gMap_Model.Load(MAP_MODEL_MAP);
	//スカイモデルファイルの入力
	gMap_Model_Sky.Load(MAP_MODEL_SKY);
	//マップのコライダファイルの入力
	gMap_Model_Collision.Load(MAP_COLLISION_MAP);
	//3Dモデルファイルの読み込み
	gEnemy_Model_Mutant.Load(ENEMY_MODEL_FILE);
	//エネミーのアニメーションの追加
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP1);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP2);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);
	//キャラクタにモデルを設定
	mPlayer.Init(&gPlayer_Model_Knight);
	//敵の初期設定
	mEnemy.Init(&gEnemy_Model_Mutant);
	mFont.LoadTexture("font\\FontG.png", 1, 4096 / 64);
	mMap.Model(&gMap_Model);
	//親インスタンスと親行列はなし
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &gMap_Model_Collision);
	//プレイヤのエフェクト
	gPlayer_Effect_Tex_ID = CEffect::GetInstance()->GetIsMaterial().Texture()->Id();
	gEffect_Texture = CEffect::GetInstance()->GetIsMaterial().Texture();
	gMaterial_Diffuse = CEffect::GetInstance()->GetIsMaterial();
	//エフェクト画像読み込み
	if (gPlayer_Effect_Tex_ID == 0) {
		gEffect_Texture->Load2D(PLAYER_EF_ATTACKSP1); //攻撃ヒット時のエフェクト
		gMaterial_Diffuse.Diffuse()[0] = 1.0f;
		gMaterial_Diffuse.Diffuse()[0] = 1.0f;
		gMaterial_Diffuse.Diffuse()[0] = 1.0f;
		gMaterial_Diffuse.Diffuse()[0] = 1.0f;
	}
}
void CRes::Update() {
	//キャラクタクラスの更新
	mPlayer.Update();
	//カメラクラスの更新
	Camera.Update();
	//カメラクラスの描画
	Camera.Render();
	//行列設定
	glMultMatrixf(gMatrix.M());
	//頂点にアニメーション適用する
	gPlayer_Model_Knight.AnimeteVertex();
	//モデル描画
	mPlayer.Render();
	//マップモデルの描画
	mMap.Render();
	gMap_Model_Sky.Render();
	//コライダの描画
	CCollisionManager::Get()->Render();
	//衝突処理
	CCollisionManager::Get()->Collision();
	//敵の更新
	mEnemy.Update();
	//敵の描画
	mEnemy.Render();
	mPlayer.Render2D();
	mEnemy.Render2D();

}
//リソースのポインタを返すことで、座標などが参照できるようになる
CRes* CRes::GetInstance()
{
	return mpRes_Instance;
}
CText& CRes::GetInUiFont()
{
	return mFont;
}
CTexture& CRes::GetInUiHpGreenGauge()
{
	return gCharacter_Ui_Hp_GreenGauge;
}
CTexture& CRes::GetInUiHpRedGauge()
{
	return gCharacter_Ui_Hp_RedGauge;
}
CTexture& CRes::GetInPlayerUiHpFrame()
{
	return gPlayer_Ui_Hp_Frame;
}
CTexture& CRes::GetInEnemyUiHpFrame()
{
	return gEnemy_Ui_Hp_Frame;
}
