#ifndef CEFFECT_H
#define CEFFECT_H

//���N�^���O���N���X
#include"CRectangle.h"
/*
* �G�t�F�N�g�N���X
* �e�N�X�`���̃A�j���[�V����
*/
class CEffect : public CRectangle
{
	int mTime;
	static CTexture mTexture;

public:
	static void LoadTexture(char* filename);
	CEffect(int x, int y, int w, int h);
	//�f�t�H���g�R���X�g���N�^
	CEffect();
	//�X�V
	void Update();
	//�`��
	void Render();
	int time = 0.3 * 60;

};

#endif //�I��

