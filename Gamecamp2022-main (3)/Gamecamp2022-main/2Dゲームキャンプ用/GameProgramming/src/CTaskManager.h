#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
//タスククラスのインクルード
#include"CTask.h"
#include"CRectangle.h"
/*
タスクマネージャ
タスクリストの管理
*/
class CRectangle;
class CTaskManager{
friend CRectangle;
public:
	//インスタンスの取得
	static CTaskManager* Get();
	//デストラクタ
	virtual ~CTaskManager();
	//衝突処理
	void Collision();
	//リストに追加
	//Add(タスクのポインタ)
	void Add(CTask* addTask);
	//リストから削除
	//Remove(タスクのポインタ)
	void Remove(CTask* task);
	//タスクの削除
	void Delete();
	//更新
	void Update();
	//描画
	void Render();
	//デフォルトコンストラクタ
	CTaskManager();
private:
	CTask mHead; //先頭タスク
	CTask mTail; //最終タスク
	//タスクマネージャのインスタンス
	static CTaskManager* mpInstance;
};


#endif //終了

