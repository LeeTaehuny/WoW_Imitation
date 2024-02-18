#include "Framework.h"
#include "QuickSlot.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Item/Item.h"
#include "Objects/Character_/CH_Base_ver2.h"
#include "Objects/Skills/Base/SkillBase.h"

QuickSlot::QuickSlot(CH_Base_ver2* player) : player(player)
{
	// 슬롯 초기화
	InitSlot();

	// 퀵슬롯 아이템 초기화
	items.resize(9);

	// 마우스 액티브 off
	mouseImg = new Quad(Vector2(55.0f, 55.0f));
	mouseImg->SetActive(false);
}

QuickSlot::~QuickSlot()
{
	SAFE_DEL(quickSlotFrame);
	FOR(9) SAFE_DEL(quickSlots[i]);
}

void QuickSlot::Update()
{
	quickSlotFrame->UpdateWorld();

	Control();
	UpdateQuickSlot();

	for (Slot* slot : quickSlots)
	{
		slot->Update();
	}

	if (mouseImg->Active())
	{
		mouseImg->Pos() = mousePos;
		mouseImg->UpdateWorld();
	}
}

void QuickSlot::RenderUI()
{
	quickSlotFrame->Render();

	for (Slot* slot : quickSlots)
	{
		slot->Render();
	}

	if (mouseImg->Active())
	{
		mouseImg->Render();
	}
}

void QuickSlot::InitSlot()
{
	quickSlotFrame = new Quad(L"Textures/UI/QuickSlot.png");
	quickSlotFrame->Scale() *= 3.0f;
	quickSlotFrame->Pos() = Vector3(CENTER_X, quickSlotFrame->GetSize().y * 0.5f * quickSlotFrame->Scale().y, 0.0f);

	quickSlots.reserve(9);

	for (int i = 0; i < 9; i++)
	{
		Slot* slot = new Slot(Vector2(45.0f, 45.0f), SlotType::Quick_Slot);
		quickSlots.push_back(slot);
	}

	FOR(9)
	{
		if (i <= 3)
		{
			quickSlots[i]->Pos().x = quickSlotFrame->Pos().x - 60 * (i + 1);
			quickSlots[i]->Pos().y = quickSlotFrame->Pos().y;
		}
		else if (i == 4)
		{
			quickSlots[4]->Pos() = quickSlotFrame->Pos();
		}
		else
		{
			quickSlots[i]->Pos().x = quickSlotFrame->Pos().x + 60 * (i - 4);
			quickSlots[i]->Pos().y = quickSlotFrame->Pos().y;
		}
	}
}

void QuickSlot::Control()
{
	// 클릭 이벤트
	if (KEY_DOWN(VK_LBUTTON))
	{
		// 플레이어의 인벤토리가 활성화 되어있다면?
		if (player->GetInventory()->Active())
		{
			vector<Slot*> invSlot = player->GetInventory()->GetInvSlots();

			int idx = 0;

			// 모든 칸을 순회하며 선택한 칸을 찾기
			for (Slot* slot : invSlot)
			{
				if (mousePos.x <= slot->GlobalPos().x + slot->GetSize().x && mousePos.x >= slot->GlobalPos().x - slot->GetSize().x &&
					mousePos.y <= slot->GlobalPos().y + slot->GetSize().y && mousePos.y >= slot->GlobalPos().y - slot->GetSize().y)
				{
					// 아이템이 존재한다면?
					if (player->GetInventory()->GetInventory()[idx] != nullptr)
					{
						// 해당 칸의 아이템 저장
						tmpItem.item = player->GetInventory()->GetInventory()[idx];
						tmpItem.skill = nullptr;

						mouseImg->GetMaterial()->SetDiffuseMap(player->GetInventory()->GetInventory()[idx]->GetIcon()->GetMaterial()->GetDiffuseMap());
						mouseImg->SetActive(true);
					}
				}

				idx++;
			}
		}

		// TODO : 스킬 슬롯 보고 넣기
	}

	// up 이벤트
	if (KEY_UP(VK_LBUTTON))
	{
		// 마우스 이미지 비활성화
		mouseImg->SetActive(false);

		// 임시 퀵슬롯 아이템의 정보가 존재하지 않으면 종료
		if (tmpItem.item == nullptr && tmpItem.skill == nullptr) return;
		//if (tmpItem.item->item == nullptr) return;

		// 퀵슬롯에 들어가지 못하는 종류의 아이템인 경우에도 종료
		if (tmpItem.item != nullptr && tmpItem.item->GetType() == ItemType::Weapon)
		{
			tmpItem.item = nullptr;
			return;
		}

		// 플레이어의 인벤토리가 활성화 되어있다면?
		if (player->GetInventory()->Active())
		{
			int idx = 0;

			// 퀵슬롯을 순회하며 마우스 위치와 비교하기
			for (Slot* slot : quickSlots)
			{
				if (mousePos.x <= slot->GlobalPos().x + slot->GetSize().x && mousePos.x >= slot->GlobalPos().x - slot->GetSize().x &&
					mousePos.y <= slot->GlobalPos().y + slot->GetSize().y && mousePos.y >= slot->GlobalPos().y - slot->GetSize().y)
				{
					// 해당 칸의 퀵슬롯 아이템에 정보 넣기
					items[idx] = tmpItem;

					// 임시 정보들 삭제
					tmpItem.item = nullptr;
					tmpItem.skill = nullptr;
				}

				idx++;
			}
		}

		tmpItem.item = nullptr;
		tmpItem.skill = nullptr;
	}
}

void QuickSlot::UpdateQuickSlot()
{
	int idx = 0;

	for (QuickSlotItem item : items)
	{
		if (item.item != nullptr)
		{
			Texture* icon = item.item->GetIcon()->GetMaterial()->GetDiffuseMap();
			quickSlots[idx]->GetMaterial()->SetDiffuseMap(icon);
		}
		else if (item.skill != nullptr)
		{
			Texture* icon = item.skill->GetIcon()->GetMaterial()->GetDiffuseMap();
			quickSlots[idx]->GetMaterial()->SetDiffuseMap(icon);
		}
		else
		{
			quickSlots[idx]->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
		}

		idx++;
	}
}
