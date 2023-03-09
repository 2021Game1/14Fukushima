#ifndef ENEMYDATA_H
#define ENEMYDATA_H



//�������ݒ�
#define ENEMY_INT_INITIALIZATION 0																//������
#define ENEMY_FLOAT_INITIALIZATION 0.0f															//���������_�̏�����

//�`��D��x�ݒ�
#define ENEMY_PRIORITY 80

//�G�p�����[�^�}�N��		
#define ENEMY_HP_MAX 150			//HP�̍ő�l
#define ENEMY_HP 150				//HP�ݒ�
#define ENEMY_DAMAGE_BODY 15		//�_���[�W(��)
#define ENEMY_ATTACK_DIS 3.2f		//�U���\�ɂȂ鋗��
#define ENEMY_SPEED_MOVE 0.1f		//�ʏ�ړ��̃X�s�[�h
#define ENEMY_SPEED_DASH 0.15f		//���s�̈ړ����x
#define ENEMY_SPEED_STOP 0.0f		//��~
#define ENEMY_WALK_DIS 30.0f		//���s���J�n���鋗��
#define ENEMY_SEARCH_DIS 60.0f		//���s���J�n���鋗��
#define ENEMY_WALK_DIS_MAX 50.0f	//���s�\�ȍő勗��
#define ENEMY_CHASE_DIS_MAX 80.0f   //���s�\�ȍő勗��
#define ENEMY_GRAVITY 0.9f			//�d��
#define ENEMY_RECEPTION 26.0f		//�����蔻��̎�t����
#define ENEMY_OUTRECEPTION 60.0f	//�����蔻��̎�t�I��

//�v���C���̃_���[�W�ݒ�
#define ENEMY_DAMAGE_ENEMYSP1 15						//�v���C���̍U��1�̃_���[�W	
#define ENEMY_DAMAGE_ENEMYSP2 10						//�v���C���̍U��2�̃_���[�W
#define ENEMY_DAMAGE_ENEMYSP3 20						//�v���C���̍U��3�̃_���[�W

//�G�̃A�j���[�V�����̃t���[���ݒ�
#define ENEMY_IDLE_ANIMATION_FRAME 60															//�ҋ@�̃A�j���[�V�����t���[���ݒ�
#define ENEMY_MOVE_ANIMATION_FRAME 60															//���s�̃A�j���[�V�����t���[���ݒ�
#define ENEMY_DASH_ANIMATION_FRAME 50															//���s�̃A�j���[�V�����t���[���ݒ�
#define ENEMY_ATTACK1_ANIMATION_FRAME 130														//�U��1�̃A�j���[�V�����t���[���ݒ�
#define ENEMY_ATTACK2_ANIMATION_FRAME 110														//�U��2�̃A�j���[�V�����t���[���ݒ�
#define ENEMY_ATTACK3_ANIMATION_FRAME 120														//�U��3�̃A�j���[�V�����t���[���ݒ�
#define ENEMY_KNOCKBACK_ANIMATION_FRAME 60														//�m�b�N�o�b�N�̃A�j���[�V�����t���[���ݒ�
#define ENEMY_DEATH_ANIMATION_FRAME 60															//���S�̃A�j���[�V�����t���[���ݒ�

//�G�̃A�j���[�V�����ԍ��̐ݒ�
#define ENEMY_ANIMATION_No_ATTACK_1 0		//�U���A�j���[�V����1�ԍ�
#define ENEMY_ANIMATION_No_ATTACK_2 1		//�U���A�j���[�V����2�ԍ�
#define ENEMY_ANIMATION_No_ATTACK_3 2		//�U���A�j���[�V����3�ԍ�
#define ENEMY_ANIMATION_No_WALK 3			//���s�A�j���[�V�����ԍ�
#define ENEMY_ANIMATION_No_DASH 4			//���s�A�j���[�V�����ԍ�
#define ENEMY_ANIMATION_No_IDLE 5			//�ҋ@�A�j���[�V�����ԍ�
#define ENEMY_ANIMATION_No_KNOCKBACK 6		//�m�b�N�o�b�N�A�j���[�V�����ԍ�
#define ENEMY_ANIMATION_No_DEATH 7			//���S�A�j���[�V�����ԍ�



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
#define ENEMY_PROBABILITY_LOW_SET1 0
#define ENEMY_PROBABILITY_MAX_SET1 60
#define ENEMY_PROBABILITY_LOW_SET2 61
#define ENEMY_PROBABILITY_MAX_SET2 100

#endif // !