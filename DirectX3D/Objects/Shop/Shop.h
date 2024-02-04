#pragma once
#include "Objects/Item/Weapon.h"
#include "Objects/Item/Potion.h"

class Shop : public Transform
{
public:
	Shop();
	~Shop();

	void Update();
	void Render();
	void UIRender();
	void GUIRender();

public:
	// 상점 아이템 추가용 함수
	void AddItem(class Item* item);
	// 아이템 구매용 함수
	void PurchaseItem(string itemName, class Inventory* inventory);
	// 아이템 판매용 함수
	void SellItem(int itemIndex, class Inventory* inventory);

// Getter
public:
	const vector<class Slot*>& GetItemSlots() { return itemSlots; }
	string GetItemName(int index);

private:
	// 상점 아이템 갱신용 함수
	void UpdataItems();
	// 아이템 생성용 함수 2종(무기, 포션)
	class Item* CreateWeapon(string name, WeaponType type);
	class Item* CreatePotion(string name, PotionType type);

// Models
private:
	Model* shop;
	Model* trader;

	RasterizerState* rs[2];

// Member Variable
private:
	vector<class Item*> items;

// UI
private:
	int MAX_COUNT = 28;				// 판매 칸 수
	class Slot* shopFrame;			// 상점 프레임
	vector<class Slot*> itemSlots;		// 상점 아이템 슬롯
};

