#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//トランスフォームクラスのインクルード
#include"CTransform.h"
/*
コライダクラス
衝突判定クラス
*/
class CCollider : public CTransform {
public:
	//コンストラクタ
	//CCollider(親,親行列,位置,半径)
	CCollider(CCharacter* parent, CMatrix* matrix,
		const CVector& position, float radius);
	//親ポインタの取得
	CCharacter* Parent();
	//描画
	void Render();

protected:
	CCharacter* mpParent;//親
	CMatrix* mpMatrix;//親行列
	float mRadius;//半径

};
#endif 

