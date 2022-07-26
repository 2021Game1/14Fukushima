#ifndef CENEMY_H
#define CENEMY_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"
//タスクマネージャのインクルード
#include"CTaskManager.h"
//コリジョンマネージャクラスのインクルード
#include"CCollisionManager.h"
//プレイヤークラスのインクルード
#include "CPlayer.h"



/*
エネミークラス
キャラクタクラスのインクルード
*/
class CEnemy : public CCharacter{
public:
	//コンストラクタ
	//CEnemy(モデル,位置,回転,拡縮)
	CEnemy(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	//更新処理
	void Update();
	//衝突処理
	//Collision(コライダ1,コライダ2)
	void Collision(CCollider* m, CCollider* o);
	//衝突処理
	void TaskCollision();

private:
	int mFireCount;

};
#endif // !CENEMY_H

