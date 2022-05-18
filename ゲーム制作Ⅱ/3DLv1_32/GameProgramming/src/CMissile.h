#ifndef CMISSILE_H
#define CMISSILE_H

//キャラクタクラスのインクルード
#include"CCharacter.h"
//コライダクラスのインクルード
#include"CCollider.h"
//タスクマネージャのインクルード
#include"CTaskManager.h"
//コリジョンマネージャクラスのインクルード
#include"CCollisionManager.h"


/*
*ミサイルクラス
*モデルデータを使った弾を撃つ
*/

class CMissile : public CCharacter{
public:

	//CEnemy(位置,回転,拡縮)
	CMissile(const CVector& position, const CVector& rotation, const CVector& scale);
	//更新
	void Update();
	//弾の生存時間
	int mLife;
	//描画
	//衝突処理
	//Collision(コライダ1,コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void TaskCollision();
	//デフォルトコンストラクタ
	CMissile();

private:
	//モデルデータ
	static CModel cpModel;
	//コライダ
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};
#endif // !



