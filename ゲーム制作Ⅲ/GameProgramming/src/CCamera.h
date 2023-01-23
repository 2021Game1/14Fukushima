#ifndef CCAMERA_H
#define CCAMERA_H
#include "CInput.h"
#include "CVector.h"
#include "CCharacter.h"
#include "CColliderLine.h"
#include "CCollisionManager.h"


/*
�J�����N���X
*/
#define DEF_CAMERA_DIST 8.0f
#define CAMERA_HEAD_ADJUST 2.0f	//�����_�̍�������
class CCamera : public CCharacter{
public:
	CCamera();
	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);
	void SetTarget(const CVector& target);
	void Init();
	//�J�����X�V
	void Update();

	//���������Ȃ�Render
	void Render();
	//�J�����`��
	void Draw();
	//�����蔻��
	void Collision(CCollider* m, CCollider* o);
	//���`���
	float mLerp(float start, float point, float rate);
	//�R���W�����}�l�[�W���ǉ�����
	void TaskCollision();
	//�C���X�^���X�̎擾
	static CCamera* Instance();
	//�x�N�g���擾
	CMatrix GetMat();
	//���_���W�̎擾
	const CVector& Eye() const;
	//���[���h���W���X�N���[�����W�֕ϊ�����
	//WorldToScreen(�X�N���[�����W, ���[���h���W)
	bool WorldToScreen(CVector* screen, const CVector& world);
private:
	CVector mRotation;//��]
	CVector mEye;//���_
	CVector mCenter;//�����_
	CVector mUp;//�����
	int mScreenWidth; //��
	int mScreenHeight; //����
	CMatrix mProjection; //�v���W�F�N�V�����s��
	CMatrix inverse; //���f���r���[�s��̋t�s��


	//�R���C�_
	CColliderLine mColliderLine;
	//�d�����邪�J��������p
	CVector mPos;		//�ʒu
	CVector mTarget;	//�^�[�Q�b�g
	float	mDist;	//����
	float mRotRad;		//��]���������p�x
	float mOldMousePosX, mOldMousePosY;

	bool mSkip;
	CTransform mTransform; //��]�k���p�s��
	

	float	mAngleX;	//�A���O��
	float	mAngleY;	//�A���O��
	//�A���O���x���p�A�ʏ탂�[�h���Ɏg�p
	float mAngleDelayX;
	float mAngleDelayY;
	//�}�E�X�̍��W�ێ��p
	int mOldMouseX, mOldMouseY; //�ȑO�̍��W
	int mMouseX, mMouseY;		//���݂̍��W
		//static�Ń|�C���^�����
	static CCamera* mpCameraInstance;
};

//�J�����̊O���Q��
extern CCamera Camera;
#endif
