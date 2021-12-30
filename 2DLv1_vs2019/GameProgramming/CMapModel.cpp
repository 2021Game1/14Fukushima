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
		int map[1][9] =
		{
				{seq[0],seq[1],seq[2],seq[3],seq[4],seq[5],seq[6],seq[7],seq[8]}
		};
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				switch (map[i][j]) {
				case 0: {
					printf("%d", map[i][j]);
				}
				case 1: {
					printf("%d", map[i][j]);
					CBlock* Block = new CBlock();
					Block->x = j * 100 + -400;
					Block->y = i + 50 + -300;
					Block->w = 25;
					Block->h = 25;
					Block->mFx = 0;
					Block->mFy = -1;
					Block->mEnabled = true;
					Block->mTag = CRectangle::EBLOCK;
					break;

				}
				case 2: {
					printf("%d", map[i][j]);
					CBlock* Block2 = new CBlock();
					Block2->x = j * 100 + -400;
					Block2->y = i + 150 + -200;
					Block2->w = 25;
					Block2->h = 25;
					Block2->mFx = 0;
					Block2->mFy = -1;
					Block2->mEnabled = true;
					Block2->mTag = CRectangle::EBLOCK;
					break;




				}

				}
			}





		}









	}
	//ファイルのクローズ
	fclose(fp);


}
	
	
