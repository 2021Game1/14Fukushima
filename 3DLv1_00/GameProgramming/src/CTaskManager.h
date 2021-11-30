#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//タスククラスのインクルード
#include"CTask.h"

/*
* タスクマネージャ
* タスクリストの管理
*/
class CTaskManager{
public:
	//デフォルトコンストラクタ
	CTaskManager();
	//デストラクタ
	virtual ~CTaskManager();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask* addTask);
	//更新
	void Update();
	//描画
	void Render();
protected:
	CTask mHead;//先頭タスク
	CTask mTail;//最終タスク
	
};

//タスクマネージャyの外部参照
extern CTaskManager TaskManager;

#endif

