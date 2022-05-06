#ifndef CMODELX_H
#define CMODELX_H

#include <vector>	 //vectorクラスのインクルード(動的配列)
#include "CMatrix.h" //マトリクスクラスのインクルード


#define MODEL_FILE "res\\sample.blend.x"

//領域開放をマクロ化
#define SAFE_DELETE_ARRAY(a) {if(a)delete[]a; a = 0;}

class CModelX; //CModelクラスの宣言
//CModelXFrameクラスの定義
class CModelXFrame {
	friend CModelX;
	std::vector<CModelXFrame*>mChild; //子フレームの配列
	CMatrix mTransformMatrix;		  //変換行列
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
	char* mpPointer;	//読み込み位置
	char mToken[1024];  //取り出した単語の領域
	std::vector<CModelXFrame*>mFrame;	//フレームの配列
public:
	CModelX();
	~CModelX();

	//ファイル読み込み
	void Load(char* file);
	//単語の取り出し
	void GetToken();
	//ノードの読み飛ばし
	void SkipNode();
};

#endif 

