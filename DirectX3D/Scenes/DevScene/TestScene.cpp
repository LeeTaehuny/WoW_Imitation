#include "Framework.h"
#include "TestScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Character_/CH_Base.h"
#include "Objects/Character_/MarksmanshipHunter.h"
#include "Objects/Character_/ArmsWarrior.h"
#include "Objects/Character_/HolyPriest.h"
#include "Objects/Character_/FireMage.h"
#include "Objects/Character_/ProtectionWarrior.h"

TestScene::TestScene()
{
	//weapon = new Weapon("sword_1", WeaponType::Sword);
	//potion = new Potion("potion", PotionType::Hp);

	//potion->Pos() = { 1, 0, 0 };

	inv = new Inventory();
	//inv->AddItem(potion);
	//inv->AddItem(potion);
	//inv->AddItem(weapon);
	//inv->AddItem(weapon);

	shop = new Shop();

	player = new ProtectionWarrior(CreatureType::Player);

	CAM->SetTarget(player);

	MONSTER->SpawnScarecrow(Vector3(0, 0, 5));
	MONSTER->SpawnScarecrow(Vector3(10));
	MONSTER->SpawnScarecrow(Vector3(-10));

	skill = new FireBall();
	skill->SetOwner(player);
	MONSTER->SetTarget(player->GetCollider());
}

TestScene::~TestScene()
{
	//delete weapon;
}

void TestScene::Update()
{
	//weapon->Update();
	//potion->Update();
	//inv->Update();
	//
	shop->Update();
	
	// 상점 - 플레이어 상호작용
	{
		if ((player->GlobalPos() - shop->GlobalPos()).Length() < 10.0f)
		{
			shop->SetActive(true);
		}
		else
		{
			shop->SetActive(false);
		}

		if (shop->Active())
		{
			const vector<Slot*> slots = shop->GetItemSlots();
			const vector<Slot*> items = player->GetInventory()->GetInvSlots();

			int idx = 0;
			for (Slot* slot : slots)
			{
				if (mousePos.x <= slot->GlobalPos().x + slot->GetSize().x && mousePos.x >= slot->GlobalPos().x - slot->GetSize().x &&
					mousePos.y <= slot->GlobalPos().y + slot->GetSize().y && mousePos.y >= slot->GlobalPos().y - slot->GetSize().y)
				{
					if (KEY_DOWN(VK_RBUTTON))
					{
						string tmpName = shop->GetItemName(idx);

						if (tmpName.size())
						{
							shop->PurchaseItem(tmpName, player->GetInventory());
						}
					}
				}

				idx++;
			}

			idx = 0;
			for (Slot* item : items)
			{
				if (mousePos.x <= item->GlobalPos().x + 33.0f && mousePos.x >= item->GlobalPos().x - 33.0f &&
					mousePos.y <= item->GlobalPos().y + 33.0f && mousePos.y >= item->GlobalPos().y - 33.0f)
				{
					if (KEY_DOWN(VK_RBUTTON))
					{
						shop->SellItem(idx, player->GetInventory());
					}
				}

				idx++;
			}
		}
	}
	
	// 임시 스킬 사용 테스트 (좌클릭 타겟 설정, K : 스킬 사용)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			// 마우스 위치의 Ray 생성
			Ray ray = CAM->ScreenPointToRay(mousePos);
			Contact contact;

			// 몬스터 배열 받기
			vector<MonsterBase*> monsters = MONSTER->GetScarecrow();

			// 몬스터 순회하며 Ray 충돌 연산
			for (MonsterBase* monster : monsters)
			{
				if (monster->GetCollider()->IsRayCollision(ray, &contact))
				{
					// 충돌했다면 해당 몬스터를 내 타겟으로 설정
					targetMonster = monster;
				}
			}
		}

		if (KEY_DOWN('K'))
		{
			if (targetMonster != nullptr)
			skill->UseSkill(targetMonster->GetCollider());
		}
	}
	

	player->Update();
	MONSTER->Update();
	skill->Update();
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	//weapon->Render();
	//potion->Render();
	//shop->Render();
	player->Render();
	MONSTER->Render();
	skill->Render();
}

void TestScene::PostRender()
{
	player->UIRender();
	shop->UIRender();
}

void TestScene::GUIRender()
{
	//weapon->GUIRender();
	//potion->GUIRender();
}

void TestScene::Start()
{
}

void TestScene::End()
{
}
