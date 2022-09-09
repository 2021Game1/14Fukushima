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
	for(size_t i =0;i< mAnimationSet.size();i++)
	{
		delete mAnimationSet[i];
	}
	//マテリアル開放
	for (size_t i = 0; i < mMaterial.size(); i++) {
		delete mMaterial[i];
	}
}




CSkinWeights::CSkinWeights(CModelX* model)
	:mpFrameName(0)
	, mFrameIndex(0)
	, mIndexNum(0)
	, mpIndex(nullptr)
	, mpWeight(nullptr)
{
	model->GetToken();	//{
	model->GetToken();  //FrameName
	//フレーム名エリア確保、設定
	mpFrameName = new char[strlen(model->Token()) + 1];
	strcpy(mpFrameName, model->Token());
	/*printf("SkinWeights\\%s \n",mpFrameName);*///課題10

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

	}
	//for (int i = 0; i < mIndexNum; i++)
	//{
	//	printf("%d %f\n", mpIndex[i], mpWeight[i]);課題10
	//}
	//オフセット行列取得
	for (int i = 0; i < 16; i++) {
		mOffset.M()[i] = model->GetFloatToken();
	}
	//mOffset.Print();課題10
	model->GetToken();		//}
}

/*
CAnimation
*/
CAnimation::CAnimation(CModelX* model)
	:mpFrameName(nullptr)
	, mFrameIndex(0)
	,mKeyNum(0)
	,mpKey(nullptr)
{
	model->GetToken();//{ or Animation Name
	if (strchr(model->mToken, '{')) {
		model->GetToken();
	}
	else {
		model->GetToken();//{
		model->GetToken();//{
	}

	model->GetToken();//FrameName
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	mFrameIndex =
		model->FindFrame(model->mToken)->mIndex;
	model->GetToken();//}
	//キーの配列を保存しておく配列
	CMatrix* key[4] = { nullptr,nullptr,nullptr,nullptr };
	//時間の配列を保存しておく配列
	float* time[4] = { nullptr,nullptr,nullptr,nullptr };
	while (*model->mpPointer != '\0') {
		model->GetToken();//} or AnimationKey
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "AnimationKey") == 0) {
			model->GetToken();//{
			//データのタイプ取得
			int type = model->GetIntToken();
			//時間数取得
			mKeyNum = model->GetIntToken();
			switch (type)
			{
			case 0: //Rotation Quaternion
				//行列の配列を時間数分確保
				key[type] = new CMatrix[mKeyNum];
				//時間の配列を時間数分確保
				time[type] = new float[mKeyNum];
				//時間数分繰り返す
				for (int i = 0; i < mKeyNum; i++) {
					//時間取得
					time[type][i] = model->GetFloatToken();
					model->GetToken();//４を読み飛ばし
					//w,x,y,zを取得
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//クォータニオンから回転行列に変換
					key[type][i].Quaternion(x, y, z, w);
				}
				break;

			case 1: //拡大縮小の行列作成
				//行列の配列を時間数分確保
				key[type] = new CMatrix[mKeyNum];
				//時間の配列を時間数分確保
				time[type] = new float[mKeyNum];
				//時間数分繰り返す
				for (int i = 0; i < mKeyNum; i++) {
					//時間取得
					time[type][i] = model->GetFloatToken();
					model->GetToken();//3
					//x,y,zを取得
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//クォータニオンから回転行列に変換
					key[type][i].Scale(x, y, z);
				}
				break;

			case 2: //移動の行列作成
				//行列の配列を時間数分確保
				key[type] = new CMatrix[mKeyNum];
				//時間の配列を時間数分確保
				time[type] = new float[mKeyNum];
				//時間数分繰り返す
				for (int i = 0; i < mKeyNum; i++) {
					//時間取得
					time[type][i] = model->GetFloatToken();
					model->GetToken();//3
					//x,y,zを取得
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//クォータニオンから回転行列に変換
					key[type][i].Translate(x, y, z);
				}
				break;
			case 4://行列データを取得
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++) {
					mpKey[i].mTime = model->GetFloatToken();//Time
					model->GetToken();//16
					for (int j = 0; j < 16; j++) {
						mpKey[i].mMatrix.M()[j] = model->GetFloatToken();
						
					}
				}
				break;
				
			}
			
			model->GetToken();//}
		}
		else {
			model->SkipNode();

		}
		//Whileの終わり

		
	}
	//行列データではない場合
	if (mpKey == 0) {
		//時間数分キーを作成
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i < mKeyNum; i++) {
			//時間設定
			mpKey[i].mTime = time[2][i];//Time
			//行列作成　Size * Rotation * Position
			mpKey[i].mMatrix = key[1][i] * key[0][i] * key[2][i];
			
		}
		
	}
	//確保したエリアの開放
	for (int i = 0; i < ARRAY_SIZE(key); i++) {
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(key[i]);
	}
	
	//printf("Frame:%s\n", mpFrameName);
	//mpKey[0].mMatrix.Print();
}

