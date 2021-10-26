#include "CMaterial.h"
//memset,strncpyのインクルード
#include <string.h>
#include "glut.h"

//デフォルトコンストラクタ
CMaterial::CMaterial() {
	//名前を0で埋め
	memset(mName, 0, sizeof(mName));
	//0で埋める
	memset(mDiffuse, 0, sizeof(mDiffuse));
}
//マテリアルを有効にする
void CMaterial::Enabled() {
	//拡散光の設定
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
}
//マテリアルの名前を取得
char* CMaterial::Name()
{
	return mName;
}
//マテリアルの名前を設定する
//Name(マテリアルの名前)
void CMaterial::Name(char* name)
{
	strncpy(mName, name, MATERIAL_NAME_LEN - 1);
}
//mDiffuse配列の取得
float* CMaterial::Diffuse()
{
	return mDiffuse;
}
