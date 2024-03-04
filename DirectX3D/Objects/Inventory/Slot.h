#pragma once
#include "Objects/UI/Button.h"

// 슬롯의 타입을 구분하기 위한 열거형
enum class SlotType
{
	Inventory_Frame,
	Inventory_Slot,
	Shop_Frame,
	Status_Frame,
	Status_Slot,
	SkillTree_Frame,
	SkillTree_Slot,
	Quick_Slot,
};

class Slot : public Button
{
public:
	Slot(wstring textureFile, SlotType type);
	Slot(Vector2 size, SlotType type);
	~Slot();

	virtual void Update() override;
	virtual void Render() override;

// Event Func
private:
	void OnClick();
	void OnHover();
	void OnPress();
	void OnRelease();

private:
	SlotType slotType;
};

