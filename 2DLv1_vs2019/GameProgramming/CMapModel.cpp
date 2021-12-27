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
		int seq[20][9];
		//ssccanf(数列,変換指定子,変数)
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[0][0], &seq[0][1], &seq[0][2], &seq[0][3], &seq[0][4], &seq[0][5], &seq[0][6], &seq[0][7], &seq[0][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[1][0], &seq[1][1], &seq[1][2], &seq[1][3], &seq[1][4], &seq[1][5], &seq[1][6], &seq[1][7], &seq[1][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[2][0], &seq[2][1], &seq[2][2], &seq[2][3], &seq[2][4], &seq[2][5], &seq[2][6], &seq[2][7], &seq[2][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[3][0], &seq[3][1], &seq[3][2], &seq[3][3], &seq[3][4], &seq[3][5], &seq[3][6], &seq[3][7], &seq[3][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[4][0], &seq[4][1], &seq[4][2], &seq[4][3], &seq[4][4], &seq[4][5], &seq[4][6], &seq[4][7], &seq[4][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[5][0], &seq[5][1], &seq[5][2], &seq[5][3], &seq[5][4], &seq[5][5], &seq[5][6], &seq[5][7], &seq[5][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[6][0], &seq[6][1], &seq[6][2], &seq[6][3], &seq[6][4], &seq[6][5], &seq[6][6], &seq[6][7], &seq[6][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[7][0], &seq[7][1], &seq[7][2], &seq[7][3], &seq[7][4], &seq[7][5], &seq[7][6], &seq[7][7], &seq[7][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[8][0], &seq[8][1], &seq[8][2], &seq[8][3], &seq[8][4], &seq[8][5], &seq[8][6], &seq[8][7], &seq[8][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[9][0], &seq[9][1], &seq[9][2], &seq[9][3], &seq[9][4], &seq[9][5], &seq[9][6], &seq[9][7], &seq[9][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[10][0], &seq[10][1], &seq[10][2], &seq[10][3], &seq[10][4], &seq[10][5], &seq[10][6], &seq[10][7], &seq[10][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[11][0], &seq[11][1], &seq[11][2], &seq[11][3], &seq[11][4], &seq[11][5], &seq[11][6], &seq[11][7], &seq[11][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[12][0], &seq[12][1], &seq[12][2], &seq[12][3], &seq[12][4], &seq[12][5], &seq[12][6], &seq[12][7], &seq[12][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[13][0], &seq[13][1], &seq[13][2], &seq[13][3], &seq[13][4], &seq[13][5], &seq[13][6], &seq[13][7], &seq[13][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[14][0], &seq[14][1], &seq[14][2], &seq[14][3], &seq[14][4], &seq[14][5], &seq[14][6], &seq[14][7], &seq[14][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[15][0], &seq[15][1], &seq[15][2], &seq[15][3], &seq[15][4], &seq[15][5], &seq[15][6], &seq[15][7], &seq[15][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[16][0], &seq[16][1], &seq[16][2], &seq[16][3], &seq[16][4], &seq[16][5], &seq[16][6], &seq[16][7], &seq[16][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[17][0], &seq[17][1], &seq[17][2], &seq[17][3], &seq[17][4], &seq[17][5], &seq[17][6], &seq[17][7], &seq[17][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[18][0], &seq[18][1], &seq[18][2], &seq[18][3], &seq[18][4], &seq[18][5], &seq[18][6], &seq[18][7], &seq[18][8]);
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[19][0], &seq[19][1], &seq[19][2], &seq[19][3], &seq[19][4], &seq[19][5], &seq[19][6], &seq[19][7], &seq[19][8]);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 20; j++) {

				if (seq[j][i] == 0)
				{
					printf("%d\n", seq[j][i]);

				}

				if (seq[j][i] == 1){
					printf("%d\n", seq[j][i]);
					CBlock* Block = new CBlock();
					Block->x = i * 100 - 350;
					Block->y = j * -100 + 250;
					Block->w = 25;
					Block->h = 25;
					Block->mFx = 0;
					Block->mFy = -1;
					Block->mEnabled = true;
					Block->mTag = CRectangle::EBLOCK;

					break;
				}

				if (seq[j][i] == 2)
				{
					printf("%d\n", seq[j][i]);
					CBlock* Block = new CBlock();
					Block->x = i * 100 - 800;
					Block->y = j * -100 + 850;
					Block->w = 25;
					Block->h = 25;
					Block->mFx = 0;
					Block->mFy = -1;
					Block->mEnabled = true;
					Block->mTag = CRectangle::EBLOCK;
					break;
				}

			}
				
			

		}
		
	}

	//ファイルのクローズ
	fclose(fp);
	
}