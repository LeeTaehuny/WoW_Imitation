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

	// 무기의 충돌체 정보가 켜져있는 경우
	if (collider->Active())
	{
		// 몬스터와의 충돌 판정 실시
		vector<MonsterBase*> cols1 = MONSTER->GetScarecrow();
		vector<MonsterBase*> cols2 = MONSTER->GetSkeleton();
		vector<MonsterBase*> cols3 = MONSTER->GetSkeleton_Knight();

		for (MonsterBase* monster : cols1)
		{
			if (find(hit.begin(), hit.end(), monster) != hit.end())
			{
				continue;
			}

			if (collider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// TODO : 플레이어 인덱스 정보 추가하기
				monster->Hit(damage + playerDamage);
				hit.push_back(monster);
			}
		}

		for (MonsterBase* monster : cols2)
		{
			if (find(hit.begin(), hit.end(), monster) != hit.end())
			{
				continue;
			}

			if (collider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// TODO : 플레이어 인덱스 정보 추가하기
				monster->Hit(damage + playerDamage);
				hit.push_back(monster);
			}
		}

		for (MonsterBase* monster : cols3)
		{
			if (find(hit.begin(), hit.end(), monster) != hit.end())
			{
				continue;
			}

			if (collider->IsCollision(monster->GetCollider()))
			{
				// 충돌한 몬스터들에게 데미지 주기
				// TODO : 플레이어 인덱스 정보 추가하기
				monster->Hit(damage + playerDamage);
				hit.push_back(monster);
			}
		}
	}
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
	// 충돌체 생성 및 옵션 초기화
	collider = new SphereCollider();
	collider->SetTag("WeaponCollider");
	collider->SetParent(this);
	collider->Scale() *= 0.3f;

	char num = atoi(&name[name.size() - 1]);

	// 무기 타입에 따라 콜라이더 위치 및 데미지 설정 + 아이콘 설정
	switch (weaponType)
	{
	case WeaponType::Sword:
		icon = new Quad(L"Textures/UI/Items/sword_" + to_wstring(num) + L".png");

		collider->Pos() = { 1.0f, 0.0f, 0.0f };
		collider->Scale() *= 1.7f;
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
