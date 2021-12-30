#ifndef CBLOCK_H
#define CBLOCK_H

//�l�p�`�̃N���X�̃C���N���[�h
#include "CRectangle.h"
//�v���C���[�N���X�̃C���N���[�h
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

