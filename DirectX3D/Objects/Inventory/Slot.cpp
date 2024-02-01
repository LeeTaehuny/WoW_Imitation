#include "Framework.h"
#include "Slot.h"


Slot::Slot(wstring textureFile, SlotType type) : Button(textureFile), slotType(type)
{
	SetDownEvent(bind(&Slot::OnClick, this));
	SetOverEvent(bind(&Slot::OnHover, this));
}

Slot::Slot(Vector2 size, SlotType type) : Button(size), slotType(type)
{
	SetDownEvent(bind(&Slot::OnClick, this));
	SetOverEvent(bind(&Slot::OnHover, this));
}

Slot::~Slot()
{
}

void Slot::Update()
{
	Button::Update();
}

void Slot::Render()
{
	Button::Render();
}

void Slot::OnClick()
{
	// 슬롯 타입에 따라 적용
	switch (slotType)
	{
	case SlotType::Inventory_Frame:
		break;
	case SlotType::Inventory_Slot:
		break;
	default:
		break;
	}
}

void Slot::OnHover()
{
	// 슬롯 타입에 따라 적용
	switch (slotType)
	{
	case SlotType::Inventory_Frame:
		break;
	case SlotType::Inventory_Slot:
		break;
	default:
		break;
	}
}
