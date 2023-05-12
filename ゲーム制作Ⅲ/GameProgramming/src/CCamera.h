#ifndef CCAMERA_H
#define CCAMERA_H
#include "CInput.h"
#include "CVector.h"
#include "CCharacter.h"
#include "CColliderLine.h"
#include "CCollisionManager.h"

//�J�����̕`��͈�
#define WINDOW_WIDTH 800				//�Q�[����ʂ̕`��͈͕��ݒ�
#define WINDOW_FIRST_WIDTH 0			//�Q�[����ʂ̕`�悵�n�߂�͈͕��ݒ�
#define WINDOW_HEIGHT 600				//�Q�[����ʂ̕`��͈͍����ݒ�
#define WINDOW_FIRST_HEIGHT 0				//�Q�[����ʂ̕`�悵�n�߂�͈͍����ݒ�

//�J�����̎��_�`��ݒ�
#define CAMERA_VIEWPORT 4				//���݂̃J�����S�̂̃r���[�|�[�g�����ݒ�
#define CAMERA_VIEWPORT_WIDTH 2			//���݂̃J�����̃r���[�|�[�g�̕��ݒ�
#define CAMERA_VIEWPORT_HEIGHT 3		//���݂̃J�����̃r���[�|�[�g�̍����ݒ�

//�J�����̋����ݒ�
#define CAMERA_DEF_DIST 4.0f	//�J�����̋����ݒ�
//�J�����̋����ݒ�ύX
#define CAMERA_DEF_DIST_CHANGE 8.0 //�J�����̋����ݒ�ύX

//�J�������쎞�̃}�E�X�ݒ�
#define WIN_CENTRAL_X WINDOW_WIDTH/2 //��ʂ̒����iX���j
#define WIN_CENTRAL_Y WINDOW_HEIGHT/2 //��ʂ̒��� �iY���j
#define ROTATION_RATE 1.0f/15.0f	//��]���������p�x�ɑ΂����]���銄��

#define CAMERA_PRIORITY 100
#define CAMERA_SENSITIVITY 0.0002f
#define CAMERA_COLLIDE_DIST 0.05f
#define CAMERA_DELAY_RATE 0.003f
#define CAMERA_POINT_VIEW_X 1.0f
#define CAMERA_POINT_VIEW_Y 6.0f
#define CAMERA_POINT_VIEW_Z 10.0f
#define CAMERA_POINT_HERD_ADJUST 2.0f
#define CAMERA_POINT_INSTALLATION_X 0.0f
#define CAMERA_POINT_INSTALLATION_Y 1.0f
#define CAMERA_POINT_INSTALLATION_Z 0.0f
#define CAMERA_SCREEN_POS_X 1.0f
#define CAMERA_SCREEN_POS_Y 1.0f
#define CAMERA_SCREEN_WIDTH 0.5f
#define CAMERA_SCREEN_HEIGHT 0.5f

/*
�J�����N���X
*/
class CCamera : public CCharacter{
public:
	CCamera();
	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector& eye, const CVector& center,
		const CVector& up);	
	//�J�����̃A���O���ύX�ݒ�
	void CameraAngleChange();
	//�J�����̃A���O���f�t�H���g�ݒ�
	void CameraAngleDefault();
	//�J�����̃^�[�Q�b�g�ݒ�
	void SetTarget(const CVector& target);
	//��x�����X�V���Ȃ�
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
	//HP�̐��`���
	float mHpLerp(float start, float point, float rate);
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
	//�`��D��x
	int mCamera_Priority;
	//�J�����̊��x�ݒ�
	float mCamera_Sensitivity;
	//�����蔻��̋���
	float mCamera_Collide_Dist;
	//�J�����̒x���ݒ�
	float mCamera_Delay_Rate;
	//�J�����̕`��ʒuX���W
	float mCamera_Point_View_X;
	//�J�����̕`��ʒuY���W
	float mCamera_Point_View_Y;
	//�J�����̕`��ʒuZ���W
	float mCamera_Point_View_Z;
	//�J�����̍�������
	float mCamera_Point_Herd_Adjust;
	//�J�����̏����X���W�ݒ�
	float mCamera_Point_Installation_X;
	//�J�����̏����Y���W�ݒ�
	float mCamera_Point_Installation_Y;
	//�J�����̏����Z���W�ݒ�
	float mCamera_Point_Installation_Z;
	//�J�����̃X�N���[��X���W�ݒ�
	float mCamera_Screen_Pos_X;
	//�J�����̃X�N���[��Y���W�ݒ�
	float mCamera_Screen_Pos_Y;
	//�J�����̃X�N���[�����ݒ�
	float mCamera_Screen_Width;
	//�J�����̃X�N���[�������ݒ�
	float mCamera_Screen_Height;


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
	CVector mZoom;		//�Y�[���p
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
