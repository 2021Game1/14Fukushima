#ifndef CBLOCK_H
#define CBLOCK_H

//�l�p�`�̃N���X�̃C���N���[�h
#include "CRectangle.h"
//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"

#include"CMapModel.h"

extern CTexture MoonBlock;


class CBlock : public CRectangle{
public:

	int mFx, mFy;
	void Update();
	void Render();
	CBlock();
	bool Collision(CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);

};



class CComet : public CRectangle {
public:

	int mFx, mFy;
	
	void Update();
	void Render();
	CComet();
	bool Collision(CRectangle& r);
	void Collision(CRectangle* i, CRectangle* y);

	static int speed;

};
#endif 

