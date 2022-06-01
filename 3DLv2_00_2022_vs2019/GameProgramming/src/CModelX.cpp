#include <stdio.h>
#include <string.h>

#include "CModelX.h"
#include "glut.h"
#include "CMaterial.h"

#define COUNT_SET 1

CModelX::CModelX() 
	:mpPointer(nullptr)
{
	//mTokenを初期化
	memset(mToken, 0, sizeof(mToken));
}
CModelX::~CModelX() {
	if (mFrame.size() > 0)
	{
		delete mFrame[0];
	}
}

/*
CModelXFrame
model:CModelXインスタンスへのポインタ
フレームを作成する
読み込み中にFrameが見つかれば、
フレームを作成し、子フレームに追加する
*/
CModelXFrame::CModelXFrame(CModelX* model) {
	//現在のフレーム配列の要素数を取得し設定する
	mIndex = model->mFrame.size();
	//CModelXのフレーム配列に追加する
	model->mFrame.push_back(this);
	//変換行列を単位行列にする
	mTransformMatrix.Identity();
	//次の単語(フレーム名の予定)を取得する
	model->GetToken();//frame name
	//フレーム名分エリアを確保する
	mpName = new char[strlen(model->mToken) + 1];
	//フレーム名をコピーする
	strcpy(mpName, model->mToken);
	//次の単語を({の予定)を取得する
	model->GetToken();//{
	//文字が無くなったら終わり
	while (*model->mpPointer != '\0') {
		//次の単語取得
		model->GetToken();//Frame
		//}かっこの場合は終了
		if (strchr(model->mToken, '}'))break;
		//新たなフレームの場合は、子フレームに追加
		if (strcmp(model->mToken, "Frame") == 0) {
			//フレームを作成し、 子フレームの配列に追加
			mChild.push_back(new CModelXFrame(model));

		}
		//FrameTransformMatrix要素を見つけた時,mTransformMatrixに設定する
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0)
		{
			model->GetToken();//{
			for (int i = 0; i < mTransformMatrix.Size(); i++)
			{
				mTransformMatrix.M()[i] = model->GetFloatToken();
			}
			model->GetToken();//}
		}
		else if (strcmp(model->mToken, "Mesh") == 0) {
			mMesh.Init(model);
		}
		else {
			//上記以外の要素は読み飛ばす
			model->SkipNode();
		}

	}
	//デバッグバージョンのみ有効
#ifdef _DEBUG
	printf("%s\n", mpName);
	mTransformMatrix.Print();
	
#endif //DEBUG
}


/*
SkipNode
ノードを読み飛ばす
*/
void CModelX::SkipNode() {
	//文字が終わったら終了
	while (*mpPointer != '\0') {
		GetToken();		//次の単語を取得
		//{が見つかったらループ終了
		if (strchr(mToken, '{'))break;
	}
	int count = COUNT_SET;
	//文字が終わるか、カウントダウンが0になったら終了
	while (*mpPointer != '\0' && count > 0) {
		GetToken();
		//{を見つけるとカウントアップ
		if (strchr(mToken, '{'))count++;
		//}を見つけるとカウントダウン
		else if (strchr(mToken, '}'))count--;
	}
}

