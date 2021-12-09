#ifndef CENEMY_H
#define CENEMY_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//コライダクラスのインクルード
#include "CCollider.h"
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
	//確認メソッド　削除予定
	void CEnemy::Render() {
		CCharacter::Render();
		mCollider1.Render();
		mCollider2.Render();
		mCollider3.Render();
	}

private:
	//コライダ
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};
#endif // !CENEMY_H

