#ifndef CCOLLISIONMANAGER
#define CCOLLISIONMANAGER

#define COLLISIONRANGE 30
//タスクマネージャのクラスのインクルード
#include "CTaskManager.h"
/*
コリジョンマネージャクラス
親:CTaskManagerクラス　子:CCollisionManagerクラス
*/
class CCollisionManager : public CTaskManager
{
public:

	//インスタンスの取得
	static CCollisionManager* Get();
	//衝突処理
	void Collision();
	//衝突判定
	void Collision(CCollider *c,int range);

private:
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;

};
#endif

