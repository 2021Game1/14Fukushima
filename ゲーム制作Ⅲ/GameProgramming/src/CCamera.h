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
#define DEF_CAMERA_HEAD_ADJUST 3.0f
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
	//�J�����K�p
	void Render();
	//�����蔻��
	void Collision(CCollider* m, CCollider* o);
	//static�Ń|�C���^�����
	static CCamera* mpCameraInstance;
	//���_
	CVector mEye;
private:

	//�����
	CVector mUp;
	//�R���C�_
	CColliderLine mColliderLine;
	//�d�����邪�J��������p
	CVector mCenter;	//�����_
};

//�J�����̊O���Q��
extern CCamera Camera;
#endif
