//�V�[���Q�[���N���X�̃C���N���[�h
#include "CSceneGame.h"
//OpenGL
#include"glut.h"

//���f���f�[�^�̎w��
#define MODEL_OBJ "res\\car.obj","res\\car.mtl"
#define MODEL_MAP "res\\city.obj","res\\city.mtl"
#define MODEL_COLISION "res\\colision.obj","res\\colision.mtl"
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"


void CSceneGame::Init() {

	mMapMatrix.Translate(0.0f, 0.0f, 0.1f);
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
	//�G�̃��f���̓ǂݍ���
	mModelC5.Load("res\\C5.obj","res\\C5.mtl");
	//�}�g���b�N�X�̕`��ϐ�
	matrix.Print();
	//�v���C���[�̃��f���|�C���^
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.5f, 0.5f, 0.5f));
	mPlayer.Position(CVector(92.0f, 0.0f, 76.0f)* mMapMatrix);
	mPlayer.Rotation(CVector(0.0f, -180.0f,0.0f));
	//�G�@2�̃C���X�^���X�쐬
	new CEnemy2(CVector(-5.0f, 0.0f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
	new CEnemy2(CVector(5.0f, 0.0f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.16f, 0.16f, 0.16f));
	//�r���{�[�h�̐���
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	//�w�i���f������O�p�R���C�_�𐶐�
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(nullptr, &mMapMatrix, &mColision);
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &mBackGround);
}

void CSceneGame::Update() {
	//�^�X�N�}�l�[�W���̍X�V
	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	CTaskManager::Get()->TaskCollision();


	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_,�����_,�����
	//���_�����߂�
	e = mPlayer.Position() + CVector(0.0f,1.0f,-4.0f) * mPlayer.MatirixRotate();
	//�����_�����߂�
	c = mPlayer.Position();
	//����������߂�
	u = CVector(0.0f,3.0f,0.0f) * mPlayer.MatirixRotate();
	//�J�����̐ݒ�
	//gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();





	


	//�}�b�v���f���̕`��
	mMap.Render();
	//�w�i���f���̕`��
	mBackGround.Render();
	////�R���W�����}�l�[�W���̃R���C�_�`��
	//CCollisionManager::Get()->Render();
	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();
	//�^�X�N�}�l�[�W���̕`��	
	CTaskManager::Get()->Render();


}



