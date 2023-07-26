#ifndef CSTONE_H
#define CSTONE_H

#include"CCharacter.h"
#include"CTaskManager.h"
#include"CCollider.h"
#include"CColliderMesh.h"
#include"CModel.h"
#include"CTable.h"
#include"CMatrix.h"
#include"CUtil.h"


//障害物(石)の優先順位
#define STONE_PRIORITY 80

/*障害物(石)のモデル*/
#define STONE_MODEL_OBJ "res\\Stone\\stone.obj","res\\Stone\\stone.mtl"
#define STONE_COLLISION_OBJ "res\\Stone\\stone_collision.obj","res\\Stone\\stone_collision.mtl"

//データベース(データテーブル)
#define STONE_DATATABLE "res\\Stone\\DataTable\\StoneData_MainGame.txt"

//障害物(石)クラス
class CStone : public CCharacter {
public:
	//敵の強さの種類
	enum class EStoneType {
		ETYPE_STONE_POS_1,						//プレイヤの初期位置から見て東に配置
		ETYPE_STONE_POS_2,						//プレイヤの初期位置から見て西に配置
		ETYPE_STONE_POS_3,						//プレイヤの初期位置から見て北に配置
	};
	//デフォルトコンストラクタ
	CStone();
	//モデルの設定
	void Model(CModel* model);
	//当たり判定の設定
	void Collision(CCollider* m, CCollider* o);
	//テーブル読み込み関数
	void StoneTable();							//データベース
	//障害物(石)の種類を設定用
	void SetIsType(EStoneType type);
	//座標の取得
	void GetPos();
	//スケールの取得
	void GetScale();
	//モデルの回転値取得
	void GetRotation();
	//インスタンスの取得
	static CStone* GetInstance();//staticで処理を作る
private:
	//石のモデルポインタ
	static CStone* mpStone_Instance;	//別のクラスから変数を呼び出す場合,staticでポインタを作る
	//障害物(石)の種類判断用
	EStoneType mStone_Type;		
	//石モデル
	CModel gStone_Model;
	//石の当たり判定モデル
	CModel gStone_Model_Collision;
	//モデルからコライダを生成
	CColliderMesh mColliderMesh;
	//マップ移動用の行列
	CMatrix mBackGroundMatrix;
	//データベースから取得する変数
	float Stone_Position_X;						//障害物のポジション設定X座標
	float Stone_Position_Y;						//障害物のポジション設定Y座標
	float Stone_Position_Z;						//障害物のポジション設定Z座標
	float Stone_Scale_X;						//障害物のモデルスケールのX座標
	float Stone_Scale_Y;						//障害物のモデルスケールのY座標
	float Stone_Scale_Z;						//障害物のモデルスケールのZ座標
	float Stone_Rotation_X;						//障害物のモデルの回転X座標
	float Stone_Rotation_Y;						//障害物のモデルの回転Y座標
	float Stone_Rotation_Z;						//障害物のモデルの回転Z座標
};
#endif
