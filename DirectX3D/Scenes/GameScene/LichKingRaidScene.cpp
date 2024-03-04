#include "Framework.h"
#include "LichKingRaidScene.h"

#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Skills/SkillManager.h"

LichKingRaidScene::LichKingRaidScene()
{
	
}

LichKingRaidScene::~LichKingRaidScene()
{
	delete map;
}

void LichKingRaidScene::Update()
{
	map->Update();

	if (KEY_DOWN(VK_UP))
	{
		MONSTER->SpawnVAlkier(Vector3());
	}

	MONSTER->Update();
	SKILL->Update();
	CH->Update();
}

void LichKingRaidScene::PreRender()
{
	CH->PreRender();
}

void LichKingRaidScene::Render()
{
	map->Render();

	MONSTER->Render();
	CH->Render();
}

void LichKingRaidScene::PostRender()
{
	MONSTER->PostRender();
	SKILL->PostRender(); // 우선
	CH->PostRender(); // 차선
}

void LichKingRaidScene::GUIRender()
{
	MONSTER->GUIRender();
	CH->GUIRender();
}

void LichKingRaidScene::Start()
{
	CH->PlayerSpawn(5);
	Weapon* wepon = new Weapon("staff_1", WeaponType::Staff);
	wepon->SetOwner(CH->GetPlayerData());
	CH->GetPlayerData()->EquipWeapon(wepon);
	//CH->GetPlayerData()->EquipWeapon(new Weapon("sword_1", WeaponType::Sword));
	//CH->GetPlayerData()->EquipWeapon(new Weapon("hammer_1", WeaponType::Hammer));
	SKILL->Init(CH->GetPlayerData());

	MONSTER->SpawnBoss(Vector3());
	map = new BossMap();
}