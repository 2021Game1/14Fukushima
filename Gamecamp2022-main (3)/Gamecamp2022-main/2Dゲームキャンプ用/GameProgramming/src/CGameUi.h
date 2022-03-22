#ifndef CGAMEUI_H
#define CGAMEUI_H

#include "CRectangle.h"
#include "CPlayer.h"

class CScoreUi : public CRectangle {
	CPlayer mScore;
public:
	CScoreUi();
	void Update();
	void Render();
private:
	int mScoreUi,mScoreCnt; 
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
