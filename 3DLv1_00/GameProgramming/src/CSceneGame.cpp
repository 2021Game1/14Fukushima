#include "CSceneGame.h"
//OpenGL
#include"glut.h"

void CSceneGame::Init() {

}

void CSceneGame::Update() {
	//���_�̐ݒ�
	//gluLookuAt(���_X,���_Y�A���_Z,���SX�A���SY�A���SZ�A���X�A���Y,���Z)
	gluLookAt(1.0f, 2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//�`�揈��
	//glBegin(�`)
	//GL_TRIANGLES:�O�p�`
	glBegin(GL_TRIANGLES);

	//�@���i�ʂ̌����j�̐ݒ�
	//glNormal3f(X���W�AY���W�AZ���W)
	glNormal3f(0.0f, 1.0f, 0.0f);

	//���_���W�̐ݒ�
	//glNormal3f(X���W�AY���W�AZ���W)
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -0.5f);

	//�`��I��
	glEnd();

}

