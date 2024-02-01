#include "Framework.h"
#include "Potion.h"

Potion::Potion(string name, PotionType type) : Item(ItemType::Potion, name), potionType(type)
{
	SetTag(name);

	// �浹ü ���� �� �ɼ� �ʱ�ȭ
	collider = new SphereCollider();
	collider->SetTag("PotionCollider");
	collider->SetParent(this);
	collider->Scale() *= 0.3f;

	// ���� Ÿ�Կ� ���� ������ �� ȸ���� ����
	if (potionType == PotionType::Hp)
	{
		icon = new Quad(L"Textures/UI/Items/hp_potion.png");
		amount = 1000;
	}
	else
	{
		icon = new Quad(L"Textures/UI/Items/mp_potion.png");
		amount = 500;
	}
}

Potion::~Potion()
{
	delete collider;
}

void Potion::Update()
{
	Item::Update();
	collider->UpdateWorld();
}

void Potion::Render()
{
	Item::Render();
	collider->Render();
}

void Potion::GUIRender()
{
	Item::GUIRender();
	collider->GUIRender();
}

void Potion::Use()
{
}
