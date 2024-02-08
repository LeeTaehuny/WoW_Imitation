#include "Framework.h"
#include "TestDungeonScene.h"

TestDungeonScene::TestDungeonScene()
{
	dungeon = new Dungeon();

	TestSize = new SphereCollider(2);

	//instaning = new ModelAnimatorInstancing("ProtectionWarrior");
	//instaning->ReadClip("Idle_1");
	//instaning->ReadClip("Attack_1");
	//instaning->ReadClip("Walk_F");
	//instaning->ReadClip("Walk_B");
	//instaning->ReadClip("Walk_L");
	//instaning->ReadClip("Walk_R");
	//instaning->ReadClip("Die");
	//instaning->ReadClip("Hit");
	//instaning->ReadClip("Jump");
	//instaning->ReadClip("S_Casting");
	//
	//Transform* transform = instaning->Add();
	//player = new ProtectionWarrior_in(CreatureType::Player, transform, instaning, 0);
	//
	//PLAYER = new Model("ProtectionWarrior");
	//
	//dungeon->SetParent(TestSize);
	

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
	//instaning->Update();
	//player->Update();
	TestSize->UpdateWorld();
	//PLAYER->UpdateWorld();

	if (!KEY_PRESS(VK_RBUTTON))
	{
		//if (KEY_PRESS('W')) PLAYER->Pos().x += 100 * DELTA;
		//if (KEY_PRESS('S')) PLAYER->Pos().x -= 100 * DELTA;
		//if (KEY_PRESS('D')) PLAYER->Pos().z -= 100 * DELTA;
		//if (KEY_PRESS('A')) PLAYER->Pos().z += 100 * DELTA;

		if (KEY_PRESS('W')) TestSize->Pos().x += 100 * DELTA;
		if (KEY_PRESS('S')) TestSize->Pos().x -= 100 * DELTA;
		if (KEY_PRESS('D')) TestSize->Pos().z -= 100 * DELTA;
		if (KEY_PRESS('A')) TestSize->Pos().z += 100 * DELTA;


		if (KEY_DOWN('F')) dungeon->OpenDoor(true);
	}

	if (KEY_PRESS(VK_DOWN)) dungeon->Pos().x -= 100 * DELTA;
}

void TestDungeonScene::Render()
{
	//instaning->Render();
	//player->Render();

	dungeon->Render();
	TestSize->Render();
	//PLAYER->Render();
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
