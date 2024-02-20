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
	Inventory(class CH_Base_ver2* player);
	~Inventory();

	void Update();
	void UIRender();

public:
	// 인벤토리 아이템 갱신용 함수
	void UpdateInventory();
	// 인벤토리 아이템 추가용 함수
	void AddItem(class Item* item);
	// 인벤토리 아이템 제거용 함수
	void DeleteItem(int itemIndex);

// Getter & Setter
public:
	vector<class Item*>& GetInventory() { return inventory; }
	const vector<class Slot*>& GetInvSlots() { return invSlot; }

	int GetTempIndex() { return tempIndex; }
	void SetTempIndex(int value) { tempIndex = value; }

// Event Func
private:
	// 인벤토리 초기화 함수
	void InitInventory();
	// 인벤토리 위치 이동용 함수
	void MoveInventoryFrame();
	// 인벤토리 위치 이동 종료용 함수
	void StopInventoryFrame();
	// 아이템 이동용 함수 (들기)
	void PickItem(void* slot);
	// 아이템 이동용 함수 (내려놓기)
	void DownItem(void* slot);

// Member Variable
private:
	// 정보를 담아줄 인벤토리
	vector<class Item*> inventory;

	// UI
	int MAX_COUNT = 28;		// 인벤토리 칸 수
	class Slot* invFrame;			// 인벤토리 프레임
	vector<class Slot*> invSlot;	// 인벤토리 칸

	// 인벤토리 이동용 변수
	bool bIsMove = false;
	Vector3 prevPos;

	// 클릭시 저장될 객체
	int tempIndex;

	// 플레이어 저장용 변수
	class CH_Base_ver2* player;
};

