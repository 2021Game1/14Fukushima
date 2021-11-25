#include"CBossEnemy.h"

int CBossEnemy::CBossEnemyLife = 20;
CBossEnemy* CBossEnemy::spInstance = nullptr;
extern CTexture Texture;

CBossEnemy::CBossEnemy()
	:mFx(0),mFy(0)
{
	spInstance = this;
	mBossFireCount = 60;
	w = 0;
	h = 100;
	//37
//	mEnabled = true;
	mTag = CRectangle::EBOSS;
}

void CBossEnemy::Update() {
	if (!mEnabled)return;

	
		
	//60�t���[����1�񔭎�
	if (mBossFireCount > 0) {
		mBossFireCount--;
	}
	if (y < -280)
	{
		//�G�̃t���O��false��
		mEnabled = false;
	}

	else {
		for (int j = 0; j < 3; j++) {
			CBullet* BEBullet = new CBullet();
			//���W�ݒ�
			BEBullet->x = x;
			BEBullet->y = y;
			//�ړ��ʐݒ�
			if (CBossEnemy::x < CPlayer::spInstance->x) {
				BEBullet->mFx = +1;
				BEBullet->mFy = -3 * ((j / 2) + 1);
				if (mFy < -280)
				{
					//�G�̃t���O��false��
					BEBullet->mEnabled = false;
				}

			}
			if (CBossEnemy::x == CPlayer::spInstance->x) {
				BEBullet->mFx = 0;
				BEBullet->mFy = -3 * ((j / 2) + 1);
				if (mFy < -280)
				{
					//�G�̃t���O��false��
					BEBullet->mEnabled = false;
				}

			}

			if (CBossEnemy::x > CPlayer::spInstance->x) {
				BEBullet->mFx = -1;
				BEBullet->mFy = -3 * ((j / 2) + 1);
				if (mFy < -280)
				{
					//�G�̃t���O��false��
					BEBullet->mEnabled = false;
				}
			}
			//�L���ɂ���
			BEBullet->mEnabled = true;
			BEBullet->mTag = EBOSSBULLET;
		}
			mBossFireCount = 60;
		
	}
}

bool CBossEnemy::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYERBULLET:
			CBossEnemy::CBossEnemyLife -= 1;
			if (CBossEnemy::CBossEnemyLife == 0)
			{
				//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
				if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
				{
					mEnabled = false;
					r.mEnabled = false;
					CSceneGame::ScoreCount += 5000;
				}
			}
			break;

		case EPLAYER:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			if (CSceneGame::Time != 0 && CSceneGame::Remain > 0)
			{
				CSceneGame::Remain -= 1;
			}
			break;
		}
		return true;
	}
	return false;
}
void CBossEnemy::Render() {
	if (mEnabled) {
		CRectangle::Render(Texture,145,185,224,183);
	}

}

//36
void CBossEnemy::Collision(CRectangle* i, CRectangle* y) {
	Collision(*y);
}