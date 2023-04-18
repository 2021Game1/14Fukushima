#ifndef PLAYERDATA_H
#define PLAYERDATA_H

//�������ݒ�
#define PLAYER_INT_INITIALIZATION 0																//������
#define PLAYER_FLOAT_INITIALIZATION 0.0f														//���������_�̏�����

//SE�E�v���C��
#define SE_PLAYER_ATTACK1 "res\\Se\\SE_Player_AttackSp1.wav"
#define SE_PLAYER_ATTACK2 "res\\Se\\SE_Player_AttackSp2.wav"
#define SE_PLAYER_WALK "res\\Se\\SE_Player_Walk.wav"
#define SE_PLAYER_DEATH "res\\Se\\SE_Player_Death.wav"
//SE�E�G
#define SE_ENEMY_ATTACK "res\\Se\\SE_Enemy_AttackSp.wav" 


/*�v���C���̃R���C�_�ݒ�*/

//�v���C���[�̐g��
#define PLAYER_COLCAPSULE_BODY_X 0.0f					//�J�v�Z���R���C�_��X���W�ݒ�
#define PLAYER_COLCAPSULE_BODY_TOP_Y 95.0f				//�J�v�Z���R���C�_��Y���W�ݒ�
#define PLAYER_COLCAPSULE_BODY_BOTTOM_Y -134.8f			//�J�v�Z���R���C�_��Y���W�ݒ�
#define PLAYER_COLCAPSULE_BODY_Z 0.0f					//�J�v�Z���R���C�_��Z���W�ݒ�
#define PLAYER_COLCAPSULE_BODY_SIZE 0.7f				//�J�v�Z���R���C�_�̃T�C�Y�ݒ�

//�v���C���̓����蔻��
#define PLAYER_COLSPHERE_BODY_SIZE 0.9					//���R���C�_�̃T�C�Y�ݒ�

//�v���C���̏�
#define PLAYER_COLSPHERE_SHIELD_X 0.0f					//���R���C�_��X���W
#define PLAYER_COLSPHERE_SHIELD_Y 0.0f					//���R���C�_��Y���W
#define PLAYER_COLSPHERE_SHIELD_Z -5.0f					//���R���C�_��Z���W
#define PLAYER_COLSPHERE_SHIELD_SIZE 0.5				//���R���C�_�̃T�C�Y

//�v���C���̌�
#define PLAYER_COLSPHERE_SWORD_X -13.0f				//���R���C�_��X���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_Y 0.0f				//���R���C�_��Y���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_Z 70.0f				//���R���C�_��Z���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_SIZE 0.35			//���R���C�_�̃T�C�Y�ݒ�

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
#define PLAYER_GAUGE_HP_BOTTOM (PLAYER_GAUGE_HP_TOP-GAUGE_HEIGHT)

#endif // !PLAYERDATA_H

