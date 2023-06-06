#ifndef CMAP_H
#define CMAP_H

#include"CCharacter.h"
#include"CTaskManager.h"
#include"CCollider.h"
#include"CColliderMesh.h"
#include"CModel.h"
#include"CMatrix.h"
#include"CUtil.h"

//�}�b�v�̗D�揇��
#define MAP_PRIORITY 90

/*�}�b�v�̃��f��*/

#define MAP_MODEL_MAP "res\\Map\\map.obj","res\\Map\\map.mtl"
#define MAP_MODEL_SKY "res\\Sky\\sky.obj","res\\Sky\\sky.mtl"
#define MAP_COLLISION_MAP "res\\Map\\collision.obj","res\\Map\\collision.mtl"

class CMap : public CCharacter {
public:
	CMap();
	void Init();
	void Collision(CCollider* m, CCollider* o);
	//�}�b�v����
	void Generate(); //����
	//�}�b�v�폜
	void Release(); //�j��
	//�C���X�^���X�̎擾
	static CMap* GetInstance();//static�ŏ��������

private:
	//�}�b�v�̃��f���|�C���^
	static CMap* mpMap_Instance;	//�ʂ̃N���X����ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
	//�}�b�v���f��
	CModel gMap_Model;
	//�}�b�v�̓����蔻�胂�f��
	CModel gMap_Model_Collision;
	//�}�b�v�ړ��p�̍s��
	CMatrix mBackGroundMatrix;
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;

};

class CSkyMap : public CCharacter {
public:
	CSkyMap();
	void Init();
	void Collision(CCollider* m, CCollider* o);
	//�}�b�v����
	void Generate(); //����
	//�}�b�v�폜
	void Release(); //�j��
	//�C���X�^���X�̎擾
	static CSkyMap* GetInstance();//static�ŏ��������

private:
	//�}�b�v�̃��f���|�C���^
	static CSkyMap* mpSkyMap_Instance;	//�ʂ̃N���X����ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
	//�}�b�v�̔w�i���f��
	CModel gSky_Map_Model;
};



#endif
