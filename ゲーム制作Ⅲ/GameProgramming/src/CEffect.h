#ifndef CEFFECT_H
#define CEFFECT_H
//�r���{�[�h�N���X�̃C���N���[�h
#include "CBillBoard.h"
/*
�G�t�F�N�g�N���X
�e�N�X�`���̃A�j���[�V����
*/
class CEffect : public CBillBoard {
public:
	//�R���X�g���N�^
	//CEffect(�ʒu, ��, ����, �e�N�X�`����, �s��, ��, 1�R�}������̃t���[����)�@�s���A�񐔁A�t���[�����̓f�t�H���g�����Ōďo�����ȗ��\
	CEffect(const CVector &pos, float w, float h, char *texture, int row = 1, int col = 1, int fps = 1);
	//�X�V
	void Update();
	//�`��
	void Render();
	CMaterial GetIsMaterial();
	//���̃N���X�ŎQ�Ɨp�̊֐�
	static CEffect* GetInstance();				//static�ŏ��������
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
	static CEffect* mpEffect_Instance;//�ʂ̃N���X�ŃG�t�F�N�g�̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
};
#endif

