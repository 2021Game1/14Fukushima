#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CModel.h"
//�v���C���[�N���X�̃C���N���[�h
#include"CPlayer.h"
//�x�N�g���N���X�̃C���N���[�h
#include"CVector.h"
//�~�T�C���N���X
#include"CMissile.h"
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


/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//���f���N���X�̃C���X�^���X�쐬
	CModel mModel; //�v���C���[���f��
	CModel mBackGround; //�w�i���f��
	CModel mModelC5; //�G���f��
	CModel mMap;     //�}�b�v
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

};

#endif
