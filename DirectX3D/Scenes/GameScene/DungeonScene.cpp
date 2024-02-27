#include "Framework.h"
#include "DungeonScene.h"

DungeonScene::DungeonScene()
{
	
}

DungeonScene::~DungeonScene()
{
	delete dungeon;
}

void DungeonScene::Start()
{
	dungeon = new Dungeon();

	Audio::Get()->Add("Out_Dungeon", "Sounds/DungeonScene/icecrownraid_theforgeofsouls.ogg", true);
	Audio::Get()->Add("in_Dungeon", "Sounds/DungeonScene/ir_lightshammer1.mp3", true);
	Audio::Get()->Add("in_Dungeon2", "Sounds/DungeonScene/ir_walkj_01.mp3", true);

	Audio::Get()->Add("Open_Gate", "Sounds/DungeonScene/icecrown_door_02_main_open.ogg", true);
	Audio::Get()->Add("Open_Door", "Sounds/DungeonScene/icecrown_door_03_open.ogg", true);
	Audio::Get()->Add("IceWall_Break", "Sounds/DungeonScene/icecrown_cavein_close.ogg", true);

	float Time = 7.0f;

	Audio::Get()->Play("Out_Dungeon", 0.1f);

	// 플레이어 위치 조정
	//player->Rot().y += 3.15f;
	//PLAYER->Pos() = dungeon->GetSpawnPoint_P();
	//player->Pos() = dungeon->GetSpawnPoint_P();
	CH->GetPlayerData()->Pos() = dungeon->GetSpawnPoint_P();

	for (int i = 1; i < CH->GetCharcterData().size(); i++)
	{
		CH->GetCharcterData()[i]->Pos() = CH->GetPlayerData()->Pos();
	}
	

	// 몬스터스폰 좌표값 주기
	//TestMonsterSpawnPos_A.resize(11);
	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i)
	//{
	//	TestMonsterSpawnPos_A[i] = new Model("Skeleton");
	//	TestMonsterSpawnPos_A[i]->Rot().y += 1.575f;
	//	vector<Vector3> spawnPoints = dungeon->SpawnMonsters_A();
	//	TestMonsterSpawnPos_A[i]->Pos() = spawnPoints[i];
	//	//MONSTER->SpawnSkeleton(TestMonsterSpawnPos_A[i]);
	//}
	//TestMonsterSpawnPos_B.resize(10);
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i)
	//{
	//	TestMonsterSpawnPos_B[i] = new Model("Skeleton_Knight");
	//	TestMonsterSpawnPos_B[i]->Rot().y += 1.575f;
	//	vector<Vector3> spawnPoints = dungeon->SpawnMonsters_B();
	//	TestMonsterSpawnPos_B[i]->Pos() = spawnPoints[i];
	//	//MONSTER->SpawnSkeletonKnight(TestMonsterSpawnPos_B[i]);
	//}
}

void DungeonScene::Update()
{
	dungeon->Update();
	CH->Update();

	if (dungeon->IsCollision(CH->GetPlayerData()->GetCollider()))
	{
		CH->GetPlayerData()->SetHeight(CH->GetPlayerData()->Pos().y);
	}
	//else
	//{
	//	CH->GetPlayerData()->SetHeight(0.0f);
	//}

	
	//if (player->Pos().y < 0) player->Pos().y = 0; // 플레이어가 바닥으로 꺼지는것 방지
	//if (player->isjump && !dungeon->IsCollision(player->GetCollider())) // 점프중이아니고 맵(오브젝트)에닿아있지않은경우 자동으로 떨어짐 
	//{
	//	player->Pos().y -= gravity * DELTA;
	//} 
	//if (dungeon->IsCollision(player->GetCollider()));
	if (dungeon->PotalCollision(CH->GetPlayerData()->GetCollider())) // 플레이어가 포탈에 닿은경우
	{
		Environment::Get()->GetLight(0)->color = { 1.0f, 1.0f, 1.0f, 1 };
		Audio::Get()->Stop("Out_Dungeon");
		SceneManager::Get()->ChangeScene("Boss");
	}

	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i]->UpdateWorld();
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i]->UpdateWorld();

	if (!KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_DOWN(VK_UP)) 
		{
			dungeon->OpenDoor(true);
			Audio::Get()->Play("Open_Gate", 0.1f);
			Audio::Get()->Stop("Out_Dungeon");
			Audio::Get()->Play("in_Dungeon", 0.1f);
		} 
		if (KEY_PRESS(VK_RIGHT)) 
		{
			dungeon->OpenDoor_I(true);
			Audio::Get()->Play("Open_Door", 0.1f);
			Audio::Get()->Pause("in_Dungeon");
			Audio::Get()->Play("in_Dungeon2", 0.1f);
		}
		if (KEY_PRESS(VK_DOWN)) 
		{
			dungeon->IsClear(true);
			Audio::Get()->Play("IceWall_Break", 0.1f);
			Audio::Get()->Play("Out_Dungeon", 0.1f);
		}
	}
}

void DungeonScene::PreRender()
{
}

void DungeonScene::Render()
{
	dungeon->Render();
	CH->Render();
	
	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i]->Render();
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i]->Render();
}

void DungeonScene::PostRender()
{
	CH->PostRender();
}

void DungeonScene::GUIRender()
{
}
