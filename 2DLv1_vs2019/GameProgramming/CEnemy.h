#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy : public CRectangle {
public:
	int mType;//�G�̎��
	int mSype;//�G�̒e�̎��
	int mPattern;//�G�̍s���p�^�[��
	int mShotpattrn;//�G�̒e�̔��˃p�^�[��
	int mEnemytime;// �G�̏o������
	int mFirecount;//�G�̒e���ˎ���
	int x;//X���W
	int y;//Y���W
	int mBullettime;//�e�̃X�s�[�h
	int mItem;//�A�C�e��
//	bool mEnabled;	//�L���t���O

//37	CBullet EBullet[20];
	
	CEnemy();
	void Update();
	bool Collision(const CRectangle &r);
	void Render();

	//36
	void Collision(CRectangle *i, CRectangle *y);
};

#endif
