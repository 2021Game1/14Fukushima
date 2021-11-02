#include"CModel.h"
//標準入出力のインクルード
#include<string.h>
//CVectorのインクルード
#include"CVector.h"
//CTriangleのインクルード
#include"CTriangle.h"



//モデルファイルの入力
//Load(モデルファイル名,マテリアルファイル名)
void CModel::Load(char* obj, char* mtl) {
	//頂点データの保存（CVector型）
	std::vector<CVector>vertex;
	//法線データの保存（CVector型）
	std::vector<CVector>normal;
	//テクスチャマッピングの保存 (CVector型)
	std::vector<CVector>uv;
	//ファイルポインタ変数の作成
	FILE* fp;
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
	//マテリアルインデックス
	int idx = 0;
	//ファイルから１行入力
	// fgets(入力エリア,エリアサイズ,ファイルポインタ)
	// ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//データを分割する
		char str[4][64] = { "","","","" };
		//文字列からデータを4つ変数へ代入する
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//先頭がnewmtlの時、マテリアルを追加する
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//マテリアル名の設定
			pm->Name(str[1]);
			//マテリアルの可変長配列に追加
			mpMaterials.push_back(pm);
			//配列の長さを取得
			idx = mpMaterials.size() - 1;
		}
	
	
		//先頭がKdの時、Diffuseを設定する
		else if (strcmp(str[0], "Kd") == 0) {
			mpMaterials[idx]->Diffuse()[0] = atof(str[1]);
			mpMaterials[idx]->Diffuse()[1] = atof(str[2]);
			mpMaterials[idx]->Diffuse()[2] = atof(str[3]);
		}
		//先頭がdの時、a値を設定する
		else if (strcmp(str[0], "d") == 0) {
			mpMaterials[idx]->Diffuse()[3] = atof(str[1]);
		}
		//先頭がmap_Kdの時、テクスチャを入力する
		else if (strcmp(str[0], "map_Kd") == 0) {
			mpMaterials[idx]->Texture()->Load(str[1]);
		}
	}
	//ファイルのクローズ
	fclose(fp);
	
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
	//ファイルから１行入力
// fgets(入力エリア,エリアサイズ,ファイルポインタ)
// ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//データを分割する
		char str[4][64] = { "","","","" };
		//文字列からデータを４つ変数へ代入する
		// sscanf(文字列,変換指定子,変数)
		sscanf(buf, "%s %s %s %s", str[0], str[1], str[2], str[3]);
		//先頭がnewmtlの時、マテリアルを追加する
		if (strcmp(str[0], "newmtl") == 0) {
			CMaterial* pm = new CMaterial();
			//マテリアル名の設定
			pm->Name(str[1]);
			//マテリアルの可変長配列に追加
			mpMaterials.push_back(pm);
			//配列の長さを取得
			idx = mpMaterials.size() - 1;
		}
		//文字列の比較
		//strcmp(文字列１,文字列２)
		//文字列１と文字列２が同じとき0,異なる時０以外を返す
		// 先頭がvnの時、頂点をnormalに追加する
		if (strcmp(str[0], "vn") == 0) {
			normal.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		if (strcmp(str[0], "v") == 0) {
			//可変長配列vertexに追加する
			//atof(文字列) 文字列からfloat型の値を返す
			vertex.push_back(CVector(atof(str[1]), atof(str[2]), atof(str[3])));
		}
		//先頭がvtの時、uvに追加する
		else if (strcmp(str[0], "vt") == 0) {
			//可変長配列uvに追加する
			//atof(文字列)　文字列からfloat型の値を返す
			uv.push_back(CVector(atof(str[1]), atof(str[2]), 0.0));
		}
		//先頭がusemtlの時、マテリアルインデックスを取得する
		else if (strcmp(str[0], "usemtl") == 0) {
			//可変長配列を後から比較
			for (idx = mpMaterials.size() - 1; idx > 0; idx--) {
				//同じ名前のマテリアルがあればループ終了
				if (strcmp(mpMaterials[idx]->Name(), str[1]) == 0) {
					break; //ループから出る
				}
			}
		}
		//先頭がfの時、三角形を作成して追加する
		else if (strcmp(str[0], "f") == 0) {
			//頂点と法線の番号作成
			int v[3], n[3];
			//テクスチャマッピングの有無を判定
			if (strstr(str[1], "//")) {
				//頂点と法線の番号取得
				sscanf(str[1], "%d//%d", &v[0], &n[0]);
				sscanf(str[2], "%d//%d", &v[1], &n[1]);
				sscanf(str[3], "%d//%d", &v[2], &n[2]);
				//三角形作成
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//マテリアル番号の設定
				t.MaterialIdx(idx);
				//可変長配列mTrianglesに三角形を追加
				mTriangles.push_back(t);
			}
			else {
				//テクスチャマッピング有り
				int u[3];//テクスチャマッピングの番号取得
				sscanf(str[1], "%d/%d/%d", &v[0], &u[0], &n[0]);
				sscanf(str[2], "%d/%d/%d", &v[1], &u[1], &n[1]);
				sscanf(str[3], "%d/%d/%d", &v[2], &u[2], &n[2]);
				//三角形作成
				CTriangle t;
				t.Vertex(vertex[v[0] - 1], vertex[v[1] - 1], vertex[v[2] - 1]);
				t.Normal(normal[n[0] - 1], normal[n[1] - 1], normal[n[2] - 1]);
				//テクスチャマッピングの設定
				t.SetUv(uv[u[0] - 1], uv[u[1] - 1], uv[u[2] - 1]);
				//マテリアル番号の設定
				t.MaterialIdx(idx);
				//可変長配列mTrianglesに三角形を追加
				mTriangles.push_back(t);
			}
		}
	}
	//ファイルのクローズ
	fclose(fp);

}
//描画
void CModel::Render() {
	//可変長配列の要素数だけ繰り返し
	for (int i = 0; i < mTriangles.size(); i++){
		//マテリアルの適用
		mpMaterials[mTriangles[i].MaterialIdx()]->Enabled();
		//可変長配列に添え字でアクセスする
		mTriangles[i].Render();
		//マテリアルを無効
		mpMaterials[mTriangles[i].MaterialIdx()]->Disabled();
	}
}
CModel::~CModel()
{
	for (int i = 0; i < mpMaterials.size(); i++)
	{
		delete mpMaterials[i];
	}
}
