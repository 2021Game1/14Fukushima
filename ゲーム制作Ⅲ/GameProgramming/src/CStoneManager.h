#ifndef CSTONEMANAGER_H
#define CSTONEMANAGER_H

#include"CStone.h"

/*
CStoneManager�N���X
��Q���̐����N���X
*/


class CStoneManager :public CCharacter {
public:

	CStoneManager();	//�f�t�H���g�R���X�g���N�^

	~CStoneManager();	//�f�X�g���N�^

	static CStoneManager* GetInstance(); //�C���X�^���X�擾

	static void Generate(); //����

	static void Release(); //�j��

	void Update();	//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)

	void Init();	//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)

	void Render();  //�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)



	//�G����
	void StoneGenerate(CStone::EStoneType type); //��Q�������A��Q���̎�ނ��w�肷��

private:
	//��Q���Ǘ��̃C���X�^���X
	static CStoneManager* mInstance;
	//��Q���̊i�[
	std::vector<CStone*> mStoneList;
	//��Q���̐���
	CStone* tmp1;
	CStone* tmp2;
	CStone* tmp3;
};

#endif