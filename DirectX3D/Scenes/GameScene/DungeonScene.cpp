#include "Framework.h"
#include "DungeonScene.h"
#include "Objects/Skills/SkillManager.h"

DungeonScene::DungeonScene()
{
	Audio::Get()->Add("Out_Dungeon", "Sounds/DungeonScene/icecrownraid_theforgeofsouls.ogg", true);
	Audio::Get()->Add("in_Dungeon", "Sounds/DungeonScene/ir_lightshammer1.mp3", true);
	Audio::Get()->Add("in_Dungeon2", "Sounds/DungeonScene/ir_walkj_01.mp3", true);

	Audio::Get()->Add("Open_Gate", "Sounds/DungeonScene/icecrown_door_02_main_open.ogg", true);
	Audio::Get()->Add("Open_Door", "Sounds/DungeonScene/icecrown_door_03_open.ogg", true);
	Audio::Get()->Add("IceWall_Break", "Sounds/DungeonScene/icecrown_cavein_close.ogg", true);
}

DungeonScene::~DungeonScene()
{
	delete dungeon;
}

void DungeonScene::Start()
{
	dungeon = new Dungeon();

	float Time = 7.0f;

	Audio::Get()->Play("Out_Dungeon", 0.1f);

	// 플레이어 위치 조정
	CH->GetPlayerData()->Pos() = dungeon->GetSpawnPoint_P();
	CH->GetPlayerData()->Rot().y = 3.15f;
	CH->GetPlayerData()->Update();

	for (int i = 1; i < CH->GetCharcterData().size(); i++)
	{
		CH->GetCharcterData()[i]->Pos() = CH->GetPlayerData()->Pos();
		CH->GetCharcterData()[i]->Rot().y = 3.15f;
	}
}

void DungeonScene::Update()
{
	dungeon->Update();
	CH->Update();
	MONSTER->Update();
	SKILL->Update();

	for (int i = 0; i < CH->GetCharcterData().size(); i++)
	{
		if (dungeon->IsCollision(CH->GetCharcterData()[i]->GetCollider()))
		{
			CH->GetCharcterData()[i]->SetHeight(0.0f);
		}
	}

	// 플레이어가 포탈에 닿은경우
	if (dungeon->PotalCollision(CH->GetPlayerData()->GetCollider())) 
	{
		Environment::Get()->GetLight(0)->color = { 1.0f, 1.0f, 1.0f, 1 };
		Audio::Get()->Stop("Out_Dungeon");
		SceneManager::Get()->ChangeScene("Boss");
	}

	// 1번방 문 열리기
	//     dungeon->OpenDoor(true);
	//	   Audio::Get()->Play("Open_Gate", 0.1f);
	//	   Audio::Get()->Stop("Out_Dungeon");
	//	   Audio::Get()->Play("in_Dungeon", 0.1f);

	// 1번방 문이 열렸고, 중앙 충돌체와 충돌하면 몬스터 스폰
	//     for (int i = 0; i < dungeon->SpawnMonsters_A().size(); i++)
	//	   {
	//	   	  MONSTER->SpawnSkeleton(dungeon->SpawnMonsters_A()[i]);
	//	   	  MONSTER->GetSkeleton()[MONSTER->GetSkeleton().size() - 1]->GetTransform()->Rot().y = 1.575f;
	//	   }

	// 1번방 몬스터가 스폰되었으며, 모두 죽었다면 2번방 문 열리기
	//     dungeon->OpenDoor_I(true);
	//	   Audio::Get()->Play("Open_Door", 0.1f);
	//	   Audio::Get()->Pause("in_Dungeon");
	//	   Audio::Get()->Play("in_Dungeon2", 0.1f);
	//

	// 2번방 문이 열렸고, 충앙 충돌체와 충돌하면 몬스터 스폰
	//     for (int i = 0; i < dungeon->SpawnMonsters_B().size(); i++)
	//	   {
	//	   	  MONSTER->SpawnSkeletonKnight(dungeon->SpawnMonsters_B()[i]);
	//	   	  MONSTER->GetSkeleton_Knight()[MONSTER->GetSkeleton_Knight().size() - 1]->GetTransform()->Rot().y = 1.575f;
	//	   }
	// 
	
	// 2번방 몬스터가 스폰되었으며, 모두 죽었다면 포탈 벽 부시기
	//	   dungeon->IsClear(true);
	//	   Audio::Get()->Play("IceWall_Break", 0.1f);
	//	   Audio::Get()->Play("Out_Dungeon", 0.1f);
}

void DungeonScene::PreRender()
{
}

void DungeonScene::Render()
{
	dungeon->Render();
	CH->Render();

	MONSTER->Render();
}

void DungeonScene::PostRender()
{
	SKILL->PostRender();
	CH->PostRender();

	MONSTER->PostRender();
}

void DungeonScene::GUIRender()
{
}
