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
	CH->PlayerSpawn(4);
	//CH->GetPlayerData()->EquipWeapon(new Weapon("hammer_1", WeaponType::Hammer));
	CH->GetPlayerData()->EquipWeapon(new Weapon("bow_1", WeaponType::Bow));
	SKILL->Init(CH->GetPlayerData());

	vector<CH_Base_ver2*> Position_Select = CH->GetCharcterData();
	float xxxx = -40;
	float zzzz = 0;
	float zzzz22 = 0;
	int charcter_count = 0;
	float nanum = 1;
	float nujec = 0.5f;
	Vector3 position_active;
	for (int i = 0; i < Position_Select.size(); i++)
	{
		position_active = Vector3(xxxx, 0, zzzz);
		Position_Select[i]->Pos() = position_active;
		Position_Select[i]->Rot().y -= XM_PI * 0.5f;
		Position_Select[i]->Update();

		if (1 - nanum == 0)
		{
			charcter_count++;
			nanum = 0;
			xxxx += -5;
			zzzz22 += 5;
		}
		else
		{
			if (nanum == 0)
			{
				zzzz = -zzzz22;
			}
			else
			{
				zzzz = zzzz22;
			}
			nanum += nujec;
		}
	}

	
	MONSTER->SpawnLickKing(Vector3());
	if (Boss_LichKing* c = dynamic_cast<Boss_LichKing*>(MONSTER->GetLichKing()))
	{
		c->SetBossMap(map);
	}
}

void LichKimgBossScene::Update()
{
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