/*
AnimateFreame
フレームの変換行列をアニメーションデータで更新する
*/
void CModelX::AnimateFrame()
{

	//アニメーション適用されているフレームの
	//変換行列をゼロクリアする
	for (size_t i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//重みが0は飛ばす
		if (anim->mWeight == 0)continue;
		//フレーム分(Animation分)繰り返す
		for (size_t j = 0; j < anim->mAnimation.size(); j++) {
			CAnimation* animation = anim->mAnimation[j];
			//該当するフレームの変換行列をゼロクリアする
			memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix));
		}
	}
	//アニメーションに該当するフレームの変換行列を
	//アニメーションのデータで設定する
	for (size_t i = 0; i < mAnimationSet.size(); i++) {
		CAnimationSet* anim = mAnimationSet[i];
		//重みが0は飛ばす
		if (anim->mWeight == 0)continue;
		//フレーム分(Animation分)繰り返す
		for (size_t j = 0; j < anim->mAnimation.size(); j++) {
			//フレームを取得する
			CAnimation* animation = anim->mAnimation[j];
			CModelXFrame* frame = mFrame[animation->mFrameIndex];
			//キーが無い場合は、飛ばず
			if (animation->mpKey == 0)continue;
			//時間を取得
			float time = anim->mTime;
			//最初の時間より小さい場合
			if (time < animation->mpKey[0].mTime) {
				//変換行列を0コマ目の行列で更新
				frame->mTransformMatrix += animation->mpKey[0].mMatrix * anim->mWeight;

			}
			//最後に時間より大きい場合
			else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime) {
				//変換行列を最後の駒の行列で更新
				frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix * anim->mWeight;
			}
			else {
				//時間が途中の場合
				for (int k = 1; k < animation->mKeyNum; k++) {
					//変換行列を、線形補完にて更新
					if (time < animation->mpKey[k].mTime &&
						animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime) {
						float r = (animation->mpKey[k].mTime - time) /
							(animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
						frame->mTransformMatrix +=
							(animation->mpKey[k - 1].mMatrix * r + animation->mpKey[k].mMatrix * (1 - r)) * anim->mWeight;
						break;

					}
				
				}

			}


		}

	}
	//////フレームサイズ分繰り返す
	//for (int i = 0; i < mFrame.size(); i++)
	//{
	//	printf("Frame:%s\n", mFrame[i]->mpName);
	//	mFrame[i]->mTransformMatrix.Print();
	//}
	
}
/*AnimateVertex 頂点にアニメーション適用*/
void CMesh::AnimateVertex(CModelX* model) {
	//アニメーション用の頂点エリアのクリア
	memset(mpAnimateVertex, 0, sizeof(CVector) * mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector) * mNormalNum);
	//スキンウェイトの繰り返し
	for (size_t i = 0; i < mSkinWeights.size(); i++) {
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//オフセット行列とフレーム行列を合成
		CMatrix mSkinningMatrix = mSkinWeights[i]->mOffset * model->mFrame[frameIndex]->CombinedMatrix();
		//頂点数分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++) {
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//法線を正規化する
	for (int i = 0; i < mNormalNum; i++){
		mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
	}
}




