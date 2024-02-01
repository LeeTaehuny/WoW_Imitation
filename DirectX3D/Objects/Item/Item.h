#pragma once
#include "Framework/Model/Model.h"

// ������ Ÿ�� ������ ���� ������
enum class ItemType
{
	Weapon,	// ����
	Potion,	// ����
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

