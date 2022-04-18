#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタークラスのインクルード
#include"CCharacter.h"
//弾クラスのインクルード
#include"CBullet.h"
//コリジョンマネージャクラスのインクルード
#include"CCollisionManager.h"
//線分コライダクラスのインクルード
#include"CColliderLine.h"
//テキストクラスのインクルード
#include"CText.h"
//ユーティリティクラスのインクルード
#include"CUtil.h"

/*
プレイヤークラス
キャラクタークラスを継承
*/

class CPlayer : public CCharacter {
public:
	CText mText;
	//CBulletクラスのインスタンス変数
	/*CBullet bullet;*/
	CPlayer();
	//更新処理
	void Update();
	//描画処理
	void Render();
	//衝突処理
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void TaskCollision();
	static CPlayer* Get();
	
private:
	//プレイヤーのインスタンス
	static CPlayer* spInstance;
	CColliderLine mLine;	//線分コライダ
	CColliderLine mLine2;	//線分コライダ2
	CColliderLine mLine3;	//線分コライダ3
	CCollider mCollider;	//本体用コライダ
};
#endif 

