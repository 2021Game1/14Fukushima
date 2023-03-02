#ifndef PLAYERDATA_H
#define PLAYERDATA_H

//�������ݒ�
#define PLAYER_INT_INITIALIZATION 0																//������
#define PLAYER_FLOAT_INITIALIZATION 0.0f														//���������_�̏�����
//�`��D��x�ݒ�
#define PLAYER_PRIORITY 95																		//�`��D��x�̐ݒ�

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
#define PLAYER_GAUGE_HP_BOTTOM (PLAYER_GAUGE_HP_TOP-GAUGE_HEIGHT)								//HP�Q�[�W�`�掞�̉����W
#define PLAYER_GAUGE_HP_SHAKE_X -5																//HP�Q�[�W�̐U���̏���X���W�ݒ�
#define PLAYER_GAUGE_HP_SHAKE_RANGE_X 12														//HP�Q�[�W�̐U���͈͂�X���W�ݒ�											
#define PLAYER_GAUGE_HP_SHAKE_Y -2																//HP�Q�[�W�̐U���̏���Y���W�ݒ�
#define PLAYER_GAUGE_HP_SHAKE_RANGE_Y 2															//HP�Q�[�W�̐U���͈͂�Y���W�ݒ�
#define PLAYER_GAUGE_HP_RATE 0.05f																//HP�Q�[�W�̐U���͈͂̂ӂ蕝�ݒ�
#define PLAYER_TURN_SET 180.0f																	//��]�̏�����
#define PLAYER_TURN_SPEEDS_SET 0.3f																//��]���x�ݒ�
#define PLAYER_TRUN_CHECK_SPEEDS_SET 1.5f														//�}�ȉ�]���x�𒲐�
#define PLAYER_TRUN_CHECK_SET 0.0f																//��]���x�����o���J�����̉����ݒ�



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
#define PLAYER_COLSPHERE_SWORD_HEAD_X -13.0f			//���R���C�_��X���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_HEAD_Y 0.0f				//���R���C�_��Y���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_HEAD_Z 70.0f				//���R���C�_��Z���W�ݒ�
#define PLAYER_COLSPHERE_SWORD_SIZE 0.3					//���R���C�_�̃T�C�Y�ݒ�


//�v���C���̃Q�[���I�[�o�̗͐ݒ�
#define PLAYER_GAMEOVER_HP 0																	//�Q�[���I�[�o�ݒ�
//�v���C���̃p�����[�^�}�N��
#define PLAYER_HP_MAX 100																		//HP�̍ő�l
#define PLAYER_HP 100																			//HP�̐ݒ�
#define PLAYER_SPEED_DEFAULT 0.2f																//�X�s�[�h(�ʏ펞)
#define PLAYER_GRAVITY 0.9f																		//�d��
#define PLAYER_THRUST 0.9																		//����
#define PLAYER_SE 0.1																			//�v���C��SE�ݒ�
#define PLAYER_DAMAGE_SE 0.3																	//�v���C���_���[�WSE�ݒ�
#define PLAYER_RECEPTION 15																		//�L�[���͂̎�t����
#define PLAYER_INRECEPTION 	21.0f																//�����蔻��̎�t����															
#define PLAYER_OUTRECEPTION 60.0f																//�����蔻��̏I������
#define PLAYER_ATTACK_DIS 2.2f																	//�G�ɍU�����Ǐ]�\�ɂȂ鋗��

//�v���C���̃A�j���[�V�����̃t���[���ݒ�
#define PLAYER_IDLE_ANIMATION_FRAME 20
#define PLAYER_MOVE_ANIMATION_FRAME 45															//�ړ��̃A�j���[�V�����t���[���ݒ�
#define PLAYER_AVOIDANCE_ANIMATION_FRAME 50														//����̃A�j���[�V�����t���[���ݒ�
#define PLAYER_ATTACK1_ANIMATION_FRAME 70														//�U��1�̃A�j���[�V�����t���[���ݒ�
#define PLAYER_ATTACK2_ANIMATION_FRAME 90														//�U��2�̃A�j���[�V�����t���[���ݒ�
#define PLAYER_ATTACK3_ANIMATION_FRAME 110														//�U��3�̃A�j���[�V�����t���[���ݒ�
#define PLAYER_KNOCKBACK_ANIMATION_FRAME 60														//�m�b�N�o�b�N�̃A�j���[�V�����t���[���ݒ�
#define PLAYER_DEATH_ANIMATION_FRAME 60															//���S�̃A�j���[�V�����t���[���ݒ�

//�v���C���̃_���[�W�ݒ�
#define PLAYER_DAMAGE_ENEMYSP1 15						//�G�̍U��1�̃_���[�W	
#define PLAYER_DAMAGE_ENEMYSP2 10						//�G�̍U��2�̃_���[�W
#define PLAYER_DAMAGE_ENEMYSP3 20						//�G�̍U��3�̃_���[�W

//�v���C���̃A�j���[�V�����ԍ��̐ݒ�
#define PLAYER_ANIMATION_No_MOVE 0			//�ړ��A�j���[�V�����ԍ�
#define PLAYER_ANIMATION_No_ATTACK_1 1		//�U���A�j���[�V����1�ԍ�
#define PLAYER_ANIMATION_No_ATTACK_2 2		//�U���A�j���[�V����2�ԍ�
#define PLAYER_ANIMATION_No_ATTACK_3 3		//�U���A�j���[�V����3�ԍ�
#define PLAYER_ANIMATION_No_AVOIDANCE 4		//����A�j���[�V�����ԍ�
#define PLAYER_ANIMATION_No_IDLE 5			//�ҋ@�A�j���[�V�����ԍ�
#define PLAYER_ANIMATION_No_KNOCKBACK 6		//�m�b�N�o�b�N�A�j���[�V�����ԍ�
#define PLAYER_ANIMATION_No_DEATH 7			//���S�A�j���[�V�����ԍ�

#endif // !PLAYERDATA_H

