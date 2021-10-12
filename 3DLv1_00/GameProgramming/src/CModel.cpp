#include"CModel.h"
//標準入出力のインクルード
#include<stdio.h>

//モデルファイルの入力
//Load(モデルファイル名,マテリアルファイル名)
void CModel::Load(char* obj, char* mtl) {
	//ファイルポインタ変数の作成
	FILE* fp;
	//ファイルポインタ変数の作成
	FILE* fp2;
	//ファイルのオープン
	//fopen(ファイル名,モード)
	//オープン出来ない時はNULLを返す
	fp = fopen(mtl, "r");
	//ファイルオープンのエラーの判定
	//fpがNULLの時はエラー
	if (fp == NULL) {
		//コンソールにエラーを出力して戻る
		printf("%s file open error\n", mtl);
		return;
	}
	//ファイルからデータを入力
	// 入力エリアを作成する
	char buf[256];
	//ファイルから１行入力
	// fgets(入力エリア,エリアサイズ,ファイルポインタ)
	// ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//入力した値をコンソールに出力する
		printf("%s", buf);
	}
	//ファイルのクローズ
	fclose(fp);

	//ファイルのオープン
	//fopen(ファイル名,モード)
	//オープン出来ない時はNULLを返す
	fp2 = fopen(obj, "r");
	//ファイルオープンのエラーの判定
	//fpがNULLの時はエラー
	if (fp2 == NULL) {
		//コンソールにエラーを出力して戻る
		printf("%s file open error\n", obj);
		return;
	}
	//ファイルから１行入力
// fgets(入力エリア,エリアサイズ,ファイルポインタ)
// ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp2) != NULL) {
		//入力した値をコンソールに出力する
		printf("%s", buf);
	}
	//ファイルのクローズ
	fclose(fp2);	
}
