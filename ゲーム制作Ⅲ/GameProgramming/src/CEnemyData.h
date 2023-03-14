#ifndef ENEMYDATA_H
#define ENEMYDATA_H

//�������ݒ�
#define ENEMY_INT_INITIALIZATION 0																//������
#define ENEMY_FLOAT_INITIALIZATION 0.0f															//���������_�̏�����
#define ENEMY_NUM 5

/*�G�̃R���C�_�ݒ�*/
//�G�̐g��
#define ENEMY_COLCAPSULE_BODY_X 0.0f					//�J�v�Z���R���C�_��X���W�ݒ�
#define ENEMY_COLCAPSULE_BODY_TOP_Y 190.0f				//�J�v�Z���R���C�_���_Y���W�ݒ�
#define ENEMY_COLCAPSULE_BODY_BOTTOM_Y -31.0f			//�J�v�Z���R���C�_���Y���W�ݒ�
#define ENEMY_COLCAPSULE_BODY_Z 0.0f					//�J�v�Z���R���C�_��Z���W�ݒ�
#define ENEMY_COLCAPSULE_BODY_SIZE 1.2f					//�J�v�Z���R���C�_�̃T�C�Y�ݒ�

//�G�̓����蔻��p�R���C�_�T�C�Y�ݒ�
#define ENEMY_COLSPHERE_BODY_X 0.0f					//���R���C�_��X���W�ݒ�
#define ENEMY_COLSPHERE_BODY_Y 94.0f				//���R���C�_��Y���W�ݒ�
#define ENEMY_COLSPHERE_BODY_Z 5.0f					//���R���C�_��Z���W�ݒ�
#define ENEMY_COLSPHERE_BODY_SIZE 1.3f				//���R���C�_�̃T�C�Y�ݒ�

//�G�̉E��
#define ENEMY_COLSPHERE_RIGHTARM_SIZE 0.7f				//���R���C�_�̃T�C�Y�ݒ�

//�G�̍���
#define ENEMY_COLSPHERE_LEFTARM_SIZE 0.7f					//���R���C�_�̃T�C�Y�ݒ�
//�G��HP�t���[��,HP�Q�[�W���W,��,����
#define ENEMY_GAUGE_WID_MAX 100.0f	//�Q�[�W�̕��̍ő�l
#define ENEMY_GAUGE_HEIGHT 20.0f //�Q�[�W�`�掞�̍���
#define ENEMY_GAUGE_HP_TOP -10.0f //HP�Q�[�W�`�掞�̏���W
#define ENEMY_GAUGE_HP_BOTTOM (ENEMY_GAUGE_HP_TOP - ENEMY_GAUGE_HEIGHT) //HP�Q�[�W�`�掞�̉����W
#define ENEMY_GAUGE_HP_RATE 0.05f																//HP�Q�[�W�̐U���͈͂̂ӂ蕝�ݒ�
//������
#define ENEMY_SPEED 0.0f //�G�̑��x������
#define ENEMY_TURNSPEED 0.0f //�^�[�����x������
#define ENEMY_TURN_SET 180.0f																	//��]�̏�����
#define ENEMY_TURN_SPEEDS_SET 0.3f																//��]���x�ݒ�
#define ENEMY_TRUN_CHECK_SPEEDS_SET 1.5f														//�}�ȉ�]���x�𒲐�
#define ENEMY_TRUN_CHECK_SET 0.0f																//��]���x�����o�������ݒ�


#endif // !