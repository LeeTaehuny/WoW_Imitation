#include "Framework.h"
#include "Item.h"

Item::Item(ItemType type, string name) : Model(name), type(type)
{
	// 셰이더 수정(아이템은 최소 밝기 보장)
	SetShader(L"Light/ItemLight.hlsl");
}

Item::~Item()
{
}

void Item::Update()
{
	UpdateWorld();
}

void Item::Render()
{
	Model::Render();
}

void Item::GUIRender()
{
	Model::GUIRender();
}
