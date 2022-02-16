#include "glut.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include "CSceneManager.h"

// �e�N�X�`���N���X�̃C���N���[�h
#include "CTexture.h"
CTexture Texture; //�S�̂̉摜
CTexture BulletTexture; //�e�̉摜
CTexture ItemTexture;//�A�C�e���̉摜
CTexture MoonBlock;//���[���u���b�N
CTexture Effect;//�G�t�F�N�g
//�V�[���}�l�[�W���̃C���X�^���X
CSceneManager SceneManager;

//Init�֐�
//�ŏ��Ɉ�x�����Ă΂��֐�
void Init() {
	//
	Texture.Load("res\\GameImage.tga");
	BulletTexture.Load("res\\BulletImage.tga");
	ItemTexture.Load("res\\Image.tga");
	MoonBlock.Load("res\\moonBLock.tga");
	Effect.Load("res\\exp.tga");
	//�����摜�̓ǂݍ���
	CText::mFont.Load("res\\font.tga");
	//�V�[���}�l�[�W���̏�����
	SceneManager.Init();
}
//Update�֐�
//�v���O�����̎��s���A�J��Ԃ��Ă΂��֐�
void Update() {
	//�V�[���}�l�[�W���̍X�V
	SceneManager.Update();
}