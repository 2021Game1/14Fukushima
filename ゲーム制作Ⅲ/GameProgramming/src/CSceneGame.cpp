#include "CSceneGame.h"
//OpenGL
#include "glut.h"
#include "CTable.h"


CSceneGame::~CSceneGame()
{
	CTaskManager::Get()->Delete();
}

void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;
	mRes.Init();
	CRes::GetInstance()->GetinSoundBgmGame().Repeat(0.2);
	//影の設定
	float shadowColor[] = { 0.4f, 0.4f, 0.4f, 0.2f };	//影の色
	float lightPos[] = { 50.0f, 160.0f, 50.0f };		//光源の位置
	mShadowMap.Init(TEXWIDTH, TEXHEIGHT, WholeRender, shadowColor, lightPos); //シャドウマップ初期化
	int _tmain(int argc, char* argv[]);
}

void CSceneGame::Update() {
	
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		if (CKey::Once(VK_RETURN))
		{
	
			mScene = ETITLE;
		}
	}
	if (CXEnemy::EEnemyState::EDEATH) {
		CRes::GetInstance()->GetinSoundBgmGame().Stop();
		
		if (CKey::Once(VK_RETURN))
		{
	
			mScene = ETITLE;
		}
	}

	//更新処理
	CTaskManager::Get()->Update();
	//衝突処理
	CCollisionManager::Get()->Collision();
	//タスクリスト削除
	CTaskManager::Get()->Delete();
}
void CSceneGame::Render() {
	CTaskManager::Get()->Draw();
	mShadowMap.Render();
	CTaskManager::Get()->Render2D();

	//デバッグバージョンのみ有効
#ifdef _DEBUG
	//コライダの描画
	CCollisionManager::Get()->Render();
#endif

	//2Dの描画開始
	CUtil::Start2D(0, 800, 0, 600);
	if (CXPlayer::GetInstance()->GetHp() == 0) {
		CRes::GetInstance()->GetinGameOverImage().DrawImage(0, 800, 0, 600, 0, 800, 600, 0);
	}
	if (CXEnemy::EEnemyState::EDEATH) {
		CRes::GetInstance()->GetinGameClearImage().DrawImage(0, 800, 0, 600, 0, 800, 600, 0);
	}
	//2Dの描画終了
	CUtil::End2D();
}
void WholeRender() {
	//タスク描画
	CTaskManager::Get()->Render();
}
CScene::EScene CSceneGame::GetNextScene()
{
	return mScene;
}

void output(OX::Table& Ctable, const char* id) {
	OX::Table::Record& r = Ctable[id];
	printf("%s\t%s\t%d\n", r["ID"].str.c_str(), r["Name"].str.c_str(), r["Value"].iVal);
}

int _tmain(int argc, char* argv[])
{
	OX::Table table("res\\Enemy\\EnemyData.txt");

	printf("ID\tName\tValue\n");
	output(table, "Enemy_Priority");
	output(table, "Enemy_Speed_WalkPattern");
	output(table, "Enemy_Speed_DashPattern");
	output(table, "Enemy_Walk_Dis");
	output(table, "Enemy_Dash_Dis");
	output(table, "Enemy_Walk_Dis_Max");
	output(table, "Enemy_Dash_Dis_Max");
	output(table, "Enemy_Attack_Dis");
	output(table, "Enemy_Attack_Reception");
	output(table, "Enemy_Attack_Outreception");
	output(table, "Enemy_Attack_Walk_Rand");
	output(table, "Enemy_Attack_Dash_Rand");
	output(table, "Enemy_Damage_PlayerSp1");
	output(table, "Enemy_Damage_PlayerSp2");
	output(table, "Enemy_Damage_PlayerSp3");
	output(table, "Enemy_Idle_Animation_Frame");
	output(table, "Enemy_Move_Animation_Frame");
	output(table, "Enemy_Dash_Animation_Frame");
	output(table, "Enemy_Attack1_Animation_Frame");
	output(table, "Enemy_Attack2_Animation_Frame");
	output(table, "Enemy_Attack3_Animation_Frame");
	output(table, "Enemy_Knockback_Animation_Frame");
	output(table, "Enemy_Death_Animation_Frame");
	output(table, "Enemy_Animation_No_Attack_1");
	output(table, "Enemy_Animation_No_Attack_2");
	output(table, "Enemy_Animation_No_Attack_3");
	output(table, "Enemy_Animation_No_Walk");
	output(table, "Enemy_Animation_No_Dash");
	output(table, "Enemy_Animation_No_Idle");
	output(table, "Enemy_Animation_No_Knockback");
	output(table, "Enemy_Animation_No_Death");
	output(table, "Enemy_Position_X");
	output(table, "Enemy_Position_Y");
	output(table, "Enemy_Position_Z");
	output(table, "Enemy_Scale_X");
	output(table, "Enemy_Scale_Y");
	output(table, "Enemy_Scale_Z");
	output(table, "Enemy_Rotation_X");
	output(table, "Enemy_Rotation_Y");
	output(table, "Enemy_Rotation_Z");
	output(table, "Enemy_ColCapsule_Body_X");
	output(table, "Enemy_ColCapsule_Body_Top_Y");
	output(table, "Enemy_ColCapsule_Body_Bottom_Y");
	output(table, "Enemy_ColCapsule_Body_Z");
	output(table, "Enemy_ColCapsule_Body_Size");
	output(table, "Enemy_ColSphere_Body_X");
	output(table, "Enemy_ColSphere_Body_Y");
	output(table, "Enemy_ColSphere_Body_Z");
	output(table, "Enemy_ColSphere_Body_Size");
	output(table, "Enemy_ColSphere_Rightarm_Size");
	output(table, "Enemy_ColSphere_Leftarm_Size");
	output(table, "Enemy_Probability_Low_Set1");
	output(table, "Enemy_Probability_Max_Set1");
	output(table, "Enemy_Probability_Low_Set2");
	output(table, "Enemy_Probability_Max_Set2");
	output(table, "Enemy_Gravity");
	output(table, "Enemy_Hp");
	output(table, "Enemy_Hp_Max");
	output(table, "Enemy_Death_Hp");
	return 0;
}


