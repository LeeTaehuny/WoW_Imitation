#include "Framework.h"
#include "Potion.h"

Potion::Potion(string name, PotionType type) : Item(ItemType::Potion, name), potionType(type)
{
	SetTag(name);

	// 충돌체 생성 및 옵션 초기화
	collider = new SphereCollider();
	collider->SetTag("PotionCollider");
	collider->SetParent(this);
	collider->Scale() *= 0.3f;
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
