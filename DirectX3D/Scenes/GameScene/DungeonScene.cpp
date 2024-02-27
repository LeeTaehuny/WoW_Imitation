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
	// 플레이어 위치 조정
	//player->Rot().y += 3.15f;
	//PLAYER->Pos() = dungeon->GetSpawnPoint_P();
	//player->Pos() = dungeon->GetSpawnPoint_P();
	

	// 몬스터스폰 좌표값 주기
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
	
	//if (player->Pos().y < 0) player->Pos().y = 0; // 플레이어가 바닥으로 꺼지는것 방지
	//if (player->isjump && !dungeon->IsCollision(player->GetCollider())) // 점프중이아니고 맵(오브젝트)에닿아있지않은경우 자동으로 떨어짐 
	//{
	//	player->Pos().y -= gravity * DELTA;
	//} 
	//if (dungeon->IsCollision(player->GetCollider()));
	//if (dungeon->PotalCollision(player->GetCollider())) // 플레이어가 포탈에 닿은경우
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
