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

	//if (player->Pos().y < 0) player->Pos().y = 0; // �÷��̾ �ٴ����� �����°� ����
	//if (player->isjump && !dungeon->IsCollision(player->GetCollider())) // �������̾ƴϰ� ��(������Ʈ)���������������� �ڵ����� ������ 
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
