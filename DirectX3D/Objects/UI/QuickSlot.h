#pragma once
#include "Objects/Inventory/Inventory.h"


struct QuickSlotItem
{
	class SkillBase* skill;
	class Item* item;
};

class QuickSlot
{
public:
	QuickSlot(class CH_Base_ver2* player);
	~QuickSlot();

	void Update();
	void RenderUI();

private:
	// 퀵슬롯 초기화용 함수
	void InitSlot();
	// 조작용 함수
	void Control();

	// 퀵슬롯 업데이트 함수
	void UpdateQuickSlot();

private:
	// 플레이어 정보를 저장하기 위한 변수
	class CH_Base_ver2* player;

	// UI
	Quad* quickSlotFrame;
	vector<class Slot*> quickSlots;

	// 클릭시 마우스에서 스폰될 이미지
	Quad* mouseImg;

	// 임시 퀵슬롯 아이템 정보
	QuickSlotItem tmpItem;

	// 들어있는 실제 아이템 정보
	vector<QuickSlotItem> items;

};

