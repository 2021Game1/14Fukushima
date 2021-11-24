//プレイヤークラスのインクルード
#include"CPlayer.h"
//キー入力クラスのインクルード
#include"CKey.h"

#define ROTATION_YV CVector(0.0f,1.0f,0.0f)//回転速度
#define ROTATION_XV CVector(1.0f,0.0f,0.0f)//回転速度
#define VELOCITY CVector(0.0f,0.0f,0.1f)//移動速度

//更新処理
void CPlayer::Update() {
	//Dキー入力で回転
	if (CKey::Push('D')) {
		//Y軸の回転値を減少
		mRotation = mRotation - ROTATION_YV;
	}
	//Aキー入力で回転
	if (CKey::Push('A')) {
		//Y軸の回転値を増加
		mRotation = mRotation + ROTATION_YV;
	}
	//Iキー入力で前進
	if (CKey::Push('I')){
		//Z軸方向の値を回転させ移動させる
		mPosition = mPosition + VELOCITY * mMatrixRotate;
	}
	//Sキー入力で上向き
	if (CKey::Push('S'))
	{
		//X軸の回転値を減算
		mRotation = mRotation - ROTATION_XV;
	}
	//Wキー入力で上向き
	if (CKey::Push('W'))
	{
		//X軸の回転値を加算
		mRotation = mRotation + ROTATION_XV;
	}
	//変換行列の更新
	CTransform::Update();
}