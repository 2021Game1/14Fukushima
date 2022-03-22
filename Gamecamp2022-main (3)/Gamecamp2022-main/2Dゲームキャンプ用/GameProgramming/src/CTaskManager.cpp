#include "CTaskManager.h"
//タスクマネージャの外部変数
CTaskManager TaskManager;
//タスクマネージャのインスタンス
CTaskManager* CTaskManager::mpInstance = nullptr;

//インスタンスの取得
CTaskManager* CTaskManager::Get()
{
	//インスタンスが無ければ
	if (mpInstance == nullptr)
	{
		//インスタンスを生成する
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}
//デフォルトコンストラクタ
CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}
CTaskManager::~CTaskManager(){}
//リストに追加
//Add(タスクのポインタ)
void CTaskManager::Add(CTask * addTask) 
{
	//mHeadの次から検索
	CTask* task = mHead.mpNext;
	
	//優先度の大きい順に挿入する
	//挿入位置の検索(優先度が同じか大きくなった前)
	//mPrirority>=0のこと
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext; //次へ
	}
	//追加ポインタ(addTask)の次をタスクのポインタ(task)を代入
	addTask->mpNext = task;
	//追加ポインタ(addTask)の前をタスクのポインタ(Task)の前に
	addTask->mpPrev = task->mpPrev;
	//追加ポインタ(addTask)の前を次の追加ポインタ(addTask)に代入
	addTask->mpPrev->mpNext = addTask;
	//タスクのポインタ(task)の前を追加ポインタ(addTask)に
	task->mpPrev = addTask;
}
//更新処理
void CTaskManager::Update()
{
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		//更新処理を呼ぶ
		task->Update();
		//次へ
		task = task->mpNext;
	}
}
//衝突処理
void CTaskManager::Collision() {
	//現在位置を先頭にする
	CRectangle* task = (CRectangle*)mHead.mpNext;
	//最後まできたら終了する
	while (task->mpNext) {
		//現在位置の次を求める
		CRectangle* next = (CRectangle*)task->mpNext;
		//次が０になったら終了
		while (next->mpNext) {
			//親の衝突判定を呼び出す
			//自分の衝突処理
		task->Collision(task, next);
			//相手の衝突処理
		next->Collision(next, task);
			//次を求める
			next = (CRectangle*)next->mpNext;

		}
		//現在位置を次にする
		task = (CRectangle*)task->mpNext;
	}

}
//リストから削除
//Remove(タスクのポインタ)
void CTaskManager::Remove(CTask* task) {
	//タスクの前の次を、タスクの次にする
	task->mpPrev->mpNext = task->mpNext;
	//タスクの次の前を、タスクの前にする
	task->mpNext->mpPrev = task->mpPrev;
}
//描画
void CTaskManager::Render() {
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext) {
		//更新処理を呼ぶ
		task->Render();
		//次へ
		task = task->mpNext;
	}
}
//タスクの削除
void CTaskManager::Delete() {
	//先頭から最後まで繰り返し
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		CTask* del = task;
		//次へ
		task = task->mpNext;
		//mEnabledがfalseなら削除
		if (del->mEnabled == false)
		{
			delete del;
		}
	}
}