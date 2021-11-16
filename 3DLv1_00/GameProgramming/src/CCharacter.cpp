#include"CCharacter.h"

void CCharacter::Model(CModel* m)
{
	mpModel = m;
}

//•`‰æˆ—
void CCharacter::Render()
{
	mpModel->Render(mMatrix);
}