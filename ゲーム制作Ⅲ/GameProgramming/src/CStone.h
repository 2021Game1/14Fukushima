#ifndef CSTONE_H
#define CSTONE_H

#include"CCharacter.h"
#include"CTaskManager.h"
#include"CCollider.h"
#include"CColliderMesh.h"
#include"CModel.h"
#include"CTable.h"
#include"CMatrix.h"
#include"CUtil.h"


//��Q��(��)�̗D�揇��
#define STONE_PRIORITY 80

/*��Q��(��)�̃��f��*/
#define STONE_MODEL_OBJ "res\\Stone\\stone.obj","res\\Stone\\stone.mtl"
#define STONE_COLLISION_OBJ "res\\Stone\\stone_collision.obj","res\\Stone\\stone_collision.mtl"

//�f�[�^�x�[�X(�f�[�^�e�[�u��)
#define STONE_DATATABLE "res\\Stone\\DataTable\\StoneData_MainGame.txt"

//��Q��(��)�N���X
class CStone : public CCharacter {
public:
	//�G�̋����̎��
	enum class EStoneType {
		ETYPE_STONE_POS_1,						//�v���C���̏����ʒu���猩�ē��ɔz�u
		ETYPE_STONE_POS_2,						//�v���C���̏����ʒu���猩�Đ��ɔz�u
		ETYPE_STONE_POS_3,						//�v���C���̏����ʒu���猩�Ėk�ɔz�u
	};
	//�f�t�H���g�R���X�g���N�^
	CStone();
	//���f���̐ݒ�
	void Model(CModel* model);
	//�����蔻��̐ݒ�
	void Collision(CCollider* m, CCollider* o);
	//�e�[�u���ǂݍ��݊֐�
	void StoneTable();							//�f�[�^�x�[�X
	//��Q��(��)�̎�ނ�ݒ�p
	void SetIsType(EStoneType type);
	//���W�̎擾
	void GetPos();
	//�X�P�[���̎擾
	void GetScale();
	//���f���̉�]�l�擾
	void GetRotation();
	//�C���X�^���X�̎擾
	static CStone* GetInstance();//static�ŏ��������
private:
	//�΂̃��f���|�C���^
	static CStone* mpStone_Instance;	//�ʂ̃N���X����ϐ����Ăяo���ꍇ,static�Ń|�C���^�����
	//��Q��(��)�̎�ޔ��f�p
	EStoneType mStone_Type;		
	//�΃��f��
	CModel gStone_Model;
	//�΂̓����蔻�胂�f��
	CModel gStone_Model_Collision;
	//���f������R���C�_�𐶐�
	CColliderMesh mColliderMesh;
	//�}�b�v�ړ��p�̍s��
	CMatrix mBackGroundMatrix;
	//�f�[�^�x�[�X����擾����ϐ�
	float Stone_Position_X;						//��Q���̃|�W�V�����ݒ�X���W
	float Stone_Position_Y;						//��Q���̃|�W�V�����ݒ�Y���W
	float Stone_Position_Z;						//��Q���̃|�W�V�����ݒ�Z���W
	float Stone_Scale_X;						//��Q���̃��f���X�P�[����X���W
	float Stone_Scale_Y;						//��Q���̃��f���X�P�[����Y���W
	float Stone_Scale_Z;						//��Q���̃��f���X�P�[����Z���W
	float Stone_Rotation_X;						//��Q���̃��f���̉�]X���W
	float Stone_Rotation_Y;						//��Q���̃��f���̉�]Y���W
	float Stone_Rotation_Z;						//��Q���̃��f���̉�]Z���W
};
#endif
