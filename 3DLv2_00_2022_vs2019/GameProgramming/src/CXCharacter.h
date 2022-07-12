#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include"CModelX.h"
#include"CMatrix.h"

class CXCharacter {
public:
	//������
	void Init(CModelX* model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix &m);
	//�`�揈��
	void Render();
	//�A�j���[�V�����̍Đ��I������
	//true:�I�� false:�Đ���
	bool IsAnimationFinished();
	int AnimationIndex();

protected:
	CModelX* mpModel;			//���f���f�[�^
	int mAnimationIndex;		//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;		//true:�A�j���[�V�������J��Ԃ�
	float mAnimationFrame;		//�A�j���[�V�����̍Đ��t���[��
	float mAnimationFramesize;	//�A�j���[�V�����̍Đ��t���[����
};
#endif //�I��

