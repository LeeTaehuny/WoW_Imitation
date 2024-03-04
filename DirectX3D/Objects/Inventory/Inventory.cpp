#include "Framework.h"
#include "Inventory.h"
#include "Objects/Item/Item.h"
#include "Objects/Item/Potion.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/UI/QuickSlot.h"

Inventory::Inventory(CH_Base_ver2* player) : player(player)
{
	// 인벤토리 초기화
	InitInventory();

	// 이벤트 등록
	{
		// 인벤토리 이동
		Observer::Get()->AddEvent("MoveInvFrame", bind(&Inventory::MoveInventoryFrame, this));
		Observer::Get()->AddEvent("StopInvFrame", bind(&Inventory::StopInventoryFrame, this));
		// 아이템 이동
		Observer::Get()->AddParamEvent("PickInvItem", bind(&Inventory::PickItem, this, placeholders::_1));
		Observer::Get()->AddParamEvent("DownInvItem", bind(&Inventory::DownItem, this, placeholders::_1));
	}
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
	if (KEY_DOWN('I'))
	{
		if (Active())
		{
			SetActive(false);
		}
		else
		{
			SetActive(true);
			Audio::Get()->Play("OpenUI", 1.0f);
		}
	}

	if (KEY_DOWN(VK_ESCAPE) && Active())
	{
		SetActive(false);
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

	if (KEY_UP(VK_LBUTTON))
	{
		//mouseImg->SetActive(false);

		if (tempIndex != -1)
		{
			invSlot[tempIndex]->SetSelect(false);
			invSlot[tempIndex]->SetCilck(false);
		}
		
		for (Slot* slot : invSlot)
		{
			if (mousePos.x > slot->GlobalPos().x + 33.0f || mousePos.x < slot->GlobalPos().x - 33.0f &&
				mousePos.y > slot->GlobalPos().y + 33.0f || mousePos.y < slot->GlobalPos().y - 33.0f)
			{
				tempIndex = -1;
			}
		}
	}
}

void Inventory::UIRender()
{
	// 액티브가 꺼진 경우 리턴
	if (!Active()) return;

	// 인벤토리 UI 렌더링
	invFrame->Render();
	for (Slot* slot : invSlot)
	{
		slot->Render();
	}

	int idx = 0;

	// 아이템 수치 렌더링 (포션)
	for (Item* item : inventory)
	{
		if (item != nullptr)
		{
			if (Potion* p = dynamic_cast<Potion*>(item))
			{
				string tempString;
				tempString = to_string(p->GetQuantity());
				Font::Get()->RenderText(tempString, { invSlot[idx]->GlobalPos().x + 15.0f, invSlot[idx]->GlobalPos().y - 5.0f });
			}
		}

		idx++;
	}

}

void Inventory::UpdateInventory()
{
	// 인벤토리 내용을 순회하며 아이콘을 해당 슬롯에 적용시키기
	int idx = 0;

	for (Item* item : inventory)
	{
		if (item == nullptr)
		{
			invSlot[idx]->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
		}
		else
		{
			// 인벤토리 내의 아이템 인덱스에 따른 이미지 추출
			Texture* icon = item->GetIcon()->GetMaterial()->GetDiffuseMap();
			// 인덱스 번째 슬롯에 이미지 적용
			invSlot[idx]->GetMaterial()->SetDiffuseMap(icon);
		}

		idx++;
	}
}

void Inventory::AddItem(Item* item)
{
	// 전달받은 아이템의 타입이 무기 타입이라면?
	if (item->GetType() == ItemType::Weapon)
	{
		// 비어있는 인벤토리 인덱스 찾기
		for (Item*& invItem : inventory)
		{
			if (invItem == nullptr)
			{
				// 인벤토리에 아이템 추가
				invItem = item;
				invItem->SetQuantity(1);

				return;
			}
		}
	}

	// 전달받은 아이템의 타입이 포션인 경우 중복되는 아이템이 있는지 찾기
	for (Item*& invItem : inventory)
	{
		if (invItem == nullptr) continue;

		// 만약 아이템의 태그가 같다면?
		if (invItem->GetTag() == item->GetTag())
		{
			// 수량 증가
			invItem->SetQuantity(invItem->GetQuantity() + 1);
			// 전달받은 아이템 삭제
			SAFE_DEL(item);
			return;
		}
	}

	// 중복된 아이템이 없는 경우 인벤토리의 맨 뒤에 아이템 추가
	// * 아이템 정보 생성
	InventoryItem desc;

	// 비어있는 인벤토리 인덱스 찾기
	for (Item*& invItem : inventory)
	{
		if (invItem == nullptr)
		{
			// 인벤토리에 추가
			invItem = item;
			invItem->SetQuantity(1);

			return;
		}
	}
}

void Inventory::DeleteItem(int itemIndex)
{
	// 아이템이 존재하지 않는 경우 리턴
	if (inventory[itemIndex] == nullptr) return;

	Item* item = inventory[itemIndex];

	// 아이템의 수량 체크
	if (item->GetQuantity() > 1)
	{
		// 1보다 큰 경우에는 수량만 감소 시키기
		item->SetQuantity(item->GetQuantity() - 1);
	}
	else if (item->GetQuantity() == 1)
	{
		// 마지막 남은 아이템인 경우
		// * 퀵슬롯 체크하기
		vector<QuickSlotItem>& quickSlots = player->GetQuickSlot()->GetQuickSlotItems();
		for (int i = 0; i < quickSlots.size(); i++)
		{
			if (quickSlots[i].item == item)
			{
				quickSlots[i].item = nullptr;
			}
		}
		// * 인벤토리 체크하기
		inventory[itemIndex] = nullptr;
		// * 아이템 삭제하기
		SAFE_DEL(item);
	}
}

void Inventory::InitInventory()
{
	// 인벤토리 프레임 설정
	invFrame = new Slot(L"Textures/UI/Inventory.png", SlotType::Inventory_Frame);
	invFrame->Scale() *= 1.75f;
	invFrame->Pos() = { CENTER_X + 320.0f, CENTER_Y - 40.0f, 1.0f };

	// 인벤토리 내용 초기화
	inventory.resize(28);

	// 인벤토리 슬롯 설정
	invSlot.resize(28);
	for (int i = 0; i < invSlot.size(); i++)
	{
		int idxY = i / 7;
		int idxX = i % 7;

		Slot* slot = new Slot(Vector2(33.0f, 33.0f), SlotType::Inventory_Slot);
		slot->GetMaterial()->SetDiffuseMap(L"Textures/Color/Black.png");
		slot->SetParent(invFrame);
		slot->Pos() = { -143.0f + (idxX * 47.5f), 45.0f - (idxY * 42.5f), 2.0f };
		invSlot[i] = slot;
	}

	// 인벤토리 액티브 off
	SetActive(false);
}

void Inventory::MoveInventoryFrame()
{
	// 인벤토리 프레임이 선택되었다면?
	if (invFrame->GetSelect())
	{
		// 슬롯이 선택된 것이 아닌지 체크하기
		for (Slot* slot : invSlot)
		{
			if (slot->GetSelect())
			{
				return;
			}
		}

		// 마우스 이동량의 Delta값 만큼 이동시키기
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
	// 이동중이 아니라고 설정
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

		if (idx >= 28) return;

		// 해당 슬롯에 아이템이 존재하지 않는 경우 리턴
		if (inventory[idx] == nullptr)
		{
			tempIndex = -1;
			// 현재 선택한 버튼 선택 여부 및 활성화 off
			invSlot[idx]->SetSelect(false);
			invSlot[idx]->SetCilck(false);
			return;
		}

		// 해당 슬롯의 인덱스 저장
		tempIndex = idx;
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

		if (idx >= 28) return;

		// 이전 인덱스 슬롯의 클릭 해제
		invSlot[tempIndex]->SetSelect(false);
		invSlot[tempIndex]->SetCilck(false);

		// 해당 인덱스의 위치에 아이템 정보 옮기기
		Item* item = inventory[tempIndex];

		inventory[tempIndex] = inventory[idx];
		inventory[idx] = item;
	}
}
