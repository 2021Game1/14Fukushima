#ifndef CXENEMYMANAGER_H
#define CXENEMYMANAGER_H

#include "CXEnemy.h"
#include"CRes.h"
//�G�}�l�[�W���̃f�[�^�e�[�u��
/*
CXEnemyManager�N���X
*/


class CXEnemyManager{
public:
	CXEnemyManager();	//�f�t�H���g�R���X�g���N�^
	~CXEnemyManager();	//�f�X�g���N�^
	static CXEnemyManager* GetInstance(); //�C���X�^���X�擾

	void Generate(); //����

	void Release(); //�j��

	void Update();	//�X�V

	void Render();

	void EnemyGenerate(int num, CXEnemy::EEnemyType type); //�G�����A�����Ő������ƓG�̎�ނ��w�肷��

	bool GetIsEnemyAllDeath(); //�G���S�Ď��S��ԂɂȂ��true��Ԃ�

private:

	static CXEnemyManager* mInstance; //�G�Ǘ��̃C���X�^���X

	std::vector<CXEnemy*> mEnemyList; //�G�i�[

	int mEnemyDeathNum; //���S��Ԃ̓G�̐�
	//�G���f��
	CModelX gEnemy_Model_Mutant;

};
#endif

