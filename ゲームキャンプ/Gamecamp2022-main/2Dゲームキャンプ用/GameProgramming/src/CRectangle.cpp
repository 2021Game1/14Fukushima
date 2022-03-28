#include "CRectangle.h"
//vector型のインクルード
#include <vector>
//タスクマネージャクラスのインクルード
#include"CTaskManager.h"
/*
可変長配列の定義
std;;vector<配列要素のデータ型> 配列名
*/
std::vector<CRectangle*> VectorRect;

//デフォルトコンストラクタ
CRectangle::CRectangle()
: mTag(EBLOCK)	//初期値ブロック
//37
, mEnabled(true)
, mStatus(EDISABLED)
{
	//タスクリストに追加
	CTaskManager::Get()->Add(this);

}


void CRectangle::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
	//三角形の描画
	glBegin(GL_TRIANGLES);	//三角形の描画開始
	glVertex2d(x0, y0);		//頂点１の座標を指定
	glVertex2d(x1, y1);		//頂点２の座標を指定
	glVertex2d(x2, y2);		//頂点３の座標を指定
	glEnd();	//描画終了
}

void CRectangle::DrawRectangle(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
	DrawTriangle(x0, y0, x1, y1, x2, y2);
	DrawTriangle(x0, y0, x2, y2, x3, y3);
}

void CRectangle::Render() {
	//クラスメンバの変数x,y,w,hを使用します
	DrawRectangle(x + w, y + h, x - w, y + h, x - w, y - h, x + w, y - h);
}

bool CRectangle::Conflict(const CRectangle& r)
{
	//X軸の重なりを判定
	//中心のX座標の距離を求める
	int lenX = x - r.x;
	//距離の絶対値を求める
	lenX = lenX < 0 ? -lenX : lenX;
	//距離が幅の合計より大きいとき、X軸は重なっていない
	if (lenX > w + r.w) {
		//重なってなければ、衝突していない
		//falseを返す
		return false;
	}

	if (z!=r.z) {
		//同じでなければ、衝突していない
		//falseを返す
		return false;
	}

	//X軸、Z軸ともに重なっているので、trueを返す
	return true;
}

bool CRectangle::Collision(const CRectangle &r) {
	//X軸の重なりを判定
	//中心のX座標の距離を求める
	int lenX = x - r.x;
	//距離の絶対値を求める
	lenX = lenX < 0 ? -lenX : lenX;
	//距離が幅の合計より大きいとき、X軸は重なっていない
	if (lenX > w + r.w) {
		//重なってなければ、衝突していない
		//falseを返す
		return false;
	}

	//Z軸の重なり判定
	//中心のZ座標の距離を求める
	int lenZ = z - r.z;
	//距離の絶対値を求める
	lenZ = lenZ < 0 ? -lenZ : lenZ;
	//距離が幅の合計より大きいとき、Z軸は重なっていない
	if (lenZ > z + r.z) {
		//重なってなければ、衝突していない
		//falseを返す
		return false;
	}

	//X軸、Z軸ともに重なっているので、trueを返す
	return true;
}

bool CRectangle::Collision(CRectangle *pr, int *px, int *pz) {
	//xとzを0に0を代入
	*px = 0;
	*pz = 0;
	//X軸の重なりを判定
	//中心のX座標の距離を求める
	int lenX = x - pr->x;
	//距離の絶対値を求める
	lenX = lenX < 0 ? -lenX : lenX;
	//距離が幅の合計より小さいとき、X軸は重なっている
	if (lenX < w + pr->w) {
		//戻す量を計算
		if (x < pr->x) {
			//相手が右の時は左へ移動
			*px = lenX - w - pr->w;
		}
		else {
			//相手が左の時は右へ移動
			*px = w + pr->w - lenX;
		}
	}
	else {
		//重なってなければ、衝突していない
		//falseを返す
		return false;
	}
	//Z軸の重なり判定
	//中心のX座標の距離を求める
	int lenZ = z - pr->z;
	//距離の絶対値を求める
	lenZ = lenZ < 0 ? -lenZ : lenZ;
	//距離が幅の合計より小さいとき、Z軸は重なっている
	if (lenZ < z + pr->z) {
		//戻す量を計算
		if (z < pr->z) {
			//相手が右の時は左へ移動
			*pz = lenZ - h - pr->h;
		}
		else {
			//相手が左の時は右へ移動
			*pz = h + pr->h - lenZ;
		}
	}
	else {
		//重なってなければ、衝突していない
		//falseを返す
		return false;
	}

	//X軸、Z軸ともに重なっているので、trueを返す
	return true;
}
CRectangle::~CRectangle() {
	//タスクリストに追加
	CTaskManager::Get()->Delete();
}