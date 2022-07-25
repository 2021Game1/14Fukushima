#ifndef CPLAYER_H
#define CPLAYER_H
//�L�����N�^�[�N���X�̃C���N���[�h
#include"CCharacter.h"
//�e�N���X�̃C���N���[�h
#include"CBullet.h"
//�R���W�����}�l�[�W���N���X�̃C���N���[�h
#include"CCollisionManager.h"
//�����R���C�_�N���X�̃C���N���[�h
#include"CColliderLine.h"
//�e�L�X�g�N���X�̃C���N���[�h
#include"CText.h"
//���[�e�B���e�B�N���X�̃C���N���[�h
#include"CUtil.h"
//�G�t�F�N�g�N���X�̃C���N���[�h
#include "CEffect.h"
//�J�����N���X�̃C���N���[�h
#include "CCamera.h"

/*
�v���C���[�N���X
�L�����N�^�[�N���X���p��
*/

class CPlayer : public CCharacter {
public:
	CText mText;
	//CBullet�N���X�̃C���X�^���X�ϐ�
	/*CBullet bullet;*/
	CPlayer();
	//�X�V����
	void Update();
	//�`�揈��
	void Render();
	//�Փˏ���
	void Collision(CCollider* m, CCollider* o);
	//�Փˏ���
	void TaskCollision();
	static CPlayer* Get();
	

	int mHp;
private:
	//�v���C���[�̃C���X�^���X
	static CPlayer* spInstance;
	CCollider mCollider;	//�{�̗p�R���C�_
	float Velocity;
	float Acceleration;
};
#endif 

