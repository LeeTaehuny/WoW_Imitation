#include "Framework.h"
#include "TestScene.h"
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Inventory.h"
#include "Objects/Shop/Shop.h"
#include "Objects/Inventory/Slot.h"

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
	shop->AddItem(new Weapon("sword_1", WeaponType::Sword));
	shop->AddItem(new Weapon("sword_2", WeaponType::Sword));
	shop->AddItem(new Weapon("staff_1", WeaponType::Staff));
	shop->AddItem(new Weapon("staff_2", WeaponType::Staff));
	shop->AddItem(new Weapon("staff_3", WeaponType::Staff));
	shop->AddItem(new Weapon("bow_1", WeaponType::Bow));
	shop->AddItem(new Weapon("bow_2", WeaponType::Bow));
	shop->AddItem(new Weapon("hammer_1", WeaponType::Hammer));
	shop->AddItem(new Weapon("hammer_2", WeaponType::Hammer));
	shop->AddItem(new Potion("potion", PotionType::Hp));
	shop->AddItem(new Potion("potionMp", PotionType::Mp));
}

TestScene::~TestScene()
{
	delete weapon;
}

void TestScene::Update()
{
	//weapon->Update();
	//potion->Update();
	inv->Update();

	shop->Update();

	if ((CAM->GlobalPos() - shop->GlobalPos()).Length() < 10.0f)
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
		const vector<Slot*> items = inv->GetInvSlots();
		
		int idx = 0;
		for (Slot* slot : slots)
		{
			if (mousePos.x <= slot->GlobalPos().x + 33.0f && mousePos.x >= slot->GlobalPos().x - 33.0f &&
				mousePos.y <= slot->GlobalPos().y + 33.0f && mousePos.y >= slot->GlobalPos().y - 33.0f)
			{
				if (KEY_DOWN(VK_RBUTTON))
				{
					string tmpName = shop->GetItemName(idx);
					
					if (tmpName.size())
					{
						shop->PurchaseItem(tmpName, inv);
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
					shop->SellItem(idx, inv);
				}
			}

			idx++;
		}
	}
}

void TestScene::PreRender()
{
}

void TestScene::Render()
{
	//weapon->Render();
	//potion->Render();
	shop->Render();
}

void TestScene::PostRender()
{
	inv->UIRender();
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
