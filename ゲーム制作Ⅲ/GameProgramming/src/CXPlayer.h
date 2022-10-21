#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CInput.h"
/*
CXPlayer
*/

class CXPlayer : public CXCharacter {
public:
	void Update();
	void Init(CModelX* model);
	CXPlayer();
	static CXPlayer* mpPlayerInstance;//別のクラスで変数を呼び出す場合,staticでポインタを作る
	static CXPlayer* GetInstance();//staticで処理を作る
	CCollider mColSphereHead;//頭
	CCollider mColSphereSword;//剣
	void Collision(CCollider* m, CCollider* o);

private:
	//コライダの宣言
	CCollider mColSphereBody; //身体
};
#endif 

