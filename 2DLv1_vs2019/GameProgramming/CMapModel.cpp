#include "CMapModel.h"
//標準入出力のインクルード
#include <stdio.h>
#include"CBlock.h"





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
	int i = 0;
	//ファイルから1行入力
	//fgets(入力エリア,エリアサイズ,ファイルポインタ)
	//ファイルの最後になるとNULLを返す
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		//数列からデータを9つ変数へ代入する
		//データを分割
		int seq[9];
		//ssccanf(数列,変換指定子,変数)
		sscanf(buf, "%d, %d, %d, %d, %d, %d, %d, %d, %d,", &seq[0], &seq[1], &seq[2], &seq[3], &seq[4], &seq[5], &seq[6], &seq[7], &seq[8]);

		for (int j = 0; j < 9; j++)
		{
			switch (seq[j]) {
			case 0: {
				printf("%d", seq[j]);
			}
				  break;
			case 1: {
				printf("%d", seq[j]);
				CBlock* Block = new CBlock();
				Block->x = j * 90 + -360;
				Block->y = i * -90 + 3180;
				Block->w = 45;
				Block->h = 45;
				Block->mEnabled = true;
				Block->mTag = CRectangle::EBLOCK;
			}
				  break;

			case 2: {
				printf("%d", seq[j]);
				CComet* Comet = new CComet();
				Comet->x = j * 90 + -370;
				Comet->y = i * -90 + 3180;
				Comet->w = 45;
				Comet->h = 45;
				Comet->mEnabled = true;
				Comet->mTag = CRectangle::ECOMET;
			}
				  break;
			case 3: {
				printf("%d", seq[j]);
				CEnemy* Enemy = new CEnemy();
				Enemy->x = j * 90 + -370;
				Enemy->y = i * -90 + 3180;
				Enemy->w = 25;
				Enemy->h = 25;
				Enemy->mFx = 0;
				Enemy->mFy = -1;
				Enemy->mEnabled = true;
				Enemy->mTag = CRectangle::EENEMY;
			}
				  break;
			}
		}













		i = i + 1;

	}
	//ファイルのクローズ
	fclose(fp);


}
	
	
