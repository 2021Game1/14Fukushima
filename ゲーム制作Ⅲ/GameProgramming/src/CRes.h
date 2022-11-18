#ifndef CRES_H
#define CRES_H


#include "CVector.h"
#include "CCamera.h"
#include "CMatrix.h"
#include "CKey.h"
#include "CUtil.h"
#include "CCollisionManager.h"
#include "CModelX.h"
#include "CXCharacter.h"
#include "CText.h"
#include "CXPlayer.h"
#include "CXEnemy.h"
#include "CMap.h"
#include "CColliderMesh.h"

#define MODEL_MAP "res\\map\\map.obj","res\\map\\map.mtl"
#define MODEL_SKY "res\\sky\\sky.obj","res\\sky\\sky.mtl"
#define COLLISION_MAP "res\\map\\collision.obj","res\\map\\collision.mtl"

class CRes {
	CText mFont;
	//�m�F�p�C���X�^���X
	CModelX gModelX;
	CModel gMap;
	CModel gSky;
	CModel gCollision;
	//�v���C���[�N���X�̃C���X�^���X
	CXPlayer mPlayer;
	//�L�[���͂ŉ�]
	CMatrix gMatrix;
	//�G�̃C���X�^���X
	CXEnemy mEnemy;
	//�G���f��
	CModelX gMutant;
	//�}�b�v���f��
	CMap mMap;
	//�}�b�v�ړ��p�̍s��
	CMatrix mBackGroundMatrix;
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;
public:

	void Init() {
		mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
		//3D���f���t�@�C���̓ǂݍ���
		gModelX.Load(PLAYER_MODEL_FILE);
		//�v���C���̃A�j���[�V�����̒ǉ�
		gModelX.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP3);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_GUARD);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_GUARDIDLE);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_IDLE);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
		gModelX.AddAnimationSet(PLAYER_ANIMATION_DEATH);
		//�J����������
		Camera.Init();

		//�}�b�v���f���t�@�C���̓���
		gMap.Load(MODEL_MAP);
		//�X�J�C���f���t�@�C���̓���
		gSky.Load(MODEL_SKY);
		//�}�b�v�̃R���C�_�t�@�C���̓���
		gCollision.Load(COLLISION_MAP);
		//3D���f���t�@�C���̓ǂݍ���
		gMutant.Load(ENEMY_MODEL_FILE);
		//�G�l�~�[�̃A�j���[�V�����̒ǉ�
		gMutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP1);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP2);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP4);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
		gMutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);
		//�L�����N�^�Ƀ��f����ݒ�
		mPlayer.Init(&gModelX);
		//�G�̏����ݒ�
		mEnemy.Init(&gMutant);
		mFont.LoadTexture("font\\FontG.png", 1, 4096 / 64);
		mMap.Model(&gMap);
		
		//�e�C���X�^���X�Ɛe�s��͂Ȃ�
		mColliderMesh.Set(nullptr, &mBackGroundMatrix, &gCollision);
	}

	void Update() {
		//�L�����N�^�N���X�̍X�V
		mPlayer.Update();


		Camera.Update();
		Camera.Render();
		

		//�s��ݒ�
		glMultMatrixf(gMatrix.M());

		//���_�ɃA�j���[�V�����K�p����
		gModelX.AnimeteVertex();
		//���f���`��
		mPlayer.Render();
		//�}�b�v���f���̕`��
		mMap.Render();
		gSky.Render();
		//�R���C�_�̕`��
		CCollisionManager::Get()->Render();
		//�Փˏ���
		CCollisionManager::Get()->Collision();
		//�G�̍X�V
		mEnemy.Update();
		//�G�`��
		mEnemy.Render();



		//2D�`��J�n
		CUtil::Start2D(0, 800, 0, 600);

		mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

		//2D�̕`��I��
		CUtil::End2D();
	}
};
#endif

