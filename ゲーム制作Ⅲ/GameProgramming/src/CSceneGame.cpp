#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"
#include "CCollisionManager.h"

CModelX gKnight;

void CSceneGame::Init() {
	//3D���f���t�@�C���̓ǂݍ���
	gModelX.Load(MODEL_FILE);
	//3D���f���t�@�C���̓ǂݍ���
	gKnight.Load("res\\knight\\knight_low.X");
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//1:�ړ�
	gKnight.SeparateAnimationSet(0, 1530, 1830, "idle1");//2:�ҋ@
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//3:�_�~�[
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//4:�_�~�[
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//5:�_�~�[
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//6:�_�~�[
	gKnight.SeparateAnimationSet(0, 440, 520, "attack1");//7:Attack1
	gKnight.SeparateAnimationSet(0, 520, 615, "attack2");//8:Attack2
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//9:�_�~�[
	gKnight.SeparateAnimationSet(0, 10, 80, "walk");//10:�_�~�[
	gKnight.SeparateAnimationSet(0, 1160, 1260, "death1");//11:�_�E��
	//�L�����N�^�Ƀ��f����ݒ�
	mPlayer.Init(&gModelX);
	//�G�̏����ݒ�
	mEnemy.Init(&gKnight);
	//�G�̔z�u
	mEnemy.Position(CVector(7.0f, 0.0f, 0.0f));
	mEnemy.ChangeAnimation(2, true, 200);
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
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
	//�Փˏ���
	CCollisionManager::Get()->Collision();
	//�G�`��
	mEnemy.Render();


	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();

}