/*
GetToken
文字列データから、単語を1つ取得する
*/
void CModelX::GetToken() {
	char* p = mpPointer;
	char* q = mToken;
	//空白( )タブ(\t)改行(\r)(\n),;"以外の文字になるまで読み飛ばす
	/*
	strchr(文字列,文字)
	文字列に文字が含まれていれば、見つかった文字へのポインタを返す
	見つからなかったらNULLを返す
	*/
	while (*p != '\0' && strchr(" \t\r\n,;\"", *p))p++;
	if (*p == '{'|| *p == '}')
	{
		//{または}ならmTokenに代入し次の文字へ
		*q++ = *p++;
	}
	else
	{
		//空白( )(\t)改行(\r)(\n),;" }の文字になるまでmTokenに代入する
		while (*p != '\0' && !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0';	//mTokenの最後に\0を代入する
	mpPointer = p;//次の読み込むポイントを更新する
	//もしmTokenが//の場合は、コメントなので改行まで読み飛ばす
	/*
	strcmp(文字列1,文字列2)
	文字列1と文字列2が等しい場合,0を返します
	文字列1と文字列2が等しくない場合、0を返します。
	*/
	if (!strcmp("//", mToken)) {
		//改行まで読み飛ばす
		while (*p != '\0' && !strchr("\r\n", *p))p++;
		//読み込み位置の更新
		mpPointer = p;
		//単語を取得する(再起呼び出し)
		GetToken();
	}
}



/*
* Init
* Meshのデータを取り込む
*/
void CMesh::Init(CModelX* model) {
	model->GetToken();	//{or 名前
	if (!strchr(model->mToken, '{')) {
		//名前の場合、次が{
		model->GetToken();		   //{
	}
	//頂点数の取得
	mVertexNum = model->GetIntToken();
	//頂点数分エリア確保
	mpVertex = new CVector[mVertexNum];
#ifdef _DEBUG
	printf("%s%d \n", "VertexNum:", mVertexNum);
#endif //DEBUG
	//頂点数分データを取り込む
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].X(model->GetFloatToken());
		mpVertex[i].Y(model->GetFloatToken());
		mpVertex[i].Z(model->GetFloatToken());

		//デバッグバージョンのみ有効
#ifdef _DEBUG
		printf("%10f %10f %10f \n", mpVertex[i].X(), mpVertex[i].Y(), mpVertex[i].Z());
#endif //DEBUG
	}
	mFaceNum = model->GetIntToken();		//面数読み込み
#ifdef _DEBUG
	printf("%s%d \n", "FaceNum:", mFaceNum);
#endif //DEBUG
	//頂点数は1面に３頂点
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3)
	{
		model->GetToken();//頂点数読み飛ばし
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
		//デバッグバージョンのみ有効
#ifdef _DEBUG
		printf("%d %d %d \n", mpVertexIndex[i], mpVertexIndex[i + 1], mpVertexIndex[i + 2]);
#endif //DEBUG
	}
	//文字が無くなったら終わり
	while (model->mpPointer != '\0') {
		model->GetToken();	//meshNormals
		//}かっこの場合は終了
		if (strchr(model->mToken, '}'))
			break;
		if (strcmp(model->mToken, "MeshNormals") == 0) {
			model->GetToken();
			//法線データ数を取得
			mNormalNum = model->GetIntToken();
			//法線のデータを配列に取り込む
			CVector* pNormal = new CVector[mNormalNum];
			for (int i = 0; i < mNormalNum; i++) {
				pNormal[i].X(model->GetFloatToken());
				pNormal[i].Y(model->GetFloatToken());
				pNormal[i].Z(model->GetFloatToken());
			}
			//法線数=面数×3
			mNormalNum = model->GetIntToken() * 3;	//FaceNum
			int ni;
			//頂点毎に法線データを設定する
			mpNormal = new CVector[mNormalNum];
#ifdef _DEBUG
			printf("%s%d \n", "NormalNum:", mNormalNum);
#endif //DEBUG
			for (int i = 0; i < mNormalNum; i += 3) {
				model->GetToken();//3
				ni = model->GetIntToken();
				mpNormal[i] = pNormal[ni];
				mpNormal[i + 1] = pNormal[ni];
				ni = model->GetIntToken();
				mpNormal[i + 2] = pNormal[ni];
				ni = model->GetIntToken();
				//デバッグバージョンのみ有効
#ifdef _DEBUG
				printf("%10f %10f %10f \n", mpNormal[i].X(), mpNormal[i].Y(), mpNormal[i].Z());
				printf("%10f %10f %10f \n", mpNormal[i + 1].X(), mpNormal[i + 1].Y(), mpNormal[i + 1].Z());
				printf("%10f %10f %10f \n", mpNormal[i + 2].X(), mpNormal[i + 2].Y(), mpNormal[i + 2].Z());
#endif //DEBUG
			}
			delete[]pNormal;
			model->GetToken();		//}
		}
	
	
	//MeshMaterialListの時
	else if (strcmp(model->mToken,"MeshMaterialList") == 0) {
		model->GetToken();//{
		//Materialの数
		mMaterialNum = model->GetIntToken();
		//FaceNum
		mMaterialIndexNum = model->GetIntToken();
		//マテリアルインデックスの作成
		mpMaterialIndex = new int[mMaterialIndexNum];
		for (int i = 0; i < mMaterialIndexNum; i++) {
			mpMaterialIndex[i] = model->GetIntToken();
		}
		//マテリアルデータの作成
		for (int i = 0; i < mMaterialNum; i++){
			model->GetToken(); //Material
			if (strcmp(model->mToken,"Material") == 0) {
				mMaterial.push_back(new CMaterial(model));
			}
		}
		model->GetToken();   //}End of MeshMaterialList
	}
	else if (strcmp(model->mToken,"SkinWeights")==0){
			//CSkinWeightsクラスのインスタンスを作成し、配列に追加
			mSkinWeights.push_back(new CSkinWeights(model));
		}
	else
		{
			//以外のノードは読み飛ばし
			model->SkipNode();
		}
	}
	
}




