#include"CStone.h"



//ポインタをnullptrに設定する
CStone* CStone::mpStone_Instance = nullptr;												//インスタンス変数の初期化

//ポインタを外部クラスから参照できるように設定
CStone* CStone::GetInstance()
{
	//ポインタを返す
	return mpStone_Instance;
}

//コライダ初期化
CStone::CStone()
	:mStone_Type(CStone::EStoneType::ETYPE_STONE_POS_1)
	,Stone_Position_X(NULL)
	, Stone_Position_Y(NULL)
	, Stone_Position_Z(NULL)
	, Stone_Scale_X(NULL)
	, Stone_Scale_Y(NULL)
	, Stone_Scale_Z(NULL)
	, Stone_Rotation_X(NULL)
	, Stone_Rotation_Y(NULL)
	, Stone_Rotation_Z(NULL)
{
	//データベースの呼び出し
	StoneTable();

	//マップのポインタをthisにする
	mpStone_Instance = this;

	//マップモデルファイルの入力
	gStone_Model.Load(STONE_MODEL_OBJ);
	//マップのコライダファイルの入力
	gStone_Model_Collision.Load(STONE_COLLISION_OBJ);

	//モデル設定
	Model(&gStone_Model);
	//出現位置の設定
	Position(CVector(Stone_Position_X, Stone_Position_Y, Stone_Position_Z));
	//モデルのスケール設定
	Scale(CVector(Stone_Scale_X, Stone_Scale_Y, Stone_Scale_Z));
	//モデルの回転設定
	Rotation(CVector(Stone_Rotation_X, Stone_Rotation_Y, Stone_Rotation_Z));
	//移動行列
	CTransform::Update();

	//石の移動行列
	mBackGroundMatrix.Translate(Stone_Position_X, Stone_Position_Y, Stone_Position_Z);
	//親インスタンスと親行列はなし
	mColliderMesh.Set(this, &mBackGroundMatrix, &gStone_Model_Collision);
	//タスクマネージャへの追加処理
	CTaskManager::Get()->Remove(this);//削除して
	CTaskManager::Get()->Add(this);//追加する
}

void CStone::Model(CModel* model)
{
	//モデル設定
	CCharacter::Model(model);
}
void CStone::StoneTable()
{
	//生成する敵の種類を判別
	switch (mStone_Type) {
	case CStone::EStoneType::ETYPE_STONE_POS_1:
	{
		OX::Table table(STONE_DATATABLE);
		Stone_Position_X = table["Stone_Position_X"]["Value"].fVal;//障害物のポジション設定X座標
		Stone_Position_Y = table["Stone_Position_Y"]["Value"].fVal;//障害物のポジション設定Y座標
		Stone_Position_Z = table["Stone_Position_Z"]["Value"].fVal;//障害物のポジション設定Z座標
		Stone_Scale_X = table["Stone_Scale_X"]["Value"].fVal;//障害物のモデルスケールのX座標
		Stone_Scale_Y = table["Stone_Scale_Y"]["Value"].fVal;//障害物のモデルスケールのY座標
		Stone_Scale_Z = table["Stone_Scale_Z"]["Value"].fVal;//障害物のモデルスケールのZ座標
		Stone_Rotation_X = table["Stone_Rotation_X"]["Value"].fVal;//障害物のモデルの回転X座標
		Stone_Rotation_Y = table["Stone_Rotation_Y"]["Value"].fVal;//障害物のモデルの回転Y座標
		Stone_Rotation_Z = table["Stone_Rotation_Z"]["Value"].fVal;//障害物のモデルの回転Z座標
		//優先度を設定
		mPriority = STONE_PRIORITY;
		//タグの設定
		mTag = CCharacter::ETag::ESTONE;
	}
	break;

	case CStone::EStoneType::ETYPE_STONE_POS_2:
	{
		OX::Table table(STONE_DATATABLE);
		Stone_Position_X = table["Stone_Position_X"]["Value"].fVal;//障害物のポジション設定X座標
		Stone_Position_Y = table["Stone_Position_Y"]["Value"].fVal;//障害物のポジション設定Y座標
		Stone_Position_Z = table["Stone_Position_Z"]["Value"].fVal;//障害物のポジション設定Z座標
		Stone_Scale_X = table["Stone_Scale_X"]["Value"].fVal;//障害物のモデルスケールのX座標
		Stone_Scale_Y = table["Stone_Scale_Y"]["Value"].fVal;//障害物のモデルスケールのY座標
		Stone_Scale_Z = table["Stone_Scale_Z"]["Value"].fVal;//障害物のモデルスケールのZ座標
		Stone_Rotation_X = table["Stone_Rotation_X"]["Value"].fVal;//障害物のモデルの回転X座標
		Stone_Rotation_Y = table["Stone_Rotation_Y"]["Value"].fVal;//障害物のモデルの回転Y座標
		Stone_Rotation_Z = table["Stone_Rotation_Z"]["Value"].fVal;//障害物のモデルの回転Z座標
		//優先度を設定
		mPriority = STONE_PRIORITY;
		//タグの設定
		mTag = CCharacter::ETag::ESTONE;
	}
	break;

	case CStone::EStoneType::ETYPE_STONE_POS_3:
	{
		OX::Table table(STONE_DATATABLE);
		Stone_Position_X = table["Stone_Position_X"]["Value"].fVal;//障害物のポジション設定X座標
		Stone_Position_Y = table["Stone_Position_Y"]["Value"].fVal;//障害物のポジション設定Y座標
		Stone_Position_Z = table["Stone_Position_Z"]["Value"].fVal;//障害物のポジション設定Z座標
		Stone_Scale_X = table["Stone_Scale_X"]["Value"].fVal;//障害物のモデルスケールのX座標
		Stone_Scale_Y = table["Stone_Scale_Y"]["Value"].fVal;//障害物のモデルスケールのY座標
		Stone_Scale_Z = table["Stone_Scale_Z"]["Value"].fVal;//障害物のモデルスケールのZ座標
		Stone_Rotation_X = table["Stone_Rotation_X"]["Value"].fVal;//障害物のモデルの回転X座標
		Stone_Rotation_Y = table["Stone_Rotation_Y"]["Value"].fVal;//障害物のモデルの回転Y座標
		Stone_Rotation_Z = table["Stone_Rotation_Z"]["Value"].fVal;//障害物のモデルの回転Z座標
		//優先度を設定
		mPriority = STONE_PRIORITY;
		//タグの設定
		mTag = CCharacter::ETag::ESTONE;
	}
	break;
	}
}

//衝突処理
void CStone::Collision(CCollider* m, CCollider* o) {
	switch (m->Type())
	{
		//相手のコライダが球の場合
	case CCollider::EType::ESPHERE: {
		//コライダのmとoが衝突しているかの判定
		if (CCollider::Collision(m, o)) {
			//行列の更新
			CTransform::Update();
		}
	}
		//相手のコライダがカプセルの場合
	case CCollider::EType::ECAPSUL: {
		CVector adjust;//調整用ベクトル
		if (CCollider::CollisionCapsule(m, o, &adjust))
		{
			//行列の更新
			CTransform::Update();
		}
	}

	}
}
void CStone::SetIsType(EStoneType type) {
	mStone_Type = type;
}

//位置を設定する
void CStone::GetPos()
{
	
}
//敵のスケールを取得
void CStone::GetScale()
{

}
//敵の回転値を取得する
void CStone::GetRotation()
{

}


