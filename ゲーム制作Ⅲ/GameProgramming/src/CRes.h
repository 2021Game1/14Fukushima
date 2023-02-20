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
#include "CSound.h"

//プレイヤのゲームオーバ体力設定
#define PLAYER_GAMEOVER_HP 0																	//ゲームオーバ設定
//プレイヤのパラメータマクロ
#define PLAYER_HP_MAX 100																		//HPの最大値
#define PLAYER_HP 100																			//HPの設定
#define PLAYER_SPEED_DEFAULT 0.2f																//スピード(通常時)
#define PLAYER_GRAVITY 0.9f																		//重力
#define PLAYER_THRUST 0.9																		//推力
#define PLAYER_SE 0.1																			//プレイヤSE設定
#define PLAYER_DAMAGE_SE 0.3																	//プレイヤダメージSE設定
#define PLAYER_RECEPTION 10																		//キー入力の受付時間
#define PLAYER_INRECEPTION 	21.0f																//当たり判定の受付時間															
#define PLAYER_OUTRECEPTION 60.0f																//当たり判定の終了時間
#define PLAYER_ATTACK_DIS 2.2f																	//敵に攻撃が追従可能になる距離

//プレイヤのアニメーションのフレーム設定
#define PLAYER_IDLE_ANIMATION_FRAME 20
#define PLAYER_MOVE_ANIMATION_FRAME 45															//移動のアニメーションフレーム設定
#define PLAYER_AVOIDANCE_ANIMATION_FRAME 50														//回避のアニメーションフレーム設定
#define PLAYER_ATTACK1_ANIMATION_FRAME 60														//攻撃1のアニメーションフレーム設定
#define PLAYER_ATTACK2_ANIMATION_FRAME 70														//攻撃2のアニメーションフレーム設定
#define PLAYER_ATTACK3_ANIMATION_FRAME 80														//攻撃3のアニメーションフレーム設定
#define PLAYER_KNOCKBACK_ANIMATION_FRAME 60														//ノックバックのアニメーションフレーム設定
#define PLAYER_DEATH_ANIMATION_FRAME 60															//死亡のアニメーションフレーム設定

//プレイヤのダメージ設定
#define PLAYER_DAMAGE_ENEMYSP1 15						//敵の攻撃1のダメージ	
#define PLAYER_DAMAGE_ENEMYSP2 10						//敵の攻撃2のダメージ
#define PLAYER_DAMAGE_ENEMYSP3 20						//敵の攻撃3のダメージ

//プレイヤのアニメーション番号の設定
#define PLAYER_ANIMATION_No_MOVE 0			//移動アニメーション番号
#define PLAYER_ANIMATION_No_ATTACK_1 1		//攻撃アニメーション1番号
#define PLAYER_ANIMATION_No_ATTACK_2 2		//攻撃アニメーション2番号
#define PLAYER_ANIMATION_No_ATTACK_3 3		//攻撃アニメーション3番号
#define PLAYER_ANIMATION_No_AVOIDANCE 4		//回避アニメーション番号
#define PLAYER_ANIMATION_No_IDLE 5			//待機アニメーション番号
#define PLAYER_ANIMATION_No_KNOCKBACK 6		//ノックバックアニメーション番号
#define PLAYER_ANIMATION_No_DEATH 7			//死亡アニメーション番号

//敵パラメータマクロ
#define ENEMY_HP_MAX 150			//HPの最大値
#define ENEMY_HP 150				//HP設定
#define ENEMY_DAMAGE_BODY 15		//ダメージ(体)
#define ENEMY_ATTACK_DIS 3.2f		//攻撃可能になる距離
#define ENEMY_SPEED_MOVE 0.1f		//通常移動のスピード
#define ENEMY_SPEED_DASH 0.15f		//走行の移動速度
#define ENEMY_SPEED_STOP 0.0f		//停止
#define ENEMY_WALK_DIS 30.0f		//歩行を開始する距離
#define ENEMY_SEARCH_DIS 60.0f		//走行を開始する距離
#define ENEMY_WALK_DIS_MAX 50.0f	//歩行可能な最大距離
#define ENEMY_CHASE_DIS_MAX 80.0f   //走行可能な最大距離
#define ENEMY_GRAVITY 0.9f			//重力
#define ENEMY_RECEPTION 26.0f		//当たり判定の受付時間
#define ENEMY_OUTRECEPTION 60.0f	//当たり判定の受付終了

//シャドウマッピング用マクロ
#define TEXWIDTH  8192	//テクスチャ幅
#define TEXHEIGHT  6144	//テクスチャ高さ


/*プレイヤのアニメーションモデル*/

