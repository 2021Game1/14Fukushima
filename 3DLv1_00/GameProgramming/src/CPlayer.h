#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�[�N���X�̃C���N���[�h
#include"CCharacter.h"
//�e�N���X�̃C���N���[�h
#include"CBullet.h"


/*
�v���C���[�N���X
�L�����N�^�[�N���X���p��
*/

class CPlayer : public CCharacter {
public:
	//CBullet�N���X�̃C���X�^���X�ϐ�
	CBullet bullet;
	//�X�V����
	void Update();


};
#endif 

