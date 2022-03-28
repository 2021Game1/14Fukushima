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
	int m_BackgroundDrawCount;
};

class CBackground2 : public CRectangle{
public:

	
	CBackground2();
	int speed;

	static CBackground2* spInstance;

private:
	void Render();
	void Update();
	int m_BackgroundDrawCount;
};

class CBackground3 : public CRectangle{
public:


	CBackground3();
	int speed;

	static CBackground3* spInstance;

private:
	void Render();
	void Update();
	int m_BackgroundDrawCount;
};

#endif //èIóπ


