#ifndef CBLOCK_H
#define CBLOCK_H

//�l�p�`�̃N���X�̃C���N���[�h
#include "CRectangle.h"
//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
extern CTexture Block;


class CBlock : public CRectangle {
public:
	//�`��
	void Render() {
		if (mEnabled) {
			CRectangle::Render(Block, 0, 72, 74, 0);
		}
	}
};

#endif 

