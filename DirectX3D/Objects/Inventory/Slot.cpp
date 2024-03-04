﻿#include "Framework.h"
#include "Slot.h"


Slot::Slot(wstring textureFile, SlotType type) : Button(textureFile), slotType(type)
{
	// 이벤트 등록
	SetDownEvent(bind(&Slot::OnClick, this));
	SetOverEvent(bind(&Slot::OnHover, this));
	SetPressEvent(bind(&Slot::OnPress, this));
	SetUpEvent(bind(&Slot::OnRelease, this));
}

Slot::Slot(Vector2 size, SlotType type) : Button(size), slotType(type)
{
	// 이벤트 등록
	SetDownEvent(bind(&Slot::OnClick, this));
	SetOverEvent(bind(&Slot::OnHover, this));
	SetPressEvent(bind(&Slot::OnPress, this));
	SetUpEvent(bind(&Slot::OnRelease, this));
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
	case SlotType::SkillTree_Slot:
		Observer::Get()->ExcuteParamEvent("LearnSkill", this);
		break;
	}
}

void Slot::OnHover()
{
}

void Slot::OnPress()
{
	// 슬롯 타입에 따라 적용
	switch (slotType)
	{
	case SlotType::Inventory_Frame:
		Observer::Get()->ExcuteEvent("MoveInvFrame");
		break;
	case SlotType::Inventory_Slot:
		Observer::Get()->ExcuteParamEvent("PickInvItem", this);
		break;
	}
}

void Slot::OnRelease()
{
	// 슬롯 타입에 따라 적용
	switch (slotType)
	{
	case SlotType::Inventory_Frame:
		Observer::Get()->ExcuteEvent("StopInvFrame");
		break;
	case SlotType::Inventory_Slot:
		Observer::Get()->ExcuteParamEvent("DownInvItem", this);
		break;
	}
}
