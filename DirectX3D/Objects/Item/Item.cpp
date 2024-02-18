#include "Framework.h"
#include "Item.h"

Item::Item(ItemType type, string name) : Model(name), type(type), itemName(name)
{
	// 셰이더 수정(아이템은 최소 밝기 보장)
	SetShader(L"Light/ItemLight.hlsl");

	// 수량 0
	quantity = 0;
}

Item::~Item()
{
	if (icon)
	{
		delete icon;
		icon = nullptr;
	}
}

void Item::Update()
{
	UpdateWorld();
}

void Item::Render()
{
	// 아이콘 출력 테스트
	//if (icon)
	//	icon->Render();
	Model::Render();
}

void Item::GUIRender()
{
	Model::GUIRender();
}
