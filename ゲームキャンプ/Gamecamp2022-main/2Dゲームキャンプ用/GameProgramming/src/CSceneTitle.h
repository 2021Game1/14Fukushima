#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "CText.h"

class CSceneTitle : public CScene {
public:
	

	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	void Render();
	void Draw(float left, float right, float bottom, float top, float tleft, float tright, float tbottom, float ttop) const;
	

	//次のシーンの取得
	EScene GetNextScene();
};

#endif
