#ifndef CBULLET_H
#define CBULLET_H
//キャラクタクラスのインクルード
#include"CCharacter.h"
//三角形クラスのインクルード
#include"CTriangle.h"

/*
* 弾クラス
* 三角形を飛ばす
*/

class CBullet : public CCharacter{
public:
	//幅と奥行き
	//Set(幅,奥行)
	void Set(float w, float d);
	//更新
	void Update();
	//描画
	void Render();
	//弾の生存時間
	int mLife;
	//デフォルトコンストラクタ
	CBullet();
private:
	//三角形
	CTriangle mT;
};
#endif 

