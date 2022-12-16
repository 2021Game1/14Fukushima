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
#include "CEffect.h"
#include "CColliderMesh.h"
#include "CEffect.h"
#include "CShadowMap.h"



//プレイヤのアニメーションモデル
#define PLAYER_MODEL_FILE "res\\paladin\\paladin.x"
#define PLAYER_ANIMATION_ATTACKSP1 "res\\paladin\\Attack1.x"
#define PLAYER_ANIMATION_ATTACKSP2 "res\\paladin\\Attack2.x"
#define PLAYER_ANIMATION_ATTACKSP3 "res\\paladin\\Attack3.x"
#define PLAYER_ANIMATION_GUARD "res\\paladin\\Guard.x"
#define PLAYER_ANIMATION_GUARDIDLE "res\\paladin\\GuardIdle.x"
#define PLAYER_ANIMATION_IDLE "res\\paladin\\Idle.x"
#define PLAYER_ANIMATION_KNOCKBACK "res\\paladin\\KnockBack.x"
#define PLAYER_ANIMATION_DEATH "res\\paladin\\Death.x"

//エネミーのアニメーションモデル
#define ENEMY_MODEL_FILE "res\\mutant\\mutant.x"
#define ENEMY_ANIMATION_ATTACKSP1 "res\\mutant\\Attack1.x"
#define ENEMY_ANIMATION_ATTACKSP2 "res\\mutant\\Attack4.x"
#define ENEMY_ANIMATION_WALK "res\\mutant\\Walk.x"
#define ENEMY_ANIMATION_DASH "res\\mutant\\Dash.x"
#define ENEMY_ANIMATION_IDLE "res\\mutant\\Idle.x"
#define ENEMY_ANIMATION_KNOCKBACK "res\\mutant\\KnockBack.x"
#define ENEMY_ANIMATION_DEATH "res\\mutant\\Death.x"

//マップのモデル
#define MAP_MODEL_MAP "res\\map\\map.obj","res\\map\\map.mtl"
#define MAP_MODEL_SKY "res\\sky\\sky.obj","res\\sky\\sky.mtl"
#define MAP_COLLISION_MAP "res\\map\\collision.obj","res\\map\\collision.mtl"

//画像,UI
#define CHARACTER_UI_HP_GREENGAUGE "res\\ui\\HP_Gauge.png"
#define CHARACTER_UI_HP_REDGAUGE "res\\ui\\HP_RedGauge.png"
#define PLAYER_UI_HP_FRAME "res\\ui\\Player_HP_Frame.png"
#define ENEMY_UI_HP_FRAME "res\\ui\\Enemy_HP_Frame.png"

#define PLAYER_EF_ATTACKSP1 "res\\effect\\Player_Attack1.png"
#define PLAYER_EF_ATTACKSP2 "res\\effect\\Player_Attack2.png"
#define PLAYER_EF_ATTACKSP3 "res\\effect\\Player_Attack3.png"
#define TEXWIDTH  8192	//テクスチャ幅
#define TEXHEIGHT  6144	//テクスチャ高さ


class CRes {
public:
	void Update();
	void Init();
	CText& GetInUiFont();
	CTexture& GetInUiHpGreenGauge();
	CTexture& GetInUiHpRedGauge();
	CTexture& GetInPlayerUiHpFrame();
	CTexture& GetInEnemyUiHpFrame();
	static CRes* GetInstance();//staticで処理を作る
private:
	//フォント
	CText mFont;
	//プレイヤモデル
	CModelX gPlayer_Model_Knight;
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
	CTexture gEnemy_Ui_Hp_Frame;
	static CRes* mpRes_Instance;//別のクラスでリソースの変数を呼び出す場合,staticでポインタを作る

};
#endif

