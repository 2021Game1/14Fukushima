#ifndef CXPLAYERMANAGER_H
#define CXPLAYERMANAGER_H

#include "CXPlayer.h"
#include"CRes.h"
/*
CXPlayerManager�N���X
�v���C�������N���X
*/


class CXPlayerManager : public CXCharacter{
public:
	CXPlayerManager();	//�f�t�H���g�R���X�g���N�^
	~CXPlayerManager();	//�f�X�g���N�^
	static CXPlayerManager* GetInstance(); //�C���X�^���X�擾

	void Generate(); //����

	void Release(); //�j��

	void Update();	//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)

	void Init();	//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)

	void Render();  //�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)

	void PlayerGenerate(); //�G�����A�����Ő������ƓG�̎�ނ��w�肷��


private:

	static CXPlayerManager* mInstance; //�v���C���Ǘ��̃C���X�^���X

	std::vector<CXPlayer*> mPlayerList; //�v���C���i�[

	//�v���C�����f��
	CModelX gPlayer_Model_Knight;

};

#endif