#ifndef CCOLLISIONMANAGER
#define CCOLLISIONMANAGER

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
private:
	//マネージャのインスタンス
	static CCollisionManager* mpInstance;

};
#endif

