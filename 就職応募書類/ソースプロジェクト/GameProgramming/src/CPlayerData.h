#ifndef PLAYERDATA_H
#define PLAYERDATA_H

//�������ݒ�
#define PLAYER_INT_INITIALIZATION 0																//������
#define PLAYER_FLOAT_INITIALIZATION 0.0f														//���������_�̏�����

//�v���C��UI
#define PLAYER_UI_HP_FRAME "res\\Ui\\Player_HP_Frame.png"

/*�f�[�^�e�[�u��*/

//�v���C���̃f�[�^�e�[�u��
#define PLAYER_DATATABLE "res\\Player\\DataTable\\PlayerData.txt"

/*�v���C���̃A�j���[�V�������f��*/

#define PLAYER_MODEL_FILE "res\\Player\\Paladin\\paladin.x"
#define PLAYER_ANIMATION_ATTACKSP1 "res\\Player\\Paladin\\Attack1.x"
#define PLAYER_ANIMATION_ATTACKSP1_IDLE "res\\Player\\Paladin\\Attack1_Idle.x"
#define PLAYER_ANIMATION_ATTACKSP2 "res\\Player\\Paladin\\Attack2.x"
#define PLAYER_ANIMATION_ATTACKSP2_IDLE "res\\Player\\Paladin\\Attack2_Idle.x"
#define PLAYER_ANIMATION_AVOIDANCE "res\\Player\\Paladin\\Avoidance.x" 
#define PLAYER_ANIMATION_IDLE "res\\Player\\Paladin\\Idle.x"
#define PLAYER_ANIMATION_KNOCKBACK "res\\Player\\Paladin\\KnockBack.x"
#define PLAYER_ANIMATION_DEATH "res\\Player\\Paladin\\Death.x"

/*SE�ݒ�*/

//SE�E�v���C��
#define SE_PLAYER_ATTACK1 "res\\Se\\SE_Player_AttackSp1.wav"	//�U��1��SE
#define SE_PLAYER_ATTACK2 "res\\Se\\SE_Player_AttackSp2.wav"	//�U��2��SE
#define SE_PLAYER_WALK "res\\Se\\SE_Player_Walk.wav"			//���s����SE
#define SE_PLAYER_DEATH "res\\Se\\SE_Player_Death.wav"			//���S����SE
//SE�E�G
#define SE_ENEMY_ATTACK "res\\Se\\SE_Enemy_AttackSp.wav"		//��e����SE

/*�v���C���̃R���C�_�ݒ�*/

//�v���C���̓�
#define PLAYER_COLSPHER_HEAD_X 0.0f					//���R���C�_��X���W�ݒ�
#define PLAYER_COLSPHER_HEAD_Y 16.0f				//���R���C�_��Y���W�ݒ�
#define PLAYER_COLSPHER_HEAD_Z 0.0f					//���R���C�_��Z���W�ݒ�
#define PLAYER_COLSPHER_HEAD_SIZE 0.7f				//���R���C�_�T�C�Y

//�v���C���[�̐g��
#define PLAYER_COLCAPSULE_BODY_X 0.0f				//�J�v�Z���R���C�_��X���W�ݒ�
#define PLAYER_COLCAPSULE_BODY_TOP_Y 95.0f			//�J�v�Z���R���C�_��Y���W�ݒ�
#define PLAYER_COLCAPSULE_BODY_BOTTOM_Y -134.8f		//�J�v�Z���R���C�_��Y���W�ݒ�
#define PLAYER_COLCAPSULE_BODY_Z 0.0f				//�J�v�Z���R���C�_��Z���W�ݒ�
#define PLAYER_COLCAPSULE_BODY_SIZE 0.7f			//�J�v�Z���R���C�_�̃T�C�Y�ݒ�

//�v���C���[�̉����g
#define PLAYER_COLSPHERE_LOWERBODY_X 0.0f			//���R���C�_��X���W�ݒ�
#define PLAYER_COLSPHERE_LOWERBODY_Y 5.0f		//���R���C�_��Y���W�ݒ�
#define PLAYER_COLSPHERE_LOWERBODY_Z 0.0f			//���R���C�_��Z���W�ݒ�
#define PLAYER_COLSPHERE_LOWERBODY_SIZE 0.3f			//���R���C�_�̃T�C�Y�ݒ�

//�v���C���̓����蔻��
#define PLAYER_COLSPHERE_BODY_SIZE 0.9				//���R���C�_�̃T�C�Y�ݒ�

//�v���C���̌�
#define PLAYER_COLSPHERE_SWORD_X -13.0f				//���R���C�_��X���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_Y 0.0f				//���R���C�_��Y���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_Z 70.0f				//���R���C�_��Z���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_SIZE 0.35			//���R���C�_�̃T�C�Y�ݒ�

/*�v���C����UI�ݒ�*/

//�v���C����HP�t���[��,HP�Q�[�W���W,��,����
#define PLAYER_GAUGE_FRAME_TEX_WID 480															//�Q�[�W�g�̉摜�̕�
#define PLAYER_GAUGE_FRAME_TEX_HEI 80															//�Q�[�W�g�̉摜�̍���
#define PLAYER_GAUGE_FRAME_TEX_FIRST_WID 0														//�Q�[�W�g�̉摜�`��̕�
#define PLAYER_GAUGE_FRAME_TEX_FIRST_HEI 10														//�Q�[�W�g�̉摜�`��̍���
#define PLAYER_GAUGE_FRAME_LEFT 0																//�Q�[�W�g�����W
#define PLAYER_GAUGE_FRAME_RIGHT 380															//�Q�[�W�g�E���W
#define PLAYER_GAUGE_FRAME_TOP PLAYER_GAUGE_FRAME_TEX_HEI										//�Q�[�W�g����W
#define PLAYER_GAUGE_FRAME_BOTTOM (PLAYER_GAUGE_FRAME_TOP-PLAYER_GAUGE_FRAME_TEX_HEI)			//�Q�[�W�g�����W
#define PLAYER_GAUGE_LEFT 0																		//�Q�[�W�`�掞�̍����W
#define PLAYER_GAUGE_WID_MAX 380																//�Q�[�W�̕��̍ő�l
#define GAUGE_HEIGHT 20																			//�Q�[�W�`�掞�̍���
#define PLAYER_GAUGE_HP_TOP 30																	//HP�Q�[�W�`�掞�̏���W
#define PLAYER_GAUGE_HP_BOTTOM (PLAYER_GAUGE_HP_TOP-GAUGE_HEIGHT)								//HP�Q�[�W�`�掞�̒�Ӎ��W

#endif // !PLAYERDATA_H

