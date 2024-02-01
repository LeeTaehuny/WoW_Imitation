#pragma once
#include "Objects/UI/Button.h"

// ������ Ÿ���� �����ϱ� ���� ������
enum class SlotType
{
	Inventory_Frame,
	Inventory_Slot,
};

class Slot : public Button
{
public:
	Slot(wstring textureFile, SlotType type);
	Slot(Vector2 size, SlotType type);
	~Slot();

	virtual void Update() override;
	virtual void Render() override;

private:
	void OnClick();
	void OnHover();

private:
	SlotType slotType;
};

