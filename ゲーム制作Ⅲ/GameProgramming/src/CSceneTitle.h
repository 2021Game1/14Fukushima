#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "CRes.h"

class CSceneTitle : public CScene {
private:
	void Init();
	void Update();
	void Render();
	//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
	EScene GetNextScene();

	CRes mRes;

	bool CSceneTitle::mSceneChange;

	CScene::EScene CSceneTitle::mNextScene;
public:
	CSceneTitle();

};
#endif
