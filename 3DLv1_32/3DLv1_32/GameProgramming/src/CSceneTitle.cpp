//#include"CSceneTitle.h"
//
//void CSceneTitle::Render()
//{
//	//�e�̕`�揈��
//	CCharacter::Render();
//
//	//2D�̕`��J�n
//	CUtil::Start2D(-400, 400, -300, 300);
//	//�`��F�̐ݒ�(�ΐF�̔�����)
//	glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
//	//������ҏW�G���A�̍쐬
//	char buf[64];
//
//	//Y���W�̕\��
//	//������̐ݒ�
//	sprintf(buf, "PY:%7.2f", mPosition.Y());
//	//������̕`��
//	mText.DrawString(buf, 100, 30, 8, 16);
//
//	//X����]�l�̕\��
//	//������̐ݒ�
//	sprintf(buf, "RX:%7.2f", mRotation.X());
//	//������̕`��
//	mText.DrawString(buf, 100, 0, 8, 16);
//
//	//Y����]�l�̕\��
//	//������̐ݒ�
//	sprintf(buf, "RY:%7.2f", mRotation.Y());
//	//������̕`��
//	mText.DrawString(buf, 100, -100, 8, 16);
//
//	//2D�̕`��I��
//	CUtil::End2D();
//}