#ifndef CENEMY_H
#define CENEMY_H

#include "CRectangle.h"
#include "CBullet.h"

class CEnemy : public CRectangle {
public:

	//	bool mEnabled;	//�L���t���O

	//CBullet EBullet[20];
	int mFx,mFy;
	int mType;//�G�̎��
	int mSype;//�G�̒e�̎��
	int mPattern;//�G�̍s���p�^�[��
	int mShotpattrn;//�G�̒e�̔��˃p�^�[��
	int mEnemytime;// �G�̏o������
	int mBullettime;//�G�̒e���ˎ���
	int x;//X���W
	int y;//Y���W
	int mFirecount;//�e�̔��ˊԊu
	int mItem;//�A�C�e��
	CEnemy();
	void Update();
	bool Collision(const CRectangle& r);
	void Render();
	int mFireCount;
	//36
	void Collision(CRectangle* i, CRectangle* y);

	
	

};
#endif
