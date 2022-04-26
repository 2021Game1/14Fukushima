#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include "CModelX.h"
#include "CUtil.h"

//�m�F�p�C���X�^���X
CModelX gModelX;

void CSceneGame::Init() {
	//3D���f���t�@�C���̓ǂݍ���
	gModelX.Load(MODEL_FILE);
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

void CSceneGame::Update() {
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




	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();
}

