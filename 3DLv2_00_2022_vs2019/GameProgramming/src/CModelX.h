#ifndef CMODELX_H
#define CMODELX_H

#define MODEL_FILE "res\\sample.blend.x"

//領域開放をマクロ化
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}
/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで確認する
*/

class CModelX {
	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の位置
public:
	CModelX();
	//ファイルの読み込み
	void Load(char* file);
	//単語の取り出し
	void GetToken();
};



#endif 

