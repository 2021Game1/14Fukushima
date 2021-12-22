#include "CMapModel.h"
//標準入出力のインクルード
#include <stdio.h>

//モデルファイルの入力
//Load(モデルファイル名,マテリアルファイル名)
void CMapModel::Load(char* csv, char* mtl) {
	//ファイルポインタ変数の作成
	FILE* fp;

	//ファイルのオープン
	//fopen(ファイル名,モード)
	fp = fopen(csv, "r");
	//ファイルオープンエラーの判定
	//fpがNULLの時はエラー
	if (fp == NULL) {
		//コンソールにエラー出力して戻る
		printf("%s file open error\n", csv);
		return;
	}

	//ファイルからデータを入力
	//入力エリアを作成する
	char buf[256];
	//ファイルから1行入力
	//fgets(入力エリア,エリアサイズ,ファイルポインタ)
	//ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//数列からデータを9つ変数へ代入する
		//データを分割
		int seq[9];
		//ssccanf(数列,変換指定子,変数)
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4], &seq[5], &seq[6], &seq[7], &seq[8]);
		for (int i = 0; i < 9; i++) {
			switch (seq[i]) {
			case 0: {
				printf("%d\n", seq[i]);
				
			}
				  break;
			case 1: {
				printf("%d\n", seq[i]);
				
			}
				  break;

			case 2: {
				printf("%d\n", seq[i]);
				
			}
				  break;
			}
		}
		
	}

	//ファイルのクローズ
	fclose(fp);
	
}