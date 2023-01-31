#include "CRes.h"

CRes* CRes::mpRes_Instance = nullptr;												//���\�[�X�̃C���X�^���X�ϐ��̏�����

void CRes::Init() {
	mpRes_Instance = this;
	//BGM�̓ǂݍ���
	Game_Bgm.Load(BGM_GAME);
	Title_Bgm.Load(BGM_TITLE);
	//�v���C��SE
	Se_Player_AttackSp1.Load(SE_PLAYER_ATTACK1);
	Se_Player_AttackSp2.Load(SE_PLAYER_ATTACK2);
	Se_Player_AttackSp3.Load(SE_PLAYER_ATTACK3);
	Se_Player_Walk.Load(SE_PLAYER_WALK);
	Se_Player_Death.Load(SE_PLAYER_DEATH);
	//�GSE
	Se_Enemy_AttackSp.Load(SE_ENEMY_ATTACK);
	Se_Enemy_Death.Load(SE_EMEMY_DEATH);

	//3D���f���t�@�C���̓ǂݍ���
	gPlayer_Model_Knight.Load(PLAYER_MODEL_FILE);
	//�v���C���̃A�j���[�V�����̒ǉ�
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP1);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP2);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_ATTACKSP3);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_IDLE);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_KNOCKBACK);
	gPlayer_Model_Knight.AddAnimationSet(PLAYER_ANIMATION_DEATH);
	//�v���C���K�[�h�A�N�V�����G�t�F�N�g���f��
	gPlayer_GuardSP_Model.Load(PLAYER_MODEL_ACTION_GUARDSP);
	//�^�C�g���摜�̒ǉ�
	gTitle_Image.Load2D(TITLE_IMAGE);
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
//�^�C�g���摜�̎擾
CTexture& CRes::GetInTitleImage()
{
	return gTitle_Image;
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
//�v���C���̎a��SE1���擾����
CSound& CRes::GetinPlayerSeAttackSp1() 
{
	return Se_Player_AttackSp1;
}
//�v���C���̎a��SE2���擾����
CSound& CRes::GetinPlayerSeAttackSp2() 
{
	return Se_Player_AttackSp2;
}
//�v���C���̎a��SE3���擾����
CSound& CRes::GetinPlayerSeAttackSp3() 
{
	return Se_Player_AttackSp3;
}
//�v���C���̕��sSE���擾
CSound& CRes::GetinPlayerSeWalk() 
{
	return Se_Player_Walk;
}
//�v���C���̎��SSE���擾
CSound& CRes::GetinPlayerSeDeath()
{
	return Se_Player_Death;
}
//�G�̍U��SE���擾����
CSound& CRes::GetinEnemySeAttackSp() 
{
	return Se_Enemy_AttackSp;
}
//�G�̎��SSE���擾����
CSound& CRes::GetinEnemySeDeath()
{
	return Se_Enemy_Death;
}
//BGM�̎擾
//�^�C�g��BGM�̎擾
CSound& CRes::GetinSoundBgmTitle()
{
	return Title_Bgm;
}
//�Q�[��BGM�̎擾
CSound& CRes::GetinSoundBgmGame() 
{
	return Game_Bgm;
}