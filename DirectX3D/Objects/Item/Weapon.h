#pragma once
#include "Objects/Item/Item.h"

// ������ Ÿ���� �����ϱ� ���� ������
enum class WeaponType
{
	Sword,	// ��
	Bow,	// Ȱ
	Hammer,	// ��ġ
	Staff,	// ������
	Shield,	// ����
	Arrow,	// ȭ��
};

class Weapon : public Item
{
public:
	Weapon(string name, WeaponType type);
	~Weapon();

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;

// Getter
public:
	SphereCollider* GetCollider() { return collider; }
	WeaponType GetWeaponType() { return weaponType; }
	int GetDamage() { return damage; }

private:
	// ������ Ÿ�Կ� ���� �ʱ�ȭ�� ���� �Լ�
	void InitWeapon();

private:
	// ������ �������� �����ϱ� ���� ����
	int damage;

	SphereCollider* collider;
	WeaponType weaponType;
};

