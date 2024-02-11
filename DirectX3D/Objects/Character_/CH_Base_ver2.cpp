#include "Framework.h"
#include "Objects/Inventory/Inventory.h"

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
}

CH_Base_ver2::~CH_Base_ver2()
{
	SAFE_DEL(inventory);
	SAFE_DEL(myPlayer);
}

void CH_Base_ver2::Update()
{
	if (inventory != nullptr) inventory->Update();
}

void CH_Base_ver2::Render()
{
	
}

void CH_Base_ver2::UIRender()
{
	if (!Active()) return;
	if (inventory != nullptr) inventory->UIRender();
}
