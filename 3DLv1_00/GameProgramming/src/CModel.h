#ifndef CMODEL_H
#define CMODEL_H
//vectorのインクルード
#include<vector>
//CTriangleのインクルード
#include"CTriangle.h"
/*
モデルクラス
モデルデータの入力や表示
*/
class CModel {
public:
	//モデルファイルの入力
	//Load(モデルファイル名、マテリアルファイル名）
	void Load(char* obj, char* mtl);

private:
	//三角形の可変長配列
	std::vector<CTriangle>mTriangles;

};

#endif 

