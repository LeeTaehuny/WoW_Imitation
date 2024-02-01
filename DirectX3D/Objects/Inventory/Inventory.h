#pragma once

// �κ��丮�� ������ �� ������ ����ü
struct InventoryItem
{
	int index;			// ������ �ε���
	class Item* item;	// ������
	int quantity;		// ����
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
	// ������ ����� �κ��丮
	vector<InventoryItem> inventory;

	// UI
	int MAX_COUNT = 28;		// �κ��丮 ĭ ��
	class Slot* invFrame;			// �κ��丮 ������
	vector<class Slot*> invSlot;	// �κ��丮 ĭ

	// �κ��丮 �̵��� ����
	bool bIsMove = false;
	Vector3 prevPos;
};

