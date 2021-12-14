//�R���C�_�N���X�̃C���N���[�h
#include"CCollider.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include"CCollisionManager.h"

CCollider::CCollider(CCharacter* parent, CMatrix* matrix,
	const CVector& position, float radius) {
	//�e�ݒ�
	mpParent = parent;
	//�e�s��ݒ�
	mpMatrix = matrix;
	//CTransform�ݒ�
	mPosition = position; //�ʒu
	//���a�ݒ�
	mRadius = radius;
	//�R���W�����}�l�[�W��y�ɒǉ�
	CCollisionManager::Get()->Add(this);
}

CCharacter* CCollider::Parent() 
{
	return mpParent;
}

void CCollider::Render() 
{
	glPushMatrix();
	//�R���C�_�̒��S���W���v�Z
	//�����̍��W�~�e�̕ϊ��s����|����
	CVector pos = mPosition * *mpMatrix;
	//���S���W�ֈړ�
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f,0.0f,0.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//���`��
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}
CCollider::~CCollider() {
	//�R���W�������X�g����폜
	CCollisionManager::Get()->Remove(this);

}