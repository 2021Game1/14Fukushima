//�V�[���Q�[���N���X�̃C���N���[�h
#include "CSceneGame.h"
//OpenGL
#include"glut.h"

//���f���f�[�^�̎w��
#define MODEL_OBJ "res\\car.obj","res\\car.mtl"
#define MODEL_BACKGROUND "res\\city.obj","res\\city.mtl"
#define MODEL_MAP "res\\colision.obj","res\\colision.mtl"


void CSceneGame::Init() {

	mBackGroundMatrix.Translate(0.0f, 0.0f, 50.0f);
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//���f���t�@�C���̓���
	mModel.Load(MODEL_OBJ);
	//�}�b�v���f���t�@�C���̓���
	mMap.Load(MODEL_MAP);
	//�w�i���f���t�@�C���̓���
	mBackGround.Load(MODEL_BACKGROUND);
	//�G�̃��f���̓ǂݍ���
	mModelC5.Load("res\\C5.obj","res\\C5.mtl");
	//�}�g���b�N�X�̕`��ϐ�
	matrix.Print();
	//�v���C���[�̃��f���|�C���^
	mPlayer.Model(&mModel);
	mPlayer.Scale(CVector(0.6f, 0.6f, 0.6f));
	mPlayer.Position(CVector(0.0f, 0.6f, -3.0f)* mBackGroundMatrix);
	mPlayer.Rotation(CVector(0.0f, -180.0f,0.0f));
	//�G�@2�̃C���X�^���X�쐬
	new CEnemy2(CVector(-5.0f, 1.0f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
	new CEnemy2(CVector(5.0f, 1.0f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.5f, 0.5f, 0.5f));
	/*new CMissile(CVector(3.0f, 1.0f, -10.0f) * mBackGroundMatrix, CVector(), CVector(0.4f, 0.4f, 0.4f));*/
	//�r���{�[�h�̐���
	new CBillBoard(CVector(-6.0f, 3.0f, -10.0f), 1.0f, 1.0f);
	//�w�i���f������O�p�R���C�_�𐶐�
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &mMap);
}

void CSceneGame::Update() {
	//�^�X�N�}�l�[�W���̍X�V
	CTaskManager::Get()->Update();
	//�R���W�����}�l�[�W���̏Փˏ���
	CTaskManager::Get()->TaskCollision();


	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_,�����_,�����
	//���_�����߂�
	e = mPlayer.Position() + CVector(0.0f,1.0f,-5.0f) * mPlayer.MatirixRotate();
	//�����_�����߂�
	c = mPlayer.Position();
	//����������߂�
	u = CVector(0.0f,1.0f,0.0f) * mPlayer.MatirixRotate();
	//�J�����̐ݒ�
	//gluLookAt(e.X(), e.Y(), e.Z(), c.X(), c.Y(), c.Z(), u.X(), u.Y(), u.Z());
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();





	

	mMap.Render();
	//�w�i���f���̕`��
	mBackGround.Render();
	//�R���W�����}�l�[�W���̃R���C�_�`��
	CCollisionManager::Get()->Render();
	//�^�X�N���X�g�̍폜
	CTaskManager::Get()->Delete();
	//�^�X�N�}�l�[�W���̕`��	
	CTaskManager::Get()->Render();


}



