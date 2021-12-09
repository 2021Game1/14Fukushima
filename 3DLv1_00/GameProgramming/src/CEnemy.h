#ifndef CENEMY_H
#define CENEMY_H
//�L�����N�^�N���X�̃C���N���[�h
#include "CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include "CCollider.h"
/*
�G�l�~�[�N���X
�L�����N�^�N���X�̃C���N���[�h
*/
class CEnemy : public CCharacter{
public:

	//�R���X�g���N�^
	//CEnemy(���f��,�ʒu,��],�g�k)
	CEnemy(CModel* model, const CVector& position,
		const CVector& rotation, const CVector& scale);
	//�X�V����
	void Update();
	//�m�F���\�b�h�@�폜�\��
	void CEnemy::Render() {
		CCharacter::Render();
		mCollider1.Render();
		mCollider2.Render();
		mCollider3.Render();
	}

private:
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;
};
#endif // !CENEMY_H

