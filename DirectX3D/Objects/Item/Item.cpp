#include "Framework.h"
#include "Item.h"

Item::Item(ItemType type, string name) : Model(name), type(type)
{
	// ���̴� ����(�������� �ּ� ��� ����)
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
