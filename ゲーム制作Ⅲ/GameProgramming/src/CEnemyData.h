#ifndef ENEMYDATA_H
#define ENEMYDATA_H

//�GUI
#define ENEMY_UI_HP_BACKBAR "res\\Ui\\Enemy_HP_BackBar.png"

/*�G�̃R���C�_�ݒ�*/
//�G�̐g��
#define ENEMY_COLCAPSULE_BODY_X 0.0f					//�J�v�Z���R���C�_��X���W�ݒ�
#define ENEMY_COLCAPSULE_BODY_TOP_Y 190.0f				//�J�v�Z���R���C�_���_Y���W�ݒ�
#define ENEMY_COLCAPSULE_BODY_BOTTOM_Y -12.0f			//�J�v�Z���R���C�_���Y���W�ݒ�
#define ENEMY_COLCAPSULE_BODY_Z 0.0f					//�J�v�Z���R���C�_��Z���W�ݒ�
#define ENEMY_COLCAPSULE_BODY_SIZE 1.2f					//�J�v�Z���R���C�_�̃T�C�Y�ݒ�

//�G�̓����蔻��p�R���C�_�T�C�Y�ݒ�
#define ENEMY_COLSPHERE_BODY_X 0.0f					//���R���C�_��X���W�ݒ�
#define ENEMY_COLSPHERE_BODY_Y 94.0f				//���R���C�_��Y���W�ݒ�
#define ENEMY_COLSPHERE_BODY_Z 5.0f					//���R���C�_��Z���W�ݒ�
#define ENEMY_COLSPHERE_BODY_SIZE 1.6f				//���R���C�_�̃T�C�Y�ݒ�

//�G�̉E��
#define ENEMY_COLSPHERE_RIGHTARM_SIZE 0.8f				//���R���C�_�̃T�C�Y�ݒ�

//�G�̍���
#define ENEMY_COLSPHERE_LEFTARM_SIZE 0.8f					//���R���C�_�̃T�C�Y�ݒ�

//�G��HP�t���[��,HP�Q�[�W���W,��,����
#define ENEMY_GAUGE_WID_MAX 100.0f										//�Q�[�W�̕��̍ő�l
#define ENEMY_GAUGE_HEIGHT 20.0f										//�Q�[�W�`�掞�̍���
#define ENEMY_GAUGE_HP_TOP -10.0f										//HP�Q�[�W�`�掞�̏���W
#define ENEMY_GAUGE_HP_BOTTOM (ENEMY_GAUGE_HP_TOP - ENEMY_GAUGE_HEIGHT) //HP�Q�[�W�`�掞�̉����W
#define ENEMY_GAUGE_HP_RATE 0.05f										//HP�Q�[�W�̐U���͈͂̂ӂ蕝�ݒ�
#define ENEMY_GAUGE_HP_Y 5.5f											//HP�Q�[�W�\����Y���W
#define ENEMY_GAUGE_HP_Z 0.0f											//HP�Q�[�W�\����Z���W
//������
#define ENEMY_SPEED 0.0f												//�G�̑��x������
#define ENEMY_TURNSPEED 0.0f											//�^�[�����x������
#define ENEMY_TURN_SET 180.0f											//��]�̏�����
#define ENEMY_TURN_SPEEDS_SET 0.3f										//��]���x�ݒ�
#define ENEMY_TRUN_CHECK_SPEEDS_SET 1.5f								//�}�ȉ�]���x�𒲐�
#define ENEMY_TRUN_CHECK_SET 0.0f										//��]���x�����o�������ݒ�
#define ENEMY_ATTACK_MAGNIFICATION 0.2									//�_���[�W�̔{���ݒ�

/*�G�f�[�^�e�[�u��*/

//�G�f�[�^�e�[�u��(�`���[�g���A����)
#define ENEMY_DATATABLE_TUTORIAL "res\\Enemy\\DataTable\\Tutorial\\EnemyData_Tutorial.txt"

//�G�f�[�^�e�[�u��(�{�Ԃ̃Q�[���łŎg�p����G1�ݒ�)
#define ENEMY_DATATABLE_MAINGAME1 "res\\Enemy\\DataTable\\MainGame\\EnemyData_MainGame1.txt"

//�G�f�[�^�e�[�u��(�{�Ԃ̃Q�[���łŎg�p����G2�ݒ�)
#define ENEMY_DATATABLE_MAINGAME2 "res\\Enemy\\DataTable\\MainGame\\EnemyData_MainGame2.txt"

/*�G�l�~�[�̃A�j���[�V�������f��*/

#define ENEMY_MODEL_FILE "res\\Enemy\\Mutant\\mutant.x"
#define ENEMY_ANIMATION_ATTACKSP1 "res\\Enemy\\Mutant\\Attack1.x"
#define ENEMY_ANIMATION_WALK "res\\Enemy\\Mutant\\Walk.x"
#define ENEMY_ANIMATION_DASH "res\\Enemy\\Mutant\\Dash.x"
#define ENEMY_ANIMATION_BACKSTEP "res\\Enemy\\Mutant\\BackStep.x"
#define ENEMY_ANIMATION_IDLE "res\\Enemy\\Mutant\\Idle.x"
#define ENEMY_ANIMATION_KNOCKBACK "res\\Enemy\\Mutant\\KnockBack.x"
#define ENEMY_ANIMATION_DEATH "res\\Enemy\\Mutant\\Death.x"

/*SE*/

//���SSE
#define SE_EMEMY_DEATH "res\\Se\\SE_Enemy_Death.wav"

/*�G�t�F�N�g*/

//�G�_���[�W�G�t�F�N�g
#define ENEMY_EF_DAMAGESP1 "Effect\\Enemy_DamageSp1.png"
#define ENEMY_EF_DAMAGESP2 "Effect\\Enemy_DamageSp2.png"
//�G�U���\������G�t�F�N�g
#define ENEMY_ATTACK_ACTION "Effect\\Enemy_Attack_Action.png"

/*UI*/

//�GUI
#define ENEMY_UI_HP_BACKBAR "res\\Ui\\Enemy_HP_BackBar.png"
#endif // !