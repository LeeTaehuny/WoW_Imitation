#include "Framework.h"
#include "LichKimgBossScene.h"

#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Skills/SkillManager.h"

LichKimgBossScene::LichKimgBossScene()
{
	map = new BossMap();
}

LichKimgBossScene::~LichKimgBossScene()
{
	delete map;
}

void LichKimgBossScene::Start()
{
	CH->PlayerSpawn(5);
	CH->GetPlayerData()->EquipWeapon(new Weapon("hammer_1", WeaponType::Hammer));
	SKILL->Init(CH->GetPlayerData());
}

void LichKimgBossScene::Update()
{
	if (KEY_DOWN(VK_RIGHT))
	{
		MONSTER->SpawnSkeletonKnight(Vector3());
	}

	map->Update();

	CH->Update();
	MONSTER->Update();
}

void LichKimgBossScene::PreRender()
{
	CH->PreRender();
}

void LichKimgBossScene::Render()
{
	map->Render();

	CH->Render();
	MONSTER->Render();
}

void LichKimgBossScene::PostRender()
{
	CH->PostRender();
	MONSTER->PostRender();
}

void LichKimgBossScene::GUIRender()
{
	CH->GUIRender();
}