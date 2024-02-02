#include "Framework.h"
#include "TestScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"

TestScene::TestScene()
{
	weapon = new Weapon("sword_1", WeaponType::Sword);
	potion = new Potion("potion", PotionType::Hp);

	potion->Pos() = { 1, 0, 0 };

	inv = new Inventory();
	inv->AddItem(potion);
	inv->AddItem(potion);
	inv->AddItem(weapon);
	inv->AddItem(weapon);
}

TestScene::~TestScene()
{
	delete weapon;
}

void TestScene::Update()
{
	weapon->Update();
	potion->Update();
	inv->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	weapon->Render();
	potion->Render();
}

void TestScene::PostRender()
{
	inv->UIRender();
}

void TestScene::GUIRender()
{
	weapon->GUIRender();
	potion->GUIRender();
}

void TestScene::Start()
{
}

void TestScene::End()
{
}
