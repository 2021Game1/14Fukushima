#ifndef CPLAYERGUARD_H
#define CPLAYERGUARD_H

#include"CCharacter.h"
#include"CXPlayer.h"


class CPlayerGuard : public CCharacter
{
public:
	void Init(CModel* model);
	void Update();
	//�`��
	void Render();
	//�v���C���̃C���X�^���X�擾�֐�
	static CPlayerGuard* GetInstance();		//static�ŏ��������
private:
	//�v���C���K�[�h�̃|�C���^
	static CPlayerGuard* mpPlayerGuard_Instance;	//�ʂ̃N���X�Ńv���C���K�[�h�̕ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
};
#endif //CPLAYERGUARD_H
