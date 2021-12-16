#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//トランスフォームクラスのインクルード
#include"CTransform.h"
//タスククラスのインクルード
#include"CTask.h"
//コリジョンマネージャクラスの宣言
class CCollisionManager;
/*
コライダクラス
衝突判定クラス
*/
class CCollider : public CTransform,public CTask {
public:
	//friend コリジョンマネージャクラス
	friend CCollisionManager;
	//コンストラクタ
	//CCollider(親,親行列,位置,半径)
	CCollider(CCharacter* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//デストラクタ
	~CCollider();
	//親ポインタの取得
	CCharacter* Parent();
	//描画
	void Render();
	//衝突判定
	//Collision(コライダ1,コライダ2)
	//retrun:true(衝突している)false(衝突していない)
	static bool Collision(CCollider* m, CCollider* o);

protected:
	CCharacter* mpParent;//親
	CMatrix* mpMatrix;//親行列
	float mRadius;//半径

};
#endif 

