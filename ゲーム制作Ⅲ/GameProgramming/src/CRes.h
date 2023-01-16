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
#include"CPlayerGuard.h"
#include "CXEnemy.h"
#include "CMap.h"
#include "CEffect.h"
#include "CColliderMesh.h"
#include "CEffect.h"
#include "CShadowMap.h"
#include "CSound.h"



/*プレイヤのアニメーションモデル*/

#define PLAYER_MODEL_FILE "res\\Player\\Paladin\\paladin.x"
#define PLAYER_ANIMATION_ATTACKSP1 "res\\Player\\Paladin\\Attack1.x"
#define PLAYER_ANIMATION_ATTACKSP2 "res\\Player\\Paladin\\Attack2.x"
#define PLAYER_ANIMATION_ATTACKSP3 "res\\Player\\Paladin\\Attack3.x"
#define PLAYER_ANIMATION_GUARD "res\\Player\\Paladin\\Guard.x"
#define PLAYER_ANIMATION_GUARDIDLE "res\\Player\\Paladin\\GuardIdle.x"
#define PLAYER_ANIMATION_IDLE "res\\Player\\Paladin\\Idle.x"
#define PLAYER_ANIMATION_KNOCKBACK "res\\Player\\Paladin\\KnockBack.x"
#define PLAYER_ANIMATION_DEATH "res\\Player\\Paladin\\Death.x"
#define PLAYER_MODEL_ACTION_GUARDSP "res\\Player\\Paladin\\Shield.obj","res\\Player\\Paladin\\Shield.mtl"

/*エネミーのアニメーションモデル*/

#define ENEMY_MODEL_FILE "res\\Enemy\\Mutant\\mutant.x"
#define ENEMY_ANIMATION_ATTACKSP1 "res\\Enemy\\Mutant\\Attack1.x"
#define ENEMY_ANIMATION_ATTACKSP2 "res\\Enemy\\Mutant\\Attack2.x"
#define ENEMY_ANIMATION_WALK "res\\Enemy\\Mutant\\Walk.x"
#define ENEMY_ANIMATION_DASH "res\\Enemy\\Mutant\\Dash.x"
#define ENEMY_ANIMATION_IDLE "res\\Enemy\\Mutant\\Idle.x"
#define ENEMY_ANIMATION_KNOCKBACK "res\\Enemy\\Mutant\\KnockBack.x"
#define ENEMY_ANIMATION_DEATH "res\\Enemy\\Mutant\\Death.x"

/*マップのモデル*/

#define MAP_MODEL_MAP "res\\Map\\map.obj","res\\Map\\map.mtl"
#define MAP_MODEL_SKY "res\\Sky\\sky.obj","res\\Sky\\sky.mtl"
#define MAP_COLLISION_MAP "res\\Map\\collision.obj","res\\Map\\collision.mtl"

/*画像, UI*/

//HPゲージ
#define CHARACTER_UI_HP_GREENGAUGE "res\\Ui\\HP_Gauge.png"
#define CHARACTER_UI_HP_REDGAUGE "res\\Ui\\HP_RedGauge.png"
//プレイヤUI
#define PLAYER_UI_HP_FRAME "res\\Ui\\Player_HP_Frame.png"
//敵UI
#define ENEMY_UI_HP_BACKBAR "res\\Ui\\Enemy_HP_BackBar.png"
//プレイヤ専用攻撃エフェクト
#define PLAYER_EF_ATTACKSP1 "res\\Effect\\Player_Attack1.png"
#define PLAYER_EF_ATTACKSP2 "res\\Effect\\Player_Attack2.png"
#define PLAYER_EF_ATTACKSP3 "res\\Effect\\Player_Attack3.png"
//シャドウマッピング用
#define TEXWIDTH  8192	//テクスチャ幅
#define TEXHEIGHT  6144	//テクスチャ高さ

/*サウンド・SE*/

#define BGM "res\\Bgm\\BGM.wav"
//SE・プレイヤ
#define SE_PLAYER_ATTACK1 "res\\Se\\SE_Player_AttackSp1.wav"
#define SE_PLAYER_ATTACK2 "res\\Se\\SE_Player_AttackSp2.wav"
#define SE_PLAYER_ATTACK3 "res\\Se\\SE_Player_AttackSp3.wav"
#define SE_PLAYER_GUARD "res\\Se\\SE_Player_Guard.wav"
#define SE_PLAYER_WALK "res\\Se\\SE_Player_Walk.wav"
//SE・敵
#define SE_ENEMY_ATTACK "res\\Se\\SE_Enemy_AttackSp.wav" 


class CRes {
public:
	void Update();
	void Init();
	
	CText& GetInUiFont();
	//HPゲージを取得す津
	CTexture& GetInUiHpGreenGauge();
	CTexture& GetInUiHpRedGauge();
	CTexture& GetInPlayerUiHpFrame();
	CTexture& GetInEnemyUiHpBackBar();
	//プレイヤSEを取得する
	CSound& GetinPlayerSeAttackSp1();
	CSound& GetinPlayerSeAttackSp2();
	CSound& GetinPlayerSeAttackSp3();
	CSound& GetinPlayerSeGuard();
	CSound& GetinPlayerSeWalk();
	//敵SEを取得する
	CSound& GetinEnemySeAttackSp();
	static CRes* GetInstance();//staticで処理を作る

private:
	//フォント
	CText mFont;
	//CSoundクラスのインスタンス作成
	CSound Bgm;
	//プレイヤSE
	CSound Se_Player_AttackSp1;
	CSound Se_Player_AttackSp2;
	CSound Se_Player_AttackSp3;
	CSound Se_Player_Guard;
	CSound Se_Player_Walk;
	//敵SE
	CSound Se_Enemy_AttackSp;
	//プレイヤモデル
	CModelX gPlayer_Model_Knight;
	//プレイヤのガードアクションエフェクト
	CModel gPlayer_GuardSP_Model;
	CPlayerGuard mPlayer_GuardSP_Model;
	//敵モデル
	CModelX gEnemy_Model_Mutant;
	//マップモデル
	CModel gMap_Model;
	//マップの背景モデル
	CModel gMap_Model_Sky;
	//マップの当たり判定モデル
	CModel gMap_Model_Collision;
	//プレイヤクラスのインスタンス
	CXPlayer mPlayer;
	//敵クラスのインスタンス
	CXEnemy mEnemy;
	//マップクラスのインスタンス
	CMap mMap;
	CMap mMap_Sky;
	//キー入力で回転
	CMatrix gMatrix;
	//マップ移動用の行列
	CMatrix mBackGroundMatrix;
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;
	//キャラクタのUIインスタンス
	CTexture gCharacter_Ui_Hp_GreenGauge;
	CTexture gCharacter_Ui_Hp_RedGauge;
	//プレイヤのUIインスタンス
	CTexture gPlayer_Ui_Hp_Frame;
	//敵のUIインスタンス
	CTexture gEnemy_Ui_Hp_BackBar;
	static CRes* mpRes_Instance;//別のクラスでリソースの変数を呼び出す場合,staticでポインタを作る

};
#endif

