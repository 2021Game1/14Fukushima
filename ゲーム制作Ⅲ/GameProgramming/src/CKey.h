#ifndef CKEY_H
#define CKEY_H

//GetKeyState�֐��̃w�b�_�t�@�C��
#include <Windows.h>
/*
CKey�N���X
�L�[�{�[�h���͂��擾����
*/

#define KEY_NOWTIME 0.0f
#define KEY_OLDTIME 0.03f
#define KEY_NEXTBUTTONDOWNTIME 0.5f

class CKey {
public:
	
	/*
	Push��static(�X�^�e�B�b�N)���\�b�h
	key�̒l�̃L�[��������Ă����true���A
	������Ă��Ȃ����false��߂�
	*/
	static bool Push(char key);
	static bool Once(char key);
	static bool Double(char key);

private:
	static bool Flg[256];
	static int	Process;
	static float Key_NowTime;         //�ŏ��Ɉړ��{�^����������Ă���̌o�ߎ���
	static float Key_OldTime;         //�ȑO�̌o�ߎ���
	static float Key_NextButtonDownTime;    //�@���Ɉړ��{�^�����������܂ł̎���
};

#endif
