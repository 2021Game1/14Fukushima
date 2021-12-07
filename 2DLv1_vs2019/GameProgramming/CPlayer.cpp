#include "CPlayer.h"
#include "CKey.h"
//37
#include "CBullet.h"

//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;
CPlayer* CPlayer::spInstance = nullptr;

int CPlayer::mPlayer = 0;

CPlayer::CPlayer()
: mFx(0.0f), mFy(1.0f)
, FireCount(0)
{
	mTag = EPLAYER;
	mEnabled = true;
	spInstance = this;
	
}

void CPlayer::Update() {
	//mEnabled��false�Ȃ�߂�
	//static���\�b�h�͂ǂ�����ł��Ăׂ�
	if (CSceneGame::Remain > 0)
	{
		if (CKey::Push('A')) {
			if (CSceneGame::EnemyCount < 14)
			{
				x -= 3;
			}
			
			if (CSceneGame::EnemyCount >= 14)
			{
				x -= 5;
			}
			if (x - w < -400) {
				x = -400 + w;
			}
			
		}
		if (CKey::Push('D')) {
			if (CSceneGame::EnemyCount < 14)
			{
				x += 3;
			}
			if (CSceneGame::EnemyCount >= 14)
			{
				x += 5;
			}
			if (x + w > 400) {
				x = 400 - w;
			}
		}
		if (CKey::Push('W')) {
			y += 3;
			if (CSceneGame::EnemyCount < 14)
			{
				mFx = 0;
				mFy = 1;
			}
			
			if (CSceneGame::EnemyCount >= 14) {
				mFx = 0;
				mFy = 2;
			}
			if (y + h > 300) {
				y = 300 - h;
			}
		}
		if (CKey::Push('S')) {
			y -= 3;
			if (y - h < -300) {
				y = -300 + h;
			}
		}

		if (CSceneGame::EnemyCount < 14)
		{
			//37
					//�X�y�[�X�L�[�Œe����
					//0���傫���Ƃ�1���Z����
			if (FireCount > 0) {
				FireCount--;
			}
			//FireCont��0�ŁA���A�X�y�[�X�L�[�Œe����
			else if (CKey::Once(' ')) {
				CBullet* Bullet = new CBullet();
				//���ˈʒu�̐ݒ�
				Bullet->x = x;
				Bullet->y = y;
				//�ړ��̒l��ݒ�
				Bullet->mFx = mFx * 5;
				Bullet->mFy = mFy * 5;
				//�L���ɂ���
				Bullet->mEnabled = true;
				//�v���C���[�̒e��ݒ�
				Bullet->mTag = CRectangle::EPLAYERBULLET;

				FireCount = 20;
			}

		}
	}
		
	//mEnabled��false�Ȃ�߂�
	//static���\�b�h�͂ǂ�����ł��Ăׂ�
	if (CSceneGame::Remain > 0){
		//37
		//�X�y�[�X�L�[�Œe����
		//0���傫���Ƃ�1���Z����
		if (FireCount > 0) {
			FireCount--;
		}
		if (CSceneGame::EnemyCount >= 14){
			//FireCont��0�ŁA���A�X�y�[�X�L�[�Œe����
				if (CKey::Once(' ')) {
				CBullet* Bullet2 = new CBullet();
				//���ˈʒu�̐ݒ�
				Bullet2->x = x;
				Bullet2->y = y;
				//�ړ��̒l��ݒ�
				Bullet2->mFx = mFx * 5;
				Bullet2->mFy = mFy * 5;
				//�L���ɂ���
				Bullet2->mEnabled = true;
				//�v���C���[�̒e��ݒ�
				Bullet2->mTag = CRectangle::EPLAYERBULLET;

				FireCount = 15;
				}

		}
		
	}
	
}
	

void CPlayer::Render() {
	if (CSceneGame::Remain > 0 )
	{
		CRectangle::Render(Texture, 65, 115, 85, 25);
	}
}
	

//36
void CPlayer::Collision(CRectangle* ri, CRectangle* ry) {
	if ((*ry).mTag == EBOSSENEMY) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			int mx, my;
			if (CRectangle::Collision(ry, &mx, &my)) {
				//abs(x)x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my)) {
					//Rect��X�����ړ�����
					x += mx;
				}
				else {
					//Rect��y�����ړ�����
					y += my;
				}
			}
		}
	}
	if ((*ry).mTag == EENEMYBULLET) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				(*ry).mEnabled = false;
				if (CSceneGame::Time != 0) {
					CSceneGame::Remain -= 1;
				}
			}
		}
	}
	if ((*ry).mTag == EENEMYITEM) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				(*ry).mEnabled = false;
				
			}
		}
	}
	if ((*ry).mTag == EBOSSBULLET) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			if (CRectangle::Collision(*ry)) {
				(*ry).mEnabled = false;
				if (CSceneGame::Time != 0) {
					CSceneGame::Remain -= 1;
				}
			}
		}
	}
	if ((*ry).mTag == EBLOCK) {
		if ((*ry).mEnabled && (*ri).mEnabled) {
			int mx, my;
			if (CRectangle::Collision(ry, &mx, &my)) {
				//abs(x)x�̐�Βl�����߂�
				//�ړ��ʂ����Ȃ����������ړ�������
				if (abs(mx) < abs(my)) {
					//Rect��X�����ړ�����
					x += mx;
				}
				else {
					//Rect��y�����ړ�����
					y += my;
				}
			}
		}
	}
}

