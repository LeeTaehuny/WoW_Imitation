#include "Framework.h"
#include "Inventory.h"
#include "Objects/Item/Item.h"
#include "Objects/Inventory/Slot.h"

Inventory::Inventory()
{
	// 인벤토리 프레임 설정
	invFrame = new Slot(L"Textures/UI/Inventory.png", SlotType::Inventory_Frame);
	invFrame->Scale() *= 1.75f;
	invFrame->Pos() = { CENTER_X, CENTER_Y };

	// 인벤토리 슬롯 설정
	invSlot.resize(28);
	for (int i = 0; i < invSlot.size(); i++)
	{
		int idxY = i / 7;
		int idxX = i % 7;

		Slot* slot = new Slot(Vector2(33.0f, 33.0f), SlotType::Inventory_Slot);
		slot->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
		slot->SetParent(invFrame);
		slot->Pos() = { -143.0f + (idxX * 47.5f), 45.0f - (idxY * 40.5f), 0}; 
		invSlot[i] = slot;
	}

	// 인벤토리 액티브 off
	SetActive(false);
}

Inventory::~Inventory()
{
	SAFE_DEL(invFrame);
	for (Slot* slot : invSlot)
	{
		SAFE_DEL(slot);
	}
}

void Inventory::Update()
{
	// 테스트 코드. 나중에는 플레이어에서 i키와 매핑할 것.
	if (KEY_DOWN('I'))
	{
		if (Active())
		{
			SetActive(false);
		}
		else
		{
			SetActive(true);
		}
	}

	if (!Active()) return;

	// 인벤토리 업데이트
	UpdateInventory();

	if (KEY_PRESS(VK_LBUTTON) && invFrame->GetSelect())
	{
		for (Slot* slot : invSlot)
		{
			if (slot->GetSelect())
			{
				return;
			}
		}

		if (!bIsMove)
		{
			prevPos = mousePos;
			bIsMove = true;
		}
		else
		{
			float deltaX = prevPos.x - mousePos.x;
			float deltaY = prevPos.y - mousePos.y;

			invFrame->Pos().x += -deltaX;
			invFrame->Pos().y += -deltaY;

			prevPos = mousePos;
		}
	}
	else
	{
		bIsMove = false;
	}

	// 슬롯 및 프레임 업데이트
	for (Slot* slot : invSlot)
	{
		slot->Update();
	}

	invFrame->Update();
}

void Inventory::UIRender()
{
	if (!Active()) return;

	invFrame->Render();
	for (Slot* slot : invSlot)
	{
		slot->Render();
	}
}

void Inventory::UpdateInventory()
{
	// 인벤토리 내용을 순회하며 아이콘을 해당 슬롯에 적용시키기
	for (InventoryItem inv : inventory)
	{
		// 인벤토리 내의 아이템 인덱스에 따른 이미지 추출
		Texture* icon = inv.item->GetIcon()->GetMaterial()->GetDiffuseMap();
		// 인덱스 번째 슬롯에 이미지 적용
		invSlot[inv.index]->GetMaterial()->SetDiffuseMap(icon);
	}
}

void Inventory::AddItem(Item* item)
{
	// 전달받은 아이템의 타입이 무기 타입이라면?
	if (item->GetType() == ItemType::Weapon)
	{
		// 아이템 정보 생성
		InventoryItem desc;

		desc.index = inventory.size();
		desc.item = item;
		desc.quantity = 1;

		// 인벤토리의 맨 뒤에 아이템 추가
		inventory.push_back(desc);

		return;
	}

	// 전달받은 아이템의 타입이 포션인 경우 중복되는 아이템이 있는지 찾기
	for (InventoryItem inv : inventory)
	{
		// 만약 아이템의 태그가 같다면?
		if (inv.item->GetTag() == item->GetTag())
		{
			// 수량 증가
			inv.quantity++;
			return;
		}
	}

	// 중복된 아이템이 없는 경우 인벤토리의 맨 뒤에 아이템 추가
	// * 아이템 정보 생성
	InventoryItem desc;

	desc.index = inventory.size();
	desc.item = item;
	desc.quantity = 1;

	// * 인벤토리에 추가
	inventory.push_back(desc);
}

void Inventory::DeleteItem(Item* item)
{
	// 삭제는 일단 나중에 상황보고 작성

	// 전달받은 아이템의 타입이 무기 타입이라면?
	//if (item->GetType() == ItemType::Weapon)
	//{
	//	// 순회
	//	for (InventoryItem inv : inventory)
	//	{
	//		// 만약 아이템의 태그가 같다면?
	//		if (item->GetTag() == inv.item->GetTag())
	//		{
	//			// 해당 슬롯의 이미지 초기화
	//			invSlot[inv.index]->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
	//
	//			// 아이템 삭제
	//			SAFE_DEL(inv.item);
	//			return;
	//		}
	//	}
	//}
	
}
