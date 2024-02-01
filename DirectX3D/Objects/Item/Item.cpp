#include "Framework.h"
#include "Item.h"

Item::Item(ItemType type, string name) : Model(name), type(type)
{
	// ���̴� ����(�������� �ּ� ��� ����)
	SetShader(L"Light/ItemLight.hlsl");
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
	// ������ ��� �׽�Ʈ
	//if (icon)
	//	icon->Render();
	Model::Render();
}

void Item::GUIRender()
{
	Model::GUIRender();
}
