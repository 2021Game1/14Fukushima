#ifndef CMODELX_H
#define CMODELX_H

#include <vector>	 //vectorクラスのインクルード(動的配列)
#include "CMatrix.h" //マトリクスクラスのインクルード
#include "CVector.h"

#define MODEL_FILE "res\\sample.blend.x"

//領域開放をマクロ化
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}

//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

class CModelX; //CModelクラスの宣言

class CModelXFrame;

//CMeshクラスの定義
class CMesh{
	friend CModelX;
	friend CModelXFrame;

	int mVertexNum;		//頂点数
	CVector* mpVertex;	//頂点データ
	int mFaceNum;		//画数
	int* mpVertexIndex;	//面を構成する頂点座標
	int mNormalNum;		//法線数
	CVector* mpNormal;	//法線ベクトル

public:
	//コンストラクタ
	CMesh()
		:mVertexNum(0)
		, mpVertex(nullptr)
		, mFaceNum(0)
		, mpVertexIndex(nullptr)
		,mNormalNum(0)
		,mpNormal(nullptr)
	{}
	//デストラクタ
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
	}
	//読み込み処理
	void Init(CModelX* model);
};


//CModelXFrameクラスの定義
class CModelXFrame {
	friend CModelX;
	friend CMesh;
	std::vector<CModelXFrame*>mChild; //子フレームの配列
	CMatrix mTransformMatrix;		  //変換行列
	CMesh mMesh;					  //Meshデータ
	char* mpName;					  //フレーム名前
	int mIndex;						  //フレーム番号
public:
	//コンストラクタ
	CModelXFrame(CModelX* model);
	//デストラクタ
	~CModelXFrame() {
		//子フレームを全て開放する
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++) {
			delete* itr;
		}
		//名前のエリアを開放する
		SAFE_DELETE_ARRAY(mpName);
	}
	
};

/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
	friend CModelXFrame;
	friend CMesh;
	char* mpPointer;	//読み込み位置
	char mToken[1024];  //取り出した単語の領域
	std::vector<CModelXFrame*>mFrame;	//フレームの配列
public:
	CModelX();
	~CModelX();
	//浮動小数点データの取得
	float GetFloatToken();
	//ファイル読み込み
	void Load(char* file);
	//単語の取り出し
	void GetToken();
	//ノードの読み飛ばし
	void SkipNode();
	//整数データの取得
	int GetIntToken();
	
};

#endif 

