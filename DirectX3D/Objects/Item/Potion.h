#pragma once
#include "Objects/Item/Item.h"

// ������ Ÿ���� �����ϱ� ���� ������
enum class PotionType
{
	Hp,	// HP ����
	Mp,	// MP ����
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
	// ������ ȸ������ �����ϱ� ���� ����
	int amount;

	SphereCollider* collider;
	PotionType potionType;
};

