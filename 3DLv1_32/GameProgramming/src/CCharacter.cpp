#include"CCharacter.h"
//タスクマネージャクラスのインクルード
#include"CTaskManager.h"

CCharacter::CCharacter() 
:mTag(EZERO)
{
	//タスクリストに追加
	CTaskManager::Get()->Add(this);
}

void CCharacter::Model(CModel* m)
{
	mpModel = m;
}

//描画処理
void CCharacter::Render()
{
	mpModel->Render(mMatrix);
}

CCharacter::ETag CCharacter::Tag()
{
	return mTag;
}

CCharacter::~CCharacter() {
	//タスクリストから削除
	CTaskManager::Get()->Remove(this);
}

