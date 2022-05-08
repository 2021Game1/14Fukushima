#include <stdio.h>
#include <string.h>

#include "CModelX.h"
#include "glut.h"

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
		else {
			//上記以外の要素は読み飛ばす
			model->SkipNode();
		}

	}
	//デバッグバージョンのみ有効
#ifdef _DEBUG
	printf("%s\n", mpName);
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
		////単語がAnimationSetの場合
		//if (strcmp(mToken, "AnimationSet") == 0) {
		//	printf("%s", mToken);//AnimationSet出力
		//	GetToken();			//AnimationSet名を取得
		//	printf("%s\n", mToken);//AnimationSet名を取得
		//}
	}
	SAFE_DELETE_ARRAY(buf);	//確保した領域を開放する
}








