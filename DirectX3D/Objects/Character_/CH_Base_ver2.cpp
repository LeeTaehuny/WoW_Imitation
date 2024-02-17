#include "Framework.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Item/Weapon.h"

CH_Base_ver2::CH_Base_ver2(CreatureType creatureType, ProfessionType professionType)
	: creatureType(creatureType), professionType(professionType)
{
	switch (this->creatureType)
	{
	case CreatureType::Player:
		inventory = new Inventory();
		break;
	case CreatureType::NonPlayer:
		break;
	}

	// 스탯 설정 (임시)
	stat.maxHp = 1000.0f;
	stat.hp = stat.maxHp;
	stat.mp = 1000;
	stat.damage = 100.0f;
	stat.defence = 100;

	mainHand = new Transform();
	mainHand->SetParent(this);
}

CH_Base_ver2::~CH_Base_ver2()
{
	SAFE_DEL(inventory);
}

void CH_Base_ver2::Update()
{
	if (inventory != nullptr) inventory->Update();

	if (weapon != nullptr)
	{
		mainHand->SetWorld(instancing->GetTransformByNode(index, mainHandBoneIndex));
		mainHand->GlobalPos() = GlobalPos();
	
		weapon->Update();
	}
}

void CH_Base_ver2::Render()
{
	if (weapon != nullptr)
	{
		weapon->Render();
	}
}

void CH_Base_ver2::UIRender()
{
	if (!Active()) return;
	if (inventory != nullptr) inventory->UIRender();
}

//void CH_Base_ver2::EquipWeapon(Weapon* weapon)
//{
//	if (weapon == nullptr) return;
//
//	this->weapon = weapon;
//	weapon->Scale() *= 100.0f;
//	weapon->Rot() = Vector3(0.0f, 11.0f, 0.0f);
//	weapon->SetParent(mainHand);
//}
