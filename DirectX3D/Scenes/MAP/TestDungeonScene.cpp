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



	//MONSTER->SetTarget(player);
	//MONSTER->SpawnScarecrow(Vector3(0.0f, 0.0f, 0.0f));

	//MONSTER->SpawnSkeletonKnight(Vector3(35.25, 0, 117));

	//dungeon->Rot().y += 3.15f;
	//dungeon->Scale() *= 6.0f;



	TestMonsterSpawnPos_A.resize(11);
	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i)
	{
		TestMonsterSpawnPos_A[i] = new Model("ProtectionWarrior");
		TestMonsterSpawnPos_A[i]->Rot().y += 1.575f;
		vector<Vector3> spawnPoints = dungeon->SpawnMonsters_A();
		TestMonsterSpawnPos_A[i]->Pos() = spawnPoints[i];
		//MONSTER->SpawnSkeleton(TestMonsterSpawnPos_A[i]);
	}
	TestMonsterSpawnPos_B.resize(10);
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) 
	{
		TestMonsterSpawnPos_B[i] = new Model("ProtectionWarrior");
		TestMonsterSpawnPos_B[i]->Rot().y += 1.575f;
		vector<Vector3> spawnPoints = dungeon->SpawnMonsters_B();
		TestMonsterSpawnPos_B[i]->Pos() = spawnPoints[i];
		//MONSTER->SpawnSkeletonKnight(TestMonsterSpawnPos_B[i]);
	}
	


	/////////////////////////////////////////////////////////////////////////////
	//TestMonsterSpawnPos_A.resize(11);
	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i] = new SphereCollider(2);
	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i] = new Model("ProtectionWarrior");
	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i)
	//{
	//	TestMonsterSpawnPos_A[i]->Rot().y += 1.575f;
	//	vector<Vector3> spawnPoints = dungeon->SpawnMonsters_A();
	//	if (i < spawnPoints.size())
	//	{
	//		TestMonsterSpawnPos_A[i]->Pos() = spawnPoints[i];
	//		
	//	}
	//	else
	//	{
	//		//��ǥ ������ �� �������� ���� ���
	//	}
	//}

	//TestMonsterSpawnPos_B.resize(10);
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i] = new SphereCollider(2);
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i] = new Model("ProtectionWarrior");
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i)
	//{
	//	TestMonsterSpawnPos_B[i]->Rot().y += 1.575f;
	//	vector<Vector3> spawnPoints = dungeon->SpawnMonsters_B();
	//	if (i < spawnPoints.size())
	//	{
	//		TestMonsterSpawnPos_B[i]->Pos() = spawnPoints[i];
	//	}
	//	else
	//	{
	//		//��ǥ ������ �� �������� ���� ���
	//	}
	//}
	//
	for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) TestMonsterSpawnPos_A[i]->UpdateWorld();
	for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) TestMonsterSpawnPos_B[i]->UpdateWorld();


}

TestDungeonScene::~TestDungeonScene()
{
	delete dungeon;

	delete instaning;
	delete player;
	delete PLAYER;
	//delete MONSTER;
}

void TestDungeonScene::Update()
{
	dungeon->Update();
	instaning->Update();
	player->Update();
	PLAYER->UpdateWorld();
	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) MONSTER->Update();
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) MONSTER->Update();
	//MONSTER->Update();
	
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
	if (dungeon->PotalCollision(player->GetCollider()));

	//CAM->SetTarget(dungeon);
	////CAM->TargetOptionLoad("Follow");
	//CAM->TargetOptionLoad("Naruto");
	//CAM->LookAtTarget(); //ī�޶��� 2�� ������ ǥ������ (���� �ѱ� // *������ ����� ���ΰ��̸�? ...���)
}

void TestDungeonScene::Render()
{
	dungeon->Render();
	instaning->Render();
	player->Render();
	PLAYER->Render();
	//for (int i = 0; i < TestMonsterSpawnPos_A.size(); ++i) MONSTER->Render();
	//for (int i = 0; i < TestMonsterSpawnPos_B.size(); ++i) MONSTER->Render();
	//MONSTER->Render();

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
