#include "CCollisionManager.h"
//マネージャのインスタンス
CCollisionManager* CCollisionManager::mpInstance = 0;
//インスタンスの取得
CCollisionManager* CCollisionManager::Get()
{
	if (mpInstance == 0)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}