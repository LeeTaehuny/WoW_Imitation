#pragma once
#include "Framework/Model/Model.h"

// 아이템 타입 구분을 위한 열거형
enum class ItemType
{
	Weapon,	// 무기
	Potion,	// 포션
};

class Item : public Model
{
public:
	Item(ItemType type, string name);
	~Item();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();
	virtual void Use() = 0;

// Getter
public:
	ItemType GetType() { return type; }
	Quad* GetIcon() { return icon; }

protected:
	Quad* icon;

	ItemType type;
};

