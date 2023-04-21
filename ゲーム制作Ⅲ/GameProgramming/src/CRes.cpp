#include "CRes.h"

CRes* CRes::mpRes_Instance = nullptr;												//���\�[�X�̃C���X�^���X�ϐ��̏�����

void CRes::Init() {
	mpRes_Instance = this;
	//BGM�̓ǂݍ���
	Game_Bgm.Load(BGM_GAME);

	//3D���f���t�@�C���̓ǂݍ���
	gPlayer_Model_Knight.Load(PLAYER_MODEL_FILE);
	//�v���C���̃A�j���[�V�����̒ǉ�
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_AVOIDANCE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_DEATH);
	//�Q�[���N���A�摜�̒ǉ�
	gGameClear_Image.Load2D(GAMECLEAR_IMAGE);
	//�Q�[���I�[�o�[�摜�̒ǉ�
	gGameOver_Image.Load2D(GAMEOVER_IMAGE);
	//�L�����N�^��UI�ǉ�
	gCharacter_Ui_Hp_GreenGauge.Load2D(CHARACTER_UI_HP_GREENGAUGE);
	gCharacter_Ui_Hp_RedGauge.Load2D(CHARACTER_UI_HP_REDGAUGE);
	//�v���C����UI�̒ǉ�
	gPlayer_Ui_Hp_Frame.Load2D(PLAYER_UI_HP_FRAME);
	//�G��UI�̒ǉ�
	gEnemy_Ui_Hp_BackBar.Load2D(ENEMY_UI_HP_BACKBAR);
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
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_WALK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DASH);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_BACKSTEP);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_IDLE);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_KNOCKBACK);
	gEnemy_Model_Mutant.AddAnimationSet(ENEMY_ANIMATION_DEATH);
	//�L�����N�^�Ƀ��f����ݒ�
	mPlayer.Init(&gPlayer_Model_Knight);
	//�G�̏����ݒ�
	mEnemy.Init(&gEnemy_Model_Mutant);
	mFont.LoadTexture("Font\\FontG.png", 1, 4096 / 64);
	mMap.Model(&gMap_Model);
	mMap_Sky.Model(&gMap_Model_Sky);
	//�}�b�v�̈ړ��s��
	mBackGroundMatrix.Translate(0.0f, 0.0f, 0.1f);
	//�e�C���X�^���X�Ɛe�s��͂Ȃ�
	mColliderMesh.Set(nullptr, &mBackGroundMatrix, &gMap_Model_Collision);
}
void CRes::Update() {

}
//���\�[�X�̃|�C���^��Ԃ����ƂŁA���W�Ȃǂ��Q�Ƃł���悤�ɂȂ�
CRes* CRes::GetInstance()
{
	return mpRes_Instance;
}
//�t�H���g�̎擾
CText& CRes::GetInUiFont()
{
	return mFont;
}
//�N���A��ʂ̎擾
CTexture& CRes::GetinGameClearImage()
{
	return gGameClear_Image;
}
//�Q�[���I�[�o�[��ʂ̎擾
CTexture& CRes::GetinGameOverImage()
{
	return gGameOver_Image;
}
//��HP�o�[�̎擾
CTexture& CRes::GetInUiHpGreenGauge()
{
	return gCharacter_Ui_Hp_GreenGauge;
}
//��HP�o�[�̎擾
CTexture& CRes::GetInUiHpRedGauge()
{
	return gCharacter_Ui_Hp_RedGauge;
}
//�v���C����HP�O�g�̎擾
CTexture& CRes::GetInPlayerUiHpFrame()
{
	return gPlayer_Ui_Hp_Frame;
}
//�G��HP�o�[�̔w�i�擾
CTexture& CRes::GetInEnemyUiHpBackBar()
{
	return gEnemy_Ui_Hp_BackBar;
}
//�Q�[��BGM�̎擾
CSound& CRes::GetinSoundBgmGame() 
{
	return Game_Bgm;
}
