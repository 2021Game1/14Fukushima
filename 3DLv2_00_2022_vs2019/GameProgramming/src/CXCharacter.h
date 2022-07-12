#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include"CModelX.h"
#include"CMatrix.h"

class CXCharacter {
public:
	//初期化
	void Init(CModelX* model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	//更新処理
	void Update(CMatrix &m);
	//描画処理
	void Render();
	//アニメーションの再生終了判定
	//true:終了 false:再生中
	bool IsAnimationFinished();
	int AnimationIndex();

protected:
	CModelX* mpModel;			//モデルデータ
	int mAnimationIndex;		//アニメーション番号
	bool mAnimationLoopFlg;		//true:アニメーションを繰り返す
	float mAnimationFrame;		//アニメーションの再生フレーム
	float mAnimationFramesize;	//アニメーションの再生フレーム数
};
#endif //終了

