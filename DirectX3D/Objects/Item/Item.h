#pragma once
#include "Framework/Model/Model.h"

class Item : public Model
{
protected:
	// 아이템 타입 구분을 위한 열거형
	enum class ItemType
	{
		Weapon,	// 무기
		Potion,	// 포션
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

