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
	
}

LichKimgBossScene::~LichKimgBossScene()
{
	delete map;
}

void LichKimgBossScene::Start()
{
	CH->PlayerSpawn(4);
	//CH->GetPlayerData()->EquipWeapon(new Weapon("hammer_1", WeaponType::Hammer));
	CH->GetPlayerData()->EquipWeapon(new Weapon("staff_1", WeaponType::Staff));
	SKILL->Init(CH->GetPlayerData());

	map = new BossMap();
	MONSTER->SpawnLickKing(Vector3());
	if (Boss_LichKing* c = dynamic_cast<Boss_LichKing*>(MONSTER->GetLichKing()))
	{
		c->SetBossMap(map);
	}
}

void LichKimgBossScene::Update()
{
	if (KEY_DOWN(VK_LEFT))
	{
		MONSTER->SpawnSkeleton(Vector3());
		//MONSTER->SpawnIceBall(Vector3());
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		MONSTER->SpawnSkeletonKnight(Vector3());
	}

	map->Update();

	SKILL->Update();
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
	SKILL->PostRender();
	CH->PostRender();
	MONSTER->PostRender();
}

void LichKimgBossScene::GUIRender()
{
	CH->GUIRender();
}