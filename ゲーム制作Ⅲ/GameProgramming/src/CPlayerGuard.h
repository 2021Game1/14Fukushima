#ifndef CPLAYERGUARD_H
#define CPLAYERGUARD_H

#include"CCharacter.h"
#include"CXPlayer.h"


class CPlayerGuard : public CCharacter
{
public:
	void Init(CModel* model);
	void Update();
	//描画
	void Render();
	//プレイヤのインスタンス取得関数
	static CPlayerGuard* GetInstance();		//staticで処理を作る
private:
	//プレイヤガードのポインタ
	static CPlayerGuard* mpPlayerGuard_Instance;	//別のクラスでプレイヤガードの変数を呼び出す場合,staticでポインタを作る
};
#endif //CPLAYERGUARD_H
