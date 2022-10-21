#ifndef CCAMERA_H
#define CCAMERA_H
#include "CInput.h"
#include "CVector.h"
#include "CCollider.h"
#include "CColliderLine.h"
#include "CCharacter.h"

/*
�J�����N���X
*/
#define DEF_CAMERA_DIST 8.0f
#define CAMERA_HEAD_ADJUST 3.0f	//�����_�̍�������
class CCamera : CCharacter{
public:
	//��]
	CVector mRotation;
	//���_���W�̎擾
	const CVector& Eye() const;
	CCamera();
	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);
	//�J�����X�V
	void Update();
	//�J����������
	void Init();
	//�J�����K�p
	void Render();
	//�x�N�g���擾
	CMatrix GetMat();
	//�����蔻��
	void Collision(CCollider* m, CCollider* o);
	//static�Ń|�C���^�����
	static CCamera* mpCameraInstance;
	//���_
	CVector mEye;
	//�����
	CVector mUp;
	//�R���C�_
	CColliderLine mColliderLine;
	//�d�����邪�J��������p
	CVector mCenter;	//�����_
	//�d�����邪�J��������p
	CVector mPos;		//�ʒu
	CVector mTarget;	//�^�[�Q�b�g
	float	mAngleX;	//�A���O��
	float	mAngleY;	//�A���O��
	float	mDist;	//����

private:
	//�A���O���x���p�A�ʏ탂�[�h���Ɏg�p
	float mAngleDelayX;
	float mAngleDelayY;
};

//�J�����̊O���Q��
extern CCamera Camera;
#endif
