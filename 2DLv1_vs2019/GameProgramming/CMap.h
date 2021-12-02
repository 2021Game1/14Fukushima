#ifndef CMAP_H
#define CMAP_H

#include "CRectangle.h"
#include"CTexture.h"
#include"CSceneTitle.h"

extern CTexture Block;

class CMap : public CRectangle {
public:
	CTexture mBlock;
	CMap();
	void Render();
	CScene::EScene mScene;

};

#endif
