#include "Framework.h"
#include "QuickSlot.h"
#include "Objects/Inventory/Slot.h"
#include "Objects/Item/Item.h"
#include "Objects/Character_/CH_Base_ver2.h"
#include "Objects/Skills/Base/SkillBase.h"

QuickSlot::QuickSlot(CH_Base_ver2* player) : player(player)
{
	// ���� �ʱ�ȭ
	InitSlot();

	// ������ ������ �ʱ�ȭ
	items.resize(9);

	// ���콺 ��Ƽ�� off
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
	// Ŭ�� �̺�Ʈ
	if (KEY_DOWN(VK_LBUTTON))
	{
		// �÷��̾��� �κ��丮�� Ȱ��ȭ �Ǿ��ִٸ�?
		if (player->GetInventory()->Active())
		{
			vector<Slot*> invSlot = player->GetInventory()->GetInvSlots();

			int idx = 0;

			// ��� ĭ�� ��ȸ�ϸ� ������ ĭ�� ã��
			for (Slot* slot : invSlot)
			{
				if (mousePos.x <= slot->GlobalPos().x + slot->GetSize().x && mousePos.x >= slot->GlobalPos().x - slot->GetSize().x &&
					mousePos.y <= slot->GlobalPos().y + slot->GetSize().y && mousePos.y >= slot->GlobalPos().y - slot->GetSize().y)
				{
					// �������� �����Ѵٸ�?
					if (player->GetInventory()->GetInventory()[idx] != nullptr)
					{
						// �ش� ĭ�� ������ ����
						tmpItem.item = player->GetInventory()->GetInventory()[idx];
						tmpItem.skill = nullptr;

						mouseImg->GetMaterial()->SetDiffuseMap(player->GetInventory()->GetInventory()[idx]->GetIcon()->GetMaterial()->GetDiffuseMap());
						mouseImg->SetActive(true);
					}
				}

				idx++;
			}
		}

		// TODO : ��ų ���� ���� �ֱ�
	}

	// up �̺�Ʈ
	if (KEY_UP(VK_LBUTTON))
	{
		// ���콺 �̹��� ��Ȱ��ȭ
		mouseImg->SetActive(false);

		// �ӽ� ������ �������� ������ �������� ������ ����
		if (tmpItem.item == nullptr && tmpItem.skill == nullptr) return;
		//if (tmpItem.item->item == nullptr) return;

		// �����Կ� ���� ���ϴ� ������ �������� ��쿡�� ����
		if (tmpItem.item != nullptr && tmpItem.item->GetType() == ItemType::Weapon)
		{
			tmpItem.item = nullptr;
			return;
		}

		// �÷��̾��� �κ��丮�� Ȱ��ȭ �Ǿ��ִٸ�?
		if (player->GetInventory()->Active())
		{
			int idx = 0;

			// �������� ��ȸ�ϸ� ���콺 ��ġ�� ���ϱ�
			for (Slot* slot : quickSlots)
			{
				if (mousePos.x <= slot->GlobalPos().x + slot->GetSize().x && mousePos.x >= slot->GlobalPos().x - slot->GetSize().x &&
					mousePos.y <= slot->GlobalPos().y + slot->GetSize().y && mousePos.y >= slot->GlobalPos().y - slot->GetSize().y)
				{
					// �ش� ĭ�� ������ �����ۿ� ���� �ֱ�
					items[idx] = tmpItem;

					// �ӽ� ������ ����
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
