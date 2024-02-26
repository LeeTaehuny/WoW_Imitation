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
	//TestMonsterSpawnPos_A.resize(11);
	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i)
	//{
	//	TestMonsterSpawnPos_A = dungeon->SpawnMonsters_A();
	//	MONSTER->SpawnSkeleton(TestMonsterSpawnPos_A[i]);
	//}
	//TestMonsterSpawnPos_B.resize(10);
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) 
	//{
	//	TestMonsterSpawnPos_B = dungeon->SpawnMonsters_B();
	//	MONSTER->SpawnSkeletonKnight(TestMonsterSpawnPos_B[i]);
	//}
}

void DungeonScene::Update()
{
	dungeon->Update();

	if (!KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_DOWN(VK_UP)) dungeon->OpenDoor(true);
		if (KEY_PRESS(VK_RIGHT)) dungeon->OpenDoor_I(true);
		if (KEY_PRESS(VK_DOWN)) dungeon->IsClear(true);
	}

	//if (player->Pos().y < 0) player->Pos().y = 0; // 플레이어가 바닥으로 꺼지는것 방지
	//if (player->isjump && !dungeon->IsCollision(player->GetCollider())) // 점프중이아니고 맵(오브젝트)에닿아있지않은경우 자동으로 떨어짐 
	//{
	//	player->Pos().y -= gravity * DELTA;
	//} 
	//if (dungeon->IsCollision(player->GetCollider()));
}

void DungeonScene::PreRender()
{
}

void DungeonScene::Render()
{
	dungeon->Render();
}

void DungeonScene::PostRender()
{
}

void DungeonScene::GUIRender()
{
}
