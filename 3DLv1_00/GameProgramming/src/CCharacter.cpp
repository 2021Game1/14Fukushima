#include"CCharacter.h"

void CCharacter::Model(CModel* m)
{
	mpModel = m;
}

//�`�揈��
void CCharacter::Render()
{
	mpModel->Render(mMatrix);
}