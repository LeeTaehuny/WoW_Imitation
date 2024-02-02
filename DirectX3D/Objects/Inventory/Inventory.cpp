#include "Framework.h"
#include "Inventory.h"
#include "Objects/Item/Item.h"
#include "Objects/Inventory/Slot.h"

Inventory::Inventory()
{
	// 인벤토리 프레임 설정
	invFrame = new Slot(L"Textures/UI/Inventory.png", SlotType::Inventory_Frame);
	invFrame->Scale() *= 1.75f;
	invFrame->Pos() = { CENTER_X, CENTER_Y, 1.0f };

	// 인벤토리 내용 초기화
	inventory.resize(28);
	int idx = 0;
	for (InventoryItem& i : inventory)
	{
		i.index = idx;
		idx++;
	}

	// 인벤토리 슬롯 설정
	invSlot.resize(28);
	for (int i = 0; i < invSlot.size(); i++)
	{
		int idxY = i / 7;
		int idxX = i % 7;

		Slot* slot = new Slot(Vector2(33.0f, 33.0f), SlotType::Inventory_Slot);
		slot->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
		slot->SetParent(invFrame);
		slot->Pos() = { -143.0f + (idxX * 47.5f), 45.0f - (idxY * 40.5f), 0.0f}; 
		invSlot[i] = slot;
	}

	// 인벤토리 액티브 off
	SetActive(false);

	// 이벤트 등록
	{
		// 인벤토리 이동
		Observer::Get()->AddEvent("MoveInvFrame", bind(&Inventory::MoveInventoryFrame, this));
		Observer::Get()->AddEvent("StopInvFrame", bind(&Inventory::StopInventoryFrame, this));
		// 아이템 이동
		Observer::Get()->AddParamEvent("PickInvItem", bind(&Inventory::PickItem, this, placeholders::_1));
		Observer::Get()->AddParamEvent("DownInvItem", bind(&Inventory::DownItem, this, placeholders::_1));
	}

	mouseImg = new Quad(Vector2(55.0f, 55.0f));
	mouseImg->SetActive(false);
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

	// 슬롯 및 프레임 업데이트
	for (Slot* slot : invSlot)
	{
		slot->Update();
	}

	invFrame->Update();

	if (mouseImg->Active())
	{
		mouseImg->Pos() = mousePos;
		mouseImg->UpdateWorld();
	}

	if (KEY_UP(VK_LBUTTON))
	{
		mouseImg->SetActive(false);

		if (tempIndex != -1)
		{
			invSlot[tempIndex]->SetSelect(false);
			invSlot[tempIndex]->SetCilck(false);
		}
	}
}

void Inventory::UIRender()
{
	if (!Active()) return;

	invFrame->Render();
	for (Slot* slot : invSlot)
	{
		slot->Render();
	}

	if (mouseImg->Active())
	{
		mouseImg->Render();
	}
}

void Inventory::UpdateInventory()
{
	// 인벤토리 내용을 순회하며 아이콘을 해당 슬롯에 적용시키기
	for (InventoryItem inv : inventory)
	{
		if (inv.item == nullptr)
		{
			invSlot[inv.index]->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
		}
		else
		{
			// 인벤토리 내의 아이템 인덱스에 따른 이미지 추출
			Texture* icon = inv.item->GetIcon()->GetMaterial()->GetDiffuseMap();
			// 인덱스 번째 슬롯에 이미지 적용
			invSlot[inv.index]->GetMaterial()->SetDiffuseMap(icon);
		}
	}
}

void Inventory::AddItem(Item* item)
{
	// 전달받은 아이템의 타입이 무기 타입이라면?
	if (item->GetType() == ItemType::Weapon)
	{
		// 아이템 정보 생성
		InventoryItem desc;

		// 비어있는 인벤토리 인덱스 찾기
		for (InventoryItem i : inventory)
		{
			if (i.item == nullptr)
			{
				desc.index = i.index;
				desc.item = item;
				desc.quantity = 1;

				// 인벤토리에 아이템 추가
				inventory[i.index] = desc;
				return;
			}
		}
	}

	// 전달받은 아이템의 타입이 포션인 경우 중복되는 아이템이 있는지 찾기
	for (InventoryItem inv : inventory)
	{
		if (inv.item == nullptr) continue;
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

	// 비어있는 인벤토리 인덱스 찾기
	for (InventoryItem i : inventory)
	{
		if (i.item == nullptr)
		{
			desc.index = i.index;
			desc.item = item;
			desc.quantity = 1;

			// 인벤토리에 추가
			inventory[i.index] = desc;
			return;
		}
	}

	
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

void Inventory::MoveInventoryFrame()
{
	if (invFrame->GetSelect())
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
}

void Inventory::StopInventoryFrame()
{
	bIsMove = false;
}

void Inventory::PickItem(void* slot)
{
	Slot* tmpSlot = static_cast<Slot*>(slot);

	if (tmpSlot)
	{
		// 모든 슬롯을 순회하며 동일한 슬롯 인덱스 찾기
		int idx = 0;
		for (Slot* slot : invSlot)
		{
			if (slot == tmpSlot)
			{
				break;
			}
			idx++;
		}

		// 해당 슬롯에 아이템이 존재하지 않는 경우 리턴
		if (inventory[idx].item == nullptr)
		{
			tempIndex = -1;
			// 현재 선택한 버튼 선택 여부 및 활성화 off
			invSlot[idx]->SetSelect(false);
			invSlot[idx]->SetCilck(false);
			return;
		}

		// 해당 슬롯의 인덱스 저장
		tempIndex = idx;

		// 마우스 이미지 활성화 및 해당 슬롯 이미지 넣기
		mouseImg->GetMaterial()->SetDiffuseMap(invSlot[idx]->GetMaterial()->GetDiffuseMap());
		mouseImg->SetActive(true);

	}
}

void Inventory::DownItem(void* slot)
{
	if (tempIndex == -1) return;

	Slot* tmpSlot = static_cast<Slot*>(slot);

	if (tmpSlot)
	{
		// 모든 슬롯을 순회하며 동일한 슬롯 인덱스 찾기
		int idx = 0;
		for (Slot* slot : invSlot)
		{
			if (slot == tmpSlot)
			{
				break;
			}
			idx++;
		}

		// 이전 인덱스 슬롯의 클릭 해제
		invSlot[tempIndex]->SetSelect(false);
		invSlot[tempIndex]->SetCilck(false);

		// 해당 인덱스의 위치에 아이템 정보 옮기기
		Item* item = inventory[tempIndex].item;
		int quantity = inventory[tempIndex].quantity;
		inventory[tempIndex].item = inventory[idx].item;
		inventory[tempIndex].quantity = inventory[idx].quantity;
		inventory[idx].item = item;
		inventory[idx].quantity = quantity;
	}
}
