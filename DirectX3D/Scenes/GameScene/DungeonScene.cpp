#include "Framework.h"
#include "DungeonScene.h"

DungeonScene::DungeonScene()
{
	dungeon = new Dungeon();
}

DungeonScene::~DungeonScene()
{
	delete dungeon;
}

void DungeonScene::Start()
{
	// �÷��̾� ��ġ ����
	//player->Rot().y += 3.15f;
	//PLAYER->Pos() = dungeon->GetSpawnPoint_P();
	//player->Pos() = dungeon->GetSpawnPoint_P();
	

	// ���ͽ��� ��ǥ�� �ֱ�
	TestMonsterSpawnPos_A.resize(11);
	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i)
	{
		TestMonsterSpawnPos_A[i] = new Model("Skeleton");
		TestMonsterSpawnPos_A[i]->Rot().y += 1.575f;
		vector<Vector3> spawnPoints = dungeon->SpawnMonsters_A();
		TestMonsterSpawnPos_A[i]->Pos() = spawnPoints[i];
		//MONSTER->SpawnSkeleton(TestMonsterSpawnPos_A[i]);
	}
	TestMonsterSpawnPos_B.resize(10);
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i)
	{
		TestMonsterSpawnPos_B[i] = new Model("Skeleton_Knight");
		TestMonsterSpawnPos_B[i]->Rot().y += 1.575f;
		vector<Vector3> spawnPoints = dungeon->SpawnMonsters_B();
		TestMonsterSpawnPos_B[i]->Pos() = spawnPoints[i];
		//MONSTER->SpawnSkeletonKnight(TestMonsterSpawnPos_B[i]);
	}
}

void DungeonScene::Update()
{
	dungeon->Update();
	
	//if (player->Pos().y < 0) player->Pos().y = 0; // �÷��̾ �ٴ����� �����°� ����
	//if (player->isjump && !dungeon->IsCollision(player->GetCollider())) // �������̾ƴϰ� ��(������Ʈ)���������������� �ڵ����� ������ 
	//{
	//	player->Pos().y -= gravity * DELTA;
	//} 
	//if (dungeon->IsCollision(player->GetCollider()));
	//if (dungeon->PotalCollision(player->GetCollider())) // �÷��̾ ��Ż�� �������
	//{
	//	
	//}

	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i]->UpdateWorld();
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i]->UpdateWorld();

	if (!KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_DOWN(VK_UP)) dungeon->OpenDoor(true);
		if (KEY_PRESS(VK_RIGHT)) dungeon->OpenDoor_I(true);
		if (KEY_PRESS(VK_DOWN)) dungeon->IsClear(true);
	}
}

void DungeonScene::PreRender()
{
}

void DungeonScene::Render()
{
	dungeon->Render();
	
	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i]->Render();
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i]->Render();
}

void DungeonScene::PostRender()
{
}

void DungeonScene::GUIRender()
{
}