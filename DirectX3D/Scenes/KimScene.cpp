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
	//CH->PlayerSpawn(2);
	//CH->GetPlayerData()->EquipWeapon(new Weapon("hammer_1", WeaponType::Hammer));
	//SKILL->Init(CH->GetPlayerData());
	//CH->GetPlayerData()->Pos() = Vector3(10);
	//CH->GetPlayerData()->GetStat().maxHp = 1000;
	//CH->GetPlayerData()->GetStat().hp = 1000;
	//CH->GetPlayerData()->Update();
	//
	//CH->NonPlayerSpawn(2);
	//
	//MONSTER;
	//ARROW;

	//shop = new Shop();

	//MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	//MONSTER->SpawnScarecrow(Vector3(10));
	//MONSTER->SpawnScarecrow(Vector3(-10));
	//MONSTER->SpawnScarecrow(Vector3(-5));

	//MONSTER->SpawnSkeleton(Vector3(10));
	//MONSTER->SpawnSkeletonKnight(Vector3(10));

	//particle = new ParticleSystem("TextData/Particles/Fire/fireBall.fx");

	//lich = new Boss_LichKing();
}

KimScene::~KimScene()
{
	delete lich;
	delete shop;
}

void KimScene::Update()
{
	CH->Update();
}

void KimScene::PreRender()
{
	CH->PreRender();
}

void KimScene::Render()
{
	CH->Render();
}

void KimScene::PostRender()
{
	CH->PostRender();
}

void KimScene::GUIRender()
{
	CH->GUIRender();
}