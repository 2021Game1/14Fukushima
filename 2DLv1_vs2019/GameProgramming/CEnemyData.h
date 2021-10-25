#ifndef CENEMYDATA_H
#define CENEMYDATA_H

struct CENEMYDATA
{
int mType;//敵の種類
int mSype;//敵の弾の種類
int mPattern;//敵の行動パターン
int mShotpattrn;//敵の弾の発射パターン
int mEnemytime;// 敵の出現時間
int mBullettime;//敵の弾発射時間
int x;//X座標
int y;//Y座標
int mFirecount;//弾の発射間隔
int mItem;//アイテム
};
#define ENEMY_NUM 5
#endif 