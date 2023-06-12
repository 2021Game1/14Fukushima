#ifndef CMAP_H
#define CMAP_H

#include"CCharacter.h"
#include"CTaskManager.h"
#include"CCollider.h"
#include"CColliderMesh.h"
#include"CModel.h"
#include"CMatrix.h"
#include"CUtil.h"

//マップの優先順位
#define MAP_PRIORITY 90

/*マップのモデル*/

#define MAP_MODEL_MAP "res\\Map\\map.obj","res\\Map\\map.mtl"
#define MAP_MODEL_SKY "res\\Sky\\sky.obj","res\\Sky\\sky.mtl"
#define MAP_COLLISION_MAP "res\\Map\\collision.obj","res\\Map\\collision.mtl"

class CMap : public CCharacter {
public:
	CMap();
	void Init();
	void Collision(CCollider* m, CCollider* o);
	//マップ生成
	void Generate(); //生成
	//マップ削除
	void Release(); //破棄
	//インスタンスの取得
	static CMap* GetInstance();//staticで処理を作る

private:
	//マップのモデルポインタ
	static CMap* mpMap_Instance;	//別のクラスから変数を呼び出す場合,staticでポインタを作る
	//マップモデル
	CModel gMap_Model;
	//マップの当たり判定モデル
	CModel gMap_Model_Collision;
	//マップ移動用の行列
	CMatrix mBackGroundMatrix;
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;

};

class CSkyMap : public CCharacter {
public:
	CSkyMap();
	void Init();
	void Collision(CCollider* m, CCollider* o);
	//マップ生成
	void Generate(); //生成
	//マップ削除
	void Release(); //破棄
	//インスタンスの取得
	static CSkyMap* GetInstance();//staticで処理を作る

private:
	//マップのモデルポインタ
	static CSkyMap* mpSkyMap_Instance;	//別のクラスから変数を呼び出す場合,staticでポインタを作る
	//マップの背景モデル
	CModel gSky_Map_Model;
};



#endif
