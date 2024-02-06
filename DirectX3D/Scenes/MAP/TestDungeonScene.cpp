#include "Framework.h"
#include "TestDungeonScene.h"

TestDungeonScene::TestDungeonScene()
{
	dungeon = new Dungeon();

	TestSize = new SphereCollider(2);
}

TestDungeonScene::~TestDungeonScene()
{
	delete dungeon;
}

void TestDungeonScene::Update()
{
	dungeon->Update();
	TestSize->UpdateWorld();

	if (!KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W')) TestSize->Pos().x += 100 * DELTA;
		if (KEY_PRESS('S')) TestSize->Pos().x -= 100 * DELTA;
		if (KEY_PRESS('D')) TestSize->Pos().z -= 100 * DELTA;
		if (KEY_PRESS('A')) TestSize->Pos().z += 100 * DELTA;

		if (KEY_PRESS('F')) dungeon->OpenDoor(true);
	}
}

void TestDungeonScene::Render()
{
	dungeon->Render();
	TestSize->Render();
}

void TestDungeonScene::PreRender()
{
}

void TestDungeonScene::PostRender()
{
}

void TestDungeonScene::GUIRender()
{
}
