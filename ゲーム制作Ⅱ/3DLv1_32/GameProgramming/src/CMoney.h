#ifndef CMONEY_H
#define CMONEY_H
//キャラクタクラスのインクルード
#include"CCharacter.h"
//コライダクラスのインクルード
#include"CCollider.h"
//タスクマネージャのインクルード
#include"CTaskManager.h"
//コリジョンマネージャクラスのインクルード
#include"CCollisionManager.h"
//エフェクトクラスのインクルード
#include "CEffect.h"
//ユーティリティクラスのインクルード
#include"CUtil.h"
//テキストクラスのインクルード
#include"CText.h"


//領域開放をマクロ化
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}

/*
マネークラス
キャラクタクラスを継承
*/
class CMoney : public CCharacter{
public:
	//デフォルトコンストラクタ
	CMoney();

	//CEnemy(位置,回転,拡縮)
	CMoney(const CVector& position, const CVector& rotation, const CVector& scale);
	void Update();
	//衝突処理
	//Collision(コライダ1,コライダ2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
private:
	//モデルデータ
	static CModel mModel;
	//コライダ
	CCollider mCollider;
	CVector mMoneyIndex;
	CMatrix mBackGroundMatrix;


};

#endif 
