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
CTexture Texture; //全体の画像
CTexture BulletTexture; //弾の画像
CTexture ItemTexture;//アイテムの画像
CTexture MoonBlock;//ムーンブロック
CTexture Effect;//エフェクト
//シーンマネージャのインスタンス
CSceneManager SceneManager;

//Init関数
//最初に一度だけ呼ばれる関数
void Init() {
	//
	Texture.Load("res\\GameImage.tga");
	BulletTexture.Load("res\\BulletImage.tga");
	ItemTexture.Load("res\\Image.tga");
	MoonBlock.Load("res\\moonBLock.tga");
	Effect.Load("res\\exp.tga");
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