#ifndef CXENEMYMANAGER_H
#define CXENEMYMANAGER_H

#include "CXEnemy.h"
#include"CRes.h"
//�G�}�l�[�W���̃f�[�^�e�[�u��
/*
CXEnemyManager�N���X
*/

#define ENEMY_A 1
#define ENEMY_B 2

class CXEnemyManager{
public:
	CXEnemyManager();	//�f�t�H���g�R���X�g���N�^
	~CXEnemyManager();	//�f�X�g���N�^
	static CXEnemyManager* GetInstance(); //�C���X�^���X�擾

	static void Generate(); //����

	static void Release(); //�j��

	void Update();	//�X�V

	void Init();    //������

	void Render();	//�`��(�`��͂��Ȃ�)

	void EnemyGenerate(int num, CXEnemy::EEnemyType type); //�G�����A�����Ő������ƓG�̎�ނ��w�肷��

	bool GetIsEnemyAllDeath(); //�G���S�Ď��S��ԂɂȂ��true��Ԃ�

	CVector GetTargetEnemy(); //��ԋ߂��G���擾����

private:
	//�G�Ǘ��̃C���X�^���X
	static CXEnemyManager* mInstance;
	//�G�i�[
	std::vector<CXEnemy*> mEnemyList;
	//���S��Ԃ̓G�̐�
	int mEnemyDeathNum;
	//�G���f��
	CModelX gEnemy_Model_Mutant;
	//�^�[�Q�b�g�ݒ�
	CVector mTargetEnemy; //��ԃv���C������߂��G���i�[
	//�^�[�Q�b�g�ݒ�ۑ�
	CVector mTarget; 
	//�^�[�Q�b�g�ݒ�ۑ�
	CVector mTargetGame1; 
	//�^�[�Q�b�g�ݒ�ۑ�
	CVector mTargetGame2;
	//�v���C�����W
	float mPlayerPos;
	//�G���W
	float mEnemyPos;
	//�G���W
	float mEnemyPosGame1;
	//�G���W
	float mEnemyPosGame2;
};
#endif

