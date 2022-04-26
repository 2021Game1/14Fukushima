#include <stdio.h>
#include <string.h>
#include "CModelX.h"
#include "glut.h"



CModelX::CModelX() 
	:mpPointer(nullptr)
{
	//mTokenを初期化
	memset(mToken, 0, sizeof(mToken));
}

void CModelX::Load(char* file) {
	//
	//ファイルサイズを取得
	//
	FILE* fp;	//ファイルポインタ
	fp = fopen(file, "rb");//ファイルポインタ変数の作成
	if (fp == NULL) {
		printf("fopen error:%s\n",file);
		return;
	}
	//ファイルの最後へ移動
	fseek(fp, 0L, SEEK_END);
	//ファイルサイズの取得
	int size = ftell(fp);
	//ファイルサイズ＋1バイト分の領域を確保
	char* buf = mpPointer = new char[size + 1];
	//
	//ファイルから3Dモデルのデータを読み込む
	//
	//ファイルの先頭へ移動
	fseek(fp, 0L, SEEK_SET);
	//確保した領域にファイルサイズ分のデータを読み込む
	fread(buf, size, 1, fp);
	printf("%s", buf);
	//最後に\0を設定する(文字列の終端)
	buf[size] = '\0';
	fclose(fp);		//ファイルをクローズする

	SAFE_DELETE_ARRAY(buf);	//確保した領域を開放する
}

