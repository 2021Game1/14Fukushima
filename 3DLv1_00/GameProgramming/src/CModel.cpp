#include"CModel.h"
//標準入出力のインクルード
#include<stdio.h>
//CVectorのインクルード
#include"CVector.h"

//モデルファイルの入力
//Load(モデルファイル名,マテリアルファイル名)
void CModel::Load(char* obj, char* mtl) {
	//頂点データの保存（CVector型）
	std::vector<CVector>vertex;
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
		//データを分割する
		char str[4][64] = { "","","","" };
		//文字列からデータを４つ変数へ代入する
		// sscanf(文字列,変換指定子,変数)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//文字列の比較
		//strcmp(文字列１,文字列２)
		//文字列１と文字列２が同じとき0,異なる時０以外を返す
		// 先頭がvの時、頂点をvertexに追加する
		if (strcmp(str[0], "v") == 0) {
			//可変長配列vertexに追加する
			//atof(文字列) 文字列からfloat型の値を返す
			vertex.push_back(CVector(atof(str[1]), atof(str[2]),atof(str[3])));
		}
		//先頭がfの時、三角形を作成して追加する
		else if(strcmp(str[0],"f")==0){
			//頂点と法線の番号作成
			int v[3], n[3];
			//頂点と法線の番号取得
			sscanf(str[1], "%d//%d,&v[0],&n[0]");
			sscanf(str[2], "%d//%d,&v[1],&n[1]");
			sscanf(str[3], "%d//%d,&v[2],&n[2]");
			//三角形作成
			CTriangle t;
			t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
			//可変長配列mTrianglesに三角形を追加
			mTriangles.push_back(t);
		}
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
