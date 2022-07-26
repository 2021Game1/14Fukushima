#ifndef CMONEY_H
#define CMONEY_H
//�L�����N�^�N���X�̃C���N���[�h
#include"CCharacter.h"
//�R���C�_�N���X�̃C���N���[�h
#include"CCollider.h"
//�^�X�N�}�l�[�W���̃C���N���[�h
#include"CTaskManager.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include"CCollisionManager.h"
//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"
//���[�e�B���e�B�N���X�̃C���N���[�h
#include"CUtil.h"
//�e�L�X�g�N���X�̃C���N���[�h
#include"CText.h"


//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}

/*
�}�l�[�N���X
�L�����N�^�N���X���p��
*/
class CMoney : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^
	CMoney();

	//CEnemy(�ʒu,��],�g�k)
	CMoney(const CVector& position, const CVector& rotation, const CVector& scale);
	void Update();
	//�Փˏ���
	//Collision(�R���C�_1,�R���C�_2)
	void Collision(CCollider* m, CCollider* o);
	void TaskCollision();
private:
	//���f���f�[�^
	static CModel mModel;
	//�R���C�_
	CCollider mCollider;
	CVector mMoneyIndex;
	CMatrix mBackGroundMatrix;


};

#endif 
