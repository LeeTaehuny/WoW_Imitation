#include "Framework.h"
#include "TestDungeonScene.h"

TestDungeonScene::TestDungeonScene()
{
	dungeon = new Dungeon();
	//terrain = new TerrainLOD(L"Textures/HeightMaps/TestTerrain_H.png");

	instaning = new ModelAnimatorInstancing("ProtectionWarrior");
	instaning->ReadClip("Idle_1");
	instaning->ReadClip("Attack_1");
	instaning->ReadClip("Walk_F");
	instaning->ReadClip("Walk_B");
	instaning->ReadClip("Walk_L");
	instaning->ReadClip("Walk_R");
	instaning->ReadClip("Die");
	instaning->ReadClip("Hit");
	instaning->ReadClip("Jump");
	instaning->ReadClip("S_Casting");
	
	Transform* transform = instaning->Add();
	player = new ProtectionWarrior_in(CreatureType::Player, transform, instaning, 0);
	player->Rot().y += 3.15f;
	PLAYER = new Model("ProtectionWarrior");
	PLAYER->Pos() = dungeon->GetSpawnPoint_P();
	player->Pos() = dungeon->GetSpawnPoint_P();

	//dungeon->Rot().y += 3.15f;
	//dungeon->Scale() *= 6.0f;

	TestMonsterSpawnPos_A.resize(11);
	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i] = new SphereCollider(2);
	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i] = new Model("ProtectionWarrior");
	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i)
	{
		TestMonsterSpawnPos_A[i]->Rot().y += 1.575f;
		vector<Vector3> spawnPoints = dungeon->SpawnMonsters_A();
		if (i < spawnPoints.size())
		{
			TestMonsterSpawnPos_A[i]->Pos() = spawnPoints[i];
		}
		else
		{
			//좌표 개수가 모델 개수보다 적을 경우
		}
	}
	TestMonsterSpawnPos_B.resize(10);
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i] = new SphereCollider(2);
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i] = new Model("ProtectionWarrior");
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i)
	{
		TestMonsterSpawnPos_B[i]->Rot().y += 1.575f;
		vector<Vector3> spawnPoints = dungeon->SpawnMonsters_B();
		if (i < spawnPoints.size())
		{
			TestMonsterSpawnPos_B[i]->Pos() = spawnPoints[i];
		}
		else
		{
			//좌표 개수가 모델 개수보다 적을 경우
		}
	}

	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i]->UpdateWorld();
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i]->UpdateWorld();


}

TestDungeonScene::~TestDungeonScene()
{
	delete dungeon;

	delete instaning;
	delete player;
	delete PLAYER;
}

void TestDungeonScene::Update()
{
	dungeon->Update();
	instaning->Update();
	player->Update();
	PLAYER->UpdateWorld();

	if (!KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_DOWN('F')) dungeon->OpenDoor(true);
		if (KEY_PRESS(VK_RIGHT)) dungeon->OpenDoor_I(true);
		if (KEY_PRESS(VK_DOWN)) dungeon->IsClear(true);
	}

	if (player->Pos().y < 0) player->Pos().y = 0;
	//if (player->isjump && !dungeon->IsCollision(player->GetCollider())) 
	//{
	//	player->Pos().y -= gravity * DELTA;
	//} 
	//if (player->Pos().y > 0) player->Pos().y = 0;
	if (dungeon->IsCollision(player->GetCollider()));

	//CAM->SetTarget(dungeon);
	////CAM->TargetOptionLoad("Follow");
	//CAM->TargetOptionLoad("Naruto");
	//CAM->LookAtTarget(); //카메라의 2차 초점을 표적에게 (락온 켜기 // *락온의 대상이 주인공이면? ...백뷰)
}

void TestDungeonScene::Render()
{
	dungeon->Render();
	instaning->Render();
	player->Render();
	PLAYER->Render();

	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i]->Render();
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i]->Render();
}

void TestDungeonScene::PreRender()
{
}

void TestDungeonScene::PostRender()
{
}

void TestDungeonScene::GUIRender()
{
	//PLAYER->GUIRender();
	dungeon->GUIRender();
}
