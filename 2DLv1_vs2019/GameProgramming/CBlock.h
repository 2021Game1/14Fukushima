#ifndef CBLOCK_H
#define CBLOCK_H

//四角形のクラスのインクルード
#include "CRectangle.h"
//プレイヤークラスのインクルード
#include"CPlayer.h"

#include"CMapModel.h"

extern CTexture Block;


class CBlock : public CRectangle{
public:

	int mFx, mFy;
	void Update();
	void Render();
	CBlock();
	bool Collision(CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);
	
};

#endif 

