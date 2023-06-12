#ifndef CCOLLIDERMESH_H
#define CCOLLIDERMESH_H
#include "CModel.h"
#include "CColliderTriangle.h"
/*
モデルデータから三角コライダの生成
*/
class CColliderMesh
{
public:
	//インスタンスの取得
	static CColliderMesh* GetInstance();//staticで処理を作る
	//三角コライダの配列作成
	CColliderTriangle *mpColliderTriangles;
	CColliderMesh();
	~CColliderMesh();
	//Set(親, 親行列, モデル)
	//モデルから三角コライダの生成
	void Set(CCharacter *parent, CMatrix *matrix, CModel *model);
private:
	//空のモデルポインタ
	static CColliderMesh* mpColliderMesh_Instance;	//別のクラスから変数を呼び出す場合,staticでポインタを作る
};

#endif
