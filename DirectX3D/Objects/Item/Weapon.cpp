#include "Framework.h"
#include "Weapon.h"

Weapon::Weapon(string name, WeaponType type) : Item(ItemType::Weapon, name), weaponType(type)
{
	SetTag(name);

	InitWeapon(name);
}

Weapon::~Weapon()
{
	delete collider;
}

void Weapon::Update()
{
	Item::Update();
	collider->UpdateWorld();
}

void Weapon::Render()
{
	Item::Render();
	collider->Render();
}

void Weapon::GUIRender()
{
	Item::GUIRender();
	collider->GUIRender();
}

void Weapon::Use()
{
}

void Weapon::InitWeapon(string name)
{
	// �浹ü ���� �� �ɼ� �ʱ�ȭ
	collider = new SphereCollider();
	collider->SetTag("WeaponCollider");
	collider->SetParent(this);
	collider->Scale() *= 0.3f;

	char num = atoi(&name[name.size() - 1]);

	// ���� Ÿ�Կ� ���� �ݶ��̴� ��ġ �� ������ ���� + ������ ����
	switch (weaponType)
	{
	case WeaponType::Sword:
		icon = new Quad(L"Textures/UI/Items/sword_" + to_wstring(num) + L".png");

		collider->Pos() = { 1.0f, 0.0f, 0.0f };
		damage = 1000;
		break;
	case WeaponType::Bow:
		icon = new Quad(L"Textures/UI/Items/bow_" + to_wstring(num) + L".png");

		collider->Pos() = { 0.0f, 0.0f, 0.0f };
		damage = 1000;
		break;
	case WeaponType::Hammer:
		icon = new Quad(L"Textures/UI/Items/hammer_" + to_wstring(num) + L".png");

		collider->Pos() = { 0.5f, 0.0f, 0.0f };
		damage = 1000;
		break;
	case WeaponType::Staff:
		icon = new Quad(L"Textures/UI/Items/staff_" + to_wstring(num) + L".png");
		collider->Pos() = { 0.8f, 0.0f, 0.0f };
		damage = 1000;
		break;
	case WeaponType::Shield:
		collider->Pos() = { 0.0f, 0.0f, 0.0f };
		damage = 0;
		break;
	case WeaponType::Arrow:
		collider->Pos() = { 1.1f, 0.0f, 0.0f };
		damage = 0;
		break;
	}

	collider->SetActive(false);
}
