#include "CRes.h"

CRes* CRes::mpRes_Instance = nullptr;												//リソースのインスタンス変数の初期化

void CRes::Init() {
	mpRes_Instance = this;
	//BGMの読み込み
	Game_Bgm.Load(BGM_GAME);
	Title_Bgm.Load(BGM_TITLE);
	//プレイヤSE
	Se_Player_AttackSp1.Load(SE_PLAYER_ATTACK1);
	Se_Player_AttackSp2.Load(SE_PLAYER_ATTACK2);
	Se_Player_AttackSp3.Load(SE_PLAYER_ATTACK3);
	Se_Player_Walk.Load(SE_PLAYER_WALK);
	Se_Player_Death.Load(SE_PLAYER_DEATH);
	//敵SE
	Se_Enemy_AttackSp.Load(SE_ENEMY_ATTACK);
	Se_Enemy_Death.Load(SE_EMEMY_DEATH);

	//3Dモデルファイルの読み込み
	gPlayer_Model_Knight.Load(PLAYER_MODEL_FILE);
	//プレイヤのアニメーションの追加
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP3);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_DEATH);
	//プレイヤガードアクションエフェクトモデル
	gPlayer_GuardSP_Model.Load(PLAYER_MODEL_ACTION_GUARDSP);
	//タイトル画像の追加
	gTitle_Image.Load2D(TITLE_IMAGE);
	//ゲームクリア画像の追加
	gGameClear_Image.Load2D(GAMECLEAR_IMAGE);
	//ゲームオーバー画像の追加
	gGameOver_Image.Load2D(GAMEOVER_IMAGE);
	//キャラクタのUI追加
	gCharacter_Ui_Hp_GreenGauge.Load2D(CHARACTER_UI_HP_GREENGAUGE);
	gCharacter_Ui_Hp_RedGauge.Load2D(CHARACTER_UI_HP_REDGAUGE);
	//プレイヤのUIの追加
	gPlayer_Ui_Hp_Frame.Load2D(PLAYER_UI_HP_FRAME);
	//敵のUIの追加
	gEnemy_Ui_Hp_BackBar.Load2D(ENEMY_UI_HP_BACKBAR);
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
	mFont.LoadTexture("Font\\FontG.png", 1, 4096 / 64);
	mMap.Model(&gMap_Model);
	mMap_Sky.Model(&gMap_Model_Sky);
	//マップの移動行列
	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
	//親インスタンスと親行列はなし
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &gMap_Model_Collision);
}
void CRes::Update() {

}
//リソースのポインタを返すことで、座標などが参照できるようになる
CRes* CRes::GetInstance()
{
	return mpRes_Instance;
}
//フォントの取得
CText& CRes::GetInUiFont()
{
	return mFont;
}
//タイトル画像の取得
CTexture& CRes::GetInTitleImage()
{
	return gTitle_Image;
}
//クリア画面の取得
CTexture& CRes::GetinGameClearImage()
{
	return gGameClear_Image;
}
//ゲームオーバー画面の取得
CTexture& CRes::GetinGameOverImage()
{
	return gGameOver_Image;
}
//緑HPバーの取得
CTexture& CRes::GetInUiHpGreenGauge()
{
	return gCharacter_Ui_Hp_GreenGauge;
}
//赤HPバーの取得
CTexture& CRes::GetInUiHpRedGauge()
{
	return gCharacter_Ui_Hp_RedGauge;
}
//プレイヤのHP外枠の取得
CTexture& CRes::GetInPlayerUiHpFrame()
{
	return gPlayer_Ui_Hp_Frame;
}
//敵のHPバーの背景取得
CTexture& CRes::GetInEnemyUiHpBackBar()
{
	return gEnemy_Ui_Hp_BackBar;
}
//プレイヤの斬撃SE1を取得する
CSound& CRes::GetinPlayerSeAttackSp1() 
{
	return Se_Player_AttackSp1;
}
//プレイヤの斬撃SE2を取得する
CSound& CRes::GetinPlayerSeAttackSp2() 
{
	return Se_Player_AttackSp2;
}
//プレイヤの斬撃SE3を取得する
CSound& CRes::GetinPlayerSeAttackSp3() 
{
	return Se_Player_AttackSp3;
}
//プレイヤの歩行SEを取得
CSound& CRes::GetinPlayerSeWalk() 
{
	return Se_Player_Walk;
}
//プレイヤの死亡SEを取得
CSound& CRes::GetinPlayerSeDeath()
{
	return Se_Player_Death;
}
//敵の攻撃SEを取得する
CSound& CRes::GetinEnemySeAttackSp() 
{
	return Se_Enemy_AttackSp;
}
//敵の死亡SEを取得する
CSound& CRes::GetinEnemySeDeath()
{
	return Se_Enemy_Death;
}
//BGMの取得
//タイトルBGMの取得
CSound& CRes::GetinSoundBgmTitle()
{
	return Title_Bgm;
}
//ゲームBGMの取得
CSound& CRes::GetinSoundBgmGame() 
{
	return Game_Bgm;
}