#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include"CModelX.h"
#include"CMatrix.h"
#include"CCharacter.h"


class CXCharacter : public CCharacter {
public:
	//�f�t�H���g�R���X�g���N�^
	CXCharacter();
	//������
	void Init(CModelX* model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update();
	//�}�g���b�N�X�̍X�V����
	void Update(CMatrix &m);
	//�`�揈��
	void Render();
	//�A�j���[�V�����̍Đ��I������
	//true:�I�� false:�Đ���
	bool IsAnimationFinished();
	int AnimationIndex();

	virtual ~CXCharacter() {
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}
protected:
	CModelX* mpModel;			//���f���f�[�^
	CMatrix* mpCombinedMatrix;	//�����s��ޔ�
	int mAnimationIndex;		//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;		//true:�A�j���[�V�������J��Ԃ�
	float mAnimationFrame;		//�A�j���[�V�����̍Đ��t���[��
	float mAnimationFramesize;	//�A�j���[�V�����̍Đ��t���[����
};
#endif //�I��

