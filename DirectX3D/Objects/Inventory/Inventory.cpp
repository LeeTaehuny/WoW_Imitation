#include "Framework.h"
#include "Inventory.h"
#include "Objects/Item/Item.h"
#include "Objects/Inventory/Slot.h"

Inventory::Inventory()
{
	// �κ��丮 ������ ����
	invFrame = new Slot(L"Textures/UI/Inventory.png", SlotType::Inventory_Frame);
	invFrame->Scale() *= 1.75f;
	invFrame->Pos() = { CENTER_X, CENTER_Y };

	// �κ��丮 ���� ����
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

	// �κ��丮 ��Ƽ�� off
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
	// �׽�Ʈ �ڵ�. ���߿��� �÷��̾�� iŰ�� ������ ��.
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

	// �κ��丮 ������Ʈ
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

	// ���� �� ������ ������Ʈ
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
	// �κ��丮 ������ ��ȸ�ϸ� �������� �ش� ���Կ� �����Ű��
	for (InventoryItem inv : inventory)
	{
		// �κ��丮 ���� ������ �ε����� ���� �̹��� ����
		Texture* icon = inv.item->GetIcon()->GetMaterial()->GetDiffuseMap();
		// �ε��� ��° ���Կ� �̹��� ����
		invSlot[inv.index]->GetMaterial()->SetDiffuseMap(icon);
	}
}

void Inventory::AddItem(Item* item)
{
	// ���޹��� �������� Ÿ���� ���� Ÿ���̶��?
	if (item->GetType() == ItemType::Weapon)
	{
		// ������ ���� ����
		InventoryItem desc;

		desc.index = inventory.size();
		desc.item = item;
		desc.quantity = 1;

		// �κ��丮�� �� �ڿ� ������ �߰�
		inventory.push_back(desc);

		return;
	}

	// ���޹��� �������� Ÿ���� ������ ��� �ߺ��Ǵ� �������� �ִ��� ã��
	for (InventoryItem inv : inventory)
	{
		// ���� �������� �±װ� ���ٸ�?
		if (inv.item->GetTag() == item->GetTag())
		{
			// ���� ����
			inv.quantity++;
			return;
		}
	}

	// �ߺ��� �������� ���� ��� �κ��丮�� �� �ڿ� ������ �߰�
	// * ������ ���� ����
	InventoryItem desc;

	desc.index = inventory.size();
	desc.item = item;
	desc.quantity = 1;

	// * �κ��丮�� �߰�
	inventory.push_back(desc);
}

void Inventory::DeleteItem(Item* item)
{
	// ������ �ϴ� ���߿� ��Ȳ���� �ۼ�

	// ���޹��� �������� Ÿ���� ���� Ÿ���̶��?
	//if (item->GetType() == ItemType::Weapon)
	//{
	//	// ��ȸ
	//	for (InventoryItem inv : inventory)
	//	{
	//		// ���� �������� �±װ� ���ٸ�?
	//		if (item->GetTag() == inv.item->GetTag())
	//		{
	//			// �ش� ������ �̹��� �ʱ�ȭ
	//			invSlot[inv.index]->GetMaterial()->SetDiffuseMap(L"Textures/Color/White.png");
	//
	//			// ������ ����
	//			SAFE_DEL(inv.item);
	//			return;
	//		}
	//	}
	//}
	
}
