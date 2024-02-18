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
	// ������ �ʱ�ȭ�� �Լ�
	void InitSlot();
	// ���ۿ� �Լ�
	void Control();

	// ������ ������Ʈ �Լ�
	void UpdateQuickSlot();

private:
	// �÷��̾� ������ �����ϱ� ���� ����
	class CH_Base_ver2* player;

	// UI
	Quad* quickSlotFrame;
	vector<class Slot*> quickSlots;

	// Ŭ���� ���콺���� ������ �̹���
	Quad* mouseImg;

	// �ӽ� ������ ������ ����
	QuickSlotItem tmpItem;

	// ����ִ� ���� ������ ����
	vector<QuickSlotItem> items;

};

