#ifndef CITEM_H
#define CITEM_H


#include "CRectangle.h"

/*
アイテムクラス
CItem　敵のアイテム設定
*/

class CItemA : public CRectangle {
public:
	CItemA();
	int mFx;
	int mFy;
	void Update();
	void Render();
	bool Collision(CRectangle& r);

};

class CItemB : public CRectangle {
public:
	CItemB();
	int mFx;
	int mFy;
	void Update();
	void Render();
	bool Collision(CRectangle& r);

};

class CItemC : public CRectangle {
public:
	CItemC();
	int mFx;
	int mFy;
	void Update();
	void Render();
	bool Collision(CRectangle& r);

};

class CItemD : public CRectangle {
public:
	CItemD();
	int mFx;
	int mFy;
	void Update();
	void Render();
	bool Collision(CRectangle& r);

};

class CItemE : public CRectangle {
public:
	CItemE();
	int mFx;
	int mFy;
	void Update();
	void Render();
	bool Collision(CRectangle& r);
};
#endif 

