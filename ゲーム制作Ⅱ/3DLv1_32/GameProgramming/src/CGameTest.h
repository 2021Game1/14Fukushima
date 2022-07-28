#ifndef CGAMETEST
#define CGAMETEST

#include "CGameTest.h"
#include "CModel.h"
//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
//�x�N�g���N���X�̃C���N���[�h
#include"CVector.h"
//�O�p�`�N���X�̃C���N���[�h
#include"CTriangle.h"
//�^�X�N�}�l�[�W���N���X�̃C���N���[�h
#include"CTaskManager.h"
//�G�̃N���X�̃C���N���[�h
#include"CEnemy.h"
//�G2�̃N���X�̃C���N���[�h
#include"CEnemy2.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include"CCollisionManager.h"
//�r���{�[�h�N���X�̃C���N���[�h
#include"CBillBoard.h"
//�J�����N���X�̃C���N���[�h
#include"CCamera.h"
//�O�p�R���C�_�N���X�̃C���N���[�h
#include"CColliderTriangle.h"
//�L�[�N���X�̃C���N���[�h
#include"CKey.h"
//�}�g���b�N�X�N���X�̃C���N���[�h
#include"CMatrix.h"
//�g�����X�t�H�[���N���X�̃C���N���[�h
#include"CTransform.h"
//�L�����N�^�N���X�̃C���N���[�h
#include"CCharacter.h"
//�O�p�R���C�_�̐����N���X�̃C���N���[�h
#include"CColliderMesh.h"
//CSound�N���X�̃C���N���[�h
#include "CSound.h"

#include"CMoney.h"

#include<time.h>
#include<stdlib.h>
#include<stdio.h>

//���f���f�[�^�̎w��
#define MODEL_OBJ "res\\model.obj","res\\model.mtl"
#define MODEL_MAP "res\\city.obj","res\\city.mtl"
#define MODEL_COLISION "res\\colision.obj","res\\colision.mtl"
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"



class CGameTest {
	//���f���N���X�̃C���X�^���X�쐬
	CModel mModel; //�v���C���[���f��
	CModel mBackGround; //�w�i���f��
	CModel mModelC5; //�G���f��
	CModel mMap; //�}�b�v���f��
	CModel mColision;     //�R���W�����}�b�v
	//�v���C���[�̕ϐ�
	CPlayer mPlayer;
	//�J�����̎��_�̕ϐ�
	CVector mEye;
	//�}�g���b�N�X�̕ϐ�
	CMatrix matrix;
	//�w�i�ړ��p�̍s��
	CMatrix mBackGroundMatrix;
	//���f������R���C�_�𐶐�
	CColliderMash mColliderMesh;
	CColliderMash ColliderMesh;
	//CSound�N���X�̃C���X�^���X�쐬
	CSound Bgm;
	int mRepop;
	int vel;
public:
	
	void Init() {
		Bgm.Load("res\\���y\\Sunrise.wav");
			
		////�T�E���h�t�@�C���̌J��Ԃ��Đ�
		Bgm.Repeat(0.3);
		
		mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
		mEye = CVector(1.0f, 2.0f, 3.0f);
		//���f���t�@�C���̓���
		mModel.Load(MODEL_OBJ);
		//�}�b�v���f���t�@�C���̓���
		mMap.Load(MODEL_MAP);
		//�w�i���f��
		mBackGround.Load(MODEL_BACKGROUND);
		//�}�b�v�R���W�����̃��f���t�@�C���̓���
		mColision.Load(MODEL_COLISION);
		//�}�g���b�N�X�̕`��ϐ�
		matrix.Print();
		//�v���C���[�̃��f���|�C���^
		mPlayer.Model(&mModel);
		mPlayer.Scale(CVector(0.5f, 0.5f, 0.5f));
		mPlayer.Position(CVector(92.0f, -0.7f, 76.0f) * mBackGroundMatrix);
		mPlayer.Rotation(CVector(0.0f, -180.0f, 0.0f));
		//�G�@2�̃C���X�^���X�쐬
		new CEnemy2(CVector(-5.0f, -0.8f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
		new CEnemy2(CVector(5.0f, -0.8f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
		new CEnemy2(CVector(92.0f, -0.8f, 100.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
		new CEnemy2(CVector(87.0f, -0.8f, 100.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
		//�r���{�[�h�̐���
		/*new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);*/
		//�w�i���f������O�p�R���C�_�𐶐�
		//�e�C���X�^���X�Ɛe�s��͂Ȃ�
		mColliderMesh.Set(nullptr, &mBackGroundMatrix, &mColision);
		//�e�C���X�^���X�Ɛe�s��͂Ȃ�
		ColliderMesh.Set(nullptr, &mBackGroundMatrix, &mBackGround);
	}

	void  Update() {
		if (mRepop % 100 == 50) {
			//�����l=rand()%�����l�̗v�f��+�����l�̍ŏ��l
			srand((unsigned)time(NULL));
			vel = (rand() % 100) + 1;
				for (int i = 0; i < 1; i++) {
					if (vel >= 0 && vel <= 7) {
						new CMoney(CVector(75.0f, -0.5f, 76.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}

				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 8 && vel <= 15) {
						new CMoney(CVector(73.5f, -0.5f, 134.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 16 && vel <= 23) {
						new CMoney(CVector(0.0f, -0.5f, 159.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 24 && vel <= 31) {
						new CMoney(CVector(-61.5f, -0.5f, 158.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 32 && vel <= 39) {
						new CMoney(CVector(-62.5f, -0.5f, 105.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 40 && vel <= 47) {
						new CMoney(CVector(-16.0f, -0.5f, 0.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 48 && vel <= 55) {
						new CMoney(CVector(27.0f, -0.5f, 56.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 56 && vel <= 63) {
						new CMoney(CVector(73.5f, -0.5f, -35.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 64 && vel <= 71) {
						new CMoney(CVector(-53.0f, -0.5f, -35.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 78 && vel <= 85) {
						new CMoney(CVector(-62.5f, -0.5f, 42.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 86 && vel <= 93) {
						new CMoney(CVector(-20.0f, -0.5f, 58.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
				for (int i = 0; i < 1; i++) {
					if (vel >= 94 && vel <= 101) {
						new CMoney(CVector(50.0f, -0.5f, 50.5f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
					}
				}
		}
		mRepop = mRepop + 1;
		//�J�����̃p�����[�^���쐬����
		CVector e, c, u;//���_,�����_,�����
			//���_�����߂�
		e = mPlayer.Position() + CVector(0.0f, 1.2f, -3.0f) * mPlayer.MatirixRotate();
		//�����_�����߂�
		c = mPlayer.Position();
		//����������߂�
		u = CVector(0.0f, 4.0f, 0.0f) * mPlayer.MatirixRotate();
		//�J�����̐ݒ�
		//gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
		//�J�����N���X�̐ݒ�
		Camera.Set(e, c, u);
		Camera.Render();
		//�}�b�v���f���̕`��
		mMap.Render();
		//�w�i���f���̕`��
		mBackGround.Render();
	}




	
};
#endif //CGAMETEST

