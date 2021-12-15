#include"CSceneScreen.h"

#include"CTexture.h"


//�X�N���[���̃|�C���^
CSceneScreen* CSceneScreen::spInstance = nullptr;

CSceneScreen::CSceneScreen()
{
	Screen.Load("screen.tga");
	spInstance = this;
	w = 510;
	h = 800;
	mTag = ESCREEN;
}

void CSceneScreen::Update()
{
	y += speed;
		if (y == -1200)
			y = 1736;
}

void CSceneScreen::Render()
{
	if (mEnabled)
	{
		CRectangle::Render(Screen, 0, 255, 255, 0);
	}
		
	
	

}
bool CSceneScreen::Collision(CRectangle& r) {
	//mEnabled��false�Ȃ�߂�
	if (!r.mEnabled)return false;
	if (!mEnabled) return false;
	//�e��Collision���\�b�h���Ăяo��
	if (CRectangle::Collision(r)) {
		switch (r.mTag) {
		case EPLAYERBULLET:
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			r.mEnabled = false;
		case EPLAYER:
			//�v���C���[�ɓ�����ƁA�����ɂ���
			mEnabled = false;
			break;
		}
		return true;
	}
	return false;
}
