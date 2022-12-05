#include "CRes.h"

CRes* CRes::mpRes_Instance = nullptr;												//���\�[�X�̃C���X�^���X�ϐ��̏�����

void CRes::Init() {
	mpRes_Instance = this;
	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
	//3D���f���t�@�C���̓ǂݍ���
	gPlayer_Model_Knight.Load(PLAYER_MODEL_FILE);
	//�v���C���̃A�j���[�V�����̒ǉ�
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP3);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_GUARD);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_GUARDIDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_DEATH);
	//�v���C����UI�̒ǉ�
	gCharacter_Ui_Hp_GreenGauge.Load(CHARACTER_UI_HP_GREENGAUGE);
	gCharacter_Ui_Hp_RedGauge.Load(CHARACTER_UI_HP_REDGAUGE);
	gPlayer_Ui_Hp_Frame.Load(PLAYER_UI_HP_FRAME);
	//�J����������
	Camera.Init();
	//�}�b�v���f���t�@�C���̓���
	gMap_Model.Load(MAP_MODEL_MAP);
	//�X�J�C���f���t�@�C���̓���
	gMap_Model_Sky.Load(MAP_MODEL_SKY);
	//�}�b�v�̃R���C�_�t�@�C���̓���
	gMap_Model_Collision.Load(MAP_COLLISION_MAP);
	//3D���f���t�@�C���̓ǂݍ���
	gEnemy_Model_Mutant.Load(ENEMY_MODEL_FILE);
	//�G�l�~�[�̃A�j���[�V�����̒ǉ�
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP1);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_ATTACKSP2);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);
	//�L�����N�^�Ƀ��f����ݒ�
	mPlayer.Init(&gPlayer_Model_Knight);
	//�G�̏����ݒ�
	mEnemy.Init(&gEnemy_Model_Mutant);
	mFont.LoadTexture("font\\FontG.png", 1, 4096 / 64);
	mMap.Model(&gMap_Model);
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &gMap_Model_Collision);
}
void CRes::Update() {
	//�L�����N�^�N���X�̍X�V
	mPlayer.Update();
	//�J�����N���X�̍X�V
	Camera.Update();
	//�J�����N���X�̕`��
	Camera.Render();
	//�s��ݒ�
	glMultMatrixf(gMatrix.M());
	//���_�ɃA�j���[�V�����K�p����
	gPlayer_Model_Knight.AnimeteVertex();
	//���f���`��
	mPlayer.Render();
	//�}�b�v���f���̕`��
	mMap.Render();
	gMap_Model_Sky.Render();
	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();
	//�Փˏ���
	CCollisionManager::Get()->Collision();
	//�G�̍X�V
	mEnemy.Update();
	//�G�̕`��
	mEnemy.Render();
	mPlayer.Render2D();
}
//�v���C���[�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CRes* CRes::GetInstance()
{
	return mpRes_Instance;
}

CText& CRes::GetInUiFont()
{
	return mFont;
}
CTexture& CRes::GetInUiHpGreenGauge()
{
	return gCharacter_Ui_Hp_GreenGauge;
}
CTexture& CRes::GetInUiHpRedGauge()
{
	return gCharacter_Ui_Hp_RedGauge;
}
CTexture& CRes::GetInUiHpFrame()
{
	return gPlayer_Ui_Hp_Frame;
}
