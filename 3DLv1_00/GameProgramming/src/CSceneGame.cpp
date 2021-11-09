#include "CSceneGame.h"
//OpenGL
#include"glut.h"
//2.1
#include"CVector.h"
//3.2
#include"CTriangle.h"
//4.2
#include"CKey.h"
//�ۑ�11
#include"CMatrix.h"
//���f���f�[�^�̎w��
#define MODEL_OBJ "res\\f14.obj","res\\f14.mtl"
#define MODEL_BACKGROUND "res\\sky.obj","res\\sky.mtl"
//�J�����̎��_�̕ϐ�
CVector mEye;
//�w�i���f���f�[�^�̎w��


void CSceneGame::Init() {
	mEye = CVector(1.0f, 2.0f, 3.0f);
	//���f���t�@�C���̓���
	mModel.Load(MODEL_OBJ);
	mBackGround.Load(MODEL_BACKGROUND);
	//�ۑ�11
	CMatrix matrix;
	//�ۑ�11
	matrix.Print();
}

void CSceneGame::Update() {

	//���_�P�C���_�Q�C���_�R�C�@���f�[�^�̍쐬
	CVector v0, v1, v2, n;
	//�@����������Őݒ肷��
	n.Set(0.0f, 1.0f, 0.0f);
	//���_�P�̍��W��ݒ肷��
	v0.Set(0.0f, 0.0f, 0.5f);
	//���_�Q�̍��W��ݒ肷��
	v1.Set(1.0f, 0.0f, 0.0f);
	//���_�R�̍��W��ݒ肷��
	v2.Set(0.0f, 0.0f, -0.5f);

	//���_�̈ړ�
	//J�L�[:X���}�C�i�X�����ֈړ�
	if (CKey::Push('J'))
	{
		mEye = mEye - CVector(0.1f, 0.0f, 0.0f);
	}
	//L�L�[:X���v���X�����ֈړ�
	if (CKey::Push('L'))
	{
		mEye = mEye + CVector(0.1f, 0.0f, 0.0f);
	}
	//I�L�[:Y���}�C�i�X�����ֈړ�
	if (CKey::Push('I'))
	{
		mEye = mEye - CVector(0.0f, 0.0f, 0.1f);
	}
	//K�L�[:Y���v���X�����ֈړ�
	if (CKey::Push('K'))
	{
		mEye = mEye + CVector(0.0f, 0.0f, 0.1f);
	}
	//�ۑ�4 M�L�[:Y���}�C�i�X�����ֈړ�
	if (CKey::Push('M'))
	{
		mEye = mEye - CVector(0.0f, 0.1f, 0.0f);
	}
	//�ۑ�4 O�L�[:Y���v���X�����ֈړ�
	if (CKey::Push('O'))
	{
		mEye = mEye + CVector(0.0f, 0.1f, 0.0f);
	}

	//���_�̐ݒ�
	//gluLookAt(���_X�A���_Y�A���_Z�A���SX�A���SY�A���SZ,���X�A���Y�A���Z)
	gluLookAt(mEye.X(), mEye.Y(), mEye.Z(), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	mModel.Render(CMatrix().RotateX(90.0f));
	mBackGround.Render(CMatrix());
}
	/*
	//�`��J�n
	glBegin(GL_TRIANGLES);


	//�@���i�ʂ̌����j�̐ݒ�
	glNormal3f(n.X(), n.Y(), n.Z());
	//���_���W�̐ݒ�
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());

	//�@���ƒ��_�̐ݒ�
	n.Set(0.0f, 0.0f, 1.0f);
	v0.Set(0.5f, 0.0f, 0.0f);
	v1.Set(0.0f, 1.0f, 0.0f);
	v2.Set(-0.5f, 0.0f, 0.0f);

	//�O�p�`�Q�̕`��
	glNormal3f(n.X(), n.Y(), n.Z());
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());

	//�ۑ�Q�@�@���ƒ��_�̐ݒ�
	n.Set(1.0f, 0.0f, 0.0f);
	v0.Set(0.0f, 0.5f, 0.0f);
	v1.Set(0.0f, 0.0f, 1.0f);
	v2.Set(0.0f,-0.5f,0.0f);

	//�ۑ�Q �O�p�`�R�̕`��
	glNormal3f(n.X(), n.Y(), n.Z());
	glVertex3f(v0.X(), v0.Y(), v0.Z());
	glVertex3f(v1.X(), v1.Y(), v1.Z());
	glVertex3f(v2.X(), v2.Y(), v2.Z());

	//�`��I��
	glEnd();

	//�O�p�`�N���X�̃C���X�^���X�쐬�@
	CTriangle t0;
	//�@���ƒ��_�̐ݒ�@
	t0.Vertex(CVector(1.0f, 0.0f, 0.5f), CVector(2.0f, 0.0f, 0.0f), CVector(1.0f, 0.0f, -0.5f));
	t0.Normal(CVector(0.0f, 1.0f, 0.0f));
	//�O�p�`�̕`��@
	t0.Render();

	//�ۑ�3�@�O�p�`�N���X�A�̃C���X�^���X�쐬
	CTriangle t1;
	//�ۑ�3 �@���ƒ��_�̐ݒ�A
	t1.Vertex(CVector(0.0f,0.5f,1.0f), CVector(0.0f, 0.0f,2.0f), CVector(0.0f,-0.5f,1.0f));
	t1.Normal(CVector(1.0f, 0.0f, 0.0f));
	//�ۑ�3 �O�p�`�̕`��A
	t1.Render();

	//�ۑ�3 �O�p�`�N���X�B�̃C���X�^���X�쐬
	CTriangle t2;
	//�ۑ�3 �@���ƒ��_�̐ݒ�B
	t2.Vertex(CVector(0.5f,1.0f,0.0f), CVector(0.0f,2.0f,0.0f), CVector(-0.5f,1.0,0.0f));
	t2.Normal(CVector(0.0f,0.0f,1.0f));
	//�ۑ�3 �O�p�`�̕`��B
	t2.Render();
	*/


