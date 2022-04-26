#ifndef CBACKGROUND_H
#define CBACKGROUND_H

#include "CRectangle.h"
#include"CTexture.h"

class CBackground : public CRectangle{
public:


	CBackground();
	int speed;

private:
	void Render();
};

class CBackground2 : public CRectangle{
public:

	
	CBackground2();
	int speed;

	static CBackground2* spInstance;

private:
	void Render();
	void Update();
};

class CBackground3 : public CRectangle{
public:


	CBackground3();
	int speed;

	static CBackground3* spInstance;

private:
	void Render();
	void Update();
};
class CBackground4 : public CRectangle {
public:


	CBackground4();
	int speed;

	static CBackground4* spInstance;

private:
	void Render();
	void Update();
};

#endif //èIóπ