void CModelX::Load(char* file) {
	//
	//ファイルサイズを取得
	//
	FILE* fp;	//ファイルポインタ
	fp = fopen(file, "rb");//ファイルポインタ変数の作成
	if (fp == NULL) {
		printf("fopen error:%s\n",file);
		return;
	}
	//ファイルの最後へ移動
	fseek(fp, 0L, SEEK_END);
	//ファイルサイズの取得
	int size = ftell(fp);
	//ファイルサイズ＋1バイト分の領域を確保
	char* buf = mpPointer = new char[size + 1];
	//
	//ファイルから3Dモデルのデータを読み込む
	//
	//ファイルの先頭へ移動
	fseek(fp, 0L, SEEK_SET);
	//確保した領域にファイルサイズ分のデータを読み込む
	fread(buf, size, 1, fp);
	//最後に\0を設定する(文字列の終端)
	buf[size] = '\0';
	fclose(fp);		//ファイルをクローズする

	//文字列の最後まで繰り返し
	while (*mpPointer != '\0') {
		GetToken();		//単語の取得
		//単語がFrameの場合
		if (strcmp(mToken, "Frame") == 0) {
			//フレームを作成する
			new CModelXFrame(this);
		}
	}
	SAFE_DELETE_ARRAY(buf);	//確保した領域を開放する
}

void CMesh::Render() {
	/*頂点データ,法線データの配列を有効にする*/
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	/*頂点データ,法線データの場所を指定する*/
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	glNormalPointer(GL_FLOAT, 0, mpNormal);

	/*頂点のインデックスの場所を指定して図形を描画する*/
	for (int i = 0; i < mFaceNum; i++) {
		//マテリアルを適用する
		mMaterial[mpMaterialIndex[i]]->Enabled();
		glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
	}
	/*頂点データ,法線データの配列を無効にする*/
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

CSkinWeights::CSkinWeights(CModelX* model)
	:mpFrameName(0)
	,mFrameindex(0)
	,mIndexNum(0)
	,mpIndex(nullptr)
	,mpWeight(nullptr)
{
	model->GetToken();	//{
	model->GetToken();  //FrameName
	//フレーム名エリア確保、設定
	mpFrameName = new char[strlen(model->Token()) + 1];
	strcpy(mpFrameName, model->Token());
	printf("%s%s \n", "SkinWeights ", mpFrameName);

	//頂点番号数
	mIndexNum = model->GetIntToken();
	//頂点番号数が0を超える
	if (mIndexNum > 0) {
		//頂点番号と頂点ウェイトのエリア確保
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//頂点番号取得
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = model->GetIntToken();
		//頂点ウェイト取得
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = model->GetFloatToken();
		printf("%d %f\n", *mpIndex, *mpWeight);
	}
	
	//オフセット行列取得
	for (int i = 0; i < 16; i++) {
		mOffset.M()[i] = model->GetFloatToken();
	}
	
	printf("%s\n", "・・・頂点番号分・・・");
	mOffset.Print();
	model->GetToken();		//}
	

	
	
	
}
/*
Render
メッシュの面数が0以外なら描画する
*/
void CModelXFrame::Render() {
	if (mMesh.mFaceNum != 0){
		mMesh.Render();
	}
}

/*
Render
全てのフレームの描画処理を呼び出す
*/
void CModelX::Render() {
	for (size_t i = 0; i < mFrame.size(); i++){
		mFrame[i]->Render();
	}
}

/*
* GetIntToken
* 単語を整数型のデータで返す
*/
int CModelX::GetIntToken() {
	GetToken();
	return atoi(mToken);
}
/*
*
*
*/
char* CModelX::Token() {
	return &mToken[0];
}

/*
* GetFloatToken
* 単語を浮動小数点型のデータで返す
*/
float CModelX::GetFloatToken() {
	GetToken();
	//atof
	//文字列をfloat型へ変換
	return atof(mToken);
}




