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
	////�R���X�g���N�^
	////CEffect(�ʒu,��,����,�e�N�X�`����,�s��,��,1�R�}������̃t���[����)�s��,��,�t���[�����̓f�t�H���g�����Ōďo�����ȗ��\
	//CEffect(const CRectangle pos, float w, float h, char* texture, int row = 1, int col = 1, int fps = 1);
	//�X�V
	void Update();
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

