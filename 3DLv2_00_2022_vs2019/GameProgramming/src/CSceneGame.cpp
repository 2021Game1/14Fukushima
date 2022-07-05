#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CModelX.h"
#include "CKey.h"
#include "CUtil.h"

//�m�F�p�C���X�^���X
CModelX gModelX;

//�L�[���͂ŉ�]
CMatrix gMatrix;

void CSceneGame::Init() {
	//3D���f���t�@�C���̓ǂݍ���
	gModelX.Load(MODEL_FILE);
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

}

void CSceneGame::Update() {
	gModelX.AnimationSet()[0]->Time(gModelX.AnimationSet()[0]->Time() + 1.0f);
	gModelX.AnimationSet()[0]->Time((int)gModelX.AnimationSet()[0]->Time() % (int)(gModelX.AnimationSet()[0]->MaxTime() + 1));
	//�ŏ��̃A�j���[�V�����d�݂�1.0(100%)�ɂ���
	gModelX.AnimationSet()[0]->Weught(1.0f);
	//�t���[���̕ϊ��s����A�j���[�V�����ōX�V����
	gModelX.AnimateFrame();
	//�t���[���̍����s����v�Z����
	gModelX.Frames()[0]->AnimateCombined(&gMatrix);
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
	gModelX.Render();

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();
}

