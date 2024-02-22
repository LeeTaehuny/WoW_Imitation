#include "Framework.h"
#include "KimScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"

#include "Objects/Skills/SkillManager.h"

//#include "Objects/Character_ver2/CH_Base_ver2.h"
//#include "Objects/Character_ver2/ProtectionWarrior_in.h"

#define UPDATE(k) if (k != nullptr) k->Update()
#define UPDATEWORLD(k) if (k != nullptr) k->UpdateWorld()
#define RENDER(k) if (k != nullptr) k->Render()
#define GUIRENDER(k) if (k != nullptr) k->GUIRender()

KimScene::KimScene()
{
	CH->PlayerSpawn(2);
	CH->GetPlayerData()->EquipWeapon(new Weapon("hammer_1", WeaponType::Hammer));
	SKILL->Init(CH->GetPlayerData());
	CH->GetPlayerData()->Pos() = Vector3(10);
	CH->GetPlayerData()->GetStat().maxHp = 1000;
	CH->GetPlayerData()->GetStat().hp = 1000;
	CH->GetPlayerData()->Update();

	//CH->NonPlayerSpawn(1);
	CH->NonPlayerSpawn(2);
	//CH->NonPlayerSpawn(1);
	//CH->NonPlayerSpawn(1);

	MONSTER;
	ARROW;

	//shop = new Shop();

	//MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	//MONSTER->SpawnScarecrow(Vector3(10));
	//MONSTER->SpawnScarecrow(Vector3(-10));
	//MONSTER->SpawnScarecrow(Vector3(-5));

	//MONSTER->SpawnSkeleton(Vector3(10));
	//MONSTER->SpawnSkeletonKnight(Vector3(10));

	//particle = new ParticleSystem("TextData/Particles/Fire/fireBall.fx");

	lich = new Boss_LichKing();
}

KimScene::~KimScene()
{
	delete lich;
	delete shop;
}

void KimScene::Update()
{
	if (KEY_DOWN(VK_LEFT))
	{
		MONSTER->SpawnSkeleton(Vector3());
	}
	if (KEY_DOWN(VK_RIGHT))
	{
		MONSTER->SpawnSkeletonKnight(Vector3());
	}
	if (KEY_DOWN(VK_DOWN))
	{
		MONSTER->SpawnScarecrow(Vector3());
	}
	
	if (KEY_DOWN('X'))
	{
		int gang = Random(1, 6);
		CH->NonPlayerSpawn(4);
	}

	if (KEY_DOWN(VK_NUMPAD5))
	{
		CH->GetPlayerData()->GetStat().hp -= 100;;
	}
	if (KEY_DOWN(VK_NUMPAD6))
	{
		CH->GetCharcterData()[1]->GetStat().hp -= 100;
	}

	SKILL->Update();
	CH->Update();
	MONSTER->Update();
	ARROW->Update();
	UPDATE(lich);
	UPDATE(shop);
}

void KimScene::PreRender()
{
	CH->PreRender();
}

void KimScene::Render()
{
	RENDER(lich);
	CH->Render();
	MONSTER->Render();
	ARROW->Render();
}

void KimScene::PostRender()
{
	SKILL->PostRender(); // 우선
	CH->PostRender(); // 차선
	
	if (shop != nullptr)
		shop->UIRender();
}

void KimScene::GUIRender()
{
	GUIRENDER(lich);
	CH->GUIRender();
}