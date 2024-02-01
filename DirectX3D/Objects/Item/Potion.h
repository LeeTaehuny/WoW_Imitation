#pragma once
#include "Objects/Item/Item.h"

// 포션의 타입을 구분하기 위한 열거형
enum class PotionType
{
	Hp,	// HP 포션
	Mp,	// MP 포션
};

class Potion : public Item
{
public:
	Potion(string name, PotionType type);
	~Potion();

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;
	virtual void Use() override;

public:

private:
	// 포션의 회복량을 저장하기 위한 변수
	int amount;

	SphereCollider* collider;
	PotionType potionType;
};

