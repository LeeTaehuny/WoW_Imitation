#pragma once
#include "Framework/Model/Model.h"

class Item : public Model
{
protected:
	// ������ Ÿ�� ������ ���� ������
	enum class ItemType
	{
		Weapon,	// ����
		Potion,	// ����
	};

public:
	Item(ItemType type, string name);
	~Item();

	virtual void Update();
	virtual void Render();
	virtual void GUIRender();

protected:
	ItemType type;
};

