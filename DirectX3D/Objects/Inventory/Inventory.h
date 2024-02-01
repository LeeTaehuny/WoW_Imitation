#pragma once

// 인벤토리에 실제로 들어갈 아이템 구조체
struct InventoryItem
{
	int index;			// 아이템 인덱스
	class Item* item;	// 아이템
	int quantity;		// 수량
};

class Inventory : public Transform
{
public:
	Inventory();
	~Inventory();

	void Update();
	void UIRender();

public:
	void UpdateInventory();
	void AddItem(class Item* item);
	void DeleteItem(class Item* item);

private:
	// 정보를 담아줄 인벤토리
	vector<InventoryItem> inventory;

	// UI
	int MAX_COUNT = 28;		// 인벤토리 칸 수
	class Slot* invFrame;			// 인벤토리 프레임
	vector<class Slot*> invSlot;	// 인벤토리 칸

	// 인벤토리 이동용 변수
	bool bIsMove = false;
	Vector3 prevPos;
};