/*
CAnimationSet
*/
CAnimationSet::CAnimationSet(CModelX* model) 
:mpName(nullptr)
,mTime(0)
,mWeight(0)
,mMaxTime(0)
{
	model->mAnimationSet.push_back(this);
	model->GetToken();
	//アニメーション名を退避
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);
	model->GetToken();
	while (*model->mpPointer != '\0'){
		model->GetToken();//} or Animation
		if (strchr(model->mToken, '}'))break;
		if(strcmp(model->mToken,"Animation")==0){
			//Animation要素読み込み
			mAnimation.push_back(new CAnimation(model));
		}

	}
	
	//終了時間設定
	mMaxTime = mAnimation[0]->mpKey[mAnimation[0]->mKeyNum - 1].mTime;
	/*printf("AnimationSet:%s\n",mpName);*///課題11
}
/*
AnimateVertex
頂点にアニメーションを適用する
*/
void CModelX::AnimeteVertex() {
	//フレーム数分繰り返し
	for (size_t i = 0; i < mFrame.size(); i++) {
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum > 0){
			//頂点をアニメーションで更新する
			mFrame[i]->mMesh.AnimateVertex(this);
		}
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
			//フレーム名取得
			model->GetToken();
			if (strchr(model->mToken,'{')){
				//フレーム名なし:スキップ
				model->SkipNode();
				model->GetToken();//}
			}
			else {
				//フレームが無ければ
				if (model->FindFrame(model->mToken)==0)
				{
					//フレームを作成し、 子フレームの配列に追加
					mChild.push_back(new CModelXFrame(model));
				}

			}
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

//#endif //DEBUG
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
	mpAnimateVertex = new CVector[mVertexNum];

	//頂点数分データを取り込む
	for (int i = 0; i < mVertexNum; i++) {
		mpVertex[i].X(model->GetFloatToken());
		mpVertex[i].Y(model->GetFloatToken());
		mpVertex[i].Z(model->GetFloatToken());

	//デバッグバージョンのみ有効
	}
	mFaceNum = model->GetIntToken();		//面数読み込み

	//頂点数は1面に３頂点
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3)
	{
		model->GetToken();//頂点数読み飛ばし
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
		//デバッグバージョンのみ有効

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
			mpAnimateNormal = new CVector[mNormalNum];
			for (int i = 0; i < mNormalNum; i += 3) {
				model->GetToken();//3
				ni = model->GetIntToken();
				mpNormal[i] = pNormal[ni];
				mpNormal[i + 1] = pNormal[ni];
				ni = model->GetIntToken();
				mpNormal[i + 2] = pNormal[ni];
				ni = model->GetIntToken();

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
		for (int i = 0; i < mMaterialNum; i++) {
			model->GetToken(); //Material
			if (strcmp(model->mToken, "Material") == 0) {
				mMaterial.push_back(new CMaterial(model));
			}
			else {
				//{既出
				model->GetToken(); //MaterialName
				mMaterial.push_back(
					model->FindMaterial(model->mToken));
				model->GetToken(); //}

			}
		}
		model->GetToken();   //}End of MeshMaterialList
	}
	else if (strcmp(model->mToken,"SkinWeights")==0){
			//CSkinWeightsクラスのインスタンスを作成し、配列に追加
			mSkinWeights.push_back(new CSkinWeights(model));
	}
	else if(strcmp(model->mToken, "MeshTextureCoords") == 0){
			model->GetToken();//{
			//テクスチャ座標の時
			int textureCoordsNum = model->GetIntToken() *2;
			//テクスチャ座標数を取得
			mpTextureCoords = new float[textureCoordsNum];
			//テクスチャ座標のデータを配列に取り込む
			for (int i = 0; i < textureCoordsNum; i++) {
				mpTextureCoords[i] = model->GetFloatToken();
			}
			model->GetToken();	//}
	}
	else {
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

	//ダミールートフレームの作成
	CModelXFrame* p = new CModelXFrame();
	//名前なし
	p->mpName = new char[1];
	p->mpName[0] = '\0';
	//フレーム配列に追加
	mFrame.push_back(p);

	//文字列の最後まで繰り返し
	while (*mpPointer != '\0') {
		GetToken();		//単語の取得
		//template 読み飛ばし
		if (strcmp(mToken, "template") == 0) {
			SkipNode();
		}
		//Materialの時
		else if (strcmp(mToken, "Material") == 0) {
			new CMaterial(this);
		}
		//単語がFrameの場合
		else if (strcmp(mToken, "Frame") == 0) {
			//フレーム名取得
			GetToken();
			if (strchr(mToken,'{')){
				//フレーム名なし:スキップ
				SkipNode();
				GetToken();//}
			}
			else {
				//フレームが無ければ
				if (FindFrame(mToken) == 0) {

					//フレームを作成する
					p->mChild.push_back(
					new CModelXFrame(this));
				}
			}

		}
		//単語がAnimationSetの場合
		else if (strcmp(mToken, "AnimationSet") == 0) {
			new CAnimationSet(this);
		}
	}
	SAFE_DELETE_ARRAY(buf);	//確保した領域を開放する
	//スキンウェイトのフレーム番号設定
	SetSkinWeightFrameIndex();
}

void CMesh::Render() {
	/*頂点データ,法線データの配列を有効にする*/
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//テクスチャマッピングを有効にする
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	/*頂点データ,法線データ,テクスチャ座標の場所を指定する*/
	glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoords);

	/*頂点のインデックスの場所を指定して図形を描画する*/
	for (int i = 0; i < mFaceNum; i++) {
		//マテリアルを適用する
		mMaterial[mpMaterialIndex[i]]->Enabled();
		glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		mMaterial[mpMaterialIndex[i]]->Disabled();
	}
	/*頂点データ,法線データの配列を無効にする*/
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}
/*
FindFrame
フレーム名に該当するフレームのアドレスを返す
*/
CModelXFrame* CModelX::FindFrame(char* name) {
	//イテレータの作成
	std::vector<CModelXFrame*>::iterator itr;
	//先頭から最後まで繰り返す
	for (itr = mFrame.begin();itr != mFrame.end(); itr++){
		//名前が一致したか?
		if (strcmp(name, (*itr)->mpName) == 0) {
			//一致したらそのアドレスを返す
			return *itr;
		}
	}
	//一致したらするフレームが無い場合は　nullptrを返す
	return nullptr;
}
/*
AnimateCombined
合成行列の作成
*/
void CModelXFrame::AnimateCombined(CMatrix* parent) {
	//自分の変換行列に、親からの変換行列を掛ける
	mCombinedMatrix = mTransformMatrix * (*parent);
	//子フレームの合成行列を作成
	for (size_t i = 0; i < mChild.size(); i++) {
		mChild[i]->AnimateCombined(&mCombinedMatrix);
	}
		/*printf("Frame:%s\n", mpName);
		mCombinedMatrix.Print();*/

}
/*
SetSkinWeightFrameIndex
スキンウェイトにフレーム番号を設定する
*/
void CModelX::SetSkinWeightFrameIndex() {
	//フレーム数分繰り返し
	for (size_t i = 0; i < mFrame.size(); i++) {
		//メッシュ面があれば
		if (mFrame[i]->mMesh.mFaceNum > 0) {
			//スキンウェイト分繰り返し
			for (size_t j = 0; j < mFrame[i]->mMesh.mSkinWeights.size(); j++) {
				//フレーム名のフレームを取得する
				CModelXFrame* frame = FindFrame(mFrame[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//フレーム番号を設定する
				mFrame[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;

			}
		}
	}
}
/*
FindMaterial
マテリアル名に該当するマテリアルを返却する
*/
CMaterial* CModelX::FindMaterial(char* name) {
	//マテリアル配列のイテレータ作成
	std::vector<CMaterial*>::iterator itr;
	//マテリアル配列の順に検索
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++) {
		//名前が一致すればマテリアルのポインタを返却
		if (strcmp(name,(*itr)->Name())==0){
			return *itr;
		}
	}
	//無い時はNULLを返す
	return NULL;
}

void CModelX::AnimateVertex(CMatrix* mat) {
	//フレーム数分繰り返し
	for (size_t i = 0; i < mFrame.size(); i++){
		//メッシュに面があれば
		if (mFrame[i]->mMesh.mFaceNum > 0){
			//頂点をアニメーションで更新する
			mFrame[i]->
				mMesh.AnimateVertex(mat);
		}
	}
}

void CMesh::AnimateVertex(CMatrix* mat) {
	//アニメーション用の頂点エリアクリア
	memset(mpAnimateVertex, 0, sizeof(CVector) * mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector) * mNormalNum);
	//スキンウェイト分繰り返し
	for (size_t i = 0; i < mSkinWeights.size(); i++){
		//フレーム番号取得
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//フレーム合成行列にオフセット行列を合計
		CMatrix mSkinningMatrix = mSkinWeights[i]->mOffset * mat[frameIndex];
		//頂点数分繰り返し
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++){
			//頂点番号取得
			int index = mSkinWeights[i]->mpIndex[j];
			//重み取得
			float weight = mSkinWeights[i]->mpWeight[j];
			//頂点と法線を更新する
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix * weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix * weight;
		}
	}
	//法線を正規化する
	for (int i = 0; i < mNormalNum; i++) {
		mpAnimateNormal[i] = mpAnimateNormal[i].Normalize();
	}
}


/*
Render
メッシュの面数が0以外なら描画する
*/
void CModelXFrame::Render() {
	if (mMesh.mFaceNum != 0) {
		mMesh.Render();
	}

}

/*
Render
全てのフレームの描画処理を呼び出す
*/
void CModelX::Render() {
	for (size_t i = 0; i < mFrame.size(); i++) {
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

std::vector<CAnimationSet*>& CModelX::AnimationSet()
{
	return mAnimationSet;
}

std::vector<CModelXFrame*>& CModelX::Frames(){
	
	return mFrame;

}
std::vector<CMaterial*>& CModelX::Material() {
	return mMaterial;
}
const CMatrix& CModelXFrame::CombinedMatrix() {
	return mCombinedMatrix;
}
float CAnimationSet::Time() {
	return mTime;
}
float CAnimationSet::MaxTime() {
	return mMaxTime;
}



