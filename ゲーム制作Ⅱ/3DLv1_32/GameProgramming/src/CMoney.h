#ifndef CMONEY_H
#define CMONEY_H
//キャラクタクラスのインクルード
#include"CCharacter.h"
//コライダクラスのインクルード
#include"CCollider.h"
//タスクマネージャのインクルード
#include"CTaskManager.h"
//コリジョンマネージャクラスのインクルード
#include"CCollisionManager.h"
//エフェクトクラスのインクルード
#include "CEffect.h"

/*
マネークラス
キャラクタクラスを継承
*/

class CMoney : public CCharacter{
public:
	//コンストラクタ
	CMoney();
	//CEnemy(位置,回転,拡縮)
	CMoney(const CVector& position, const CVector& rotation, const CVector& scale);
	void Update();
	//衝突処理
	//Collision(コライダ1,コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
private:
	//モデルデータ
	static CModel mModel;
	//コライダ
	CCollider mCollider;
};

#endif 
