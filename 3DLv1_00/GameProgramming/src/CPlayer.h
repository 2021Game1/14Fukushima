#ifndef CPLAYER_H
#define CPLAYER_H
//キャラクタークラスのインクルード
#include"CCharacter.h"
//弾クラスのインクルード
#include"CBullet.h"


/*
プレイヤークラス
キャラクタークラスを継承
*/

class CPlayer : public CCharacter {
public:
	//CBulletクラスのインスタンス変数
	CBullet bullet;
	//更新処理
	void Update();


};
#endif 