#define PLAYER_MODEL_FILE "res\\Player\\Paladin\\paladin.x"
#define PLAYER_ANIMATION_ATTACKSP1 "res\\Player\\Paladin\\Attack1.x"
#define PLAYER_ANIMATION_ATTACKSP2 "res\\Player\\Paladin\\Attack2.x"
#define PLAYER_ANIMATION_ATTACKSP3 "res\\Player\\Paladin\\Attack3.x"
#define PLAYER_ANIMATION_AVOIDANCE "res\\Player\\Paladin\\Avoidance.x" 
#define PLAYER_ANIMATION_IDLE "res\\Player\\Paladin\\Idle.x"
#define PLAYER_ANIMATION_KNOCKBACK "res\\Player\\Paladin\\KnockBack.x"
#define PLAYER_ANIMATION_DEATH "res\\Player\\Paladin\\Death.x"

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
//タイトル画像
#define TITLE_IMAGE "res\\Image\\Title_Image.png"
//ゲームクリア画像
#define GAMECLEAR_IMAGE "res\\Image\\GameClear.png"
//ゲームオーバー画像
#define GAMEOVER_IMAGE "res\\Image\\GameOver_Image.png"
//HPゲージ
#define CHARACTER_UI_HP_GREENGAUGE "res\\Ui\\HP_Gauge.png"
#define CHARACTER_UI_HP_REDGAUGE "res\\Ui\\HP_RedGauge.png"
//プレイヤUI
#define PLAYER_UI_HP_FRAME "res\\Ui\\Player_HP_Frame.png"
//敵UI
#define ENEMY_UI_HP_BACKBAR "res\\Ui\\Enemy_HP_BackBar.png"
//敵ダメージエフェクト
#define ENEMY_EF_DAMAGESP1 "Effect\\Enemy_DamageSp1.png"
#define ENEMY_EF_DAMAGESP2 "Effect\\Enemy_DamageSp2.png"
#define ENEMY_EF_DAMAGESP3 "Effect\\Enemy_DamageSp3.png"

/*BGM・SE*/

//BGM
#define BGM_GAME "res\\Bgm\\Bgm_Game.wav"
#define BGM_TITLE "res\\Bgm\\Bgm_Title.wav"

//SE・プレイヤ
#define SE_PLAYER_ATTACK1 "res\\Se\\SE_Player_AttackSp1.wav"
#define SE_PLAYER_ATTACK2 "res\\Se\\SE_Player_AttackSp2.wav"
#define SE_PLAYER_ATTACK3 "res\\Se\\SE_Player_AttackSp3.wav"
#define SE_PLAYER_WALK "res\\Se\\SE_Player_Walk.wav"
#define SE_PLAYER_DEATH "res\\Se\\SE_Player_Death.wav"

//SE・敵
#define SE_ENEMY_ATTACK "res\\Se\\SE_Enemy_AttackSp.wav" 
#define SE_EMEMY_DEATH "res\\Se\\SE_Enemy_Death.wav"

class CRes {
public:
	//更新処理
	void Update();
	void Init();
	//タイトル画像を取得する
	CTexture& GetInTitleImage();
	//ゲームクリア画像を取得する
	CTexture& GetinGameClearImage();
	//ゲームオーバー画像を取得する
	CTexture& GetinGameOverImage();
	//UIフォントの取得
	CText& GetInUiFont();
	//HPゲージを取得する
	CTexture& GetInUiHpGreenGauge();
	CTexture& GetInUiHpRedGauge();
	CTexture& GetInPlayerUiHpFrame();
	CTexture& GetInEnemyUiHpBackBar();
	//プレイヤSEを取得する
	CSound& GetinPlayerSeAttackSp1();
	CSound& GetinPlayerSeAttackSp2();
	CSound& GetinPlayerSeAttackSp3();
	CSound& GetinPlayerSeWalk();
	CSound& GetinPlayerSeDeath();
	//敵SEを取得する
	CSound& GetinEnemySeAttackSp();
	CSound& GetinEnemySeDeath();
	//ゲームBGMの取得
	CSound& GetinSoundBgmGame();
	//タイトルBGMの取得
	CSound& GetinSoundBgmTitle();
	//インスタンスの取得
	static CRes* GetInstance();//staticで処理を作る

private:
	//フォント
	CText mFont;
	//CSoundクラスのインスタンス作成
	//BGM
	CSound Game_Bgm;
	CSound Title_Bgm;
	//プレイヤSE
	CSound Se_Player_AttackSp1;
	CSound Se_Player_AttackSp2;
	CSound Se_Player_AttackSp3;
	CSound Se_Player_Walk;
	CSound Se_Player_Death;
	//敵SE
	CSound Se_Enemy_AttackSp;
	CSound Se_Enemy_Death;
	//プレイヤモデル
	CModelX gPlayer_Model_Knight;
	//プレイヤのガードアクションエフェクト
	CModel gPlayer_GuardSP_Model;
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
	//タイトル画像
	CTexture gTitle_Image;
	//ゲームクリア画像
	CTexture gGameClear_Image;
	//ゲームオーバー画像
	CTexture gGameOver_Image;
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

