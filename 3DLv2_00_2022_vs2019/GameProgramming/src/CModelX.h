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

class CModelX;//フレンドクラス用

class CModelXFrame;//フレンドクラス用

class CMesh;//フレンドクラス用

class CMaterial;//フレンドクラス用

class CAnimationSet;//フレンドクラス用

class CAnimation;//フレンドクラス用
/*
CAnimationKey
アニメーションキークラス
*/
class CAnimationKey{
	friend CAnimation;
	friend CAnimationSet;
	friend CModelX;

	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
};

/*
CAnimation
アニメーションクラス
*/
class CAnimation {
	friend CAnimationSet;
	friend CModelX;
	friend CAnimationKey;

	char* mpFrameName;//フレーム名
	int mFrameIndex; //フレーム番号
	int mKeyNum;	//キー数(時間数)
	CAnimationKey* mpKey;	//キーの配列
public:
	CAnimation(CModelX* model);

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
	}
};

/*
CAnimationSet
アニメーションセット
*/
class CAnimationSet {
	friend CModelX;
	friend CAnimation;
	friend CAnimationKey;
	//アニメーションセット名
	char* mpName;
	float mTime;    //現在の時間
	float mWeight;  //重み
	float mMaxTime; //最大時間

	//アニメーション
	std::vector<CAnimation*>mAnimation;
public:
	CAnimationSet(CModelX* model);
	~CAnimationSet()
	{
		SAFE_DELETE_ARRAY(mpName);
		//アニメーション要素の削除
		for (size_t i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}
	}
	void CAnimationSet::Time(float time)
	{
		mTime = time;
	}
	void CAnimationSet::Weught(float weight)
	{
		mWeight = weight;
	}
};

/*
CSkinWeights
スキンウェイトクラス
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
	char* mpFrameName; //フレーム名
	int mFrameindex;   //フレーム番号
	int mIndexNum;	   //頂点番号数
	int* mpIndex;   //頂点番号配列
	float* mpWeight;   //頂点ウェイト配列
	CMatrix mOffset;   //オフセットマトリックス
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights() {
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
	const int& FrameIndex();
	const CMatrix& Offset();


};

//CMeshクラスの定義
class CMesh{
	friend CModelX;
	friend CModelXFrame;
	friend CSkinWeights;

	int mVertexNum;		//頂点数
	CVector* mpVertex;	//頂点データ
	int mFaceNum;		//画数
	int* mpVertexIndex;	//面を構成する頂点座標
	int mNormalNum;		//法線数
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;	//マテリアル番号数(面数)
	int* mpMaterialIndex;//マテリアル番号
	std::vector<CMaterial*>mMaterial;//マテリアルデータ
	std::vector<CSkinWeights*>mSkinWeights;//スキンウェイト
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
		,mMaterialNum(0)
		,mMaterialIndexNum(0)
		,mpMaterialIndex(nullptr)
	{}
	//デストラクタ
	~CMesh() {
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		//スキンウェイトの削除
		for (size_t i = 0; i < mSkinWeights.size(); i++)
		{
			delete mSkinWeights[i];
		}
	}
	//読み込み処理
	void Init(CModelX* model);
	//描画
	void Render();
};


//CModelXFrameクラスの定義
class CModelXFrame { //フレーム=ボーン
	friend CModelX;
	friend CMesh;
	friend CAnimation;
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
	//描画
	void Render();

private:
};


/*
CModelX
Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
	friend CModelXFrame;
	friend CMesh;
	friend CSkinWeights;
	friend CAnimationSet;
	friend CAnimation;
	friend CAnimationKey;
	char* mpPointer;	//読み込み位置
	char mToken[1024];  //取り出した単語の領域
	std::vector<CModelXFrame*>mFrame;	//フレームの配列
	std::vector<CAnimationSet*>mAnimationSet; //アニメーションセットの配列

public:
	CModelX();
	~CModelX();
	//浮動小数点データの取得
	float GetFloatToken();
	//ファイル読み込み
	void Load(char* file);
	//描画
	void Render();
	//単語の取り出し
	void GetToken();
	//ノードの読み飛ばし
	void SkipNode();
	//フレームの変換行列をアニメーションデータで更新する
	void AnimateFrame();
	//整数データの取得
	int GetIntToken();
	//
	char* Token();
	//フレーム名に該当するフレームにアドレスを返す
	CModelXFrame* FindFrame(char* name);

	std::vector<CAnimationSet*>& AnimationSet();

	

};



#endif 

