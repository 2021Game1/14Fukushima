#ifndef CGAMEUI_H
#define CGAMEUI_H

#include "CRectangle.h"
#include "CPlayer.h"

class CScoreUi0 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi0();
	void Render();
};

class CScoreUi1 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi1();
	void Render();
};

class CScoreUi2 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi2();
	void Render();
};

class CScoreUi3 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi3();
	void Render();
};

class CScoreUi4 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi4();
	void Render();
};

class CScoreUi5 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi5();
	void Render();
};

class CScoreUi6 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi6();
	void Render();
};

class CScoreUi7 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi7();
	void Render();
};

class CScoreUi8 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi8();
	void Render();
};

class CScoreUi9 : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi9();
	void Render();
};

class CHpUi : public CPlayer {

public:
	CHpUi();
	void Update();
	void Render();

private:
	int mHpUi,mHpCnt;
	//int mHpX[5];
	
};

#endif
