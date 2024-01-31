#include "Framework.h"
#include "TestScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"

TestScene::TestScene()
{
	weapon = new Weapon("sword_2", WeaponType::Arrow);
	potion = new Potion("potion", PotionType::Hp);
	potion->Pos() = { 1, 0, 0 };
}

TestScene::~TestScene()
{
	delete weapon;
}

void TestScene::Update()
{
	weapon->Update();
	potion->Update();
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
