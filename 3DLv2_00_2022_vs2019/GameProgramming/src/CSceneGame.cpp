#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"



void CSceneGame::Init() {
	//3D���f���t�@�C���̓ǂݍ���
	gModelX.Load(MODEL_FILE);
	//�L�����N�^�Ƀ��f����ݒ�
	mPlayer.Init(&gModelX);
	//�G�̏����ݒ�
	mEnemy.Init(&gModelX);
	//�G�̔z�u
	mEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

void CSceneGame::Update() {
	//�L�����N�^�N���X�̍X�V
	mPlayer.Update();
	//�G�̍X�V
	mEnemy.Update();
	
	//�J�����̃p�����[�^���쐬����
	CVector e, c, u;//���_�A�����_�A�����
	//���_�����߂�
	e = CVector(1.0f, 2.0f, 10.0f);
	//�����_�����߂�
	c = CVector();
	//����������߂�
	u = CVector(0.0f, 1.0f, 0.0f);
	
	//�J�����N���X�̐ݒ�
	Camera.Set(e, c, u);
	Camera.Render();

	//X��+��]
	if (CKey::Push('K')) {
		gMatrix = gMatrix * CMatrix().RotateX(1);
	}
	//Y��+��]
	if (CKey::Push('L')){
		gMatrix = gMatrix * CMatrix().RotateY(1);
	}
	//X��-��]
	if (CKey::Push('I')) {
		gMatrix = gMatrix * CMatrix().RotateX(-1);
	}
	//Y��-��]
	if (CKey::Push('J')) {
		gMatrix = gMatrix * CMatrix().RotateY(-1);
	}
	//�s��ݒ�
	glMultMatrixf(gMatrix.M());
	
	//���_�ɃA�j���[�V�����K�p����
	gModelX.AnimeteVertex();
	//���f���`��
	mPlayer.Render();
	//�G�`��
	mEnemy.Render();


	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();

}

