#ifndef CKEY_H
#define CKEY_H

//GetKeyState�֐��̃w�b�_�t�@�C��
#include <Windows.h>
#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44
/*
CKey�N���X
�L�[�{�[�h���͂��擾����
*/


class CKey {
public:
	
	/*
	Push��static(�X�^�e�B�b�N)���\�b�h
	key�̒l�̃L�[��������Ă����true���A
	������Ă��Ȃ����false��߂�
	*/
	static bool Push(char key);
	static bool Once(char key);

private:
	static bool Flg[256];
};

#endif
