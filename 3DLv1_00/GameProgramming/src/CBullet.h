#ifndef CBULLET_H
#define CBULLET_H
//�L�����N�^�N���X�̃C���N���[�h
#include"CCharacter.h"
//�O�p�`�N���X�̃C���N���[�h
#include"CTriangle.h"

/*
* �e�N���X
* �O�p�`���΂�
*/

class CBullet : public CCharacter{
public:
	//���Ɖ��s��
	//Set(��,���s)
	void Set(float w, float d);
	//�X�V
	void Update();
	//�`��
	void Render();

private:
	//�O�p�`
	CTriangle mT;
};
#endif 
