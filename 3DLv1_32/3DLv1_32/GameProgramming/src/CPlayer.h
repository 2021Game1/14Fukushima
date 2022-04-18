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
	
private:
	//�v���C���[�̃C���X�^���X
	static CPlayer* spInstance;
	CColliderLine mLine;	//�����R���C�_
	CColliderLine mLine2;	//�����R���C�_2
	CColliderLine mLine3;	//�����R���C�_3
	CCollider mCollider;	//�{�̗p�R���C�_
};
#endif 

