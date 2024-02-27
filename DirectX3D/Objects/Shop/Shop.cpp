#include "Framework.h"
#include "Shop.h"
#include "Objects/Item/Item.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Inventory/Inventory.h"

Shop::Shop()
{
	// 모델 설정
	{
		shop = new Model("Shop");
		trader = new Model("Trader");

		shop->SetParent(this);
		shop->GetMaterials()[0]->SetShader(L"Light/ItemLight.hlsl");
		shop->GetMaterials()[1]->SetShader(L"Light/ItemLight.hlsl");
		shop->Scale() *= 0.5f;

		trader->SetParent(this);
		trader->GetMaterials()[0]->SetShader(L"Light/ItemLight.hlsl");
	}
	
	// RS 설정 (shop 전용)
	{
		FOR(2) rs[i] = new RasterizerState();
		rs[1]->CullMode(D3D11_CULL_NONE);
	}

	// 아이템 배열 초기화
	items.resize(28);

	// UI 설정
	shopFrame = new Slot(L"Textures/UI/shop_frame.png", SlotType::Shop_Frame);

	shopFrame->Scale() *= 1.75f;
	shopFrame->Pos() = { CENTER_X * 0.5f, CENTER_Y, 1.0f };

	itemSlots.resize(28);
	for (int i = 0; i < itemSlots.size(); i++)
	{
		int idxY = i / 7;
		int idxX = i % 7;

		Slot* slot = new Slot(Vector2(33.0f, 33.0f), SlotType::Inventory_Slot);
		slot->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
		slot->SetParent(shopFrame);
		slot->Pos() = { -143.0f + (idxX * 47.5f), 65.5f - (idxY * 42.5f), 0.0f };
		itemSlots[i] = slot;
	}

	// 아이템 추가
	{
		AddItem(new Weapon("sword_1", WeaponType::Sword));
		AddItem(new Weapon("sword_2", WeaponType::Sword));
		AddItem(new Weapon("staff_1", WeaponType::Staff));
		AddItem(new Weapon("staff_2", WeaponType::Staff));
		AddItem(new Weapon("staff_3", WeaponType::Staff));
		AddItem(new Weapon("bow_1", WeaponType::Bow));
		AddItem(new Weapon("bow_2", WeaponType::Bow));
		AddItem(new Weapon("hammer_1", WeaponType::Hammer));
		AddItem(new Weapon("hammer_2", WeaponType::Hammer));
		AddItem(new Potion("potion", PotionType::Hp));
		AddItem(new Potion("potionMp", PotionType::Mp));
	}

	SetActive(false);
}

Shop::~Shop()
{
	SAFE_DEL(shop);
	SAFE_DEL(trader);
	SAFE_DEL(rs[1]);
	SAFE_DEL(rs[2]);
	SAFE_DEL(shopFrame);
}

void Shop::Update()
{
	if ((CH->GetPlayerData()->GlobalPos() - GlobalPos()).Length() < 10.0f)
	{
		SetActive(true);
	}
	else
	{
		SetActive(false);
	}

	shop->UpdateWorld();
	trader->UpdateWorld();
	
	if (!Active()) return;

	shopFrame->Update();

	for (Slot* slot : itemSlots)
	{
		slot->Update();
	}

	InteractWithPlayer();
}

void Shop::Render()
{
	rs[1]->SetState();
	shop->Render();
	rs[0]->SetState();

	trader->Render();
}

void Shop::UIRender()
{
	Vector3 screenPos = CAM->WorldToScreen(shop->GlobalPos());
	Font::Get()->RenderText("SHOP", { screenPos.x + 30.0f, screenPos.y + 150.0f });

	if (!Active()) return;

	shopFrame->Render();

	for (Slot* slot : itemSlots)
	{
		slot->Render();
	}
}

void Shop::GUIRender()
{
}

void Shop::AddItem(Item* item)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] == nullptr)
		{
			items[i] = item;
			break;
		}
	}

	UpdataItems();
}

string Shop::GetItemName(int index)
{
	if (items[index] != nullptr)
	{
		return items[index]->GetItemName();
	}
	else
	{
		return "";
	}
}

void Shop::UpdataItems()
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] != nullptr)
		{
			itemSlots[i]->GetMaterial()->SetDiffuseMap(items[i]->GetIcon()->GetMaterial()->GetDiffuseMap());
		}
	}
}

Item* Shop::CreateWeapon(string name, WeaponType type)
{
	return new Weapon(name, type);
}

Item* Shop::CreatePotion(string name, PotionType type)
{
	return new Potion(name, type);
}

void Shop::InteractWithPlayer()
{
	if (Active())
	{
		const vector<Slot*> items = CH->GetPlayerData()->GetInventory()->GetInvSlots();

		int idx = 0;
		for (Slot* slot : itemSlots)
		{
			if (mousePos.x <= slot->GlobalPos().x + slot->GetSize().x && mousePos.x >= slot->GlobalPos().x - slot->GetSize().x &&
				mousePos.y <= slot->GlobalPos().y + slot->GetSize().y && mousePos.y >= slot->GlobalPos().y - slot->GetSize().y)
			{
				if (KEY_DOWN(VK_RBUTTON))
				{
					string tmpName = GetItemName(idx);

					if (tmpName.size())
					{
						PurchaseItem(tmpName, CH->GetPlayerData()->GetInventory());
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
					SellItem(idx, CH->GetPlayerData()->GetInventory());
				}
			}

			idx++;
		}
	}
}

void Shop::PurchaseItem(string itemName, Inventory* inventory)
{
	for (Item* item : items)
	{
		if (item->GetName() == itemName)
		{
			if (Weapon* weapon = dynamic_cast<Weapon*>(item))
			{
				Item* item = CreateWeapon(weapon->GetName(), weapon->GetWeaponType());
				inventory->AddItem(item);
				return;
			}
			else if (Potion* potion = dynamic_cast<Potion*>(item))
			{
				Item* item = CreatePotion(potion->GetName(), potion->GetPotionType());
				inventory->AddItem(item);
				return;
			}
		}
	}
}

void Shop::SellItem(int itemIndex, Inventory* inventory)
{
	// 나중에 추가 사항(골드 등)이 있다면 추가하기

	// 해당 인덱스의 아이템 삭제
	inventory->DeleteItem(itemIndex);
}
