#ifndef CSCENE_H
#define CSCENE_H

/*
�V�[���̊��N���X
*/
class CScene {
public:
	enum class EScene {
		EGAME,		  //�Q�[��
		ETUTORIAL,	  //�`���[�g���A��
		ESCENESELECT, //�V�[���Z���N�g
		ETITLE, 	  //�^�C�g��
	};
	EScene mScene;
	//virtual ���z�֐�
	//�|�����[�t�B�Y���̎���
	//=0 �������z�֐��̐ݒ�
	virtual void Init() = 0;	//�������z�֐� ����������
	virtual void Update() = 0; //�������z�֐� �X�V����
	virtual void Render() = 0; //�������z�֐� �`�揈��
	////���̃V�[���̎擾
	virtual EScene GetNextScene() = 0;
	virtual ~CScene() {}	//�f�X�g���N�^�̒�`
};


#endif
