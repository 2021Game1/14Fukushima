#include"CModel.h"
//標準入出力のインクルード
#include<stdio.h>

//モデルファイルの入力
//Load(モデルファイル名,マテリアルファイル名)
void CModel::Load(char* obj, char* mtl) {
	//ファイルポインタ変数の作成
	FILE* fp;
	//ファイルのオープン
	//fopen(ファイル名,モード)
	//オープン出来ない時はNULLを返す
	fp = fopen(mtl, "r");
	//ファイルオープンのエラーの判定
	//fpがNULLの時はエラー
	if (fp==NULL){
		//コンソールにエラーを出力して戻る
		printf("%s file open error\n",mtl);
		return;
	}
	//ファイルのオープン
	//fopen(ファイル名,モード)
	//オープン出来ない時はNULLを返す
	fp = fopen(obj, "r");
	//ファイルオープンのエラーの判定
	//fpがNULLの時はエラー
	if (fp == NULL) {
		//コンソールにエラーを出力して戻る
		printf("%s file open error\n", obj);
		return;
	}
	//ファイルからデータを入力
	// 入力エリアを作成する
	char buf[256];
	//ファイルから１行入力
	// fgets(入力エリア,エリアサイズ,ファイルポインタ)
	// ファイルの最後になるとNULLを返す
	while(fgets(buf, sizeof(buf), fp) != NULL) {
		//入力した値をコンソールに出力する
		printf("%s", buf);
	}
	//ファイルから１行入力
	// fgets(入力エリア,エリアサイズ,ファイルポインタ)
	// ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//入力した値をコンソールに出力する
		printf("%s", buf);
	}
	//ファイルのクローズ
	fclose(fp);

	
	
	
	
}
