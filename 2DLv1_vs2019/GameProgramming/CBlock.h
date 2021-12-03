#ifndef CBLOCK_H
#define CBLOCK_H

//四角形のクラスのインクルード
#include "CRectangle.h"
//プレイヤークラスのインクルード
#include"CPlayer.h"
extern CTexture Block;


class CBlock : public CRectangle {
public:
	//描画
	void Render() {
		if (mEnabled) {
			CRectangle::Render(Block, 0, 72, 74, 0);
		}
	}
};

#endif 

