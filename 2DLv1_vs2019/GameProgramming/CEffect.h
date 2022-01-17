#ifndef CEFFECT_H
#define CEFFECT_H
//�}�e���A���N���X
#include"CMaterial.h"
//�x�N�g���N���X
#include"CVector.h"
/*
* �G�t�F�N�g�N���X
* �e�N�X�`���̃A�j���[�V����
*/
class CEffect{
public:
	//�R���X�g���N�^
	//CEffect(�ʒu,��,����,�e�N�X�`����,�s��,��,1�R�}������̃t���[����)�s��,��,�t���[�����̓f�t�H���g�����Ōďo�����ȗ��\
	CEffect(const CVector pos, float w, float h, char* texture, int row = 1, int col = 1, int fps = 1);
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
	//�}�e���A��
	static CMaterial sMaterial;
};

#endif //�I��

