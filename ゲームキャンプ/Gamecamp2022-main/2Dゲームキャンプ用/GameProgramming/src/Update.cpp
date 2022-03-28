#include "glut.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include "CSceneManager.h"

// テクスチャクラスのインクルード
#include "CTexture.h"
CTexture Texture; //マップの画像
CTexture mpBackground1;
CTexture mpBackground2;
CTexture mpBackground3;
CTexture mpBackground4;
CTexture mpBackground5;
CTexture mpBackground6;
CTexture mpBackground7;
CTexture mpBackground8;
CTexture PlayerTexture0; //プレイヤー立ち絵
CTexture PlayerTexture1; //プレイヤー移動
CTexture PlayerTexture2; //プレイヤージャンプ
CTexture PlayerTexture3; //プレイヤー攻撃
CTexture PlayerTexture4; //プレイヤー被弾
CTexture PlayerAttack; //プレイヤー魔法
CTexture EnemyMoveTexture1;//スライムの移動画像
CTexture EnemyAttackTexture1; //スライムの攻撃モーション画像
CTexture EnemyAttackBulTex1; //スライムの弾画像
CTexture EnemyMoveTexture2;//スケルトンの移動画像
CTexture EnemyAttackTexture2; //スケルトンの攻撃モーション画像
CTexture EnemyAttackBulTex2; //スケルトンの攻撃画像
CTexture EnemyMoveTexture3; //ゾンビの移動画像
CTexture EnemyAttackTexture3; //ゾンビの攻撃モーション画像
CTexture EnemyAttackBulTex3; //ゾンビの攻撃画像
CTexture GameUI1; //ゲームUI数字
CTexture GameUI2; //ゲームUIHP
CTexture Title;//ゲームタイトル
//シーンマネージャのインスタンス
CSceneManager SceneManager;

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {
	//テクスチャ画像の読み込み
	Texture.Load("res\\Image.tga");
	mpBackground1.Load("res\\ゲーム背景昼１後ろ.png");
	mpBackground2.Load("res\\お昼真ん中２.png");
	mpBackground3.Load("res\\ゲーム背景夜１.png");
	mpBackground4.Load("res\\夜墓背景.png");
	mpBackground5.Load("res\\ゲーム背景.png");
	mpBackground6.Load("res\\夜墓真ん中.png");
	mpBackground7.Load("res\\お昼後ろ.png");
	mpBackground8.Load("res\\夜ステージ１.png");
	EnemyMoveTexture1.Load("res\\スライム移動.png");
	EnemyAttackTexture1.Load("res\\スライム攻撃.png");
	EnemyAttackBulTex1.Load("res\\スライム遠距離攻撃.png");
	EnemyMoveTexture2.Load("res\\スケルトン移動.png");
	EnemyAttackTexture2.Load("res\\スケルトン攻撃.png");
	EnemyAttackBulTex2.Load("res\\スケルトン遠距離攻撃.png");
	EnemyMoveTexture3.Load("res\\ゾンビ移動.png");
	EnemyAttackTexture3.Load("res\\ゾンビ攻撃.png");
	EnemyAttackBulTex3.Load("res\\ゾンビ遠距離攻撃.png");
	PlayerTexture0.Load("res\\tatie.png"); //0 立ち絵
	PlayerTexture1.Load("res\\プレイヤー移動.png"); //1 走る
	PlayerTexture2.Load("res\\ジャンプモーション.png");  //2 ジャンプ
	PlayerTexture3.Load("res\\攻撃モーション.png");  //3 攻撃
	PlayerTexture4.Load("res\\受身モーション.png");  //4 被弾
	PlayerAttack.Load("res\\雷魔法.png");  //プレイヤー 弾
	GameUI1.Load("res\\スコア.png"); //数字
	GameUI2.Load("res\\HP.png"); //HP
	Title.Load("res\\taitoru.png");//タイトル
	//文字画像の読み込み
	CText::mFont.Load("res\\font.tga");
	//シーンマネージャの初期化
	SceneManager.Init();
}
//Update関数
//プログラムの実行中、繰り返し呼ばれる関数
void Update() {
	//シーンマネージャの更新
	SceneManager.Update();
}
