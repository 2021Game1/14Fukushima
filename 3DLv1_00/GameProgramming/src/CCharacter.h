#ifndef CCHARACTER_H
#define CCHARACTER_H

//変換行列クラスのインクルード
#include"CTransform.h"
//モデルクラスのインクルード
#include"CModel.h"

/*
キャラクタークラス
ゲームキャラクタの基本的な機能を定義する
*/

class CCharacter : public CTransform{
protected:
	CModel* mpModel; //モデルのポインタ
public:
	//モデルの設定
	//Model(モデルクラスのポインタ)
	void Model(CModel* m);
	//描画処理
	void Render();

};
#endif 


