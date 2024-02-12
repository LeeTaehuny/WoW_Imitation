#pragma once
#include "Objects/Item/Item.h"

// 무기의 타입을 구분하기 위한 열거형
enum class WeaponType
{
	Sword,	// 검
	Bow,	// 활
	Hammer,	// 망치
	Staff,	// 지팡이
	Shield,	// 방패
	Arrow,	// 화살
};

class Weapon : public Item
{
public:
	Weapon(string name, WeaponType type);
	~Weapon();

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;
	virtual void Use() override;

// Getter
public:
	SphereCollider* GetCollider() { return collider; }
	WeaponType GetWeaponType() { return weaponType; }
	int GetWeaponDamage() { return damage; }
	void SetDamage(int damage) { this->playerDamage = damage; }
	void SetOwner(CH_Base_ver2* owner) { this->owner = owner; }

	void ClearHit() { hit.clear(); }

private:
	// 무기의 타입에 따라 초기화를 위한 함수
	void InitWeapon(string name);

private:
	CH_Base_ver2* owner;
	// 무기의 데미지를 저장하기 위한 변수
	int damage;
	// 플레이어의 공격력을 저장하기 위한 임시 변수
	int playerDamage;

	SphereCollider* collider;
	WeaponType weaponType;

	vector<MonsterBase*> hit;
};

