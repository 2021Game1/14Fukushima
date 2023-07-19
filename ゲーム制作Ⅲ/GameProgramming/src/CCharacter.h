#ifndef CCHARACTER_H
#define CCHARACTER_H
//変換行列クラスのインクルード
#include "CTransform.h"
//モデルクラスのインクルード
#include "CModel.h"
//
#include "CTask.h"
//コライダクラスの宣言
class CCollider;

/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/
class CCharacter : public CTransform ,public CTask {
public:
	enum class ETag
	{
		EZERO,		//初期値
		EPLAYER,	//プレイヤー
		EENEMY,		//敵
		EMAP,		//マップ
		ESTONE		//障害物(石)
	};
	//モデルの設定
	//Model(モデルクラスのポインタ)
	void Model(CModel *m);
	//モデルの設定
	//タグの取得
	ETag Tag();
	//描画処理
	void Render();
	//デストラクタ
	~CCharacter();
	//コンストラクタ
	CCharacter();
	//衝突処理
	virtual void Collision(CCollider *m, CCollider *o) {}
protected:
	CModel* mpModel; //モデルのポインタ
	ETag mTag;
};

#endif
