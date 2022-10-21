#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include <time.h>
#include "CScene.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CText.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CMap.h"
#include "CColliderMesh.h"


/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
	CText mFont;
	//�m�F�p�C���X�^���X
	CModelX gModelX;
	CModel gMap;
	CModel gCollision;
	//�v���C���[�N���X�̃C���X�^���X
	CXPlayer mPlayer;
	//�L�[���͂ŉ�]
	CMatrix gMatrix;
	//�G�̃C���X�^���X
	CXEnemy mEnemy;
	//�G���f��
	CModelX gKnight;
	//�}�b�v���f��
	CMap mMap;
	//�}�b�v�ړ��p�̍s��
	CMatrix mBackGroundMatrix;
	clock_t mStartTime, mEndTime;//�v���J�n�����A�v���I������
	bool mCountStart; //�N���A���Ԍv���J�n�p
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;
	//static�Ń|�C���^�����
	static CSceneGame* mpSceneGameInstance;
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//static�ŏ��������
	static CSceneGame* GetInstance();

};

#endif