#include"CBullet.h"


//���Ɖ��s���̐ݒ�
//Set(��,���s)
void CBullet::Set(float w, float d) {
	//�X�P�[���ݒ�
	mScale = CVector(1.0f, 1.0f, 1.0f);
	//�O�p�`�̒��_�ݒ�
	mT.Vertex(CVector(0.1f, 0.0f, 0.0f), CVector(0.0f, 0.0f, -0.3f), CVector(-0.1f, 0.0f,0.0f));
	//�O�p�`�̖@���ݒ�
	mT.Normal(CVector(0.0f, 1.0f, 0.0f));
}

//�X�V����
void CBullet::Update() {
	CTransform::Update();
	//�ʒu�X�V
	CBullet::mPosition = CBullet::mPosition + CVector(0.0f, 0.0f, 1.0f) * mMatrixRotate;
}

//�`��
void CBullet::Render() {
	//DIFFUSE���F�ݒ�
	float c[] = { 1.0f,1.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//�O�p�`�`��
	mT.Render(mMatrix);
	

}