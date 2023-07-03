#ifndef CXENEMYMANAGER_H
#define CXENEMYMANAGER_H

#include "CXEnemy.h"
#include "CEnemyData.h"
//�G�}�l�[�W���̃f�[�^�e�[�u��
/*
CXEnemyManager�N���X
*/
//�v���C���̍U���͈͉��̍��W
#define PLAYER_ATTACK_POS 5.3

class CXEnemyManager :public CXCharacter{
public:
	CXEnemyManager();	//�f�t�H���g�R���X�g���N�^
	~CXEnemyManager();	//�f�X�g���N�^
	static CXEnemyManager* GetInstance(); //�C���X�^���X�擾

	static void Generate(); //����

	static void Release(); //�j��

	void Update();	//�X�V

	void Init();	//�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)

	void Render();  //�^�X�N�}�l�[�W���Ɋi�[���邽�߂̃��\�b�h(�������Ȃ�����)

	//�G����
	void EnemyGenerate(int num, CXEnemy::EEnemyType type); //�G�����A�����Ő������ƓG�̎�ނ��w�肷��

	bool GetIsEnemyAllDeath(); //�G���S�Ď��S��ԂɂȂ��true��Ԃ�

	CVector GetTargetEnemy(); //��ԋ߂��G���擾����

private:
	//�G�Ǘ��̃C���X�^���X
	static CXEnemyManager* mInstance;
	//�G�i�[
	std::vector<CXEnemy*> mEnemyList;
	//�G�̐��������i�[
	int mEnemyGenerate;
	//�G�𐶐�
	CXEnemy* tmp1;
	CXEnemy* tmp2;
	CXEnemy* tmp3;
	//���S��Ԃ̓G�̐�
	int mEnemyDeathNum;							
	//�^�[�Q�b�g�ݒ�
	CVector mTargetEnemy; //��ԃv���C������߂��G���i�[
	//�^�[�Q�b�g�ݒ�ۑ�
	CVector mTarget; 
	//�v���C�����W
	float mPlayerPos;
	//�G���W
	float mEnemyPos;
};
#endif

