#ifndef CEFFECT_H
#define CEFFECT_H

//���N�^���O���N���X
#include"CRectangle.h"
/*
* �G�t�F�N�g�N���X
* �e�N�X�`���̃A�j���[�V����
*/
class CEffect : public CRectangle{
public:

	//�f�t�H���g�R���X�g���N�^
	CEffect();
	//�`��
	void Render();
private:
	//�s��
	int mRows;
	//��
	int mCols;
	//1�R�}�̃t���[����
	int mFps;
	//�t���[���J�E���^
	int mFrame;

};

#endif //�I��

