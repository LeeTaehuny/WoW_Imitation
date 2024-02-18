#include "Framework.h"
#include "TestDungeonScene.h"

TestDungeonScene::TestDungeonScene()
{
	dungeon = new Dungeon();

	TestSize = new SphereCollider(2);

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

	TestSize->Pos() = dungeon->GetSpawnPoint_P();
	PLAYER->Pos() = dungeon->GetSpawnPoint_P();
	//instaning->Pos() = dungeon->GetSpawnPoint_P();
	player->Pos() = dungeon->GetSpawnPoint_P();

	//skybox = new SkyBox(L"Textures/Landscape/Space.dds");
	//skybox->UpdateWorld();

	//dungeon->Rot().y += 3.15f;
	//dungeon->Scale() *= 6.0f;
}

TestDungeonScene::~TestDungeonScene()
{
	delete dungeon;
	//delete instaning;
	//delete player;
	//delete PLAYER;
}

void TestDungeonScene::Update()
{
	dungeon->Update();
	instaning->Update();
	player->Update();
	TestSize->UpdateWorld();
	PLAYER->UpdateWorld();

	if (!KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W')) PLAYER->Pos().z += 100 * DELTA;
		if (KEY_PRESS('S')) PLAYER->Pos().z -= 100 * DELTA;
		if (KEY_PRESS('D')) PLAYER->Pos().x += 100 * DELTA;
		if (KEY_PRESS('A')) PLAYER->Pos().x -= 100 * DELTA;

		if (KEY_PRESS('W')) TestSize->Pos().z += 100 * DELTA;
		if (KEY_PRESS('S')) TestSize->Pos().z -= 100 * DELTA;
		if (KEY_PRESS('D')) TestSize->Pos().x += 100 * DELTA;
		if (KEY_PRESS('A')) TestSize->Pos().x -= 100 * DELTA;


		if (KEY_DOWN('F')) dungeon->OpenDoor(true);
		if (KEY_PRESS(VK_RIGHT)) dungeon->OpenDoor_I(true);
	}

	if (KEY_PRESS(VK_DOWN)) dungeon->IsClear(true);

	if (player->Pos().y < 0) player->Pos().y = 0;
	//if (player->Pos().y > 0) player->Pos().y = 0;
	if (dungeon->IsCollision(TestSize));
	if (dungeon->IsCollision(player->GetCollider()));
}

void TestDungeonScene::Render()
{
	//skybox->Render();
	dungeon->Render();
	instaning->Render();
	player->Render();

	TestSize->Render();
	PLAYER->Render();
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
}
