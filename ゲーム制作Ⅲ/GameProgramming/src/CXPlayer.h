#ifndef CXPLAYER_H
#define CXPLAYER_H


#include"CXCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CInput.h"
/*
CXPlayer
*/

class CXPlayer : public CXCharacter {
public:
	void Update();
	void Init(CModelX* model);
	CXPlayer();
	static CXPlayer* mpPlayerInstance;//�ʂ̃N���X�ŕϐ����Ăяo���ꍇ,static�Ń|�C���^�����
	static CXPlayer* GetInstance();//static�ŏ��������
	CCollider mColSphereHead;//��
	CCollider mColSphereSword;//��
	void Collision(CCollider* m, CCollider* o);

private:
	//�R���C�_�̐錾
	CCollider mColSphereBody; //�g��
};
#endif 

